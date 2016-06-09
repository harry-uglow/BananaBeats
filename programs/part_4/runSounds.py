from touchHat import *
import sys
import time
import pygame

import python.adafruit_libraries.Adafruit_MPR121.MPR121 as MPR121


print('Adafruit MPR121 deviceacitive Touch Sensor Test')

# Create MPR121 instance
device = MPR121.MPR121()

if not device.begin():
    sys.exit(1)

# Define audio file parameters TODO
pygame.mixer.pre_init(44100, -16, 12, 512)
pygame.init()

# Main loop to play the corroect sound every time a pin is touched
last_touched = device.touched()
while True:
    current_touched = device.touched()
    for i in range(12):
        pin_bit = 1 << i
        if current_touched & pin_bit and not last_touched & pin_bit:
            sound = pygame.mixer.Sound(touched(i))
            sound.set_volume(1)
            sound.play
        if not current_touched & pin_bit and last_touched & pin_bit:
            released(i)
    last_touched = current_touched
    time.sleep(0.08)
 
