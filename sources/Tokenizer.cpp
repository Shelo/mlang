#include "Tokenizer.hpp"

Tokenizer::Tokenizer(std::string source) :
        source(std::shared_ptr<std::string>(&source)),
        cursor(0)
{
    // keywords.
    registerToken('a', TokenParsers::keyword(Token::KW_ANNOTATION, "annotation"));
    registerToken('b', TokenParsers::keyword(Token::KW_BOOL, "bool"));
    registerToken('c', TokenParsers::keyword(Token::KW_CHAR, "char"));
    registerToken('c', TokenParsers::keyword(Token::KW_CLASS, "class"));
    registerToken('d', TokenParsers::keyword(Token::KW_STRING, "double"));
    registerToken('f', TokenParsers::keyword(Token::KW_FALSE, "false"));
    registerToken('f', TokenParsers::keyword(Token::KW_FLOAT, "float"));
    registerToken('i', TokenParsers::keyword(Token::KW_IMPORT, "import"));
    registerToken('i', TokenParsers::keyword(Token::KW_INT, "int"));
    registerToken('n', TokenParsers::keyword(Token::KW_NEW, "new"));
    registerToken('n', TokenParsers::keyword(Token::KW_NULL, "null"));
    registerToken('r', TokenParsers::keyword(Token::KW_RETURN, "return"));
    registerToken('s', TokenParsers::keyword(Token::KW_STRING, "string"));
    registerToken('s', TokenParsers::keyword(Token::KW_STRING, "static"));
    registerToken('t', TokenParsers::keyword(Token::KW_TRUE, "true"));
    registerToken('v', TokenParsers::keyword(Token::KW_VOID, "void"));
    registerToken('u', TokenParsers::keyword(Token::KW_UNSIGNED, "unsigned"));

    // start/stop carets.
    registerToken('[', TokenParsers::symbol(Token::BRACKET_START));
    registerToken(']', TokenParsers::symbol(Token::BRACKET_STOP));
    registerToken('(', TokenParsers::symbol(Token::PARENTHESIS_START));
    registerToken(')', TokenParsers::symbol(Token::PARENTHESIS_STOP));
    registerToken('{', TokenParsers::symbol(Token::CURLY_BRACE_START));
    registerToken('}', TokenParsers::symbol(Token::CURLY_BRACE_STOP));

    // punctuation.
    registerToken(';', TokenParsers::symbol(Token::SEMI_COLON));
    registerToken(',', TokenParsers::symbol(Token::COMMA));
    registerToken('.', TokenParsers::symbol(Token::DOT));
    registerToken('=', TokenParsers::symbol(Token::EQUALS));
    registerToken('!', TokenParsers::symbol(Token::EXCLAMATION_MARK));
    registerToken('?', TokenParsers::symbol(Token::QUESTION_MARK));
    registerToken('+', TokenParsers::symbol(Token::PLUS));
    registerToken('-', TokenParsers::symbol(Token::MINUS));
    registerToken('#', TokenParsers::symbol(Token::SHARP));

    // match.
    registerToken('"', TokenParsers::string);
    registerToken('\'', TokenParsers::character);
    registerToken('/', TokenParsers::singleLineComment);

    // whitespace.
    registerToken(' ', TokenParsers::whitespace);
    registerToken('\t', TokenParsers::whitespace);
    registerToken('\n', TokenParsers::whitespace);

    // numbers.
    registerToken('0', TokenParsers::number);
    registerToken('1', TokenParsers::number);
    registerToken('2', TokenParsers::number);
    registerToken('3', TokenParsers::number);
    registerToken('4', TokenParsers::number);
    registerToken('5', TokenParsers::number);
    registerToken('6', TokenParsers::number);
    registerToken('7', TokenParsers::number);
    registerToken('8', TokenParsers::number);
    registerToken('9', TokenParsers::number);
}

void Tokenizer::registerToken(const char c, bool (*parser)(ParserData &data))
{
    parsers.push_back(TokenParser{c, parser});
}

void Tokenizer::registerToken(const char c, std::function<bool (ParserData &data)> parser)
{
    parsers.push_back(TokenParser{c, parser});
}

void Tokenizer::process()
{
    while (cursor < source->length()) {
        size_t last = cursor;

        parseToken(source->at(cursor));

        // this should never happen with a well written file.
        if (last == cursor) {
            std::cerr << "Syntax error." << std::endl;
            break;
        }
    }

    buffer.debug(&*source);
}

void Tokenizer::parseToken(char &c)
{
    ParserData data;
    data.source = &*source;
    data.cursor = cursor;

    if (!testParsers(c, data)) {
        // if the character could not be parsed, then this is a keyword.
        parseKeyword(c, data);
    }

    // set values to the buffer.
    buffer.setPosition(cursor + data.offsetStart);
    buffer.setLength(data.length);
    buffer.setType(data.type);

    // just for debugging.
    if (data.type != Token::WHITESPACE) {
        // push data as a token index.
        buffer.push();
    }

    cursor += data.length + data.offsetStart + data.offsetStop;
}

bool Tokenizer::testParsers(char &c, ParserData &data)
{
    for (size_t i = 0; i < parsers.size(); ++i) {
        if (parsers[i].c == c) {
            if (parsers[i].parser(data)) {
                return true;
            }
        }
    }

    return false;
}

void Tokenizer::parseKeyword(char &c, ParserData &data)
{
    size_t tempPosition = data.cursor;

    bool finish = false;

    while (!finish && tempPosition < data.source->length()) {
        switch (data.source->at(tempPosition)) {
            case '(':
            case ' ':
            case ')':
            case ',':
            case '.':
            case ';':
            case '\n':
                finish = true;
                break;
            default:
                tempPosition++;
        }
    }

    data.type = Token::KEYWORD;

    // set the length as the difference.
    data.length = tempPosition - data.cursor;
}
