# Traffic Light FSM System

An Arduino-based traffic light control system using a Finite State Machine (FSM) to manage vehicle and pedestrian traffic flow across two intersecting streets.

## Overview

This system manages a 4-node traffic light intersection with:
- **Main Street**: Primary traffic flow with 2 traffic light nodes
- **Vein Street**: Secondary street with 2 traffic light nodes
- **Car Detection**: Ultrasonic sensor triggers car priority
- **Pedestrian Management**: Button-based pedestrian crossing control

Each traffic light node controls:
- 3 vehicle lights (red, yellow, green)
- 2 pedestrian lights (red, green)

## System States

The FSM operates with 9 states:

1. **MAIN_GL** - Main street green, vein red (default stable state)
2. **CAR_ON_VEIN** - Car detected on vein street
3. **VEIN_PD_RL** - Transition: Warning phase with yellow lights
4. **VEIN_GL** - Vein street green light for vehicles
5. **MAIN_RL** - Main street red light
6. **PED_ON_MAIN** - Pedestrian waiting on main street
7. **MAIN_PD_GL** - Main street pedestrian crossing (green for pedestrians)
8. **MAIN_PD_RL** - Main street pedestrian red light
9. **VEIN_PD_GL** - Vein street pedestrian crossing (green for pedestrians)

## Hardware Requirements

### Microcontroller
- Arduino-compatible board (ESP-32)

### Sensors
- **Ultrasonic Sensor (HC-SR04)**
  - Trigger Pin: GPIO 5
  - Echo Pin: GPIO 18
  - Purpose: Car detection on vein street (distance < 50cm)

- **Pedestrian Button**
  - Connected to: `PEDESTRIAN_BUTTON_PIN` (define as needed)
  - Triggers when pressed with waiting time > 10 seconds

### Outputs (via shift registers)
- 4 sets of traffic lights (one per node)
- Each light requires 3 GPIO pins (red, yellow, green for cars + pedestrians)
- **Total: 24 GPIO pins** (controlled via shift registers to reduce pin count)

## Pin Configuration

Edit these constants in `main.cpp`:
```cpp
#define CAR_SENSOR_PIN          // Ultrasonic sensor interrupt pin
#define PEDESTRIAN_BUTTON_PIN   // Pedestrian button interrupt pin
```

Configure Light GPIO pins for each node in the Light struct initialization.

## State Transitions

```
MAIN_GL (default)
├─ Car detected → VEIN_PD_RL → VEIN_GL → VEIN_RL → (pedestrian_waiting? MAIN_PD_GL : VEIN_PD_GL)
└─ Pedestrian waiting → MAIN_RL → MAIN_PD_GL → MAIN_PD_RL → VEIN_GL
```

**Timing:**
- Yellow warning phase: 5 seconds
- Green light duration: 30 seconds
- Pedestrian crossing: 30 seconds

## Building and Uploading

1. Install Arduino IDE or compatible tool
2. Connect your Arduino board via USB
3. Compile and upload `main.cpp` with the structs files

```bash
# Using Arduino CLI
arduino-cli compile --fqbn arduino:avr:uno .
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:uno .
```

## File Structure

- `main.cpp` - FSM state machine logic and main loop
- `structs.hpp` - Header file with struct declarations
- `structs.cpp` - Struct implementations (Light, Car, Person)
- `traffic-light-fsm.drawio` - FSM diagram visualization

## Known Limitations & Issues

### Current Implementation Notes
1. **Timing**: Loop-based timing doesn't account for actual elapsed time intervals
2. **Pin Initialization**: GPIO pins for lights must be manually configured before runtime
3. **Interrupt Handler Limitations**: Arduino interrupt callbacks cannot pass struct parameters directly
4. **Typo in Code**: `gpio_car_pin_greem` should be `gpio_car_pin_green`
5. **Undefined Variable**: `main_pd_rd()` function references undefined variable `i`

### Improvements Needed
- [ ] Implement proper timing with `millis()` instead of loop counters
- [ ] Add debouncing for sensor inputs (50-100ms window)
- [ ] Implement shift register library for GPIO expansion
- [ ] Add serial logging and system diagnostics
- [ ] Create adaptive timing based on traffic volume
- [ ] Add emergency vehicle override capability
- [ ] Implement state timeout safeguards

## How It Works

1. **Startup**: System enters `MAIN_GL` state with main street green
2. **Car Detection**: Ultrasonic sensor triggers interrupt → transition to `VEIN_PD_RL` (yellow warning)
3. **Traffic Priority**: Vein street gets green when car detected
4. **Pedestrian Override**: If pedestrian button pressed while main street is red, transition to pedestrian crossing
5. **Default Return**: After sequences complete, returns to `MAIN_GL` stable state

## Testing Notes

- Simulate car detection by moving object within 50cm of ultrasonic sensor
- Test pedestrian button with waiting_time > 10 seconds
- Verify all lights cycle through red → yellow → green transitions

## License

Educational project - use and modify as needed.
