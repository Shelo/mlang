#ifndef MLANG_PARSER_H
#define MLANG_PARSER_H


#include "TokenBuffer.hpp"

class Parser
{
private:
    std::shared_ptr<TokenBuffer> tokens;
    std::shared_ptr<TokenBuffer> buffer;
    size_t cursor;

public:
    Parser(std::shared_ptr<TokenBuffer> tokens);

    void process();

    void parseToken(TokenIndex &index);
};


#endif //MLANG_PARSER_H
