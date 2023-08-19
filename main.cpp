
#include "scanner.hpp"
#include "tokeniser.hpp"

// --------------------------------------------------

#include <string>

// --------------------------------------------------

int main(int argc, char** argv) 
{
    std::string basic_text = scanner::load_file_to_string("../test.bas");

    std::vector<std::string> lines = scanner::split(basic_text, "\n");
    std::map<unsigned int, std::vector<Token>> file_tokens;
    std::vector<Token> line_tokens;

    for(auto current_line : lines ) {
        tokenizer::tokenize_line(current_line, line_tokens);
    }

    for(auto token : line_tokens ) {
        std::cout << token << std::endl;
    }
    
    return 0;
}

// --------------------------------------------------
