#include "TokenBuffer.hpp"

void TokenBuffer::setPosition(size_t position)
{
    current.position = position;
}

void TokenBuffer::setLength(size_t length)
{
    current.length = length;
}

void TokenBuffer::setType(Token type)
{
    current.type = type;
}

void TokenBuffer::push()
{
    tokens.push_back(current);
}

std::string TokenBuffer::substring(size_t i, std::string *source)
{
    size_t position = tokens[i].position;
    size_t length = tokens[i].length;

    return source->substr(position, length);
}

void TokenBuffer::debug(std::string *source)
{
    for (size_t i = 0; i < tokens.size(); i++) {
        std::cout << i << "\t (" << (int) tokens[i].type << ")" << "\t: [ " << substring(i, source) << " ]" << std::endl;
    }
}

size_t TokenBuffer::getCurrentIndex()
{
    return tokens.size() - 1;
}

size_t TokenBuffer::size()
{
    return tokens.size();
}

TokenIndex &TokenBuffer::at(size_t index)
{
    return tokens.at(index);
}
