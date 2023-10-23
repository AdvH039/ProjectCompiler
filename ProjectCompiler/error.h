#pragma once
#include <string>
#include <iostream>
#include "lexer.h"
/*Types of Errors encountered while compiling. */
const std::string ERLEX = "Lexical Error";
const std::string ERSYN = "Syntactical Error";
const std::string ERSEM = " Semantic Error";
extern int line_count;
extern int  word_count;
/* Unique error codes for each kind of error encountered.
   Starts with 1 ---> it is a lexical error
   Starts with 2 ---> it is a syntactical error
   Starts with 3 ----> it is a semantical error

*/
constexpr int ERRNUM101 = 101;
constexpr int ERRNUM102 = 102;
constexpr int ERRNUM103 = 103;
constexpr int ERRNUM104 = 104;
constexpr int ERRNUM105 = 105;
constexpr int ERRNUM201 = 201;
constexpr int ERRNUM202 = 202;
constexpr int ERRNUM203 = 203;
constexpr int ERRNUM204 = 204;
constexpr int ERRNUM301 = 301;
constexpr int ERRNUM302 = 302;
/* Error messages for each error encountered .*/
const std::string L_ERRMSG_AN = "Given expression is not a word. Did you mean it to be a Noun or Adword? ";
const std::string L_ERRMSG_N = "Given expression is not a word. Did you mean it to be a Noun? ";
const std::string L_ERRMSG_AV= "Given expression is not a word. Did you mean it to be a Verb or Adword? ";
const std::string L_ERRMSG_V = "Given expression is not a word. Did you mean it to be a Verb? ?";
const std::string L_ERRMSG_P = "Given expression is not a word. Did you mean it to be a Punctuation?";
const std::string S_ERRMSG_N = "Expected the usage of a Noun here.";
const std::string S_ERRMSG_V = "Expected the usage of a Verb here.";
const std::string S_ERRMSG_P = "Expected the usage of a Punctuation here.";
const std::string S_ERRMSG_F = "End of file detected before sentence termination. Terminate the last sentence with a punctuation symbol."
;
const std::string SE_ERRMSG_N = "A Noun cannot be used both as an Object and a Subject.";
const std::string SE_ERRMSG_A = "An Adword cannot be used both as an Adjective and Adverb. ";

/* Calculates the position where the error has occured. 
*The column position in terms of characters.
*/

int word(int word_count)
{
	if (word_count > str.length())
	{
		return word_count - str.length();
	}
	else
	{
		return 0;
	}
}
/*
   Error functor
   stores error related information and displays when needed.


*/
struct Error {
	int error_code;
	const std::string error_message;
	const std::string error_type;
	Error(int er_c, std::string er_t, std::string er_m) : error_code(er_c),error_type(er_t),error_message(er_m)
	{

	}
	void  operator()()
	{
		std::cerr << "ERROR CODE : " << error_code << " " << "ERROR TYPE : " << error_type<<" " << "ERROR MESSAGE : " << error_message<<" LN : "<<line_count<<" CH : "<<word(word_count) << "\n";
	}
};
/*
* All the various error functors are declared.
*/
static struct Error ERR_101(ERRNUM101, ERLEX, L_ERRMSG_AN);
static struct Error ERR_102(ERRNUM102, ERLEX, L_ERRMSG_N);
static struct Error ERR_103(ERRNUM103, ERLEX,L_ERRMSG_AV );
static struct Error ERR_104(ERRNUM104, ERLEX,L_ERRMSG_V);
static struct Error ERR_105(ERRNUM105, ERLEX, L_ERRMSG_P);
static struct Error ERR_201(ERRNUM201, ERSYN, S_ERRMSG_N);
static struct Error ERR_202(ERRNUM202, ERSYN, S_ERRMSG_V);
static struct Error ERR_203(ERRNUM203, ERSYN, S_ERRMSG_P);
static  struct Error ERR_204(ERRNUM204, ERSYN, S_ERRMSG_F);
static struct Error ERR_301(ERRNUM301, ERSEM, SE_ERRMSG_N);
static struct Error ERR_302(ERRNUM302, ERSEM, SE_ERRMSG_A);