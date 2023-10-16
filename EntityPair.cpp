#include<iomanip>
#include "EntityPair.hpp"

bool EntityPair::printInJSON(int numSpaces){
    if ( this->_value != ""){
        for (int i = 0; i < numSpaces * 2; i++) std::cout << ' ';
        std::cout << '"' << this->_key << '"' << " : " << this->_value;
        return true;
    }
    return false;
}

void EntityPair::printInCSV(){
    std::cout << this->_value;
}
