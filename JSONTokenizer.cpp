#include <iostream>
#include "JSONTokenizer.hpp"

JSONTokenizer::JSONTokenizer(const std::string &inputFile){
    inputStream.open(inputFile, std::ios::in);
}

bool JSONTokenizer::isOperator(char c){
    return c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ',';
}

bool JSONTokenizer::isKey(char c){
    if (c == '"' && (prevTokenStack.top().isNewKeyValueOperator() || prevTokenStack.top().isStartObjOperator()))
        return true;
    else
        return false;
}

bool JSONTokenizer::isValue(char c){
    if ((isalpha(c) || isdigit(c) || c == '"') && prevTokenStack.top().isKeyValueSeperatorOperator())
        return true;
    else
        return false;
}

JSONToken JSONTokenizer::getToken() {
    if (!this->inputStream.is_open()){ // Make sure imput stream is open
        std::cout << "Input stream in JSONTokenizer::getToken is not open. Terminating...\n";
        exit(2);
    }

    // Handle overflow tokens
    if (!overflowStack.empty()){
        JSONToken token = overflowStack.top();
        if (token.isOperator())
            prevTokenStack.push(token);
        overflowStack.pop();
        return token;
    }

    // Handel the token
    char c;
    inputStream >> c;
    //std::cout << "Temp: " << c << std::endl;
    if (inputStream.eof()){
        JSONToken token(c);
        token.makeEOF();
        while(!prevTokenStack.empty())
            prevTokenStack.pop(); // Emptys stack clearing up unused memory
        return token;
    } else if(isOperator(c)){
        JSONToken token;
        token.makeOperator(c);
        prevTokenStack.push(token);
        return token;
    } else if (isKey(c)){
        JSONToken token;
        std::string keyStr = "";
        inputStream >> c;
        while(c != '"'){
            keyStr.push_back(c);
            inputStream >> c; // Done first to skip the first quotation mark
        }
        token.makeKey(keyStr);
        return token;
    } else if (isValue(c)){
        JSONToken token;
        std::string valueStr = "";
        while(c != ',' && c != '}'){
            valueStr.push_back(c);
            inputStream >> c; // Done first to skip the first quotation mark
        }
        if (c == ',' || c == '}'){ // Handels the overflow operator character
            JSONToken overflowToken(c);
            overflowToken.makeOperator(c);
            overflowStack.push(overflowToken);
        }
        token.makeValue(valueStr);
        return token;
    }

    std::cout << "Unexcted character in input ->" << c << "<-\n";
    std::cout << "Terminating...\n";
    exit(3);
}