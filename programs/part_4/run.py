import sys
import time

import adafruit_libraries.Adafruit_MPR121.MPR121 as MPR121


print('Adafruit MPR121 deviceacitive Touch Sensor Test')

# Create MPR121 instance.
device = MPR121.MPR121()

if not device.begin():
    print('Error initializing MPR121.  Check your wiring!')
    sys.exit(1)

# Main loop to print a message every time a pin is touched.
print('Press Ctrl-C to quit.')
last_touched = device.touched()
while True:
    current_touched = device.touched()
    for i in range(12):
        pin_bit = 1 << i
        if current_touched & pin_bit and not last_touched & pin_bit:
            print('{0} touched!'.format(i))
        if not current_touched & pin_bit and last_touched & pin_bit:
            print('{0} released!'.format(i))
    last_touched = current_touched
    time.sleep(0.1)
 
