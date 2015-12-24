#ifndef SLAN2_TYPES_H
#define SLAN2_TYPES_H

enum class Token : int
{
    NONE,
    KEYWORD,
    SEMI_COLON,
    STRING,
    COMMA,
    WHITESPACE,
    NUMBER,
    EQUALS,
    DOT,
    CHARACTER,
    EXCLAMATION_MARK,
    QUESTION_MARK,

    // start/stop carets.
    PARENTHESIS_START,
    PARENTHESIS_STOP,
    CURLY_BRACE_START,
    CURLY_BRACE_STOP,
    BRACKET_START,
    BRACKET_STOP,

    // Keywords
    KW_FALSE,
    KW_TRUE,
    KW_IMPORT,
    KW_NEW,
    KW_NULL,
    KW_CHAR,
    KW_VOID,
    KW_INT,
    KW_FLOAT,
    KW_STRING,
    KW_BOOL,
    KW_CLASS,
    KW_ANNOTATION,
    KW_RETURN,
    KW_UNSIGNED,
    SINGLE_LINE_COMMENT,
    PLUS,
    MINUS,
    SHARP
};

#endif //SLAN2_TYPES_H
