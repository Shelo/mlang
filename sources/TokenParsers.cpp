#include "TokenParsers.hpp"

bool TokenParsers::whitespace(ParserData &data)
{
    size_t tempPosition = data.cursor;

    bool finish = false;

    while (!finish && tempPosition < data.source->length()) {
        switch (data.source->at(tempPosition)) {
            case ' ':
            case '\t':
            case '\n':
                tempPosition++;
                break;
            default:
                finish = true;
                break;
        }
    }

    data.length = tempPosition - data.cursor;
    data.type = Token::WHITESPACE;

    return true;
}

bool TokenParsers::string(ParserData &data)
{
    size_t tempPosition = data.cursor + 1;

    bool finish = false;

    // read until the next matching double-quote.
    while (!finish && tempPosition < data.source->length()) {
        switch (data.source->at(tempPosition)) {
            case '"':
                tempPosition++;
            case '\n':
                finish = true;
                break;
            default:
                tempPosition++;
        }
    }

    if (!finish) {
        return false;
    }

    data.type = Token::STRING;
    data.offsetStart = 1;
    data.offsetStop = 1;

    // set the length as the difference minus the two semi-colons.
    data.length = tempPosition - data.cursor - 2;

    return true;
}

bool TokenParsers::number(ParserData &data)
{
    size_t tempPosition = data.cursor;

    bool finish = false;

    while (!finish && tempPosition < data.source->length()) {
        switch (data.source->at(tempPosition)) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                tempPosition++;
                break;
            case 'f':
                if (tempPosition > data.cursor) {
                    tempPosition++;
                } else {
                    break;
                }
            default:
                finish = true;
                break;
        }
    }

    data.length = tempPosition - data.cursor;
    data.type = Token::NUMBER;

    return true;
}

std::function<bool (ParserData &data)> TokenParsers::symbol(Token type) {
    return [=](ParserData &data) {
        data.length = 1;
        data.type = type;

        return true;
    };
}

bool TokenParsers::character(ParserData &data)
{
    if (data.cursor + 2 < data.source->length()) {
        if (data.source->at(data.cursor + 2) == '\'') {
            data.type = Token::CHARACTER;
            data.offsetStart = 1;
            data.offsetStop = 1;
            data.length = 1;

            return true;
        } else if (data.source->at(data.cursor + 1) == '\'') {
            data.type = Token::CHARACTER;
            data.offsetStart = 1;
            data.offsetStop = 1;
            data.length = 0;

            return true;
        }

        return false;
    }

    return false;
}

bool TokenParsers::singleLineComment(ParserData &data)
{
    if (data.cursor + 1 < data.source->length() && data.source->at(data.cursor + 1) == '/') {
        size_t tempPosition = data.cursor;

        bool finish = false;

        while (!finish && tempPosition < data.source->length()) {
            switch (data.source->at(tempPosition)) {
                case '\n':
                    finish = true;
                    break;
                default:
                    tempPosition++;
            }
        }

        data.type = Token::SINGLE_LINE_COMMENT;
        data.length = tempPosition - data.cursor;

        return true;
    }

    return false;
}
