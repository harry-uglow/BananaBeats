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

pygame.mixer.pre_init(44100, -16, 12, 512)
pygame.init()

sounds = [0,0,0,0,0,0,0,0,0,0,0,0]

def updateSoundArray(instrument, volume):
    if not updateSoundArray.lastIns == instrument:
        for pin in range(12):
            soundfile = getSounds(pin)
            sounds[pin] = pygame.mixer.Sound(soundfile)
            sounds[pin].set_volume(volume)
    updateSoundArray.lastIns = instrument
updateSoundArray.lastIns = -1


# Main loop to play the corroect sound every time a pin is touched
last_touched = device.touched()
while True:
    updateSoundArray(getInstrument(), getVolume())
    current_touched = device.touched()
    for i in range(12):
        pin_bit = 1 << i
        if current_touched & pin_bit and not last_touched & pin_bit:
            sounds[i].play()
            touched(i)
        if not current_touched & pin_bit and last_touched & pin_bit:
            released(i)
    last_touched = current_touched
    time.sleep(0.01) 
