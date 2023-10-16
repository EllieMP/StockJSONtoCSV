#ifndef EQUITYINSTANCE_H
#define EQUITYINSTANCE_H

#include "EntityPair.hpp"
#include <vector>

class EntityInstance{
    public:
        EntityInstance() {};
        EntityInstance(std::vector<EntityPair *> pairs): _pairs{ pairs } {};
        void addPair(EntityPair *pairToAdd) { this->_pairs.push_back(pairToAdd); }
        std::string getValueByKey(std::string key);
        void printInJSON(int numSpaces);
        void printInCSV(std::vector<std::string> order); // Order determines the order in which pairs are printed
    private:
        std::vector<EntityPair *> _pairs;
};

#endif