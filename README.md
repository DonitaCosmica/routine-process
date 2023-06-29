# Routine Process
## main.c:
1. The necessary libraries are included: avr/io.h, util/delay.h and stdbool.h. In addition, the "stepper.h" and "coordinates.h" header files are included.
2. Define the pins used in the PORTB and PORTD registers to control the LEDs, buttons, and stepper motors.
3. The EEMEM variable storedCoordinate is declared to store the coordinates in EEPROM memory.
4. The setup() function configures the pins as inputs or outputs and sets the initial values of the PORTB and PORTD registers.
5. The start() function is responsible for starting the movement of the stepper motors. Set the address pins of the motors and call the step() function to perform the necessary steps on each motor.
6. The reset() function moves the motors to the initial position. Reads the coordinates stored in EEPROM memory, moves to the origin using the home() function, updates the coordinates to (0, 0) and saves the new values in EEPROM memory.
7. The loop() function is the main loop of the program. Checks if any of the buttons (BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3) have been pressed and executes a corresponding movement sequence.
8. If the BUTTON_PIN_1 button is pressed, a specific motion sequence is performed using the stepper motors. After the sequence is complete, the LED_START LED is turned on, a time defined by DELAY_MS is waited, and the reset() function is called to return to the starting position.
9. If the BUTTON_PIN_2 button is pressed, another specific motion sequence is performed using the stepper motors. As in the previous case, the LED_START LED is activated, it waits for a while and the reset() function is called.
10. If the BUTTON_PIN_3 button is pressed, a third specific movement sequence is performed. On completion, the LED_HOME LED is turned on and the reset() function is called.
11. The program runs in an infinite loop inside the main() function, repeatedly calling the loop() function.

## coordinate.h:
This code defines a header file for managing coordinates on an AVR microcontroller. It provides a structure to represent coordinates, declares an external variable for storing a coordinate pair in EEPROM memory, and includes necessary headers for EEPROM access and standard integer types.

## motor.c:
1. The necessary libraries are included: avr/io.h, util/delay.h, stdio.h and stdbool.h.
2. A constant DELAY_MS is defined with a value of 10, which represents the number of milliseconds of delay between motor steps.
3. There are three helper functions defined:
    - setBit: Sets a specific bit in a specific register.
    - clearBit: Clears (sets to zero) a specific bit in a specific register.
    - isBitSet: Check if a specific bit is set (1) in a specific byte.
4. The step function is the main part of the code and takes three parameters:
    - steps: The number of steps to take.
    - bit: The bit number in the PORTD register to be changed during each step.
    - dir: The bit number in the PIND register to check to determine the direction of movement.
5. The step function reads the coordinates stored in EEPROM memory and saves them in the coordinate variable.
6. Then a for loop is executed to perform the specified number of steps.
    - At each step, the corresponding bit in the PORTD register is set to activate the motor.
    - A delay of DELAY_MS milliseconds is expected.
    - The corresponding bit in the PORTD register is cleared to disable the motor.
    - Another delay of DELAY_MS milliseconds is expected.
    - The state of the dir bit in the PIND register is checked to determine the direction of movement.
    - The x and y coordinates are updated according to the current bit y address.
    - The updated coordinates are saved in the EEPROM memory.
7. The home function is used to move back to the starting position.
    - A for loop is executed, decrementing steps from its initial value to 1.
    - At each iteration, the motor is activated and deactivated with a delay between them.

## MAKEFILE:
If you want to generate all the build files, you need to run the **make** command in your terminal at the file address where the MAKEFILE file is located, running this file will create two important folders, the first one has all the build files and this one is called **build**, the second called **lib** has the static library generated from the **led.c** file
To run the code on the arduino, it must be connected to the computer, once connected to the terminal you must execute the **make flash** command, in this way the file will be compiled on the arduino, working.
If you want to delete the build files, all you have to do is write the **make clean** command, this way it removes the files from the build and lib folders, but it doesn't delete these folders.
