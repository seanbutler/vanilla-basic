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

namespace tokenizer 
{

    void tokenize_identifier(const std::string & inputString,
                                unsigned int & currentPosition,
                                std::vector<Token> & tokens) 
    {
        char currentChar = inputString[currentPosition];
            
        std::string whole_string;
        
        while (currentChar == '_' || isalnum(currentChar)) 
        {
            whole_string += currentChar;

            currentPosition++;
            currentChar = inputString[currentPosition];
        }

        Token new_token;
        new_token.type = Token::TokenTypeEnum::IDENTIFIER;
        new_token.string = whole_string;
        tokens.push_back(new_token);
    }

    // --------------------------------------------------

    std::map<std::string, Token::TokenEnum> keywords =
    {   
        { "let",        Token::TokenEnum::TOK_LET      },
        { "dim",        Token::TokenEnum::TOK_DIM      },

        { "if",         Token::TokenEnum::TOK_IF       },
        { "then",       Token::TokenEnum::TOK_THEN     },

        { "for",        Token::TokenEnum::TOK_FOR      },
        { "to",         Token::TokenEnum::TOK_TO       },
        { "next",       Token::TokenEnum::TOK_NEXT     },

        { "while",      Token::TokenEnum::TOK_WHILE    },
        { "wend",       Token::TokenEnum::TOK_ENDWHILE },

        { "input",      Token::TokenEnum::TOK_INPUT    },
        { "print",      Token::TokenEnum::TOK_PRINT    },

        { "goto",       Token::TokenEnum::TOK_GOTO     },
        { "gosub",      Token::TokenEnum::TOK_GOSUB    },
        { "return",     Token::TokenEnum::TOK_RETURN   },
        { "rem",        Token::TokenEnum::TOK_REM      }
    };

    bool tokenize_keyword(const std::string & inputString,
                        unsigned int & currentPosition,
                        std::vector<Token> & tokens ) 
    {
        char currentChar = inputString[currentPosition];
        currentPosition++;
        std::string whole_string = "";

        while (isalpha(currentChar))
        {
            whole_string += currentChar;
            currentChar = inputString[currentPosition++];
        }
        --currentPosition;

        for ( auto K : tokenizer::keywords ) 
        {
            if ( K.first == whole_string ) 
            {
                Token new_token;
                new_token.type = Token::TokenTypeEnum::KEYWORD;
                new_token.token = K.second;
                new_token.string = whole_string;
                tokens.push_back(new_token);
                // break;
                return true;
            }
        }
        return false;
    }
 
    // --------------------------------------------------

    std::map<std::string, Token::SymbolEnum> symbols = 
    {   
        { "?", Token::SymbolEnum::TOK_UNKNOWN       },
        { "=", Token::SymbolEnum::TOK_EQUALS        },
        { "+", Token::SymbolEnum::TOK_ADD         },
        { "-", Token::SymbolEnum::TOK_SUB         },
        { "*", Token::SymbolEnum::TOK_MUL         },
        { "/", Token::SymbolEnum::TOK_DIV         },
        { "(", Token::SymbolEnum::TOK_LPAREN        },
        { ")", Token::SymbolEnum::TOK_RPAREN        },
        { ">", Token::SymbolEnum::TOK_GREATERTHAN   },
        { "<", Token::SymbolEnum::TOK_LESSTHAN      },
        { ">=", Token::SymbolEnum::TOK_GREATERTHANEQUAL  },
        { "<=", Token::SymbolEnum::TOK_LESSTHANEQUAL     },
        { "!=", Token::SymbolEnum::TOK_NOTEQUAL     },
        { "[", Token::SymbolEnum::TOK_LBRACKET      },
        { "]", Token::SymbolEnum::TOK_RBRACKET      },
    };

    // --------------------------------------------------

    bool tokenize_symbol(const std::string & inputString,
                        unsigned int & currentPosition,
                        std::vector<Token> & tokens ) 
    {
        char currentChar = inputString[currentPosition];
        currentPosition++;
        std::string whole_string = "";

        while (currentChar == '=' || ispunct(currentChar))
        {
            whole_string += currentChar;
            currentChar = inputString[currentPosition++];
        }
        --currentPosition;

        for ( auto K : tokenizer::symbols ) 
        {
            if ( K.first == whole_string ) 
            {
                Token new_token;
                new_token.type = Token::TokenTypeEnum::SYMBOL;
                new_token.symbol = K.second;
                new_token.string = whole_string;
                tokens.push_back(new_token);
                return true;
                // break;
            }
        }
        return false;
    }
 
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
                        std::vector<Token> & tokens) 
    {
        unsigned int currentPosition = 0;
        char currentChar;

        currentChar = inputString[currentPosition];
        const unsigned int len = inputString.length();

        while ( currentPosition < len ) 
        {
            currentChar = inputString[currentPosition];
            
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
            else if ( currentChar == '=' || ispunct(currentChar))            
            {
                //
                // its punctuation, so probably a symbol of some kind, like an operator or bracket 
                //
                tokenize_symbol(inputString, currentPosition, tokens);
            }
            else if ( isalpha(currentChar))
            {
                int tmpCurrentPosition = currentPosition;
                if ( ! tokenize_keyword(inputString, currentPosition, tokens) )
                {
                    currentPosition = tmpCurrentPosition;
                    tokenize_identifier(inputString, currentPosition, tokens);
                }
            }
            currentPosition+=1;

        }
    }

    // --------------------------------------------------

}