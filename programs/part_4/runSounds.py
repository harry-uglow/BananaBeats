from touchHat import *
from multiprocessing import Process
import sys
import time
import pygame

import python.adafruit_libraries.Adafruit_MPR121.MPR121 as MPR121

initSounds()
p = Process(target=gui)
p.start()

# Create MPR121 instance
device = MPR121.MPR121()

if not device.begin():
    sys.exit(1)

pygame.mixer.init()

# Main loop to play the corroect sound every time a pin is touched
last_touched = device.touched()
while True:
    current_touched = device.touched()
    for i in range(12):
        pin_bit = 1 << i
        if current_touched & pin_bit and not last_touched & pin_bit:
            filename = touched(i)
            pygame.mixer.music.load(filename)
            pygame.mixer.music.play()
        if not current_touched & pin_bit and last_touched & pin_bit:
            released(i)
    last_touched = current_touched
    time.sleep(0.08)
 
