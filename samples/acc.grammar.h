#define RULE(...)
#define EXP_RULE(...)
#define KEY_RULE(...)
#define DEF_RULE(...)

//==============================================================================

KEY_RULE(translation_unit,
    *(struct_definition
     |uniform_definition
     |function_declaration
     |function_definition)
)

RULE(keyword, KEYWORDS-KEYWORDS_END)

// punctuation =================================================================

RULE(comma, COMMA)
RULE(lbrack, LBRACK)
RULE(rbrack, RBRACK)
RULE(lparen, LPAREN)
RULE(rparen, RPAREN)

// definitions =================================================================

DEF_RULE(struct_definition,
    STRUCT,
    (struct_name|"expected struct name"),
    SCOPE(
        (LBRACE|"expected '{'"),
        struct_members,
    ),
    (RBRACE|"expected '}'"),
    (+SEMICOLON|"expected ';'")
)
KEY_RULE(struct_name, IDENTIFIER|(keyword&"invalid struct name"))
KEY_RULE(struct_members,
    *member_definition,
)
DEF_RULE(member_definition,
    member_type,
    (member_name|"expected member name"),
    (+SEMICOLON|"expected ';'")
)
KEY_RULE(member_type, IDENTIFIER|VOID-MAT4X4|(keyword&"invalid type name"))
KEY_RULE(member_name, IDENTIFIER|(keyword&"invalid member name"))

//------------------------------------------------------------------------------

DEF_RULE(function_declaration,
    function_return_type,
    function_name,
    SCOPE(
        lparen,
        function_parameters,
        (rparen|"expected ')'"),
        +SEMICOLON,
    ),
)

DEF_RULE(function_definition,
    function_return_type,
    function_name,
    SCOPE(
        lparen,
        function_parameters,
        (rparen|"expected ')'"),
        (&LBRACE|"expected ';' or '{'"),
        function_body,
    ),
    *SEMICOLON
)

KEY_RULE(function_return_type,
    IDENTIFIER|VOID-MAT4X4|(keyword&"invalid type name")
)
KEY_RULE(function_name,
    IDENTIFIER|(keyword&"invalid function name")
)

KEY_RULE(function_parameters,
    ~(
        parameter_definition,
        *(comma,parameter_definition|"expected parameter")
    ),
)
DEF_RULE(parameter_definition,
    parameter_type,
    ~parameter_name
)
KEY_RULE(parameter_type,
    IDENTIFIER|VOID-MAT4X4|(keyword&"invalid type name")
)
KEY_RULE(parameter_name,
    IDENTIFIER|(keyword&"invalid parameter name")
)

KEY_RULE(function_body,
    LBRACE,
    *statement,
    (RBRACE|"expected '}'"),
)

//------------------------------------------------------------------------------

DEF_RULE(uniform_definition,
    UNIFORM,
    (uniform_type|"expected type name"),
    (uniform_name|"expected uniform name"),
    (+SEMICOLON|"expected ';'")
)
KEY_RULE(uniform_type, IDENTIFIER|VOID-MAT4X4|(keyword&"invalid type name"))
KEY_RULE(uniform_name, IDENTIFIER|(keyword&"invalid uniform name"))

//------------------------------------------------------------------------------

DEF_RULE(variable_definition,
    variable_type,
    variable_name,
    ~variable_initializer
)
KEY_RULE(variable_type,
    IDENTIFIER|VOID-MAT4X4|(keyword&"invalid type name")
)
KEY_RULE(variable_name,
    IDENTIFIER|(keyword&"invalid variable name")
)
KEY_RULE(variable_initializer,
    EQ,expression|"expected expression"
)

// statements ==================================================================

RULE(statement,
    if_statement
    |switch_statement
    |while_statement
    |do_statement
    |for_statement
    |goto_statement
    |continue_statement
    |break_statement
    |return_statement
    |compound_statement
    |variable_statement
    |expression_statement
)

//------------------------------------------------------------------------------

KEY_RULE(if_statement,
    IF,
    SCOPE(
        if_condition,
        if_body,
    )
)
KEY_RULE(if_condition,
    (lparen|"expected '('"),
    (expression|"expected expression"),
    (rparen|"expected ')'"),
)
KEY_RULE(if_body,
    (LBRACE,*statement,(RBRACE|"expected '}'"),*SEMICOLON)
    |statement
    |"expected statement"
)

//------------------------------------------------------------------------------

KEY_RULE(switch_statement,
    SWITCH,
    SCOPE(
        switch_condition,
        switch_body
    )
)
KEY_RULE(switch_condition,
    (lparen|"expected '('"),
    (expression|"expected expression"),
    (rparen|"expected ')'"),
)
KEY_RULE(switch_body,
    (LBRACE,*statement,(RBRACE|"expected '}'"),*SEMICOLON)
    |statement
    |"expected statement"
)

//------------------------------------------------------------------------------

KEY_RULE(while_statement,
    WHILE,
    SCOPE(
        while_condition,
        while_body,
    )
)
KEY_RULE(while_condition,
    (lparen|"expected '('"),
    (expression|"expected expression"),
    (rparen|"expected ')'"),
)
KEY_RULE(while_body,
    (LBRACE,*statement,(RBRACE|"expected '}'"),*SEMICOLON)
    |statement
    |"expected statement"
)

//------------------------------------------------------------------------------

KEY_RULE(do_statement,
    DO,
    SCOPE(
        do_body,
    ),
    do_condition,
    (+SEMICOLON|"expected ';'")
)
KEY_RULE(do_condition,
    (WHILE|"expected 'while'"),
    (lparen|"expected '('"),
    (expression|"expected expression"),
    (rparen|"expected ')'"),
)
KEY_RULE(do_body,
    (LBRACE,*statement,(RBRACE|"expected '}'"),*SEMICOLON)
    |statement
    |"expected statement"
)

//------------------------------------------------------------------------------

KEY_RULE(for_statement,
    FOR,
    SCOPE(
        for_parameters,
        for_body,
    )
)
KEY_RULE(for_parameters,
    (lparen|"expected '('"),
    for_variables,(SEMICOLON|"expected ';'"),
    for_condition,(SEMICOLON|"expected ';'"),
    for_increment,
    (rparen|"expected ')'"),
)
KEY_RULE(for_variables, ~variable_definition)
KEY_RULE(for_condition, ~expression)
KEY_RULE(for_increment, ~expression)
KEY_RULE(for_body,
    (LBRACE,*statement,(RBRACE|"expected '}'"),*SEMICOLON)
    |statement
    |"expected statement"
)

//------------------------------------------------------------------------------

KEY_RULE(goto_statement,
    GOTO,
    (goto_label|"expected label name"),
    (+SEMICOLON|"expected ';'")
)
KEY_RULE(goto_label, IDENTIFIER|(keyword&"invalid label name"))

//------------------------------------------------------------------------------

KEY_RULE(continue_statement,
    CONTINUE,
    (+SEMICOLON|"expected ';'")
)

//------------------------------------------------------------------------------

KEY_RULE(break_statement,
    BREAK,
    (+SEMICOLON|"expected ';'")
)

//------------------------------------------------------------------------------

KEY_RULE(return_statement,
    RETURN,
    ~return_expression,
    (+SEMICOLON|"expected ';'")
)
KEY_RULE(return_expression, expression)

//------------------------------------------------------------------------------

KEY_RULE(compound_statement,
    SCOPE(LBRACE,*statement,(RBRACE|"expected '}'"),*SEMICOLON)
)

//------------------------------------------------------------------------------

KEY_RULE(variable_statement,
    variable_definition,
    (+SEMICOLON|"expected ';'")
)

//------------------------------------------------------------------------------

KEY_RULE(expression_statement,
    expression,
    (+SEMICOLON|"expected ';'")
)

// expressions =================================================================

RULE(expression, assignment_expression|ternary_expression)

RULE(primary_expression,
    symbol_identifier
    |bool_literal
    |int_literal
    |uint_literal
    |float_literal
    |double_literal
    |char_literal
    |string_literal
    |nested_expression
)

EXP_RULE(symbol_identifier, IDENTIFIER|(keyword&"invalid identifier"))
EXP_RULE(bool_literal,      TRUE|FALSE)
EXP_RULE(int_literal,       INT_LITERAL)
EXP_RULE(uint_literal,      UINT_LITERAL)
EXP_RULE(float_literal,     FLOAT_LITERAL)
EXP_RULE(double_literal,    DOUBLE_LITERAL)
EXP_RULE(char_literal,      CHAR_LITERAL)
EXP_RULE(string_literal,    STRING_LITERAL)
EXP_RULE(nested_expression,
    lparen,(expression|"expected expression"),(rparen|"expected ')'")
)

// operators in precedence order -----------------------------------------------

EXP_RULE(postfix_expression,
    primary_expression,
    *postfix_operator
)
RULE(postfix_operator, INC|DEC)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(invocation_expression,
    function_name, // could be a function or a constructor
    invocation_argument_list,
)
KEY_RULE(invocation_argument_list,
    lparen,
    ~(function_argument,*(comma,function_argument|"expected expression")),
    (rparen|"expected ')'")
)
KEY_RULE(function_argument, assignment_expression|ternary_expression)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(subscript_expression,
    (invocation_expression|postfix_expression),
    *subscript_operator
)
RULE(subscript_operator,
    lbrack,(expression|"expected expression"),(rbrack|"expected ']'")
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(member_ref, IDENTIFIER|(keyword&"invalid identifier"))

EXP_RULE(member_postfix_expression,
    member_ref,
    *postfix_operator
)

EXP_RULE(member_subscript_expression,
    member_postfix_expression,
    *subscript_operator
)

EXP_RULE(member_submember_expression,
    member_subscript_expression,
    ~(member_operator,(member_submember_expression|"expected member name"))
)

EXP_RULE(member_expression,
    subscript_expression,
    ~(member_operator,(member_submember_expression|"expected member name"))
)
RULE(member_operator, DOT|(ARROW&"invalid indirection"))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(prefix_expression,
    (prefix_operator,prefix_expression)
    |member_expression
)
RULE(prefix_operator, INC|DEC|ADD|SUB|NOT|TILDE|MUL|AND)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(product_expression,
    prefix_expression,
    ~(product_operator,product_expression|"expected expression")
)
RULE(product_operator, MUL|DIV|MOD)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(sum_expression,
    product_expression,
    ~(sum_operator,sum_expression|"expected expression")
)
RULE(sum_operator, ADD|SUB)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(shift_expression,
    sum_expression,
    ~(shift_operator,shift_expression|"expected expression")
)
RULE(shift_operator, LSH|RSH)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(relational_expression,
    shift_expression,
    ~(relational_operator,relational_expression|"expected expression")
)
RULE(relational_operator, LT|LTEQ|GT|GTEQ)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(equality_expression,
    relational_expression,
    ~(equality_operator,equality_expression|"expected expression")
)
RULE(equality_operator, EQEQ|NOTEQ)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(bitwise_and_expression,
    equality_expression,
    ~(bitwise_and_operator,bitwise_and_expression|"expected expression")
)
RULE(bitwise_and_operator, AND)

EXP_RULE(bitwise_xor_expression,
    bitwise_and_expression,
    ~(bitwise_xor_operator,bitwise_xor_expression|"expected expression")
)
RULE(bitwise_xor_operator, XOR)

EXP_RULE(bitwise_or_expression,
    bitwise_xor_expression,
    ~(bitwise_or_operator,bitwise_or_expression|"expected expression")
)
RULE(bitwise_or_operator, OR)

EXP_RULE(logical_and_expression,
    bitwise_or_expression,
    ~(logical_and_operator,logical_and_expression|"expected expression")
)
RULE(logical_and_operator, ANDAND)

EXP_RULE(logical_or_expression,
    logical_and_expression,
    ~(logical_or_operator,logical_or_expression|"expected expression")
)
RULE(logical_or_operator, OROR)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(assignment_expression,
    assignment_target,assignment_operator,assignment_source
)
KEY_RULE(assignment_target, prefix_expression)
RULE(assignment_operator,
     EQ|ADDEQ|SUBEQ|MULEQ|DIVEQ|MODEQ|LSHEQ|RSHEQ|ANDEQ|XOREQ|OREQ
)
KEY_RULE(assignment_source, (expression|"expected expression"))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EXP_RULE(ternary_expression,
    logical_or_expression,
    ~(QUESTION,
        (logical_or_expression|"expected expression"),
        (COLON|"expected ':'"),
        (logical_or_expression|"expected expression"))
)

//------------------------------------------------------------------------------

#undef RULE
#undef EXP_RULE
#undef KEY_RULE
#undef DEF_RULE
