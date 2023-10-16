#ifndef ENTITYSET_H
#define ENTITYSET_H

#include "EntityPair.hpp"
#include "EntityInstance.hpp"
#include <vector>

class EntitySet{
    public:
        EntitySet() {};
        EntitySet(std::vector<EntityInstance *> instances): _instances{ instances } {};
        void addInstance(EntityInstance *instanceToAdd) { this->_instances.push_back(instanceToAdd); }
        void printInJSON(int numSpaces);
        void printInCSV(std::vector<std::string> order);
        EntityInstance* getInstance(int index) { return this->_instances.at(index); }
        int getInstanceSize() { return this->_instances.size(); }
    private:
        std::vector<EntityInstance *> _instances;
};

#endif