#pragma once
#include "lexer.hpp"
#include "symbol_map.hpp"

namespace app::gpuc {

    struct parser : symbol_map {
        const_sequence<lexeme> lexemes {};
        node_ptr               root    {};

        parser(const char* source)
        :parser(lexer(source)) {}

        parser(lexer&& x)
        :symbol_map(std::move(x))
        ,lexemes(std::move(x.lexemes))
        ,root(semantic::TRANSLATION_UNIT) { parse(); }

    private:
        using itr_t  = const lexeme*;
        using end_t  = const lexeme* const;
        using rule_t = node_ptr(parser::*)(itr_t&,end_t);

        void parse() {
            itr_t itr = lexemes.data();
            end_t end = itr + lexemes.size();
            symbol_scope module_scope(this);
            while (root << top_level_declaration(itr,end));
        }

    private: // diagnostics

        template<typename... Args>
        auto error(const lexeme* lexeme, Args&&... args) {
            diagnostics::error(*lexeme,args...);
            return nullptr;
        }

        template<typename... Args>
        auto error_after(const lexeme* lexeme, Args&&... args) {
            substring location(lexeme->begin()+lexeme->size(),1);
            diagnostics::error(location,args...);
            return nullptr;
        }

        template<typename... Args>
        auto error_before(const lexeme* lexeme, Args&&... args) {
            if (lexeme > lexemes.data()) {
                lexeme -= 1;
                error_after(lexeme-1,args...);
                return nullptr;
            }
            diagnostics::error(*lexeme,args...);
            return nullptr;
        }

        auto find_type_or_report_error(const lexeme* type_name) {
            auto type = find_type(type_name);
            if (not type)
                error(type_name,"unknown type name '",*type_name,"'");
            return type;
        }

    private: // scope state

        const node* structure_variable_type = nullptr;

        struct structure_variable_type_scope {
            parser* const parser;
            const node* const old_structure_variable_type;

            structure_variable_type_scope(
                struct parser* p,
                const node* new_structure_variable_type)
            :parser(p)
            ,old_structure_variable_type(p->structure_variable_type) {
                parser->structure_variable_type = new_structure_variable_type;
            }

            ~structure_variable_type_scope() {
                parser->structure_variable_type = old_structure_variable_type;
            }
        };

    private: // grammar

        #define app_gpuc_parser_rule(app_gpuc_parser_rule)\
            node_ptr app_gpuc_parser_rule(itr_t& itr, end_t end) {\
                auto ptr = itr;\
                if (node_ptr result = app_gpuc_parser_rule<void>(ptr,end)) {\
                    itr = ptr; return result;\
                } return nullptr;\
            }\
            template<typename>\
            node_ptr app_gpuc_parser_rule(itr_t& itr, end_t end)

        app_gpuc_parser_rule(top_level_declaration) {
            if (auto x = struct_definition(itr,end)) return x;
            if (auto x = function(itr,end))          return x;
            return nullptr;
        }

        // structures ----------------------------------------------------------

        app_gpuc_parser_rule(struct_definition) {
            if (not read(itr,end,STRUCT))
                return nullptr;

            auto name = read(itr,end,IDENTIFIER);
            if (not name)
                return error(itr,"expected struct name");

            if (not read(itr,end,LBRACE))
                return error(itr,"expected '{'");

            node_ptr structure(STRUCT_DEFINITION,name,recursively_typed());
            while (structure << struct_field_definition(itr,end));

            if (not read(itr,end,RBRACE))
                error_before(itr,"expected '}'");

            if (not read(itr,end,SEMICOLON))
                error_before(itr,"expected ';'");

            while(read(itr,end,SEMICOLON));

            define_type(structure);
            return structure;
        }

        app_gpuc_parser_rule(struct_field_definition) {
            if (peek(itr,end,RBRACE))
                return nullptr;

            auto type_name = read(itr,end,is_identifier_or_typename);
            if (not type_name) {
                error(itr,"expected type name");
                if (seek(itr,end,SEMICOLON,RBRACE))
                    read(itr,end,SEMICOLON);
                return node_ptr(STRUCT_FIELD_DEFINITION);
            }

            auto type = find_type_or_report_error(type_name);
            auto name = read(itr,end,IDENTIFIER);
            if (not name) {
                error_before(itr,"expected member name");
                if (seek(itr,end,SEMICOLON,RBRACE))
                    read(itr,end,SEMICOLON);
                return node_ptr(STRUCT_FIELD_DEFINITION);
            }

            if (not read(itr,end,SEMICOLON))
                error(itr,"expected ';'");

            while(read(itr,end,SEMICOLON));

            return node_ptr(STRUCT_FIELD_DEFINITION,name,type);
        }

        // uniforms and variables ----------------------------------------------

        app_gpuc_parser_rule(uniform_definition) {
            if (not read(itr,end,UNIFORM))
                return nullptr;

            auto type_name = read(itr,end,is_identifier_or_typename);
            if (not type_name) {
                error(itr,"expected type name");
                if (seek(itr,end,SEMICOLON,RBRACE))
                    read(itr,end,SEMICOLON);
                return node_ptr(UNIFORM_DEFINITION);
            }

            auto type = find_type_or_report_error(type_name);
            auto name = read(itr,end,IDENTIFIER);
            if (not name) {
                error_before(itr,"expected uniform name");
                if (seek(itr,end,SEMICOLON,RBRACE))
                    read(itr,end,SEMICOLON);
                return node_ptr(UNIFORM_DEFINITION);
            }

            auto uniform = node_ptr(UNIFORM_DEFINITION,name,type);
            define_variable(uniform);
            return uniform;
        }

        app_gpuc_parser_rule(variable_definition) {
            auto type_name = read(itr,end,is_identifier_or_typename);
            if (not type_name)
                return nullptr;

            auto name = read(itr,end,IDENTIFIER);
            if (not name)
                return nullptr;

            auto type = find_type_or_report_error(type_name);
            auto variable = node_ptr(VARIABLE_DEFINITION,name,type);
            define_variable(variable);
            return variable;
        }

        // functions -----------------------------------------------------------

        app_gpuc_parser_rule(function) {
            auto type_name = read(itr,end,is_identifier_or_typename);
            if (not type_name)
                return nullptr;

            auto name = read(itr,end,IDENTIFIER);
            if (not name)
                return nullptr;

            auto lparen = read(itr,end,LPAREN);
            if (not lparen)
                return nullptr;

            auto type = find_type_or_report_error(type_name);
            node_ptr params(FUNCTION_PARAMETER_LIST,lparen);
            node_ptr body;
            {
                symbol_scope function_scope(this);
                while (params << function_parameter(itr,end)) {
                    if (read(itr,end,COMMA)) continue;
                    if (read(itr,end,RPAREN)) break;
                    error(itr,"expected ',' or ')'");
                    break;
                }
                body = compound_statement_in_existing_scope(itr,end);
            }
            if (body) {
                node_ptr function(FUNCTION_DEFINITION,name,type);
                function << params;
                function << body;
                define_function(function);
                return function;
            }

            if (not read(itr,end,SEMICOLON))
                error(itr,"expected ';' or '{'");

            node_ptr function(FUNCTION_DECLARATION,name,type);
            function << params;
            declare_function(function);
            return function;
        }

        app_gpuc_parser_rule(function_parameter) {
            if (peek(itr,end,RPAREN))
                return nullptr;

            if (auto x = uniform_definition(itr,end))  return x;
            if (auto x = variable_definition(itr,end)) return x;

            error(itr,"expected parameter");
            seek(itr,end,COMMA,LPAREN);
            return nullptr;
        }

        // statements ----------------------------------------------------------

        app_gpuc_parser_rule(statement) {
            if (auto x = empty_statement(itr,end)) return x;
            // if (auto x = if_statement(itr,end))         return x;
            // if (auto x = switch_statement(itr,end))     return x;
            // if (auto x = while_statement(itr,end))      return x;
            // if (auto x = do_statement(itr,end))         return x;
            // if (auto x = for_statement(itr,end))        return x;
            // if (auto x = goto_statement(itr,end))       return x;
            // if (auto x = continue_statement(itr,end))   return x;
            // if (auto x = break_statement(itr,end))      return x;
            if (auto x =     return_statement(itr,end)) return x;
            if (auto x =   compound_statement(itr,end)) return x;
            if (auto x =   variable_statement(itr,end)) return x;
            if (auto x = expression_statement(itr,end)) return x;
            return invalid_statement(itr,end);
        }

        app_gpuc_parser_rule(empty_statement) {
            if (peek(itr,end,SEMICOLON))
                return node_ptr(EMPTY_STATEMENT);
            return nullptr;
        }

        app_gpuc_parser_rule(if_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(switch_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(while_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(do_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(for_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(goto_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(continue_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(break_statement) {
            return error(itr,"TODO");
        }

        app_gpuc_parser_rule(return_statement) {
            auto key = read(itr,end,RETURN);
            if (not key)
                return nullptr;

            auto expr = expression(itr,end);
            if (not read(itr,end,SEMICOLON))
                return error(itr,"expected ';'");

            auto type = expr ? expr->type : find_type(VOID);
            node_ptr ret(RETURN_STATEMENT,key,type);
            ret << expr;
            return ret;
        }

        app_gpuc_parser_rule(compound_statement) {
            symbol_scope block_scope(this);
            return compound_statement_in_existing_scope(itr,end);
        }

        app_gpuc_parser_rule(compound_statement_in_existing_scope) {
            auto lbrace = read(itr,end,LBRACE);
            if (not lbrace)
                return nullptr;

            node_ptr block(COMPOUND_STATEMENT,lbrace);
            while (not peek(itr,end,RBRACE) and block << statement(itr,end));

            if (not read(itr,end,RBRACE))
                error(itr,"expected '}'");

            return block;
        }

        app_gpuc_parser_rule(invalid_statement) {
            error(itr,"invalid statement");
            node_ptr stmt(INVALID_STATEMENT,itr);
            seek(itr,end,SEMICOLON,RBRACE,END);
            read(itr,end,SEMICOLON);
            return stmt;
        }

        app_gpuc_parser_rule(expression_statement) {
            auto expr = expression(itr,end);
            if (not expr) return nullptr;
            if (not read(itr,end,SEMICOLON))
                error(itr,"expected ';'");

            node_ptr stmt(EXPRESSION_STATEMENT);
            stmt << expr;
            return stmt;
        }

        app_gpuc_parser_rule(variable_statement) {
            auto expr = variable_expression(itr,end);
            if (not expr) return nullptr;
            if (not read(itr,end,SEMICOLON))
                error(itr,"expected ';'");

            node_ptr stmt(EXPRESSION_STATEMENT);
            stmt << expr;
            return stmt;
        }

        // expressions ---------------------------------------------------------

        app_gpuc_parser_rule(expression) {
            if (auto x = assignment_expression(itr,end)) return x;
            if (auto x =    ternary_expression(itr,end)) return x;
            return nullptr;
        }

        app_gpuc_parser_rule(variable_expression) {
            auto lhs = variable_definition(itr,end);
            if (not lhs) return nullptr;

            auto op = read(itr,end,EQ);
            if (not op) return lhs;

            auto rhs = expression(itr,end);
            if (not rhs) {
                error_before(itr,"expected expression");
                seek(itr,end,SEMICOLON);
            }

            node_ptr assign(ASSIGNMENT_EXPRESSION,op,lhs->type);
            assign << lhs;
            assign << rhs;
            return assign;
        }

        app_gpuc_parser_rule(assignment_expression) {
            auto lhs = prefix_expression(itr,end);
            if (not lhs) return nullptr;

            auto op = read(itr,end,is_assignment_operator);
            if (not op) return nullptr;

            auto rhs = expression(itr,end);
            if (not rhs) {
                error_before(itr,"expected expression");
                seek(itr,end,SEMICOLON);
            }

            node_ptr expr(ASSIGNMENT_EXPRESSION,op,lhs->type);
            expr << lhs;
            expr << rhs;
            return expr;
        }

        static bool is_assignable(const node* node) {
            app_assert(node);
            switch (node->semantic) {
                case PREFIX_EXPRESSION:
                case MEMBER_REFERENCE:
                case SYMBOL_REFERENCE:
                case VARIABLE_REFERENCE:
                    return true;
                case NESTED_EXPRESSION:
                    return is_assignable(node->child(0));
                default:
                    return false;
            }
        }

        app_gpuc_parser_rule(prefix_expression) {
            auto op = read(itr,end,is_prefix_operator);
            if (not op)
                return member_expression(itr,end);

            auto rhs = prefix_expression(itr,end);
            if (not rhs) {
                error_before(itr,"expected expression");
                seek(itr,end,SEMICOLON);
            }

            if (not is_assignable(rhs)) {
                error_before(itr,"expression is not assignable");
            }

            node_ptr expr(PREFIX_EXPRESSION,op);
            expr << rhs;
            return expr;
        }

        app_gpuc_parser_rule(member_reference) {
            auto member_name = read(itr,end,is_identifier_or_typename);
            if (not member_name)
                return nullptr;
            
            if (not structure_variable_type) {
                return node_ptr(MEMBER_REFERENCE,member_name);
            }

            auto member = find_member(structure_variable_type,member_name);
            if (not member) {
                const auto& structure_name = *structure_variable_type->lexeme;
                error(member_name,
                    "no member named '",*member_name,"' ",
                    "in '",structure_name,"'");
                return node_ptr(MEMBER_REFERENCE,member_name);
            }

            return node_ptr(MEMBER_REFERENCE,member_name,member->type);
        }

        app_gpuc_parser_rule(member_expression) {
            auto lhs = subscript_expression(itr,end);
            if (not lhs)
                return nullptr;

            auto op = read(itr,end,DOT);
            if (not op)
                if ((op = read(itr,end,ARROW)))
                    error(op,"expected '.'");

            if (not op)
                return lhs;

            structure_variable_type_scope member_scope(this,lhs->type);
            auto rhs = member_submember_expression(itr,end);
            if (not rhs)
                error(itr,"expected member name");

            auto expr = node_ptr(MEMBER_EXPRESSION,op,rhs->type);
            expr << lhs;
            expr << rhs;
            return expr;
        }

        app_gpuc_parser_rule(member_submember_expression) {
            auto lhs = member_subscript_expression(itr,end);
            if (not lhs)
                return nullptr;

            auto op = read(itr,end,DOT);
            if (not op)
                if ((op = read(itr,end,ARROW)))
                    error(op,"expected '.'");

            if (not op)
                return lhs;

            structure_variable_type_scope member_scope(this,lhs->type);
            auto rhs = member_submember_expression(itr,end);
            if (not rhs)
                error(itr,"expected member name");

            auto expr = node_ptr(MEMBER_EXPRESSION,op,rhs->type);
            expr << lhs;
            expr << rhs;
            return expr;
        }

        app_gpuc_parser_rule(member_subscript_expression) {
            auto lhs = member_postfix_expression(itr,end);
            if (not lhs)
                return nullptr;

            auto op = read(itr,end,LBRACK);
            if (not op)
                return lhs;

            structure_variable_type_scope(this,nullptr);
            auto rhs = expression(itr,end);
            if (not rhs) error(itr,"expected expression");
            if (not read(itr,end,RBRACK)) error(itr,"expected ']'");

            node_ptr expr(SUBSCRIPT_EXPRESSION,op);
            expr << lhs;
            expr << rhs;
            while (read(itr,end,LBRACK)) {
                rhs = expression(itr,end);
                if (not rhs) error(itr,"expected expression");
                if (not read(itr,end,RBRACK)) error(itr,"expected ']'");
                expr << rhs;
            }
            return expr;
        }

        app_gpuc_parser_rule(member_postfix_expression) {
            auto lhs = member_reference(itr,end);
            if (not lhs) return nullptr;

            auto op = read(itr,end,is_postfix_operator);
            if (not op) return lhs;

            if (read(itr,end,is_postfix_operator))
                error_before(itr,"expression is not assignable");

            node_ptr expr(POSTFIX_EXPRESSION,op);
            expr << lhs;
            return expr;
        }

        app_gpuc_parser_rule(subscript_expression) {
            auto lhs = invocation_or_postfix_expression(itr,end);
            if (not lhs)
                return nullptr;

            auto op = read(itr,end,LBRACK);
            if (not op) return lhs;

            auto rhs = expression(itr,end);
            if (not rhs) return error(itr,"expected expression");
            if (not read(itr,end,RBRACK)) return error(itr,"expected ']'");

            node_ptr expr(SUBSCRIPT_EXPRESSION,op);
            expr << lhs;
            expr << rhs;
            while (read(itr,end,LBRACK)) {
                rhs = expression(itr,end);
                if (not rhs) return error(itr,"expected expression");
                if (not read(itr,end,RBRACK)) return error(itr,"expected ']'");
                expr << rhs;
            }
            return expr;
        }

        app_gpuc_parser_rule(invocation_or_postfix_expression) {
            if (auto x = invocation_expression(itr,end)) return x;
            if (auto x =    postfix_expression(itr,end)) return x;
            return nullptr;
        }

        app_gpuc_parser_rule(invocation_expression) {
            auto name = read(itr,end,is_identifier_or_typename);
            if (not name)
                return nullptr;

            if (not read(itr,end,LPAREN))
                return nullptr;

            auto symbol = find_symbol(name);
            const node* type = nullptr;
            if (is_function(symbol)) {
                type = symbol->type;
            }
            else
            if (is_type(symbol)) {
                type = symbol;
            }

            node_ptr expr(INVOCATION_EXPRESSION,name,type);
            if (not read(itr,end,RPAREN)) {
                while (expr << expression(itr,end)) {
                    if (read(itr,end,COMMA)) continue;
                    if (peek(itr,end,RPAREN)) break;
                    return error(itr,"expected ',' or ')'");
                }
            }

            if (not read(itr,end,RPAREN))
                return error(itr,"expected ')'");

            return expr;
        }

        app_gpuc_parser_rule(postfix_expression) {
            int i;
            ++(i);

            auto lhs = primary_expression(itr,end);
            if (not lhs)
                return nullptr;

            auto op = read(itr,end,is_postfix_operator);
            if (not op)
                return lhs;

            if (auto err = read(itr,end,is_postfix_operator)) {
                error_before(itr,"expression is not assignable");
                while (read(itr,end,is_postfix_operator));
            }

            node_ptr expr(POSTFIX_EXPRESSION,op);
            expr << lhs;
            return expr;
        }

        app_gpuc_parser_rule(primary_expression) {
            if (auto x = literal_expression(itr,end)) return x;
            if (auto x =   symbol_reference(itr,end)) return x;
            if (auto x =  nested_expression(itr,end)) return x;
            return nullptr;
        }

        app_gpuc_parser_rule(literal_expression) {
            auto literal = read(itr,end,is_literal);
            if (not literal) return nullptr;

            const node* type = nullptr;
            switch (token(literal)) {
                case token::DOUBLE_LITERAL: type = find_type(DOUBLE); break;
                case token::FALSE_LITERAL:  type = find_type(BOOL);   break;
                case token::FLOAT_LITERAL:  type = find_type(FLOAT);  break;
                case token::INT_LITERAL:    type = find_type(INT);    break;
                case token::TRUE_LITERAL:   type = find_type(BOOL);   break;
                case token::UINT_LITERAL:   type = find_type(UINT);   break;
                default: return nullptr;
            }
            return node_ptr(LITERAL_EXPRESSION,literal,type);
        }

        app_gpuc_parser_rule(symbol_reference) {
            auto name = read(itr,end,is_identifier_or_typename);
            if (not name) return nullptr;

            auto symbol = find_symbol(name);
            if (not symbol) {
                error(name,"undeclared identifier '",*name,"'");
                return node_ptr(SYMBOL_REFERENCE,name);
            }
            auto type = symbol->type;
            switch (symbol->semantic) {
                case semantic::FUNCTION_PARAMETER:
                    return node_ptr(VARIABLE_REFERENCE,name,type);
                case semantic::UNIFORM_DEFINITION:
                    return node_ptr(UNIFORM_REFERENCE,name,type);
                case semantic::VARIABLE_DEFINITION:
                    return node_ptr(VARIABLE_REFERENCE,name,type);
                default: break;
            }
            error(name,"expected variable name");
            return node_ptr(SYMBOL_REFERENCE,name);
        }

        app_gpuc_parser_rule(nested_expression) {
            auto op = read(itr,end,LPAREN);
            if (not op) return nullptr;
            auto child = expression(itr,end);
            if (not child) return error(itr,"expected expression");
            if (not read(itr,end,RPAREN)) return error(itr,"expected ')'");
            auto expr = node_ptr(NESTED_EXPRESSION,op,child->type);
            expr << child;
            return expr;
        }

        app_gpuc_parser_rule(ternary_expression) {
            auto cexpr = logical_or_expression(itr,end);
            if (not cexpr) return nullptr;

            auto op = read(itr,end,QUESTION);
            if (not op) return cexpr;

            auto texpr = logical_or_expression(itr,end);
            if (not texpr) return error(itr,"expected expression");

            if (not read(itr,end,COLON))
                return error(itr,"expected ':'");

            auto fexpr = logical_or_expression(itr,end);
            if (not fexpr) return error(itr,"expected expression");

            node_ptr expr(TERNARY_EXPRESSION,op);
            expr << cexpr;
            expr << texpr;
            expr << fexpr;
            return expr;
        }

        // binary expressions --------------------------------------------------

        using expr_type_t = const node* (parser::*)(const node*, const node*);

        template<semantic Semantic, rule_t LHS, typename Token>
        node_ptr binary_expression(
            itr_t&  itr, end_t end,
            Token&& token,
            expr_type_t expr_type)
        {
            auto lhs = (this->*LHS)(itr,end);
            if (not lhs) return nullptr;

            auto op = read(itr,end,token);
            if (not op) return lhs;

            auto rhs = binary_expression<Semantic,LHS>(itr,end,token,expr_type);
            if (not rhs) return error(itr,"expected expression");

            auto type = (this->*expr_type)(lhs,rhs);
            if (not type) {
                auto type_a = lhs->type;
                auto type_b = rhs->type;
                auto typename_a = type_a ? *type_a->lexeme : lexeme("?",END);
                auto typename_b = type_b ? *type_b->lexeme : lexeme("?",END);
                error(op,
                    "invalid operands to binary expression ",
                    "('",typename_a,"' and '",typename_b,"')"
                );
            }

            node_ptr expr(Semantic,op,type);
            expr << lhs;
            expr << rhs;
            return expr;
        }

        const node*
        boolean_expression_type(const node* lhs, const node* rhs) {
            return find_type(BOOL);
        }

        app_gpuc_parser_rule(logical_or_expression) {
            return binary_expression<
                LOGICAL_OR_EXPRESSION,
                &parser::logical_and_expression
            >(itr,end,OROR,&parser::boolean_expression_type);
        }

        app_gpuc_parser_rule(logical_and_expression) {
            return binary_expression<
                LOGICAL_AND_EXPRESSION,
                &parser::bitwise_or_expression
            >(itr,end,ANDAND,&parser::boolean_expression_type);
        }

        const node*
        integral_expression_type(const node* lhs, const node* rhs) {
            app_todo("integral_expression_type");
            return nullptr;
        }

        app_gpuc_parser_rule(bitwise_or_expression) {
            return binary_expression<
                BITWISE_OR_EXPRESSION,
                &parser::bitwise_xor_expression
            >(itr,end,OR,&parser::integral_expression_type);
        }

        app_gpuc_parser_rule(bitwise_xor_expression) {
            return binary_expression<
                BITWISE_XOR_EXPRESSION,
                &parser::bitwise_and_expression
            >(itr,end,XOR,&parser::integral_expression_type);
        }

        app_gpuc_parser_rule(bitwise_and_expression) {
            return binary_expression<
                BITWISE_AND_EXPRESSION,
                &parser::equality_expression
            >(itr,end,AND,&parser::integral_expression_type);
        }

        app_gpuc_parser_rule(equality_expression) {
            return binary_expression<
                EQUALITY_EXPRESSION,
                &parser::relational_expression
            >(itr,end,is_equality_operator,&parser::boolean_expression_type);
        }

        app_gpuc_parser_rule(relational_expression) {
            return binary_expression<
                RELATIONAL_EXPRESSION,
                &parser::shift_expression
            >(itr,end,is_relational_operator,&parser::boolean_expression_type);
        }

        app_gpuc_parser_rule(shift_expression) {
            return binary_expression<
                SHIFT_EXPRESSION,
                &parser::sum_expression
            >(itr,end,is_shift_operator,&parser::integral_expression_type);
        }

        static
        constexpr
        uint32_t
        opid(const enum token a, const enum token b) {
            return ((uint32_t(a)<<8)|uint32_t(b));
        }

        const node*
        arithmetic_expression_type(const node* lhs, const node* rhs) {
            switch (opid(token(lhs->type),token(rhs->type))) {
                case opid(BOOL,     BOOL):     return find_type(BOOL);
                case opid(BOOL2,    BOOL2):    return find_type(BOOL2);
                case opid(BOOL3,    BOOL3):    return find_type(BOOL3);
                case opid(BOOL4,    BOOL4):    return find_type(BOOL4);
                case opid(FLOAT,    FLOAT):    return find_type(FLOAT);
                case opid(FLOAT2,   FLOAT2):   return find_type(FLOAT2);
                case opid(FLOAT2X2, FLOAT2X2): return find_type(FLOAT2X2);
                case opid(FLOAT2X3, FLOAT2X3): return find_type(FLOAT2X3);
                case opid(FLOAT2X4, FLOAT2X4): return find_type(FLOAT2X4);
                case opid(FLOAT3,   FLOAT3):   return find_type(FLOAT3);
                case opid(FLOAT3X2, FLOAT3X2): return find_type(FLOAT3X2);
                case opid(FLOAT3X3, FLOAT3X3): return find_type(FLOAT3X3);
                case opid(FLOAT3X4, FLOAT3X4): return find_type(FLOAT3X4);
                case opid(FLOAT4,   FLOAT4):   return find_type(FLOAT4);
                case opid(FLOAT4X2, FLOAT4X2): return find_type(FLOAT4X2);
                case opid(FLOAT4X3, FLOAT4X3): return find_type(FLOAT4X3);
                case opid(FLOAT4X4, FLOAT4X4): return find_type(FLOAT4X4);
                case opid(INT,      INT):      return find_type(INT);
                case opid(INT2,     INT2):     return find_type(INT2);
                case opid(INT3,     INT3):     return find_type(INT3);
                case opid(INT4,     INT4):     return find_type(INT4);
                case opid(UINT,     UINT):     return find_type(UINT);
                case opid(UINT2,    UINT2):    return find_type(UINT2);
                case opid(UINT3,    UINT3):    return find_type(UINT3);
                case opid(UINT4,    UINT4):    return find_type(UINT4);

                case opid(FLOAT2, FLOAT2X2):   return find_type(FLOAT2);
                case opid(FLOAT3, FLOAT3X3):   return find_type(FLOAT3);
                case opid(FLOAT4, FLOAT4X4):   return find_type(FLOAT4);

                case opid(FLOAT2X2, FLOAT2):   return find_type(FLOAT2);
                case opid(FLOAT3X3, FLOAT3):   return find_type(FLOAT3);
                case opid(FLOAT4X4, FLOAT4):   return find_type(FLOAT4);

                default:                       return nullptr;
            }
        }

        app_gpuc_parser_rule(sum_expression) {
            return binary_expression<
                SUM_EXPRESSION,
                &parser::product_expression
            >(itr,end,is_sum_operator,&parser::arithmetic_expression_type);
        }

        app_gpuc_parser_rule(product_expression) {
            return binary_expression<
                PRODUCT_EXPRESSION,
                &parser::prefix_expression
            >(itr,end,is_product_operator,&parser::arithmetic_expression_type);
        }

        #undef app_gpuc_parser_rule

    private: // navigaton

        static
        enum token token(const lexeme* lexeme) {
            return lexeme ? lexeme->token : END;
        }

        static
        enum token token(const node* node) {
            return node ? token(node->lexeme) : END;
        }

        static
        enum token token(itr_t itr, end_t end) {
            return itr < end ? token(itr) : END;
        }

        static
        const lexeme* peek(itr_t itr, end_t end) {
            return itr < end ? itr : nullptr;
        }

        static
        const lexeme* peek(itr_t itr, end_t end, enum token token) {
            return itr < end and token == *itr ? itr : nullptr;
        }

        template<typename Bool, typename Token>
        static
        const lexeme* peek(itr_t itr, end_t end, Bool(&f)(Token)) {
            return itr < end and f(*itr) ? itr : nullptr;
        }

        template<typename A, typename... B>
        static
        const lexeme* peek(itr_t& itr, end_t end, A&& a, B&&... b) {
            if (auto lexeme = peek(itr,end,a)) return lexeme;
            return peek(itr,end,b...);
        }

        static
        const lexeme* read(itr_t& itr, end_t end) {
            auto x = peek(itr,end);
            if (x) ++itr;
            return x;
        }

        static
        const lexeme* read(itr_t& itr, end_t end, enum token token) {
            auto x = peek(itr,end,token);
            if (x) ++itr;
            return x;
        }

        template<typename Bool, typename Token>
        static
        const lexeme* read(itr_t& itr, end_t end, Bool(&f)(Token)) {
            auto x = peek(itr,end,f);
            if (x) ++itr;
            return x;
        }

        template<typename A, typename... B>
        static
        const lexeme* seek(itr_t& itr, end_t end, A&& a, B&&... b) {
            const lexeme* lexeme = nullptr;
            do { lexeme = peek(itr,end,a,b...); }
            while (not lexeme and read(itr,end));
            return lexeme;
        }
    };

} // namespace app::gpuc
