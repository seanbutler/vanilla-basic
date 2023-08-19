//
// tokenizer.hpp
//

// --------------------------------------------------

#include "token.hpp"

// --------------------------------------------------

#include <cstdlib>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// --------------------------------------------------

namespace tokenizer {

    // --------------------------------------------------

    void tokenize_string(const std::string & inputString,
                        unsigned int & currentPosition,
                        std::vector<Token> & tokens) 
    {
        char currentChar = inputString[currentPosition];
        
        if (currentChar=='\"')
            currentPosition++; // skip the leading quote character
    
        currentChar = inputString[currentPosition];
        currentPosition++;

        std::string whole_string = "";
        
        while ( currentChar != '\"') 
        {
            whole_string += currentChar;
            
            currentChar = inputString[currentPosition];
            currentPosition++;
        }

        --currentPosition;

        Token new_token;
        new_token.type = Token::TokenTypeEnum::STRING;
        new_token.string = whole_string;

        tokens.push_back(new_token);
    }
 
    // --------------------------------------------------

    void tokenize_number(const std::string & inputString,
                        unsigned int & currentPosition,
                        std::vector<Token> & tokens) 
    {
        char currentChar = inputString[currentPosition];
        currentPosition++;
        std::string whole_float_string = "";

        while ( isdigit(currentChar) ) 
        {
            whole_float_string += currentChar;
            currentChar = inputString[currentPosition++];
        }
        --currentPosition;

        Token new_token;
        new_token.type = Token::TokenTypeEnum::NUMBER;

        if ( currentChar == '.' ){
            currentPosition++;
            currentChar = inputString[currentPosition];

            whole_float_string += ".";
            while ( isdigit(currentChar) ) 
            {
                whole_float_string += currentChar;
                currentPosition++;
                currentChar = inputString[currentPosition];
            }
            --currentPosition;
        }

        new_token.number = std::stod(whole_float_string);

        tokens.push_back(new_token);
    }

    // --------------------------------------------------

    void tokenize_line(const std::string & inputString,
                        std::vector<Token> & tokens) {

        unsigned int currentPosition = 0;
        char currentChar;

        currentChar = inputString[currentPosition];
        const unsigned int len = inputString.length();

        while ( currentPosition < len ) 
        {
            //
            // skip whitespace
            //
            while (currentChar == ' ' || currentChar == '\t' ) {
                currentChar = inputString[currentPosition++];
            }

            //
            // exit on carriage return
            //
            if ( currentChar == '\n' ) {
                break;
            }
            else if ( isdigit(currentChar) )            
            {
                //
                // digit found, so probably number (all numbers are floats in our langauge, because hey 64 bits etc) 
                //
                tokenize_number(inputString, currentPosition, tokens);
            }
            else if ( currentChar == '\"')            
            {
                //
                // quote found, so probably a string 
                //
                tokenize_string(inputString, currentPosition, tokens);
            }
            
            currentPosition+=1;

        }
    }

    // --------------------------------------------------

}