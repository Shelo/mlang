#include "Parser.h"

Parser::Parser(std::shared_ptr<TokenBuffer> tokens) :
        tokens(tokens)
{

}

void Parser::process()
{
    /*
    while (cursor < tokens->size()) {
        parseToken(tokens->at(cursor));
    }
     */
}

void Parser::parseToken(TokenIndex &index)
{

}
