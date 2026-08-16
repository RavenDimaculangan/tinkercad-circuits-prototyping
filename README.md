# Digital Prototyping, Schematic Design, and Micro-Firmware Simulations

## Project Overview
This repository serves as a centralized portfolio for my electronic engineering simulations and rapid prototyping projects developed within **Tinkercad Circuits**. 

Before moving to physical hardware deployment, I utilize cloud-based simulation environments to design schematics, calculate circuit loads, map wiring topologies, and validate embedded firmware logic. This workflow focuses heavily on industrial control concepts, including hardware interrupts, sensor fusion, object-oriented micro-firmware architecture, and closed-loop actuation systems.


## Key Engineering Skills Demonstrated
* **Object-Oriented Firmware Architecture (OOP):** Designing modular, decoupled C++ class structures (`ServoControl`, `TempSensing`, `BuzzerControl`) utilizing private encapsulation, constructors, and dependency injection via references (`&`).
* **Non-Blocking Multitasking & State Timers:** Replacing blocking execution (`delay()`) with independent `millis()` timestamp tracking to achieve concurrent sensor polling and multi-actuator execution.
* **Edge Detection Logic (Rtrig / Ftrig):** Implementing state memory variables (`_wasDetected`, `_wasOverTemp`) to catch discrete single-shot rising ($\text{LOW} \rightarrow \text{HIGH}$) and falling ($\text{HIGH} \rightarrow \text{LOW}$) transitions.
* **I2C Bus Traffic & Interrupt Optimization:** Preventing LCD display flickering and servo PWM pulse corruption by enforcing state-change rendering logic, eliminating redundant I2C bus traffic and CPU timer starvation.
* **Hardware Interrupt Handling:** Implementing low-latency, event-driven execution loops utilizing `attachInterrupt()` for real-time sensor and safety inputs.
* **Closed-Loop Feedback Systems:** Designing automated environmental controls that continuously poll sensors (temperature, distance) and calculate proportionally mapped actuator outputs.
* **Industrial Latching Logic:** Implementing Set-Reset (SR) control configurations to safely govern physical state memories without mechanical logic interference.
* **Signal Mapping & Conversion:** Parsing raw analog telemetry (potentiometers, gas sensors) and normalizing values into readable digital metrics, voltmeters, and multi-segment displays.


## Technical Stack
* **Simulation Platform:** Tinkercad Circuits
* **Microcontrollers Modeled:** ATmega328P (Arduino Uno)
* **Programming Languages:** Embedded C / C++ (Procedural & Object-Oriented)
* **Design Patterns & Techniques:** Non-Blocking Timers (`millis()`), State Memory & Edge Detection, Encapsulation, State-Change LCD Rendering
* **Component Categories:** Servos, I2C LCD Modules, 7-Segment Displays, Ultrasonic/Proximity Transducers, H-Bridge Motor Drivers, Relays, and Environmental Sensors (TMP36, Gas, Flame, Photoresistor).


## Laboratory Project Index

### 1. Advanced Industrial Control Systems & OOP Architectures
* **Multi-Actuator Object-Oriented Sorting & Alarm Cell:** Engineered an object-oriented, multi-class firmware node governing 3 servo gates, an IR sensor array, a TMP36 thermal sensor, a piezo alarm, and an I2C LCD screen. Features non-blocking timing, falling-edge detection (`Ftrig`) to actuate gates only after objects completely clear sensor view, and state-change display updates to eliminate I2C interrupt collisions and servo signal jitter.
* **Proximity Adaptive Motor with Material Sorting:** Designed an automated conveyor sorting cell that differentiates between metallic and non-metallic objects, driving adaptive motor speeds governed by Set-Reset interlocking logic.
* **Closed-Loop Automated Cooling System:** Integrated a TMP36 temperature sensor, an H-Bridge driver, and a DC fan to simulate a variable-frequency drive. The fan speed is proportionally mapped (0-100%) based on environmental thermal thresholds and logged via an I2C LCD screen.
* **Industrial Safety Cells (Fire & Gas Detection):** Configured standalone edge-alarm nodes utilizing specialized analog threshold logic to trigger immediate acoustic/visual alerts upon detecting hazardous combustion or gas levels.
* **Discrete Multi-Stage Analog Cooling Controller:** Engineered a hardwired, controllerless 3-level automatic fan speed driver using an array of Operational Amplifiers as voltage comparators, an NTC thermistor network for thermal tracking, Diodes, and bipolar junction transistors (BJTs) to sequentially step current loads based on raw analog voltage thresholds.


### 2. Interrupt-Driven & Digital Logic Arrays
* **Dual-Interrupt Diagnostic Display Array:** Implemented a multi-I/O matrix incorporating an I2C LCD, dual LEDs, and dual tactile switches. Utilizes `attachInterrupt()` to execute real-time up/down counting threads while logging total component states.
* **Event-Driven 7-Segment Counter:** Used asynchronous hardware interrupts to detect debounced button states, incrementing a 7-segment display sequentially from 1 to 9.
* **Analog Voltmeter & Data Mapping Array:** Built a functional digital voltmeter parsing analog steps into precise voltage variables, as well as a potentiometer-driven 7-segment array mapping 0-5V levels into distinct 0-9 scalar values.


### 3. Smart Infrastructure & Commercial Prototypes
* **Ultrasonic Distance Telemetry Node:** Designed a non-contact distance tracking module utilizing an HC-SR04 sonar transducer, parsing timing echoes into centimeters, and formatting data arrays for standard I2C LCD screens.
* **Smart Facility Light Controls:** Built dual-input automated lighting frameworks using PIR motion sensors and photoresistors to govern energy-saving illumination triggers.
* **Automatic Waste Management Cell:** Programmed a proximity-triggered automated trashcan lid utilizing localized servo motor sweeps.
