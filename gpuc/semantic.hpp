#pragma once
#include <cstdint>

namespace app::gpuc {

    #define \
    app_gpuc_semantic(app_gpuc_semantic)\
    app_gpuc_semantic(UNDEFINED_SEMANTIC)\
    /**/\
    app_gpuc_semantic(BUILTIN_TYPE)\
    /**/\
    app_gpuc_semantic(TRANSLATION_UNIT)\
    /**/\
    app_gpuc_semantic(STRUCT_DEFINITION)\
    app_gpuc_semantic(STRUCT_FIELD_DEFINITION)\
    /**/\
    app_gpuc_semantic(UNIFORM_DEFINITION)\
    /**/\
    app_gpuc_semantic(VARIABLE_DEFINITION)\
    /**/\
    app_gpuc_semantic(FUNCTION_DECLARATION)\
    app_gpuc_semantic(FUNCTION_DEFINITION)\
    app_gpuc_semantic(FUNCTION_PARAMETER_LIST)\
    app_gpuc_semantic(FUNCTION_PARAMETER)\
    /**/\
    app_gpuc_semantic(EMPTY_STATEMENT)\
    app_gpuc_semantic(IF_STATEMENT)\
    app_gpuc_semantic(SWITCH_STATEMENT)\
    app_gpuc_semantic(WHILE_STATEMENT)\
    app_gpuc_semantic(DO_STATEMENT)\
    app_gpuc_semantic(FOR_STATEMENT)\
    app_gpuc_semantic(GOTO_STATEMENT)\
    app_gpuc_semantic(CONTINUE_STATEMENT)\
    app_gpuc_semantic(BREAK_STATEMENT)\
    app_gpuc_semantic(RETURN_STATEMENT)\
    app_gpuc_semantic(COMPOUND_STATEMENT)\
    app_gpuc_semantic(EXPRESSION_STATEMENT)\
    app_gpuc_semantic(INVALID_STATEMENT)\
    /**/\
    app_gpuc_semantic(ASSIGNMENT_EXPRESSION)\
    app_gpuc_semantic(PREFIX_EXPRESSION)\
    app_gpuc_semantic(POSTFIX_EXPRESSION)\
    app_gpuc_semantic(NESTED_EXPRESSION)\
    app_gpuc_semantic(MEMBER_EXPRESSION)\
    app_gpuc_semantic(SUBSCRIPT_EXPRESSION)\
    app_gpuc_semantic(INVOCATION_EXPRESSION)\
    app_gpuc_semantic(TERNARY_EXPRESSION)\
    app_gpuc_semantic(LOGICAL_OR_EXPRESSION)\
    app_gpuc_semantic(LOGICAL_AND_EXPRESSION)\
    app_gpuc_semantic(BITWISE_OR_EXPRESSION)\
    app_gpuc_semantic(BITWISE_XOR_EXPRESSION)\
    app_gpuc_semantic(BITWISE_AND_EXPRESSION)\
    app_gpuc_semantic(EQUALITY_EXPRESSION)\
    app_gpuc_semantic(RELATIONAL_EXPRESSION)\
    app_gpuc_semantic(SHIFT_EXPRESSION)\
    app_gpuc_semantic(SUM_EXPRESSION)\
    app_gpuc_semantic(PRODUCT_EXPRESSION)\
    app_gpuc_semantic(LITERAL_EXPRESSION)\
    /**/\
    app_gpuc_semantic(MEMBER_REFERENCE)\
    app_gpuc_semantic(SYMBOL_REFERENCE)\
    app_gpuc_semantic(UNIFORM_REFERENCE)\
    app_gpuc_semantic(VARIABLE_REFERENCE)\
    /**/

    enum struct semantic : uint8_t {
        #define app_gpuc_semantic_enum(SEMANTIC)\
        SEMANTIC,
        app_gpuc_semantic(app_gpuc_semantic_enum)
        #undef app_gpuc_semantic_enum
    };

    inline std::ostream& operator<<(std::ostream& o, semantic s) {
        switch (s) {
            #define app_gpuc_semantic_string(SEMANTIC)\
            case semantic::SEMANTIC: return o << #SEMANTIC;
            app_gpuc_semantic(app_gpuc_semantic_string)
            #undef app_gpuc_semantic_string

            default: return o << "<unrecognized semantic>";
        }
    }

    inline bool is_function(const semantic s) {
        switch (s) {
            case semantic::FUNCTION_DECLARATION:
            case semantic::FUNCTION_DEFINITION:
                return true;
            default: return false;
        }
    }

    inline bool is_type(const semantic s) {
        switch (s) {
            case semantic::BUILTIN_TYPE:
            case semantic::STRUCT_DEFINITION:
                return true;
            default: return false;
        }
    }

    inline bool is_variable(const semantic s) {
        switch (s) {
            case semantic::FUNCTION_PARAMETER:
            case semantic::UNIFORM_DEFINITION:
            case semantic::VARIABLE_DEFINITION:
                return true;
            default: return false;
        }
    }

} // namespace app::gpuc