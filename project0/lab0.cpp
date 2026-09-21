#include <iostream>
#include <sstream>
#include <fstream>

int main(){
    std::cout << "Hello baka" << std::endl;

    std::string line;

    // ifstream有open的功能，好，耶！
    // fstream只是收到一个文件，它不知道要干嘛
    std::ifstream file("project0_test_data.csv");

    while(std::getline(file, line)){
        std::string baka;
        std::stringstream ss(line);
        while(std::getline(ss, baka, ',')){
            std::cout << baka << std::endl;
        }
    }
}