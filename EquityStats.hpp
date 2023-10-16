#ifndef ENTITYSTAT_H
#define ENTITYSTAT_H

#include "EntityPair.hpp"
#include "EntityInstance.hpp"
#include "EntitySet.hpp"
#include <string>
#include <vector>
#include <math.h>

class EquityStats{
    public:
        EquityStats(EntitySet* set): _set{ set } {};
        void calculateExponentialMovingAverage(int period);
        void calculateMACD();
        void calculateSignal(int period);
        void print(std::vector<std::string> attributesToPrint);
    private:
        EntitySet* _set;
};

#endif