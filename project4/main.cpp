#include "Treetreed.h"

int main(){
    std::string line;
    TimeSeries obj;
    Datasets obj2;
    Treetreed obj3;

    do{
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string command;
        std::string variable;

        std::string command2;
        double variable1;

        std::getline(ss, command, ' ');

        if (command == "FIND_P3"){
            ss >> variable1 >> variable;
            obj3.FIND_P3(variable1, variable);
        }

        std::getline(ss, variable);

        if (command == "LOAD_P3"){
            obj3.LOAD_P3();
        }
        if (command == "LIST_P3"){ 
            obj3.LIST_P3(variable);
        }
        if (command == "COUNTRY_MIN_P3"){
            obj3.COUNTRY_MIN_P3(variable);
        }
        if (command == "RANGE_P3"){
            obj3.RANGE_P3(variable);
        }
        if (command == "BUILD_P3"){
            obj3.BUILD_P3(variable);
        }
        if (command == "DELETE_P3"){
            obj3.DELETE_P3(variable);
        }
        if (command == "LIMITS_P3"){
            obj3.LIMITS_P3(variable);
        }
        if (command == "TRACE_P3"){
            obj3.TRACE_P3(variable);
        }
        if (command == "LOOKUP_P4"){
            obj3.LOOKUP_P4(variable);
        }
        if (command == "REMOVE_P4"){
            obj3.REMOVE_P4(variable);
        }
        if (command == "INSERT_P4"){
            obj3.INSERT_P4(variable);
        }
        if (command == "CLEAN_P4"){
            obj3.CLEAN_P4();
        }
    }while(line != "EXIT");
}