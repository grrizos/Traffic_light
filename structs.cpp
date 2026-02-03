#include <iostream>
#include <string>

struct Person {
    std::string name = "Bob";
    float waiting_time = 0;

    void displayInfo() {
        std::cout << "Name: " << name << ", Waiting Time: " << waiting_time << " minutes" << std::endl;
    }
};

struct Car {
    std::string Type = "IX";
    float waiting_time = 0;   // time the car is waiting at the light

    void displayInfo() {
        std::cout << "Type: " << Type << ", Waiting Time: " << waiting_time << " minutes" << std::endl;
    }
};

struct Light {
    bool at_intesection = 0;
    int light_state = 0; // 0 = red, 1 = green, 2 = yellow
    bool has_pedestrian = 0;
    bool has_car = 0;

};