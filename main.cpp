#include "JSONTokenizer.hpp"
#include "JSONParser.hpp"
#include "EquityStats.hpp"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
     if (argc != 3){
          std::cout << "Usage: " << argv[0] << "-json inputFileName.json" << std::endl;
          std::cout << "Terminating..." << std::endl;
          exit(2);
     }
     std::ifstream inputStream;
     inputStream.open(argv[2], std::ios::in);    // open for reading
     if( ! inputStream.is_open()) {
           std::cout << "Unable top open " << argv[2] << ". Terminating...";
           exit(3);
     }
     inputStream.close();


     JSONTokenizer jsonTokenizer(argv[2]); // The Tokenizer opens and reads from the input file.
     std::vector<JSONToken> tokens;
     JSONToken token = jsonTokenizer.getToken();
     tokens.push_back(token);
     while( ! token.endOfFile() ) {
          token = jsonTokenizer.getToken();
          tokens.push_back(token);					  
     }
     JSONParser parser(tokens);
     parser.populatePairs();
     parser.populateInstances();
     parser.populateSet();

     EquityStats stats(parser.getEntitySet());
     stats.calculateExponentialMovingAverage(12);
     stats.calculateExponentialMovingAverage(26);
     stats.calculateMACD();
     stats.calculateSignal(9);
     
     if (strcmp(argv[1], "-csv") == 0){
     parser.printSetInCSV( { "Date", "Open", "High","Low","Close","Volume","EMA-12","EMA-26","MACD","Signal" });
     }
     else if (strcmp(argv[1], "-json") == 0){
          parser.printSetInJSON(4);
     }
     return 0;
}