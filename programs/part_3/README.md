
README

  This directory contains 3 files for Part 3 of the ARM project. 

  'gpio.s': This file pertains to the main task of this part with an assembly program that
  makes a the LED corresponding to GPIO pin 16 switch on and off repeatedly.

  'gpio17.s': There is also an alternative implementation of the same procedure with GPIO pin
  17 rather than GPIO pin 16 found in 'gpio17.s'. This repeatedly switches GPIO pin 17 on and 
  off which can be connected to an external LED to reproduce the same effect.

  'kernel.img': This file contains the program corresponding to 'gpio.s' which is loaded onto
  the Raspberry Pi to run the execution of the flashing LED in GPIO pin 16.
 
