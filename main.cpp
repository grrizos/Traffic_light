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

int green = 2;
int red = 0;
int yellow =1; 
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
    // First lets make everylight notify driver of incoming change via the use of orange light
    // and make pedestrian lights all red since cars from vein cross every crosswalk
    for (i=time_now; i<=time_now + 5; i++){
        std::cout << "Drivers are getting notified for change and time remaninig :" << i << std::endl;
        light_main1.car_light_state = yellow;
        light_vein1.car_light_state = yellow;     ///here we add the gpio commands to set the lights
        light_main2.car_light_state = yellow;
        light_vein2.car_light_state = yellow;
        light_main1.ped_light_state = red;
        light_vein1.ped_light_state = red;     
        light_main2.ped_light_state = red;
        light_vein2.ped_light_state = red;
    }
    //Now the vein car lights are on and car shall move, and main road is red lights
    for (i=time_now + 5; i<=time_now + 35; i++){
        std::cout << "Main road lights red and vein green time remaining:" << i << std::endl;
        light_main1.car_light_state = red;
        light_vein1.car_light_state = green;     ///here we add the gpio commands to set the lights
        light_main2.car_light_state = red;
        light_vein2.car_light_state = green;
    }
    // Cars have now moved, and lets let pedestrians lights on main road on, even if there is not yet any person waiting(ped button not pressed)
    for (i=time_now + 36; i<=time_now + 45; i++){
        std::cout << "Pedestrian lights now on for main road time remaining:" << i << std::endl;
        light_main1.ped_light_state = green;
        light_vein1.ped_light_state = red;     ///here we add the gpio commands to set the lights
        light_main2.ped_light_state = green;
        light_vein2.ped_light_state = red;
    }
    //then we go back to the normal state of things
    return;
}



bool get_pedestrian(Person NPC)
{
    // Interupt function should always run
    if (NPC.button_pressed == true){
        std::cout << "Pedestrian waiting in vein street!" << std::endl; 
        if (NPC.waiting_time > 10){
        return true;
    }
    }
    return false;
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

        // for (i=time_now; i<=time_now + 20; i++){
        //     std::cout << i << std::endl;
        light_main1.car_light_state = green;
        light_vein1.car_light_state = red;   ///here we add the gpio commands to set the lights
        light_main2.car_light_state = green;
        light_vein2.car_light_state = red;

        light_main1.ped_light_state = red;
        light_vein1.ped_light_state = green;   ///here we add the gpio commands to set the lights
        light_main2.ped_light_state = red;
        light_vein2.ped_light_state = green;
        // }
        // for (i=time_now + 20; i<=time_now + 21; i++){
        //     std::cout << i << std::endl;
        //     light_main1.light_state = 0;
        //     light_vein1.light_state = 2;     ///here we add the gpio commands to set the lights
        //     light_main2.light_state = 0;
        //     light_vein2.light_state = 2;
        // }


    }

}