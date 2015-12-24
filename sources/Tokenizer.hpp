#ifndef SLAN2_TOKENIZER_H
#define SLAN2_TOKENIZER_H

#include <string>
#include <memory>

#include "TokenBuffer.hpp"
#include "Types.hpp"
#include "TokenParsers.hpp"

/**
 * Data that the parser should return as result from a parse.
 */
struct ParserData
{
    std::string *source;
    size_t cursor;

    size_t offsetStart = 0;
    size_t offsetStop = 0;
    size_t length = 1;
    Token type = Token::NONE;
};

/**
 * One parser registry.
 */
struct TokenParser
{
    const char c;
    std::function<bool (ParserData &data)> parser;
};

class Tokenizer
{
private:
    std::shared_ptr<std::string> source;
    std::vector<TokenParser> parsers;
    TokenBuffer buffer;
    size_t cursor;

public:
    Tokenizer(std::string source);

    void registerToken(const char c, bool (*parser) (ParserData &data));
    void registerToken(const char c, std::function<bool (ParserData &data)> parser);

    void process();
    void parseToken(char &c);
    void parseKeyword(char &c, ParserData &data);
    bool testParsers(char &c, ParserData &data);
};


#endif //SLAN2_TOKENIZER_H
