#include <iostream>
#include <string>
#include <structs.hpp>
#include <vector>
#include <chrono>

enum State { 
    MAIN_GL,           // Main street green, vein red (stable state)
    CAR_ON_VEIN,       // Car detected on vein - transition state
    VEIN_PD_RL,        // Vein pedestrian red light
    VEIN_GL,           // Vein green light for cars
    MAIN_RL,           // Main street red light
    PED_ON_MAIN,       // Pedestrian crossing on main - transition state
    MAIN_PD_GL,        // Main pedestrian green light
    MAIN_PD_RL,        // Main pedestrian red light
    VEIN_PD_GL         // Vein pedestrian green light
};

Light light_main1;
Light light_main2;
Light light_vein1;
Light light_vein2;

Car car ;
Person NPC;

volatile bool car_detected = false;      // Set by car interrupt
volatile bool pedestrian_waiting = false; // Set by pedestrian interrupt

bool get_cars(Car car)
{
    // Interupt function should always run
    car.distance = car.get_distance();
    if (car.distance < 50)
    {
        car_detected = true;
        std::cout << "Car detected in vein street!" << std::endl; 
        return true;
    }
    car_detected = false;
    return false;
}

bool get_pedestrian(Person NPC)
{
    // Interupt function should always run
    if (NPC.button_pressed == true){
        std::cout << "Pedestrian waiting in vein street!" << std::endl; 
        if (NPC.waiting_time > 10){
        pedestrian_waiting = true;
        return true;
    }
    }
    pedestrian_waiting = false;
    return false;
}

void car_on_vein(){
    // This is function changes the behaviour of the traffic lights to
    // enable cars in vein street to enter the highway
    //Routine Function
    int i =0;
    int time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) % 60; //change how we handle timing

    //Now the vein car lights are on and car shall move, and main road is red lights
    for (i=time_now + 5; i<=time_now + 35; i++){
        std::cout << "Main road lights red and vein green time remaining:" << i << std::endl;
        light_main1.set_car_light_state("red");
        light_vein1.set_car_light_state("green");     ///here we add the gpio commands to set the lights
        light_main2.set_car_light_state("red");
        light_vein2.set_car_light_state("green");
    }
    // Cars have now moved, and lets let pedestrians lights on main road on, even if there is not yet any person waiting(ped button not pressed)
    for (i=time_now + 36; i<=time_now + 45; i++){
        std::cout << "Pedestrian lights now on for main road time remaining:" << i << std::endl;
        light_main1.set_ped_light_state("green");
        light_vein1.set_ped_light_state("red");     ///here we add the gpio commands to set the lights
        light_main2.set_ped_light_state("green");
        light_vein2.set_ped_light_state("red");
    }
    //then we go back to the normal state of things
    return;
}
//HERE WE HAVE THE FUNCITONS FOR EACH STATE OF THE FSM
// VEIN_PD_RL
void vein_pd_rd(){
        // First lets make everylight notify driver of incoming change via the use of orange light
    // and make pedestrian lights all red since cars from vein cross every crosswalk
    int i =0;
    int time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) % 60; //change how we handle timing

    for (i=time_now; i<=time_now + 5; i++){
        std::cout << "Drivers are getting notified for change and time remaninig :" << i << std::endl;
        light_main1.set_car_light_state("yellow");
        light_vein1.set_car_light_state("yellow");     ///here we add the gpio commands to set the lights
        light_main2.set_car_light_state("yellow");
        light_vein2.set_car_light_state("yellow");
        light_main1.set_ped_light_state("red");
        light_vein1.set_ped_light_state("red");     
        light_main2.set_ped_light_state("red");
        light_vein2.set_ped_light_state("red");
    }
    return ;
}

// MAIN_RD
void main_rd(){
    light_main2.set_car_light_state("red");
    light_main1.set_car_light_state("red");
    return ;
}
// VEIN_GL
void vein_gl(){
    int i =0;
    int time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) % 60; //change how we handle timing
    // At timer to let the cars pass for 30sec
    for (i=time_now; i<=time_now + 30; i++){
        light_vein1.set_car_light_state("green");
        light_vein2.set_car_light_state("green");
    }
    return;
}
// VEIN_RL
void vein_rl(){
    int i =0;
    int time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) % 60; //change how we handle timing
    for (i=time_now; i<=time_now + 5; i++){
        light_vein1.set_car_light_state("yellow");
        light_vein2.set_car_light_state("yellow");
    }
    light_vein1.set_car_light_state("red");
    light_vein2.set_car_light_state("red");
    return;
}
// MAIN_PD_GL
void main_pd_gl(){
    int i =0;
    int time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) % 60; //change how we handle timing
    for (i=time_now ; i<=time_now + 30; i++){
        std::cout << "Pedestrian lights now on for main road time remaining:" << i << std::endl;
        light_main1.set_ped_light_state("green");
        light_main2.set_ped_light_state("green");
    }
    return;
}
// MAIN_PD_RL
void main_pd_rd(){
    
    std::cout << "Pedestrian lights red on for main road time remaining:" << i << std::endl;
    light_main1.set_ped_light_state("red");
    light_main2.set_ped_light_state("red");
    return;
}
void vein_pd_gl(){

    std::cout << "Pedestrian lights now on for vein road time remaining:" << i << std::endl;
    light_vein1.set_ped_light_state("green");
    light_vein2.set_ped_light_state("green");
    return;
}


long get_elapsed_milliseconds(auto start_time) {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
}



int main() {
        //---here i ahve to se the inyerrupt handdler and most other functions will be interupt based
        //this is the main loop that will run the traffic light system, when no interupt occurs
    State current_state = MAIN_GL;
    auto state_start_time = std::chrono::system_clock::now();
    //set up the pins for the interupts handelrs functions
    attachInterrupt(digitalPinToInterrupt(CAR_SENSOR_PIN), get_cars, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PEDESTRIAN_BUTTON_PIN), get_pedestrian, RISING);
    while(true) {
        long elapsed = get_elapsed_milliseconds(state_start_time);
        switch(current_state)

        case MAIN_GL:
            light_main1.set_car_light_state("green");
            light_vein1.set_car_light_state("red");   ///here we add the gpio commands to set the lights
            light_main2.set_car_light_state("green");
            light_vein2.set_car_light_state("red");

            light_main1.set_ped_light_state("red");
            light_vein1.set_ped_light_state("green");   ///here we add the gpio commands to set the lights
            light_main2.set_ped_light_state("red");
            light_vein2.set_ped_light_state("green");

            if (car_detected == true) // this has to be a interupt so it triggers at any time //it is now a volative parameter
            {
                current_state = VEIN_PD_RL
            }

            if (pedestrian_waiting == true ) // this has to be a interupt so it triggers at any time // it is now a volative parameter
            {
                current_state = MAIN_RL
            }
            break;

        case VEIN_PD_RL
            vein_pd_rd();
            current_state = MAIN_RL
            break;
        // we have pedestrian on main waiting
        case MAIN_RL
            main_rd();
            if (car_detected == true){
                current_state = VEIN_GL
            }
            if (pedestrian_waiting == true && car_detected == false){
                current_state = MAIN_PD_GL
            }
            break;
        case VEIN_GL
            vein_gl();
            current_state = VEIN_RL
            break;
        case VEIN_RL
            vein_rl();
            if (pedestrian_waiting == false){
                current_state = VEIN_PD_GL
            }
            current_state = MAIN_PD_GL
            break;
        case MAIN_PD_GL
            main_pd_gl();
            current_state = MAIN_PD_RL
            break;
        case MAIN_PD_RL
            main_pd_rl();
            current_state = VEIN_GL;
            break;
        case VEIN_PD_GL
            vein_pd_gl();
            current_state = MAIN_GL;
            break;
        default:
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Prevent CPU thrashing
    }
 
}