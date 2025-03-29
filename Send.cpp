#include <cstdlib>
#include <iostream>
#include <string>

int main() {
    std::string name_of_a_character="";

    std::cout << "Enter the name of your character: ";
    std::cin >>name_of_a_character;

    std::string command = "python sendData.py " + name_of_a_character;
    int status = std::system(command.c_str());
    
    if (status == 0) {
        std::cout<<"Successfully inserted "<<name_of_a_character<<std::endl;
    }

    if (status == 1) {
        std::cout << "Error executing Python script" << std::endl;
    }

    if (status == 2) {
        std::cout << "Error: The name already exists in the database" << std::endl;
    }
    return 0;
}
