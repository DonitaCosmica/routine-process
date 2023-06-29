# Routine Process

## MAKEFILE:
If you want to generate all the build files, you need to run the **make** command in your terminal at the file address where the MAKEFILE file is located, running this file will create two important folders, the first one has all the build files and this one is called **build**, the second called **lib** has the static library generated from the **led.c** file
To run the code on the arduino, it must be connected to the computer, once connected to the terminal you must execute the **make flash** command, in this way the file will be compiled on the arduino, working.
If you want to delete the build files, all you have to do is write the **make clean** command, this way it removes the files from the build and lib folders, but it doesn't delete these folders.
