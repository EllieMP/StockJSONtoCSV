#ifndef JSONPARSER_H
#define JSONPARSER_H
#include "JSONTokenizer.hpp"
#include "EntityPair.hpp"
#include "EntityInstance.hpp"
#include "EntitySet.hpp"
#include <vector>
#include <algorithm>

class JSONParser {
    public:
        JSONParser(std::vector<JSONToken>);
        void addToken(JSONToken tokenToAdd) { _tokens.push_back(tokenToAdd); }
        void populateTokens(std::vector<JSONToken>);

        void addPair(EntityPair *pairToAdd) { this->_pairs.push_back(pairToAdd); }
        void populatePairs(); // Populates _pairs based on _tokens

        void addInstance(EntityInstance *instanceToAdd) { this->_instances.push_back(instanceToAdd); }
        void populateInstances(); // Populates _instances based on _pairs

        void populateSet(); // Populates _set based on _instances
        EntitySet* getEntitySet() { return this->_set; }

        // Development functions
        void printPairsInJSON(int numSpaces);
        void printPairsInCSV();
        void printInstancesInJSON(int numSpaces);
        void printInstancesInCSV(std::vector<std::string> order);
        void printSetInJSON(int numSpaces);
        void printSetInCSV(std::vector<std::string> order);
        
    private:
        std::vector<JSONToken> _tokens;
        std::vector<EntityPair *> _pairs; // Stores operators and key/value pairs in order
        std::vector<EntityInstance *> _instances;
        EntitySet* _set;
};

#endif