#include "Lexer.hpp"

Lexer::Lexer(std::shared_ptr<std::string> source) :
        source(source),
        cursor(0),
        buffer(std::make_shared<TokenBuffer>())
{
    // keywords.
    registerKeyword("class", Token::KW_CLASS);
    registerKeyword("module", Token::KW_MODULE);
    registerKeyword("import", Token::KW_IMPORT);
    registerKeyword("annotation", Token::KW_ANNOTATION);
    registerKeyword("annotation", Token::KW_ANNOTATION);
    registerKeyword("bool", Token::KW_BOOL);
    registerKeyword("char", Token::KW_CHAR);
    registerKeyword("double", Token::KW_DOUBLE);
    registerKeyword("false", Token::KW_FALSE);
    registerKeyword("float", Token::KW_FLOAT);
    registerKeyword("int", Token::KW_INT);
    registerKeyword("new", Token::KW_NEW);
    registerKeyword("null", Token::KW_NULL);
    registerKeyword("return", Token::KW_RETURN);
    registerKeyword("string", Token::KW_STRING);
    registerKeyword("static", Token::KW_STATIC);
    registerKeyword("true", Token::KW_TRUE);
    registerKeyword("void", Token::KW_VOID);
    registerKeyword("unsigned", Token::KW_UNSIGNED);

    // start/stop carets.
    registerToken('[', TokenParsers::symbol(Token::BRACKET_START));
    registerToken(']', TokenParsers::symbol(Token::BRACKET_STOP));
    registerToken('(', TokenParsers::symbol(Token::PARENTHESIS_START));
    registerToken(')', TokenParsers::symbol(Token::PARENTHESIS_STOP));
    registerToken('{', TokenParsers::symbol(Token::CURLY_BRACE_START));
    registerToken('}', TokenParsers::symbol(Token::CURLY_BRACE_STOP));

    // punctuation.
    registerToken(':', TokenParsers::symbol(Token::COLON));
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

void Lexer::registerToken(const char c, bool (*parser) (ParserData &data))
{
    parsers.push_back(TokenParser{c, parser});
}

void Lexer::registerToken(const char c, std::function<bool (ParserData &data)> parser)
{
    parsers.push_back(TokenParser{c, parser});
}

void Lexer::registerKeyword(std::string keyword, Token token)
{
    ParserData data;

    data.length = keyword.size();
    data.type = token;

    keywords[keyword] = data;
}

void Lexer::process()
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

    buffer->debug(&*source);
}

void Lexer::parseToken(char &c)
{
    ParserData data;
    data.source = &*source;
    data.cursor = cursor;

    if (!testParsers(c, data)) {
        // if the character could not be parsed, then this is a keyword.
        parseKeyword(c, data);
    }

    // set values to the buffer.
    buffer->setPosition(cursor + data.offsetStart);
    buffer->setLength(data.length);
    buffer->setType(data.type);

    // just for debugging.
    if (data.type != Token::WHITESPACE) {
        // push data as a token index.
        buffer->push();
    }

    cursor += data.length + data.offsetStart + data.offsetStop;
}

bool Lexer::testParsers(char &c, ParserData &data)
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

void Lexer::parseKeyword(char &c, ParserData &data)
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
            case ':':
            case '\n':
                finish = true;
                break;
            default:
                tempPosition++;
        }
    }

    // set the length as the difference.
    data.length = tempPosition - data.cursor;

    auto registry = keywords[data.source->substr(data.cursor, data.length)];

    if (registry.type != Token::NONE) {
        data.type = registry.type;
    } else {
        data.type = Token::KEYWORD;
    }
}

std::shared_ptr<TokenBuffer> &Lexer::getTokens()
{
    return buffer;
}
