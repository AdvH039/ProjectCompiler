
#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <regex>


//variables
constexpr auto EMPTY = "";
// regular expression for token identification
const std::regex IS_NOUN("^[A-Z][a-zA-Z]*$");
const std::regex IS_VERB("\\b\\w*\\d\\w*\\b");
const std::regex IS_ADWORD("^[a-z]+$");
const std::regex IS_PUNC("^[.?!]$");

/* global variables for coordinates of current character
 * useful for error logging
*/
inline int line_count=1;
inline int word_count=1;


enum TOKEN_TYPE
{

	Noun,
	Verb,
	Adword,
	Punc,
	Eof
    
};
enum TOKEN_SUB_TYPE
{
    Subject,
    Object,
    Adverb,
    Adjective,
    Q_mark,
    P_mark,
    Period,
    Undef



};
/* takes enum token type as argument and 
    returns corresponding string. */
inline std::string Token_type(enum TOKEN_TYPE tt)
{
    if (tt == TOKEN_TYPE::Noun)
    {
        return "Noun";
    }
    else if (tt == TOKEN_TYPE::Adword)
    {
        return "Adword";
    }
    else if (tt == TOKEN_TYPE::Verb)
    {
        return "Verb";
    }
    else if (tt == TOKEN_TYPE::Punc)
    {
        return "Punc";
    }
    else
    {
        return "Eof";
    }



}
/* takes enum token sub type as argument and
    returns corresponding string. */
inline std::string Token_sub_type(enum TOKEN_SUB_TYPE tst)
{
    if (tst == TOKEN_SUB_TYPE::Subject)
    {
        return "Subject";
    }
    else if (tst == TOKEN_SUB_TYPE::Object)
    {
        return "Object";
    }
    else if (tst == TOKEN_SUB_TYPE::Adjective)
    {
        return "Adjective";
    }
    else if (tst == TOKEN_SUB_TYPE::Adverb)
    {
        return "Adverb";
    }
    else if (tst == TOKEN_SUB_TYPE::P_mark)
    {
        return "Punctuation Mark";
    }
    else if (tst == TOKEN_SUB_TYPE::Q_mark)
    {
        return "Question Mark";
    }
    else if (tst == TOKEN_SUB_TYPE::Period)
    {
        return "Period";
    }
    else
    {
        return "Undef";
    }



}
class Token
{
public:
    Token(TOKEN_TYPE t, TOKEN_SUB_TYPE ts) : type(t), sub_type(ts)
    {
    }
    Token()
    {

    }
    TOKEN_TYPE type;
    TOKEN_SUB_TYPE sub_type;
    
};

//global variables
 inline std::string str;
 inline std::optional<Token> current_token;






    class Tokenizer {
    private:
        std::string m_src;
        size_t m_index;
        bool cont;
        char ch;
        
        
        
        
        /*when offset is zero--->look at current character.
        when offset is non zero say x ---> look x steps ahead of the current character.
         when offset is -x ---> look -1 steps behind the current character.
         */
        std::optional<char> peek(int offset = 0)
        {
            if (m_index + offset >= m_src.length()) {
                return {};
            }
            else {
                return m_src.at(m_index + offset);
            }
        }
        
    
    
    public:
        void next_token()
        {
            
            str = "";
            cont = peek().has_value();
            if (cont) /*ignore whitespaces, keep track of ln and ch coordinates, terminate loop when EOF
                        encountered.
                */
            {
                while (cont)
                {
                    ch = *peek();
                    
                    
                    
                    if (!std::isspace(*peek()))
                    {
                        break;
                    }
                    if (peek(-1).has_value())
                    {
                        if (*peek(-1) == '\n')
                        {
                            line_count += 1;
                            word_count = 0;
                        }
                    }
                    word_count += 1;
                    m_index++;
                    cont = peek().has_value();
                    
                }
                
            }
            if (cont) {

                while (cont)/* add non-space characters to string , keep track of ln and ch coordinates, terminate loop when EOF
                        encountered.
                */
                {
                    ch = *peek();
                   
                    
                    

                    if (!std::isspace(ch))
                    {
                        if (peek(-1).has_value())
                        {
                            if (*peek(-1) == '\n')
                            {
                                line_count += 1;
                                word_count = 0;
                            }
                        }

                        word_count += 1;
                        str += ch;
                        m_index++;
                        cont = peek().has_value();
                        
                    }
                    else
                    {
                        break;
                    }

                }

            }
            /*
             compare token with each regular expression.
             return the corresponding token if match successful.
             return EOF token if EOF is found.
             return {} if the token is not lexically valid. For this we use the optional library.
            
            */
           
           if (!cont && str==EMPTY)
           {
               
                current_token=Token(TOKEN_TYPE::Eof,TOKEN_SUB_TYPE:: Undef);
                

            }
            else if (std::regex_match(str, IS_VERB))
            {
               current_token = Token(TOKEN_TYPE::Verb, TOKEN_SUB_TYPE::Undef);
                
            }
            else if (std::regex_match(str, IS_ADWORD))
            {
                current_token=Token(TOKEN_TYPE::Adword, TOKEN_SUB_TYPE::Undef);
                
            }
            else if (std::regex_match(str, IS_PUNC))
            {
               

                current_token= Token(TOKEN_TYPE::Punc, TOKEN_SUB_TYPE::Undef);
                if (str == "!")
                {
                    (*current_token).sub_type = TOKEN_SUB_TYPE::P_mark;
                }
                else if (str == "?")
                {
                    (*current_token).sub_type = TOKEN_SUB_TYPE::Q_mark;
                }
                else
                {
                    (*current_token).sub_type = TOKEN_SUB_TYPE::Period;
                }
                

            }
            else if (std::regex_match(str, IS_NOUN)) //end of string
            {
                 current_token= Token(TOKEN_TYPE::Noun, TOKEN_SUB_TYPE::Undef);
                

            }
            else {

                current_token= {};
            }


        }

        inline explicit Tokenizer(std::string src)
            : m_src(std::move(src))// change the ownership of src
        {

            //unecessary initialisations to avoid warnings
            ch = ' ';
            cont = true;
            m_index = 0;
        }




    };








