from touchHat import *
import sys
import time
import pygame

import python.adafruit_libraries.Adafruit_MPR121.MPR121 as MPR121

# Mode number
instr = int(sys.argv[1])

initSounds()

# Create MPR121 instance
device = MPR121.MPR121()

if not device.begin():
    sys.exit(1)

pygame.mixer.pre_init(44100, -16, 12, 2048)
pygame.init()

sounds = [0,0,0,0,0,0,0,0,0,0,0,0]

for pin in range(12):
    soundfile = getSoundsFromInstrument(pin, instr)
    sounds[pin] = pygame.mixer.Sound(soundfile)
    sounds[pin].set_volume(1)

# Main loop to play the corroect sound every time a pin is touched
last_touched = device.touched()
while True:
    # volume = getVolume()
    current_touched = device.touched()
    for i in range(12):
        pin_bit = 1 << i
        if current_touched & pin_bit and not last_touched & pin_bit:
            sys.stdout.write("inputt" + str(i) + '\n')
            sys.stdout.flush()
            sounds[i].play()
            touched(i)
        if not current_touched & pin_bit and last_touched & pin_bit:
            released(i)
            sys.stdout.write("inputr" + str(i) + '\n')
            sys.stdout.flush()
    last_touched = current_touched
    time.sleep(0.01) 

