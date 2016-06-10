import sys
import time
import pygame

pygame.mixer.pre_init(44100, -16, 12, 512)
pygame.init()

instr = int(sys.argv[1])

#soundfile = "pianomusic.wav"
#print soundfile
#playingSound = pygame.mixer.Sound(soundfile)
#playingSound.set_volume(1)
#playingSound.play()

while True:
  print instr
  time.sleep(1) 

