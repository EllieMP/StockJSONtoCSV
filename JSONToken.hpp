#ifndef JSONTOKEN_H
#define JSONTOKEN_H
#include <string>


class JSONToken {
    public:
        JSONToken(): _isKey{false}, _isValue{false}, _isOperator{false}, _eof{false} {};
        JSONToken(char c): _isKey{false}, _isValue{false}, _isOperator{false}, _eof{false} {};

        void makeKey(std::string k){
            _key = k;
            _isKey = true;
        }
        bool isKey() { return _isKey; }
        std::string getKey() { return _key; }

        void makeValue(std::string v){
            _value = v;
            _isValue = true;
        }
        bool isValue() { return _isValue; }
        std::string getValue() { return _value; }

        void makeOperator(char c){
            _operator = c;
            _isOperator = true;
        }
        bool isOperator() { return _isOperator; }
        char getOperator() { return _operator; }

        bool isOpenArrOperator() { return _isOperator && _operator == '['; }
        bool isCloseArrOperator() { return _isOperator && _operator == ']'; }
        bool isStartObjOperator() { return _isOperator && _operator == '{'; }
        bool isEndObjOperator() { return _isOperator && _operator == '}'; }
        bool isKeyValueSeperatorOperator() { return _isOperator && _operator == ':'; }
        bool isNewKeyValueOperator() { return _isOperator && _operator == ','; }

        bool endOfFile() { return _eof; }
        void makeEOF() { _eof = true; }

        void print();

    private:
        char _operator;
        std::string _key, _value;
        bool _isKey, _isValue, _isOperator, _eof;
};

#endif