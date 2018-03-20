#pragma once
#include "tree.hpp"
#include "../gpu/shader.hpp"

namespace app::gpuc {

    using gpu::shader_stage;

    struct writer {

        #define app_gpuc_token_alias(TOKEN,...)\
            static constexpr token TOKEN = token::TOKEN;
        app_gpuc_token(app_gpuc_token_alias)
        #undef app_gpuc_token_alias

        #define app_gpuc_semantic_alias(SEMANTIC)\
            static constexpr semantic SEMANTIC = semantic::SEMANTIC;
        app_gpuc_semantic(app_gpuc_semantic_alias)
        #undef app_gpuc_semantic_alias

        struct tree& tree;

        const enum shader_stage shader_stage {};

    private:

        std::ostream* out {};

        int indent_depth {};

        bool indent_pending {};

    public:

        writer(struct tree& tree, enum shader_stage shader_stage)
        :tree(tree),shader_stage(shader_stage) {}

    protected:

        struct separator : substring { using substring::substring; };

        virtual
        void write(const char* s) {
            if (s) puts(s,strlen(s));
        }

        virtual
        void write(unsigned n) {
            if (n == 0) {
                put('0');
                return;
            }
            while (n > 0) {
                put('0' + n%10);
                n /= 10;
            }
        }

        virtual
        void write(const lexeme* l) {
            if (l) write(*l);
        }

        virtual
        void write(const lexeme& l) {
            puts(l.begin(),l.size());
        }

        virtual
        void write(const node* node) {
            app_assert(node != nullptr);
            if (node) write(*node);
        }

        virtual
        void write(const node& node) {
            switch (node.semantic) {
                #define app_gpuc_semantic_alias(SEMANTIC)\
                    case SEMANTIC: return write_##SEMANTIC(node);
                app_gpuc_semantic(app_gpuc_semantic_alias)
                #undef app_gpuc_semantic_alias
            }
        }

        virtual
        void write(const nodes& nodes) {
            for (auto& node : nodes) write(node);
        }

        virtual
        void write(const nodes& nodes, separator s) {
            auto n = 0u - nodes.size();
            for (auto& node : nodes) {
                write(node); if (++n) s.write(*out);
            }
        }

        template<typename A, typename B, typename... C>
        void write(A&& a, B&& b, C&&... c) {
            write(a);
            write(b);
            app_unpack(write(c));
        }

        friend
        auto& operator<<(std::ostream& o, writer&& w) {
            w.out = &o;
            w.write(w.tree.root());
            return o;
        }

    protected:

        #define app_gpuc_writer_write(SEMANTIC) \
            virtual void write_##SEMANTIC(const node& node)

        app_gpuc_writer_write(UNDEFINED_SEMANTIC) {
            app_err("UNDEFINED_SEMANTIC");
        }

        app_gpuc_writer_write(BUILTIN_TYPE) {
            app_err("BUILTIN_TYPE");
        }

        app_gpuc_writer_write(TRANSLATION_UNIT) {
            write(node.children());
        }

        //----------------------------------------------------------------------

        app_gpuc_writer_write(STRUCT_DEFINITION) {
            write("struct ",node.lexeme," {");
            if (node.children()) {
                write("\n");
                indent([&]{ write(node.children()); });
            }
            write("};\n\n");
        }

        app_gpuc_writer_write(STRUCT_FIELD_DEFINITION) {
            write(node.type_name()," ",node.lexeme,";\n");
        }

        //----------------------------------------------------------------------

        app_gpuc_writer_write(UNIFORM_DEFINITION) {
            write("uniform ",node.type_name()," ",node.lexeme);
        }

        app_gpuc_writer_write(VARIABLE_DEFINITION) {
            write(node.type_name()," ",node.lexeme);
        }

        //----------------------------------------------------------------------

        app_gpuc_writer_write(FUNCTION_DECLARATION) {
            write(node.type_name()," ",node.lexeme);
            write(node.children(),";\n\n");
        }

        app_gpuc_writer_write(FUNCTION_DEFINITION) {
            write(node.type_name()," ",node.lexeme);
            write(node.children(),"\n");
        }

        app_gpuc_writer_write(FUNCTION_PARAMETER_LIST) {
            write("(");
            write(node.children(),separator(", "));
            write(")");
        }

        app_gpuc_writer_write(FUNCTION_PARAMETER) {
            write(node.type_name()," ",node.lexeme);
        }

        //----------------------------------------------------------------------

        app_gpuc_writer_write(EMPTY_STATEMENT) {
            write(";\n");
        }

        app_gpuc_writer_write(IF_STATEMENT) {
            app_todo("IF_STATEMENT");
        }

        app_gpuc_writer_write(SWITCH_STATEMENT) {
            app_todo("SWITCH_STATEMENT");
        }

        app_gpuc_writer_write(WHILE_STATEMENT) {
            app_todo("WHILE_STATEMENT");
        }

        app_gpuc_writer_write(DO_STATEMENT) {
            app_todo("DO_STATEMENT");
        }

        app_gpuc_writer_write(FOR_STATEMENT) {
            app_todo("FOR_STATEMENT");
        }

        app_gpuc_writer_write(GOTO_STATEMENT) {
            app_todo("GOTO_STATEMENT");
        }

        app_gpuc_writer_write(CONTINUE_STATEMENT) {
            app_todo("CONTINUE_STATEMENT");
        }

        app_gpuc_writer_write(BREAK_STATEMENT) {
            app_todo("BREAK_STATEMENT");
        }

        app_gpuc_writer_write(RETURN_STATEMENT) {
            write("return ",node.children(),";\n");
        }

        app_gpuc_writer_write(COMPOUND_STATEMENT) {
            write(" {");
            if (node.children()) {
                write("\n");
                indent([&]{ write(node.children()); });
            }
            write("}\n");
        }

        app_gpuc_writer_write(EXPRESSION_STATEMENT) {
            write(node.children(),";\n");
        }

        app_gpuc_writer_write(INVALID_STATEMENT) {
            app_err("INVALID_STATEMENT");
        }

        //----------------------------------------------------------------------

        app_gpuc_writer_write(ASSIGNMENT_EXPRESSION) {
            write(node.child(0)," ",node.lexeme," ",node.child(1));
        }

        app_gpuc_writer_write(PREFIX_EXPRESSION) {
            write(node.lexeme,node.children());
        }

        app_gpuc_writer_write(POSTFIX_EXPRESSION) {
            write(node.children(),node.lexeme);
        }

        app_gpuc_writer_write(NESTED_EXPRESSION) {
            write("(");
            write(node.children());
            write(")");
        }

        app_gpuc_writer_write(MEMBER_EXPRESSION) {
            write(node.child(0),node.lexeme,node.child(1));
        }

        app_gpuc_writer_write(SUBSCRIPT_EXPRESSION) {
            app_todo("SUBSCRIPT_EXPRESSION");
        }

        app_gpuc_writer_write(INVOCATION_EXPRESSION) {
            write(node.lexeme,"(");
            write(node.children(),separator(", "));
            write(")");
        }

        app_gpuc_writer_write(TERNARY_EXPRESSION) {
            app_todo("TERNARY_EXPRESSION");
        }

        app_gpuc_writer_write(LOGICAL_OR_EXPRESSION) {
            app_todo("LOGICAL_OR_EXPRESSION");
        }

        app_gpuc_writer_write(LOGICAL_AND_EXPRESSION) {
            app_todo("LOGICAL_AND_EXPRESSION");
        }

        app_gpuc_writer_write(BITWISE_OR_EXPRESSION) {
            app_todo("BITWISE_OR_EXPRESSION");
        }

        app_gpuc_writer_write(BITWISE_XOR_EXPRESSION) {
            app_todo("BITWISE_XOR_EXPRESSION");
        }

        app_gpuc_writer_write(BITWISE_AND_EXPRESSION) {
            app_todo("BITWISE_AND_EXPRESSION");
        }

        app_gpuc_writer_write(EQUALITY_EXPRESSION) {
            app_todo("EQUALITY_EXPRESSION");
        }

        app_gpuc_writer_write(RELATIONAL_EXPRESSION) {
            app_todo("RELATIONAL_EXPRESSION");
        }

        app_gpuc_writer_write(SHIFT_EXPRESSION) {
            app_todo("SHIFT_EXPRESSION");
        }

        app_gpuc_writer_write(SUM_EXPRESSION) {
            write(node.child(0));
            write(" ",node.lexeme," ");
            write(node.child(1));
        }

        app_gpuc_writer_write(PRODUCT_EXPRESSION) {
            write(node.child(0));
            write(" ",node.lexeme," ");
            write(node.child(1));
        }

        app_gpuc_writer_write(LITERAL_EXPRESSION) {
            write(node.lexeme);
        }

        //----------------------------------------------------------------------

        app_gpuc_writer_write(MEMBER_REFERENCE) {
            write(node.lexeme);
        }

        app_gpuc_writer_write(SYMBOL_REFERENCE) {
            write(node.lexeme);
        }

        app_gpuc_writer_write(UNIFORM_REFERENCE) {
            write(node.lexeme);
        }

        app_gpuc_writer_write(VARIABLE_REFERENCE) {
            write(node.lexeme);
        }

        //----------------------------------------------------------------------

        #undef app_gpuc_writer_write

        #define app_gpuc_writer_write(SEMANTIC) \
            void write_##SEMANTIC(const node& node) override

    protected:

        template<typename F>
        void indent(F&& f) {
            indent_depth += 1;
            indent_pending = true;
            f();
            indent_depth -= 1;
        }

        // void indent(const node& node) {
        //     indent_depth += 1;
        //     write(node);
        //     indent_depth -= 1;
        // }

        // void indent(const nodes& nodes) {
        //     indent_depth += 1;
        //     write(nodes);
        //     indent_depth -= 1;
        // }

        // void indent(const nodes& nodes, separator s) {
        //     indent_depth += 1;
        //     write(nodes,s);
        //     indent_depth -= 1;
        // }

        void put(const char c) {
            if (c == '\n') {
                *out << c;
                indent_pending = true;
                return;
            }
            if (indent_pending) {
                indent_pending = false;
                for (int i = 0; i < indent_depth; ++i) {
                    *out << "    ";
                }
            }
            *out << c;
        }

        void puts(const char* s, intptr_t n) {
            while (n --> 0) put(*s++);
        }

        static
        auto token(const lexeme* lexeme) {
            return lexeme ? lexeme->token : END;
        }

        static
        auto token(const node* node) {
            return node ? token(node->lexeme) : END;
        }

    };

} // namespace app::gpuc
