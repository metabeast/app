#pragma once
#include <iostream>

namespace app::gpuc {

    #define \
    app_gpuc_token_keyword(app_gpuc_token_keyword)\
    app_gpuc_token_keyword(ATTRIBUTE,         "attribute")\
    app_gpuc_token_keyword(BREAK,             "break")\
    app_gpuc_token_keyword(CASE,              "case")\
    app_gpuc_token_keyword(CONST,             "const")\
    app_gpuc_token_keyword(CONTINUE,          "continue")\
    app_gpuc_token_keyword(DEFAULT,           "default")\
    app_gpuc_token_keyword(DISCARD,           "discard")\
    app_gpuc_token_keyword(DO,                "do")\
    app_gpuc_token_keyword(ELSE,              "else")\
    app_gpuc_token_keyword(FALSE_LITERAL,     "false")\
    app_gpuc_token_keyword(FOR,               "for")\
    app_gpuc_token_keyword(IF,                "if")\
    app_gpuc_token_keyword(RETURN,            "return")\
    app_gpuc_token_keyword(STRUCT,            "struct")\
    app_gpuc_token_keyword(SWITCH,            "switch")\
    app_gpuc_token_keyword(TRUE_LITERAL,      "true")\
    app_gpuc_token_keyword(UNIFORM,           "uniform")\
    app_gpuc_token_keyword(WHILE,             "while")\

    #define \
    app_gpuc_token_typename(app_gpuc_token_typename)\
    app_gpuc_token_typename(VOID,             "void")\
    app_gpuc_token_typename(BOOL,             "bool")\
    app_gpuc_token_typename(BOOL2,            "bool2")\
    app_gpuc_token_typename(BOOL3,            "bool3")\
    app_gpuc_token_typename(BOOL4,            "bool4")\
    app_gpuc_token_typename(DOUBLE,           "double")\
    app_gpuc_token_typename(FLOAT,            "float")\
    app_gpuc_token_typename(FLOAT2,           "float2")\
    app_gpuc_token_typename(FLOAT2X2,         "float2x2")\
    app_gpuc_token_typename(FLOAT2X3,         "float2x3")\
    app_gpuc_token_typename(FLOAT2X4,         "float2x4")\
    app_gpuc_token_typename(FLOAT3,           "float3")\
    app_gpuc_token_typename(FLOAT3X2,         "float3x2")\
    app_gpuc_token_typename(FLOAT3X3,         "float3x3")\
    app_gpuc_token_typename(FLOAT3X4,         "float3x4")\
    app_gpuc_token_typename(FLOAT4,           "float4")\
    app_gpuc_token_typename(FLOAT4X2,         "float4x2")\
    app_gpuc_token_typename(FLOAT4X3,         "float4x3")\
    app_gpuc_token_typename(FLOAT4X4,         "float4x4")\
    app_gpuc_token_typename(INT,              "int")\
    app_gpuc_token_typename(INT2,             "int2")\
    app_gpuc_token_typename(INT3,             "int3")\
    app_gpuc_token_typename(INT4,             "int4")\
    app_gpuc_token_typename(TEXTURE_1D,       "texture_1d")\
    app_gpuc_token_typename(TEXTURE_2D,       "texture_2d")\
    app_gpuc_token_typename(TEXTURE_3D,       "texture_3d")\
    app_gpuc_token_typename(TEXTURE_CUBE,     "texture_cube")\
    app_gpuc_token_typename(UINT,             "uint")\
    app_gpuc_token_typename(UINT2,            "uint2")\
    app_gpuc_token_typename(UINT3,            "uint3")\
    app_gpuc_token_typename(UINT4,            "uint4")\

    /* consider:
        texture<1>, texture<2>, texture<3>
        texture<linear>
        texture<planar,multisample>  texture_2d_ms
        texture<volume>
        texture<cube>
    */

    #define \
    app_gpuc_token_symbol(app_gpuc_token_symbol)\
    app_gpuc_token_symbol(LBRACE,             "{")\
    app_gpuc_token_symbol(RBRACE,             "}")\
    app_gpuc_token_symbol(LBRACK,             "[")\
    app_gpuc_token_symbol(RBRACK,             "]")\
    app_gpuc_token_symbol(LPAREN,             "(")\
    app_gpuc_token_symbol(RPAREN,             ")")\
    app_gpuc_token_symbol(LSHEQ,              "<<=")\
    app_gpuc_token_symbol(LSH,                "<<")\
    app_gpuc_token_symbol(RSHEQ,              "<<=")\
    app_gpuc_token_symbol(RSH,                ">>")\
    app_gpuc_token_symbol(DEC,                "--")\
    app_gpuc_token_symbol(INC,                "++")\
    app_gpuc_token_symbol(ARROW,              "->")\
    app_gpuc_token_symbol(EQEQ,               "==")\
    app_gpuc_token_symbol(LTEQ,               "<=")\
    app_gpuc_token_symbol(LT,                 "<")\
    app_gpuc_token_symbol(GTEQ,               ">=")\
    app_gpuc_token_symbol(GT,                 ">")\
    app_gpuc_token_symbol(NOTEQ,              "!=")\
    app_gpuc_token_symbol(NOT,                "!")\
    app_gpuc_token_symbol(ANDAND,             "&&")\
    app_gpuc_token_symbol(OROR,               "||")\
    app_gpuc_token_symbol(ADDEQ,              "+=")\
    app_gpuc_token_symbol(ADD,                "+")\
    app_gpuc_token_symbol(ANDEQ,              "&=")\
    app_gpuc_token_symbol(AND,                "&")\
    app_gpuc_token_symbol(DIVEQ,              "/=")\
    app_gpuc_token_symbol(DIV,                "/")\
    app_gpuc_token_symbol(MODEQ,              "%=")\
    app_gpuc_token_symbol(MOD,                "%")\
    app_gpuc_token_symbol(MULEQ,              "*=")\
    app_gpuc_token_symbol(MUL,                "*")\
    app_gpuc_token_symbol(OREQ,               "|=")\
    app_gpuc_token_symbol(OR,                 "|")\
    app_gpuc_token_symbol(SUBEQ,              "-=")\
    app_gpuc_token_symbol(SUB,                "-")\
    app_gpuc_token_symbol(XOREQ,              "^=")\
    app_gpuc_token_symbol(XOR,                "^")\
    app_gpuc_token_symbol(TILDE,              "~")\
    app_gpuc_token_symbol(EQ,                 "=")\
    app_gpuc_token_symbol(ELLIPSIS,           "...")\
    app_gpuc_token_symbol(DOT,                ".")\
    app_gpuc_token_symbol(COMMA,              ",")\
    app_gpuc_token_symbol(SEMICOLON,          ";")\
    app_gpuc_token_symbol(QUESTION,           "?")\
    app_gpuc_token_symbol(COLON,              ":")\

    #define \
    app_gpuc_token(app_gpuc_token)\
    app_gpuc_token(END)\
    app_gpuc_token(DIRECTIVE)\
    app_gpuc_token(DOUBLE_LITERAL)\
    app_gpuc_token(FLOAT_LITERAL)\
    app_gpuc_token(IDENTIFIER)\
    app_gpuc_token(INT_LITERAL)\
    app_gpuc_token(UINT_LITERAL)\
    app_gpuc_token_keyword(app_gpuc_token)\
    app_gpuc_token_typename(app_gpuc_token)\
    app_gpuc_token_symbol(app_gpuc_token)

    enum struct token : uint8_t {
        #define app_gpuc_token_enum(TOKEN,...)\
        TOKEN,
        app_gpuc_token(app_gpuc_token_enum)
        #undef app_gpuc_token_enum
    };

    inline std::ostream& operator<<(std::ostream& o, token t) {
        switch (t) {
            #define app_gpuc_token_string(TOKEN,...)\
            case token::TOKEN: return o << #TOKEN;
            app_gpuc_token(app_gpuc_token_string)
            #undef app_gpuc_token_string

            default: return o << "<unrecognized token>";
        }
    }

    inline bool is_keyword(const token t) {
        switch (t) {
            #define app_gpuc_is_keyword(TOKEN,...)\
            case token::TOKEN: return true;
            app_gpuc_token_keyword(app_gpuc_is_keyword)
            #undef app_gpuc_is_keyword

            default: return false;
        }
    }

    inline bool is_typename(const token t) {
        switch (t) {
            #define app_gpuc_is_typename(TOKEN,...)\
            case token::TOKEN: return true;
            app_gpuc_token_typename(app_gpuc_is_typename)
            #undef app_gpuc_is_typename

            default: return false;
        }
    }

    inline bool is_reserved_word(const token t) {
        return is_keyword(t)
            or is_typename(t);
    }

    inline bool is_identifier_or_typename(const token t) {
        return t == token::IDENTIFIER
            or is_typename(t);
    }

    inline bool is_identifier_or_reserved_word(const token t) {
        return t == token::IDENTIFIER
            or is_reserved_word(t);
    }

    inline bool is_assignment_operator(const token t) {
        switch (t) {
            case token::LSHEQ: // <<=
            case token::RSHEQ: // <<=
            case token::ADDEQ: // +=
            case token::ANDEQ: // &=
            case token::DIVEQ: // /=
            case token::MODEQ: // %=
            case token::MULEQ: // *=
            case token::OREQ:  // |=
            case token::SUBEQ: // -=
            case token::XOREQ: // ^=
            case token::EQ:    // =
                return true;

            default: return false;
        }
    }

    inline bool is_equality_operator(const token t) {
        switch (t) {
            case token::EQEQ:  // ==
            case token::NOTEQ: // !=
                return true;

            default: return false;
        }
    }

    inline bool is_relational_operator(const token t) {
        switch (t) {
            case token::LT:   // <
            case token::LTEQ: // <=
            case token::GT:   // >
            case token::GTEQ: // >=
                return true;

            default: return false;
        }
    }

    inline bool is_shift_operator(const token t) {
        switch (t) {
            case token::LSH: // <<
            case token::RSH: // >>
                return true;

            default: return false;
        }
    }

    inline bool is_sum_operator(const token t) {
        switch (t) {
            case token::ADD: // +
            case token::SUB: // -
                return true;

            default: return false;
        }
    }

    inline bool is_product_operator(const token t) {
        switch (t) {
            case token::DIV: // /
            case token::MOD: // %
            case token::MUL: // *
                return true;

            default: return false;
        }
    }

    inline bool is_prefix_operator(const token t) {
        switch (t) {
            case token::INC:    // ++
            case token::DEC:    // --
            case token::ADD:    // +
            case token::SUB:    // -
            case token::NOT:    // !
            case token::TILDE:  // ~
                return true;

            default: return false;
        }
    }

    inline bool is_postfix_operator(const token t) {
        switch (t) {
            case token::INC: // ++
            case token::DEC: // --
                return true;

            default: return false;
        }
    }

    inline bool is_literal(const token t) {
        switch (t) {
            case token::DOUBLE_LITERAL:
            case token::FALSE_LITERAL:
            case token::FLOAT_LITERAL:
            case token::INT_LITERAL:
            case token::TRUE_LITERAL:
            case token::UINT_LITERAL:
                return true;

            default: return false;
        }
    }

} // namespace app::gpuc