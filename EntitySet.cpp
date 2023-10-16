#include "EntitySet.hpp"

void EntitySet::printInJSON(int numSpaces) {
    std::cout << '[' << std::endl;
    for (int i = 0; i < this->_instances.size(); i++){
        this->_instances.at(i)->printInJSON(numSpaces);
        if ( i != this->_instances.size() - 1)
            std::cout << ',' << std::endl;
    }
    std::cout << std::endl << ']' << std::endl;
}

void EntitySet::printInCSV(std::vector<std::string> order) {
    for (int i = 0; i < this->_instances.size(); i++){
        this->_instances.at(i)->printInCSV(order);
    }
}