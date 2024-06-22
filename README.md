# ProjectCompiler

## A Frontend of a Compiler hand-built consisting of Parser, Lexer, Error Detection and Recovery System for a Context-Free Grammar (CFG)

This project is built for a language similar to that of English.

The grammatical specifications are mentioned in the link below (Note: This implementation a part of language does not include prepositions or numbers.):
https://docs.google.com/document/d/1uBBrA52rutLfrqMGSvT5C-W2yC91tFdh_a6E8lbkkss/edit#heading=h.yxfcs8ml1jc8
Additionally :-
- All the lexer functions are in the header file lexer.h.
- All the parser functions are declared in parser.h and defined in parser.cpp
- All the error log information are in the header file error.h
- The parser receives tokens, one at a time, from the lexer through an object of the Tokenizer class and carries out the productions of the grammar through controlled function calls.
- The parser contains an in-built error detection and recovery system that monitors the parsing and uses 'Error' functors to display errors when intervention is necessary.
- Lexical and syntactical errors are displayed if detected. Semantical Errors are detected and displayed only when an sentence is correct lexically and syntactically.

## Grammar Productions  ( a theoretical approach to the language of the compiler)
    S--> Sp Vp Op P      * S means language sentence                                          
    Sp --> A N / N       * Sp means Subject phrase      
    Vp--> A V / V        * Vp means Verb phrase       
    Op--> A N / N / e    * Op means Object phrase 
    * A-Adword, N-Noun, V-Verb, P- Punctuation Mark, e- empty string                    
    A N V P are all terminal symbols                    
    Sp Op Vp S are all non-terminal symbols



## Watch the full series to get an idea about compilers!

<a href="url">https://www.youtube.com/watch?v=9p_s457RSQE&list=PLTsf9UeqkRebOYdw4uqSN0ugRShSmHrzH
</a>

                    
## Challenges Faced
- Building a parser from scratch and handling the various grammar productions was a tedious task but overall just needed some time and a systematic approach.
- Travelling the implicit Abstract Syntax Tree (AST) for semantic correctness and ensuring no infinite recursion during error handling required some deep thought on the design of the parser's functions and it's implementation.
- The implementation of error handling proved to be the most demanding task. Managing numerous error productions necessitated a combination of patience, precise thinking, and a significant investment of time.


## Find a bug?

If you found an issue or would like to submit an improvement to this project, please submit an issue using the issues tab above. If you would like to submit a PR with a fix, reference the issue you created!

## Known issues (Work in progress)

The Error Recovery currently finds missing or invalid tokens and reports them for violating lexical and syntactical rules of the language . It also reports violation of the language's semantic rules, for example  if we consider this line of code:                                                                                                                                                 
                                                                                       
           Adv run1 creepy ghost .
We receive this output:
                                                                                                           
     ERROR CODE : 201 ERROR TYPE : Syntactical Error ERROR MESSAGE : Expected the usage of a Noun here. LN : 1 CH : 17     
     ERROR CODE : 203 ERROR TYPE : Syntactical ErrorERROR MESSAGE : Expected the usage of a Punctuation here. LN : 1 CH : 17    
     ERROR CODE : 201 ERROR TYPE : Syntactical Error ERROR MESSAGE : Expected the usage of a Noun here. LN : 1 CH : 23  
     ERROR CODE : 202 ERROR TYPE : Syntactical Error ERROR MESSAGE : Expected the usage of a Verb here. LN : 1 CH : 23                                                                                
The reason for implementing such error recovery in the compiler is because the error detection system of the compiler perceives the input in the following manner:     
                                            
    Sentence 1 :[Noun] [Verb] [Adword] {Adword at invalid position -ignored } (Missing Noun) (Missing Punctuation Mark)                                                                      
    Sentence 2 : (Missing Noun) (Missing Verb) [Punctuation Mark]                                             

What I want it to perceive is :             
                                            
     Sentence 1: [Noun] [Verb] [Adword] [Misspelt Noun.. should be Ghost not ghost] [Punctuation Mark]
Thus, the compiler should incorporate robust error handling techniques, going beyond mere error detection. It should intelligently assess whether an Adword has been mistakenly used as a Noun, while evaluating if the sentence still remains grammatically correct. This is crucial as a common mistake is neglecting to capitalize the first letter of a word to make it a valid Noun.


## Like this project?

Mail me at advhbase@gmail.com for any queries.
