
#include "scanner.hpp"
#include "tokeniser.hpp"
#include "interpreter.hpp"

// --------------------------------------------------

#include <string>

// --------------------------------------------------

int main(int argc, char** argv) 
{
    std::string basic_text = scanner::load_file_to_string("../test.bas");

    std::vector<std::string> line_strings_vector = scanner::split(basic_text, "\n");

    std::map<unsigned int, std::vector<Token>> file_tokens;

    std::vector<Token> line_tokens;

    for(auto current_line_string : line_strings_vector ) {
        if ( tokenizer::tokenize_line(current_line_string, line_tokens) > 0 ) {
            file_tokens[line_tokens[0].number]=line_tokens;
            line_tokens.clear();
        }
    }

    for(auto line : file_tokens ) {
        std::cout << "line no : " << line.first << " -- ";

        for(auto token : line.second ) {
            std::cout << token << " ";
        }

        std::cout << std::endl;
    }


    struct Interpreter::Context execution_context;

    Interpreter::execute_token_vector_map(execution_context, file_tokens);
    
    return 0;
}

// --------------------------------------------------
