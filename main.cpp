
#include "scanner.hpp"
#include "tokeniser.hpp"

// --------------------------------------------------

#include <string>

// --------------------------------------------------

int main(int argc, char** argv) 
{
    std::string basic_text = scanner::load_file_to_string("../test.bas");

    std::vector<std::string> line_strings_vector = scanner::split(basic_text, "\n");

    std::map<int, std::vector<Token>> file_tokens;

    std::vector<Token> line_tokens;

    for(auto current_line_string : line_strings_vector ) {
        if ( tokenizer::tokenize_line(current_line_string, line_tokens) ) {
            file_tokens[line_tokens[0].number]=line_tokens;
        }
        line_tokens.clear();
    }

    for(auto line : file_tokens ) {
        std::cout << "line: " << line.first << " : ";

        for(auto token : line.second ) {
            std::cout << token << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}

// --------------------------------------------------
