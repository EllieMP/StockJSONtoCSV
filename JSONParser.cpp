#include "JSONParser.hpp"

JSONParser::JSONParser(std::vector<JSONToken> tokensToAdd){
    for (int i = 0; i < tokensToAdd.size(); i++)
        this->_tokens.push_back(tokensToAdd.at(i));
}

void JSONParser::populatePairs(){
    // Turn Token array into key value pairs

    // valueTypes are -1 for undefined, 1 for int, 2 for float, 3 for char, 4 for string
    std::string emptyString = ""; // Makes code cleaner
    EntityPair *tempPair;
    for (int i = 0; i < this->_tokens.size(); i++){
        if (this->_tokens.at(i).isKey()){
            if (_tokens.at(i+1).isKeyValueSeperatorOperator()) { // If seperator token exists in the correct spot
                if (_tokens.at(i+2).isValue()){ // If value exists
                    this->_pairs.push_back(new EntityPair(this->_tokens.at(i).getKey(), this->_tokens.at(i+2).getValue()));
                    i += 2;
                }
                else {
                    this->_pairs.push_back(new EntityPair(this->_tokens.at(i).getKey(), emptyString));
                    i += 1;
                }
            }
            else if (_tokens.at(i+1).isStartObjOperator()){ // If next token is an object opening operator
                std::cout << "This program does not support json objects in key value pairs.  See preconditions for details." << std::endl;
                std::cout << "Terminating..." <<std::endl;
                exit (4);
            }
            else {
                std::cout << "Misidentified Token.  Likely an issue in the tokenizer.  Terminating..." << std::endl;
                exit (5);
            }
        }
    }
}

void JSONParser::populateInstances(){
    EntityInstance *tempInstance = new EntityInstance();
    std::vector<std::string> usedKeys;
    for (int i = 0; i < this->_pairs.size(); i++){
        if (std::find(usedKeys.begin(), usedKeys.end(), this->_pairs.at(i)->getKey()) == usedKeys.end()){
            tempInstance->addPair(this->_pairs.at(i));
            usedKeys.push_back(this->_pairs.at(i)->getKey());
        }
        else {
            this->addInstance(tempInstance);
            tempInstance = new EntityInstance();
            tempInstance->addPair(this->_pairs.at(i));
            usedKeys.clear();
            usedKeys.push_back(this->_pairs.at(i)->getKey());
        }
    }
    this->addInstance(tempInstance);
}

void JSONParser::populateSet(){
    this->_set = new EntitySet;
    for (int i = 0; i < this->_instances.size(); i++)
        this->_set->addInstance(this->_instances.at(i));
}

// Development functions
void JSONParser::printPairsInJSON(int numSpaces){
    for (int i = 0; i < _pairs.size(); i++){
        this->_pairs.at(i)->printInJSON(numSpaces);
        std::cout << std::endl;
    }
}

void JSONParser::printPairsInCSV(){
    for (int i = 0; i < _pairs.size(); i++){
        this->_pairs.at(i)->printInCSV();
        std::cout << std::endl;
    }
}

void JSONParser::printInstancesInJSON(int numSpaces){
    for (int i = 0; i < _instances.size(); i++){
        this->_instances.at(i)->printInJSON(numSpaces);
        if ( i != this->_instances.size() - 1)
            std::cout << ',';
        std::cout << std::endl;
    }
}

void JSONParser::printInstancesInCSV(std::vector<std::string> order){
    for (int i = 0; i < _instances.size(); i++)
        this->_instances.at(i)->printInCSV(order);
}

void JSONParser::printSetInJSON(int numSpaces){
    this->_set->printInJSON(numSpaces);
}

void JSONParser::printSetInCSV(std::vector<std::string> order){
    this->_set->printInCSV(order);
}

