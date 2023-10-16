#include "EntityInstance.hpp"

std::string EntityInstance::getValueByKey(std::string key){
    for (int i = 0; i < this->_pairs.size(); i++){
        if (this->_pairs.at(i)->getKey() == key){
            return this->_pairs.at(i)->getValue();
        }
    }
    return "";
}

void EntityInstance::printInJSON(int numSpaces){
    int i = 0; // Fewer declerations of variables
    for (i = 0; i < numSpaces; i++) std::cout << ' '; // Left at one line due to repitition
    std::cout << '{' << std::endl;
    bool pairPrinted = false;
    for (i = 0; i < this->_pairs.size(); i++){
        if (this->_pairs.at(i)->printInJSON(numSpaces)){
            for (int j = i + 1; j < this->_pairs.size(); j++){
                if (this->_pairs.at(j)->getValue() != ""){
                    std::cout << ',' << std::endl;
                    break;
                }
            }
        }
    }
    std::cout << std::endl;
    for (i = 0; i < numSpaces; i++) std::cout << ' ';
    std::cout << '}';
}

void EntityInstance::printInCSV(std::vector<std::string> order){ // Order determines the order in which pairs are printed
    for (int i = 0; i < order.size(); i++){
        for (int j = 0; j < this->_pairs.size(); j++){ // Looks for matches to order in _pairs
            if (order.at(i) == this->_pairs.at(j)->getKey()){
                this->_pairs.at(j)->printInCSV();
                if (i != order.size() - 1)
                    std::cout << ',';
                break; // Ensures extra commas are not printed
            }
            else {
                if (j == this->_pairs.size() - 1)
                    std::cout << ',';
            }
        }
    }

    std::cout << std::endl;
}
