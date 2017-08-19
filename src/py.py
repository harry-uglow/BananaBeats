import subprocess
import threading
import sys
import time
import pygame
import os
import signal

import python.adafruit_libraries.Adafruit_MPR121.MPR121 as MPR121

print('strt')
p = subprocess.Popen(['./main'], stdin = subprocess.PIPE, close_fds=True, shell=True)
# Maybe add shell=True if it doesn't work
print('mon')
monitorInputs()

def monitorInputs():
    # Create MPR121 instance
    device = MPR121.MPR121()

    if not device.begin():
        sys.exit(1)

    pygame.mixer.pre_init(44100, -16, 12, 2048)
    pygame.init()

    # Main loop to play the corroect sound every time a pin is touched
    last_touched = device.touched()
    while True:
        current_touched = device.touched()
        for i in range(12):
            pin_bit = 1 << i
            if current_touched & pin_bit and not last_touched & pin_bit:
                p.stdin.write('t' + i + '\n')
                print('t' + i)
                p.stdin.flush()
                print('Pin ', i, ' touched') # Get rid of this?
            if not current_touched & pin_bit and last_touched & pin_bit:
                p.stdin.write('r' + i + '\n')
                p.stdin.flush() # Get rid of this?
                print('Pin ', i, ' released')
        last_touched = current_touched
        time.sleep(0.1)
