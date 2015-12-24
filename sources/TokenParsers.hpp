#ifndef SLAN2_TOKENPARSERS_H
#define SLAN2_TOKENPARSERS_H

#include "Tokenizer.hpp"
#include "Types.hpp"

struct ParserData;

class TokenParsers
{
public:
    static bool matchingParser(size_t cursor, std::string *code, const std::string &keyword, size_t length);

public:
    static bool whitespace(ParserData &data);

    static bool string(ParserData &data);
    static bool number(ParserData &data);
    static bool character(ParserData &data);
    static bool singleLineComment(ParserData &data);

    static std::function<bool (ParserData &data)> symbol(Token token);
    static std::function<bool (ParserData &data)> keyword(Token token, const std::string keyword);
};

#endif //SLAN2_TOKENPARSERS_H
