#include "TimeSeries.h"

int main(){
    std::string line;
    TimeSeries obj;
    do{
        std::getline(std::cin, line);
        std::stringstream ssss(line);
        std::stringstream sssss(line);

        std::string command;
        std::string filein;
        int yearin;
        double datain;
        
        if(line == "PRINT_P1"){
            obj.PRINT_P1();
        }

        if(line == "MEAN_P1"){
            obj.MEAN_P1();
        }

        if(line == "MONOTONIC_P1"){
            obj.MONOTONIC_P1();
        }
        
        if(line == "FIT_P1"){
            obj.FIT_P1();
        }

        if (ssss >> command >> filein){
            if(command == "LOAD_P1"){
                obj.LOAD_P1(filein);
            }
        }
        
        if (sssss >> command >> yearin >> datain){
            if(command == "ADD_P1"){
                obj.ADD_P1(yearin, datain);
            }
            else if(command == "UPDATE_P1"){
                obj.UPDATE_P1(yearin, datain);
            }
        }

    }while(line != "EXIT");
}