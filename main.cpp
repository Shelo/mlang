#include <iostream>
#include <fstream>
#include <sstream>

#include "Tokenizer.hpp"

int main(int argc, const char *argv[])
{
    if (argc == 2) {
        std::ifstream source(argv[1]);

        if (source) {
            std::stringstream codeStream;
            codeStream << source.rdbuf();
            source.close();

            auto code = std::make_shared<std::string>(codeStream.str());

            Tokenizer tokenizer(code);
            tokenizer.process();
        } else {
            std::cout << "No such file or directory." << std::endl;
        }

    } else {
        std::cout << "Needs an input file." << std::endl;
    }

    return 0;
}