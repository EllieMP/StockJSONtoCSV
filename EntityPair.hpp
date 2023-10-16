#ifndef ENTITYPAIR_H
#define ENTITYPAIR_H

#include <string>
#include <iostream>
#include <ctype.h>

class EntityPair{
    public:
        EntityPair(): _key{""}, _value{""} {};
        EntityPair(std::string key, std::string value): _key {key}, _value {value} {};

        std::string getKey() { return this->_key; }
        void setKey(std::string key) { this->_key = key; }
        std::string getValue() { return this->_value; }
        void setValue(std::string value) { this->_value = value; }

        bool printInJSON(int numSpaces);
        void printInCSV();

    private:
        std::string _key;
        std::string _value; // All values are internaly stored as strings
};

#endif