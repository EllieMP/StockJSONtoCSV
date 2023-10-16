#ifndef JSONTOKENIZER_H
#define JSONTOKENIZER_H

#include <string>
#include <fstream>
#include <stack>

#include "JSONToken.hpp"

class JSONTokenizer {
    public:
        explicit JSONTokenizer(const std::string &inputFile);
        JSONToken getToken();

    private:
        std::string inputFileName;
        std::fstream inputStream;
        std::stack<JSONToken> prevTokenStack; // Used in isKey and isValue to determine if a 
        std::stack<JSONToken> overflowStack;

        static bool isOperator(char c);
        bool isKey(char c);
        bool isValue(char c);
};

#endif