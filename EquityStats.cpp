#include "EquityStats.hpp"


void EquityStats::calculateExponentialMovingAverage(int period){
    std::string EMAValueName = "EMA-" + std::to_string(period); // Constructs key based on period
    EntityPair* tempPairPtr;
    EntityInstance* tempInstancePtr;
    double smoothingFactor = 2.0; // 2 is a common smoothing factor used in EMAs
    double sum = 0;
    int sizeOfSet = this->_set->getInstanceSize();
    for (int i = 0; i < period && i < sizeOfSet - 1; i++) {
        tempPairPtr = new EntityPair(EMAValueName, "");
        tempInstancePtr = this->_set->getInstance(i);
        tempInstancePtr->addPair(tempPairPtr);
        sum += std::stod(tempInstancePtr->getValueByKey("Close")); // Gets the Closing value and adds it to sum
    }
    if (this->_set->getInstanceSize() >= period){
        double todaysClose = 0.0;
        double oldEMA = sum/period; // Also the first average
        double newEMA = 0.0;
        tempInstancePtr = this->_set->getInstance(period - 1);
        tempPairPtr = new EntityPair(EMAValueName, std::to_string(oldEMA));
        tempInstancePtr->addPair(tempPairPtr);
        for (int i = period; i < sizeOfSet; i++){
            todaysClose = std::stod(tempInstancePtr->getValueByKey("Close"));
            newEMA = (todaysClose * (smoothingFactor/(1 + period)) + (oldEMA * (1 - (smoothingFactor/(1 + period)))));
            tempPairPtr = new EntityPair(EMAValueName, std::to_string(newEMA));
            tempInstancePtr = this->_set->getInstance(i);
            tempInstancePtr->addPair(tempPairPtr);
            oldEMA = newEMA;
        }
    }
}

// Note: This function can be made far more dynamic but this project predetermined the paramaters this function would use
void EquityStats::calculateMACD(){
    EntityPair* tempPairPtr;
    double EMA12 = 0.0;
    double EMA26 = 0.0;
    for (int i = 0; i < this->_set->getInstanceSize(); i++){
        // Check if EMA-12 and EMA-26 exist for instance
        if (this->_set->getInstance(i)->getValueByKey("EMA-12") != "" && this->_set->getInstance(i)->getValueByKey("EMA-26") != ""){
            EMA12 = std::stod(this->_set->getInstance(i)->getValueByKey("EMA-12"));
            EMA26 = std::stod(this->_set->getInstance(i)->getValueByKey("EMA-26"));
            tempPairPtr = new EntityPair("MACD", std::to_string(EMA12 - EMA26));
        }
        else{
            tempPairPtr = new EntityPair("MACD", "");
        }
        this->_set->getInstance(i)->addPair(tempPairPtr);
    }
}

// The signal is a EMA of the MACD.  9 is a common period used, but others are commonly used
void EquityStats::calculateSignal(int period = 9){
    int EMAHighPeriod = 26; // Accounts for how the MACD values don't not exist until index EMAHigh - 1
    EntityPair* tempPairPtr;
    EntityInstance* tempInstancePtr;
    double sum = 0.0;
    if (this->_set->getInstanceSize() >= EMAHighPeriod + period){ // Ensures theres enough data to calculate a signal
        for (int i = 0; i < EMAHighPeriod; i++){ // Add empty signal pairs
            tempPairPtr = new EntityPair("Signal", "");
            this->_set->getInstance(i)->addPair(tempPairPtr);
        }
        for (int i = EMAHighPeriod; i < period + EMAHighPeriod; i++){
            tempPairPtr = new EntityPair("Signal", "");
            tempInstancePtr = this->_set->getInstance(i);
            tempInstancePtr->addPair(tempPairPtr);
            sum += std::stod(tempInstancePtr->getValueByKey("MACD"));
        }
        int SignalOld = sum/period;
        double todaysMACD = 0.0;
        double newSignal = 0.0;
        double oldSignal = 0.0;
        double smoothingFactor = 2.0;
        for ( int i = EMAHighPeriod + period; i < this->_set->getInstanceSize(); i++){
            todaysMACD = std::stod(tempInstancePtr->getValueByKey("MACD"));
            newSignal = (todaysMACD * (smoothingFactor/(1 + period)) + (oldSignal * (1 - (smoothingFactor/(1 + period)))));
            tempPairPtr = new EntityPair("Signal", std::to_string(newSignal));
            tempInstancePtr = this->_set->getInstance(i);
            tempInstancePtr->addPair(tempPairPtr);
            oldSignal = newSignal;
        }
    }
    else { // If there are not enough data points to calculate EMAHigh
        for (int i = 0; i < this->_set->getInstanceSize(); i++){ // Add empty signal pairs
            tempPairPtr = new EntityPair("Signal", "");
            this->_set->getInstance(i)->addPair(tempPairPtr);
        }
    }
}

void EquityStats::print(std::vector<std::string> attributesToPrint){
    this->_set->printInCSV(attributesToPrint);
}