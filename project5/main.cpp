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
        double variable1;
        int variable2;
        std::string variable3;

        std::getline(ss, command, ' ');

        if (command == "LOAD_P3"){
            obj3.LOAD_P3();
        }
        if (command == "BUILD_P3"){
            ss >> variable;
            obj3.BUILD_P3(variable);
        }
        if (command == "INITIALIZE_P5"){
            obj3.INITIALIZE_P5();
        }
        if (command == "UPDATE_EDGES_P5"){
            ss >> variable >> variable1 >> variable3;
            obj3.UPDATE_EDGES_P5(variable, variable1, variable3);
        }
        if (command == "ADJACENT_P5"){
            ss >> variable;
            obj3.ADJACENT_P5(variable);
        }
        if (command == "PATH_P5"){
            ss >> variable3 >> variable;
            obj3.PATH_P5(variable3, variable);
        }
        if (command == "RELATIONSHIPS_P5"){
            ss >> variable3 >> variable;
            obj3.RELATIONSHIPS_P5(variable3, variable);
        }
    }while(line != "EXIT");
}