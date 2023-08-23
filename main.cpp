/*

MIT License

Copyright (c) 2023 sean butler

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

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
