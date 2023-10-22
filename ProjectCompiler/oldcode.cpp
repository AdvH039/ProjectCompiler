/*

#pragma once
#include <unordered_set>
#include <string>
#include <optional>
#include <regex>
//variables
constexpr auto ONE_STEP = 1;
std::unordered_set<char> punc_set = { '!','?', '.' };

bool is_punc;
bool is_word;
bool is_f_ch_up;
bool num_pres;
bool all_low_case;
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
    Undef,



};
class Token
{
public:
    Token(TOKEN_TYPE t, TOKEN_SUB_TYPE ts, std::string v) : type(t), sub_type(ts), value(v)
    {
    }
    TOKEN_TYPE type;
    TOKEN_SUB_TYPE sub_type;
    std::string value;
};
inline bool is_noun()
{
    return is_f_ch_up && is_word && !num_pres && !is_punc;
}
inline bool is_verb()
{
    return num_pres && is_word && !is_punc;
}
inline bool is_adword()
{
    return all_low_case && is_word && !num_pres && !is_punc;
}





class Tokenizer {
private:
    std::optional<char> peek(int offset = 0)
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        else {
            return m_src.at(m_index + offset);
        }
    }


    std::string m_src;
    size_t m_index = 0;



public:
    std::optional<Token> next_token()
    {
        char ch;
        std::string str = "";
        bool cont = true;


        while (std::isspace(*peek()) && cont) //keep ignoring whitespaces
        {
            m_index++;
            cont = peek().has_value();

        }
        if (cont) {
            ch = m_src.at(m_index);
            is_f_ch_up = isupper(ch);
            cont = peek(ONE_STEP).has_value();
            if (punc_set.find(ch) != punc_set.end())
            {
                if (cont)
                {
                    if (isspace(*peek(1)))
                        is_punc = true;
                    str += ch;

                }
                else
                {
                    is_punc = true;
                    str += ch;

                }
            }
            else
            {
                is_punc = false;
            }
            is_word = true;
            num_pres = false;
            all_low_case = true;
            while (cont && !is_punc)
            {
                if (!std::isspace(m_src.at(m_index)))
                {

                    ch = m_src.at(m_index);
                    str += ch;
                    if (!isalnum(ch) && is_word)
                    {
                        is_word = false;
                    }
                    if (isdigit(ch) && !num_pres)
                    {
                        num_pres = true;
                    }

                    if (!islower(ch) && all_low_case)
                    {
                        all_low_case = false;
                    }
                    m_index++;
                    cont = peek().has_value();
                }
                else
                {
                    break;
                }

            }

        }


        if (is_noun())
        {
            return Token(Noun, Undef, str);

        }
        else if (is_verb())
        {
            return Token(Verb, Undef, str);
        }
        else if (is_adword())
        {
            return Token(Adword, Undef, str);
        }
        else if (is_punc)
        {
            m_index++;
            return Token(Punc, Undef, str);

        }
        else {
            return {};
        }


    }

    inline explicit Tokenizer(std::string src)
        : m_src(std::move(src))

    {
        m_src += " "; // prevents bug, provides seperation between EOF and last character of string
    }




};






//functions

/* load a string in the class
* iterate continuously, once a token following the given rules is found send it to the parser to generate a tree
* wait for parser to add it and reconfirm correct syntax and continue look ahead
* once a sentence is finished or a lexical error has occured reset the parser use panic mode error handling and continue
* to the next token.
* final ast is checked for semantic errors and only then does the lexer start lexing the new sentence
*
* Lexer()
* {
* continue until end of line token reached.
* next_token=next_token();
* Sp() --->syntactic error-->exit()-->panic mode()-->reset
*      --->lexical error--->exit()-->panic mode()--->reset
* V()
* Op()
* P()
* Semantic check-->Sp()
* push all errors into a queue
*
*
*
* }*/