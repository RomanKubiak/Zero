#!/bin/bash
echo "RESET"
/usr/bin/ard-reset-arduino --caterina  /dev/ttyACM0
echo "/usr/bin/avrdude $@"
/usr/share/arduino-nightly/hardware/tools/avr/bin/avrdude $@