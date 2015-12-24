#ifndef SLAN2_TOKENBUFFER_H
#define SLAN2_TOKENBUFFER_H

#include <stddef.h>
#include <vector>
#include <string>
#include <iostream>

#include "Types.hpp"

struct TokenIndex
{
    size_t position;
    size_t length;
    Token type;
};

class TokenBuffer
{
private:
    std::vector<TokenIndex> tokens;
    TokenIndex current;

public:
    void setPosition(size_t position);
    void setLength(size_t length);
    void setType(Token type);

    void push();
    std::string substring(size_t i, std::string *code);
    void debug(std::string *code);
    size_t getCurrentIndex();
};


#endif //SLAN2_TOKENBUFFER_H
