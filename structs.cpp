#include <iostream>
#include <string>

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

struct Person {
    std::string name = "Bob";
    float waiting_time = 0;
    bool button_pressed = 0;
    void displayInfo() {
        std::cout << "Name: " << name << ", Waiting Time: " << waiting_time << " minutes" << std::endl;
    }
};

struct Car {
    std::string Type = "IX";
    float waiting_time = 0;   // time the car is waiting at the light
    int distance = 0;
    void displayInfo() {
        std::cout << "Type: " << Type << ", Waiting Time: " << waiting_time << " minutes" << std::endl;
    }

    int get_distance() {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        long duration = pulseIn(echoPin, HIGH);
        distance = duration * SOUND_SPEED / 2;
        return distance;
    }

};

struct Light {
    //  we have 4 nodes with 2 lights each one for ped and one for vehicle,
    //  and each one 3 states meaning 3 different led so we need 4*2*3=24 gpio pin ???
    //  we will set in main the gpio pin for each light of each node

    // we dont have that many pins so we will use shift registers to control them
    int gpio_car_pin_yellow = 0;
    int gpio_car_pin_greem = 0;
    int gpio_car_pin_red = 0;

    int gpio_ped_pin_yellow = 0;
    int gpio_ped_pin_greem = 0;
    int gpio_ped_pin_red = 0;
    
    int car_light_state = 0; // 2 = green,1 = yellow , 0 = red,  
    int ped_light_state = 0;
    bool has_pedestrian = 0;
    bool has_car = 0;

    // Function to make text into int for carlight state 
    void set_car_light_state(std::string state) {
        if (state == "red"){car_light_state = 0;}
        if (state == "yellow"){car_light_state = 1;}
        if (state == "green"){car_light_state = 2;}
        set_car_light();
        // return car_light_state;
    }

    // Function to make text into int for pedestrian light state 
    void set_ped_light_state(std::string state) {
        if (state == "red"){ped_light_state = 0;}
        if (state == "yellow"){ped_light_state = 1;}
        if (state == "green"){ped_light_state = 2;}
        set_ped_light();
        // return ped_light_state;
    }

    void set_car_light() {
        //  Car lights
        if (car_light_state == 2){                      //GREEN LIGHT
            digitalWrite(gpio_car_pin_green, HIGH);
            digitalWrite(gpio_car_pin_yellow, LOW);
            digitalWrite(gpio_car_pin_red, LOW);
        }
        if (car_light_state == 1){                      //YELLOW LIGHT
            digitalWrite(gpio_car_pin_yellow, HIGH);
            digitalWrite(gpio_car_pin_green, LOW);
            digitalWrite(gpio_car_pin_red, LOW);
        }
        if (car_light_state == 0){                      //RED LIGHT
            digitalWrite(gpio_car_pin_red, HIGH);
            digitalWrite(gpio_car_pin_green, LOW);
            digitalWrite(gpio_car_pin_yellow, LOW);
        }
    }
    
    void set_ped_light(){
        //  Pedestrian lights
        if (ped_light_state == 2){                      //GREEN LIGHT
            digitalWrite(gpio_ped_pin_green, HIGH);
            digitalWrite(gpio_ped_pin_yellow, LOW);
            digitalWrite(gpio_ped_pin_red, LOW);
        }
        if (ped_light_state == 1){                      //YELLOW LIGHT
            digitalWrite(gpio_ped_pin_yellow, HIGH);
            digitalWrite(gpio_ped_pin_green, LOW);
            digitalWrite(gpio_ped_pin_red, LOW);
        }
        if (ped_light_state == 0){                      //RED LIGTH
            digitalWrite(gpio_ped_pin_red, HIGH);
            digitalWrite(gpio_ped_pin_green, LOW);
            digitalWrite(gpio_ped_pin_yellow, LOW);
        }
    }
};