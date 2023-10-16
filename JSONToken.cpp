#include <iostream>
#include "JSONToken.hpp"

void JSONToken::print() {
    if ( isKey() )
        std::cout << getKey() << std::endl;
    else if ( isValue() )
        std::cout << getValue() << std::endl;
    else if ( isOperator() )
        std::cout << getOperator() << std::endl;
    else if ( endOfFile() )
        std::cout << "EOF" << std::endl;
    else
        std::cout << "Unknown token" << std::endl;
}