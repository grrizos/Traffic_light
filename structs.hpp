#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <iostream>
#include <string>
#include <structs.cpp>

struct Person {
    std::string name = "Bob";
    float waiting_time = 0;
    bool button_pressed = 0;
    void displayInfo();
};

struct Car {
    std::string Type = "IX";
    int distance = 0;
    float waiting_time = 0;   // time the car is waiting at the light

    void displayInfo();
};

struct Light {
    int car_light_state = 0; // 0 = red, 1 = green, 2 = yellow
    int ped_light_state = 0;
    bool has_pedestrian = 0;
    bool has_car = 0;
};

#endif // STRUCTS_HPP
