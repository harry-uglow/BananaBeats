import sys
import time
import pygame

import adafruit_libraries.MPR121 as MPR121

# Create instance of the MPR121 object
device = MPR121.MPR121()

pygame.mixer.pre_init(44100, -16, 12, 512)
pygame.init()

# Last pin touched
last_touched = device.touched()

def loopIteration():
    # Current pin touched
    current_touched = device.touched()
    for i in range(12):
        # 1 = touched, 0 = not touched 
        pin_bit = 1 << i
        # First check if transitioned from not touched to touched.
        if current_touched & pin_bit and not last_touched & pin_bit:
            print('{0} touched!'.format(i))
            # Call C function here TODO

    # Update last pin touched
    last_touched = current_touched

