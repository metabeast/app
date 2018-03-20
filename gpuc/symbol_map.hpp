#pragma once
#include "../detail/iterator_range.hpp"
#include "diagnostics.hpp"
#include "node.hpp"

namespace app::gpuc {

    struct symbol_map : diagnostics {
        friend struct symbol_scope;

    private:
        struct entry {
            size_t scope;
            const node* symbol;
            auto name() const { return *symbol->lexeme; }
        };
        size_t             _scope   {};
        std::vector<entry> _entries {};

    protected:
        symbol_map() = default;
        symbol_map(symbol_map&&) = default;
        symbol_map& operator=(symbol_map&&) = default;

        symbol_map(diagnostics&& x)
        :diagnostics(std::move(x)) {
            _entries.reserve(64);
            #define app_gpuc_builtin_type(TOKEN,token) {\
                static const lexeme lexeme {token,TOKEN};\
                static const node   symbol {BUILTIN_TYPE,&lexeme};\
                define_type(&symbol);\
            }
            app_gpuc_token_typename(app_gpuc_builtin_type)
            #undef app_gpuc_builtin_type
        }

    protected:

        static
        const node* find_member(const node* structure, const lexeme& name) {
            if (not structure)
                return nullptr;

            app_assert(structure->semantic == STRUCT_DEFINITION);

            for (const auto& child : structure->children()) {
                app_assert(child->semantic == STRUCT_FIELD_DEFINITION);
                const auto child_name = *child->lexeme;
                if (child_name == name)
                    return child;
            }
            return nullptr;
        }

        static
        const node* find_member(const node* structure, const lexeme* name) {
            return name ? find_member(structure,*name) : nullptr;
        }

        const node* find_symbol(const lexeme& name) {
            for (auto& entry : detail::reverse(_entries)) {
                if (entry.name() == name)
                    return entry.symbol;
            }
            return nullptr;
        }

        const node* find_symbol(const enum token token) {
            for (auto& entry : _entries) {
                if (entry.name().token == token)
                    return entry.symbol;
            }
            return nullptr;
        }

        const node* find_symbol(const lexeme* name) {
            return name ? find_symbol(*name) : nullptr;
        }

        const node* find_type(const lexeme& name) {
            auto* symbol = find_symbol(name);
            return is_type(symbol) ? symbol : nullptr;
        }

        const node* find_type(const lexeme* name) {
            return name ? find_type(*name) : nullptr;
        }

        const node* find_type(const enum token token) {
            auto* symbol = find_symbol(token);
            return is_type(symbol) ? symbol : nullptr;
        }

        bool define_type(const node* symbol) {
            app_assert(_scope <= 1); // global scope
            app_assert(is_type(symbol));
            app_assert(symbol->lexeme);
            const auto scope = _scope;
            const auto name = *symbol->lexeme;

            // check for conflicts with existing symbols
            for (const auto& entry : _entries) {
                app_assert(entry.scope <= scope);
                const auto* previous = entry.symbol;
                const auto& previous_name = *previous->lexeme;
                if (previous_name != name)
                    continue;

                error(name,"redefinition of '",name,"'");
                note(previous_name,"previous definition is here");
                return false;
            }

            _entries.emplace_back(entry{scope,symbol});
            return true;
        }

        bool declare_function(const node* symbol) {
            app_assert(_scope <= 1); // global scope
            app_assert(is_function_declaration(symbol));
            const auto scope = _scope;
            const auto name = *symbol->lexeme;

            // check for conflicts with existing symbols
            for (const auto& entry : _entries) {
                app_assert(entry.scope <= scope);
                const auto* previous = entry.symbol;
                const auto& previous_name = *previous->lexeme;
                if (previous_name != name)
                    continue;

                if (is_function(previous)) {
                    if (is_function_override(previous,symbol))
                        continue;

                    if (previous->type != symbol->type) {
                        const auto signature = function_signature(symbol);
                        error(name,"redeclaration of '",signature,"' ",
                            "differs only in return type");
                        if (is_function_declaration(previous))
                            note(previous_name,"previous declaration is here");
                        else
                            note(previous_name,"previous definition is here");
                        return false;
                    }

                    // multiple identical function declarations are OK
                }

                error(name,"redefinition of '",name,"'");
                note(previous_name,"previous definition is here");
                return false;
            }

            _entries.emplace_back(entry{scope,symbol});
            return true;
        }

        bool define_function(const node* symbol) {
            app_assert(_scope <= 1); // global scope
            app_assert(is_function_definition(symbol));
            const auto scope = _scope;
            const auto name = *symbol->lexeme;

            // check for conflicts with existing symbols
            for (const auto& entry : _entries) {
                app_assert(entry.scope <= scope);
                const auto* previous = entry.symbol;
                const auto& previous_name = *previous->lexeme;
                if (previous_name != name)
                    continue;

                if (is_function(previous)) {
                    if (is_function_override(previous,symbol))
                        continue;

                    if (is_function_declaration(previous)) {
                        if (previous->type == symbol->type)
                            continue;

                        const auto signature = function_signature(symbol);
                        error(name,"definition of '",signature,"' ",
                            "differs only in return type");
                        note(previous_name,"declaration is here");
                        return false;
                    }

                    const auto signature = function_signature(symbol);
                    error(name,"redefinition of '",signature,"'");
                    note(previous_name,"previous definition is here");
                }

                error(name,"redefinition of '",name,"'");
                note(entry.name(),"previous definition is here");
                return false;
            }

            _entries.emplace_back(entry{scope,symbol});
            return false;
        }

        bool define_variable(const node* symbol) {
            app_assert(is_variable(symbol));
            const auto scope = _scope;
            const auto name = *symbol->lexeme;

            // check for conflicts with existing symbols in the same scope
            for (const auto& entry : detail::reverse(_entries)) {
                if (entry.scope < scope)
                    break;

                const auto* previous = entry.symbol;
                const auto& previous_name = *previous->lexeme;
                if (previous_name != name)
                    continue;

                error(name,"redefinition of '",name,"'");
                note(entry.name(),"previous definition is here");
                return false;
            }

            _entries.emplace_back(entry{scope,symbol});
            return false;
        }

    protected:

        #define app_gpuc_token_alias(TOKEN,...)\
            static constexpr token TOKEN = token::TOKEN;
        app_gpuc_token(app_gpuc_token_alias)
        #undef app_gpuc_token_alias

        #define app_gpuc_semantic_alias(SEMANTIC)\
            static constexpr semantic SEMANTIC = semantic::SEMANTIC;
        app_gpuc_semantic(app_gpuc_semantic_alias)
        #undef app_gpuc_semantic_alias

        static std::string function_signature(const node* function) {
            app_assert(is_function(function));
            std::stringstream s;
            if (auto* return_type = function->type)
                s << *return_type->lexeme;
            else
                s << "?";
            s << " " << *function->lexeme << "(";
            auto* params = function->child(FUNCTION_PARAMETER_LIST);
            size_t param_index = 0;
            for (auto& param : params->children()) {
                if (param_index++) s << ",";
                if (auto* type_name = param->type_name())
                    s << *type_name;
                else
                    s << "?";
            }
            s << ")";
            return s.str();
        }

        static bool is_function(const node* symbol) {
            return symbol and gpuc::is_function(symbol->semantic);
        }

        static bool is_function_declaration(const node* symbol) {
            return symbol and symbol->semantic == FUNCTION_DECLARATION;
        }

        static bool is_function_definition(const node* symbol) {
            return symbol and symbol->semantic == FUNCTION_DEFINITION;
        }

        static bool is_function_override(const node* f, const node* g) {
            auto* f_parameter_list = f->child(FUNCTION_PARAMETER_LIST);
            auto* g_parameter_list = g->child(FUNCTION_PARAMETER_LIST);
            app_assert(f_parameter_list);
            app_assert(g_parameter_list);
            auto& f_parameters = f_parameter_list->children();
            auto& g_parameters = g_parameter_list->children();
            const size_t parameter_count = f_parameters.size();
            if (g_parameters.size() != parameter_count)
                return true; // different parameter count

            for (size_t i = 0; i < parameter_count; ++i)
                if (f_parameters[i]->type != g_parameters[i]->type)
                    return true; // different parameter types

            return false;
        }

        static bool is_type(const node* symbol) {
            return symbol and gpuc::is_type(symbol->semantic);
        }

        static bool is_variable(const node* symbol) {
            return symbol and gpuc::is_variable(symbol->semantic);
        }
    };

    //--------------------------------------------------------------------------

    struct symbol_scope {
    private:
        symbol_map* const _symbols {};
        const size_t      _offset  {};

    public:
        symbol_scope(symbol_map* s)
        :_symbols(s)
        ,_offset(_symbols ? _symbols->_entries.size() : 0) {
            if (_symbols) {
                _symbols->_scope += 1;
                app_assert(_symbols->_scope);
            }
        }

        symbol_scope(symbol_map& s)
        :symbol_scope(&s) {}

        ~symbol_scope() {
            if (_symbols) {
                app_assert(_symbols->_scope);
                _symbols->_entries.resize(_offset);
                _symbols->_scope -= 1;
            }
        }
    };

} // namespace app::gpuc