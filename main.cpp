#include <iostream>
#include <string>
#include <structs.hpp>
#include <vector>
#include <chrono>

Light light_main1;
Light light_main2;
Light light_vein1;
Light light_vein2;

Car car ;
Person NPC;

bool get_cars(Car car)
{
    // Interupt function should always run
    // HERE ADD THE DIGITALREAD(SENSRO) to get distance
    if (car.distance < 50)
    {
        std::cout << "Car detected in vein street!" << std::endl; 
        return true;
    }
     return false;
}

void car_on_vein(){
    // This is function changes the behaviour of the traffic lights to
    // enable cars in vein street to enter the highway
    //Routine Function
    int i =0;
    int time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) % 60; //change how we handle timing
    for (i=time_now; i<=time_now + 10; i++){
        std::cout << i << std::endl;
        light_main1.light_state = 0;
        light_vein1.light_state = 2;     ///here we add the gpio commands to set the lights
        light_main2.light_state = 0;
        light_vein2.light_state = 2;
    }
}



bool get_pedestrian(Person NPC)
{
    // Interupt function should always run
}

void pedestrian_on_vein(){
    
}





int main() {

    while(true){
        //---here i ahve to se the inyerrupt handdler and most other functions will be interupt based
        //this is the main loop that will run the traffic light system, when no interupt occurs
        
        if (get_cars(car) == true) // this has to be a interupt so it triggers at any time
        {
            car_on_vein();
        }

        if (get_pedestrian(NPC) == true )
        {
            pedestrian_on_vein();
        }

        int i =0;
        int time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) % 60;
        for (i=time_now; i<=time_now + 20; i++){
            std::cout << i << std::endl;
            light_main1.light_state = 2;
            light_vein1.light_state = 0;   ///here we add the gpio commands to set the lights
            light_main2.light_state = 2;
            light_vein2.light_state = 0;
        }
        for (i=time_now + 20; i<=time_now + 22; i++){
            std::cout << i << std::endl;
            light_main1.light_state = 0;
            light_vein1.light_state = 2;     ///here we add the gpio commands to set the lights
            light_main2.light_state = 0;
            light_vein2.light_state = 2;
        }


    }

}