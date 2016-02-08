#ifndef SLAN2_TOKENPARSERS_H
#define SLAN2_TOKENPARSERS_H

#include "Lexer.hpp"
#include "Types.hpp"

struct ParserData;

class TokenParsers
{
public:
    static bool whitespace(ParserData &data);

    static bool string(ParserData &data);
    static bool number(ParserData &data);
    static bool character(ParserData &data);
    static bool singleLineComment(ParserData &data);

    static std::function<bool (ParserData &data)> symbol(Token token);
};

#endif //SLAN2_TOKENPARSERS_H
