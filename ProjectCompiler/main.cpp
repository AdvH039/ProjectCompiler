
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>
#include<string>
#include "lexer.h"
#include "parser.h"
//#include "error.h"
extern Tokenizer token_generator;
extern int EOF_REACHED;
extern std::string Token_type(enum TOKEN_TYPE tt);
extern std::string Token_sub_type(enum TOKEN_SUB_TYPE tst);







int main(int argc, char* argv[])
{
   /* if (argc != 2) {
        std::cerr << "Incorrect usage." << std::endl;
        
        return EXIT_FAILURE;
    }*/

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input("sampleprogram.txt", std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
        


    }

    token_generator = Tokenizer(contents);
    token_generator.next_token();
    
    
    while (!EOF_REACHED)
    {
       
        Adjective1_node(current_token);
        
        
          
     }
    if (!symbol_table.empty())
    {
        std::cout << "List of all tokens, mentioning their types and subtypes in their respective first valid sentence." << std::endl;
        std::cout << "      Token Value         Token Type        Token Subtype      " << std::endl;

        for (auto const& [key, value] : symbol_table)
        {
            std::cout << "            " << key << "                  " << Token_type(value.type) << "                " << Token_sub_type( value.sub_type) << "\n";
        }
    }
    
   return EXIT_SUCCESS;
}