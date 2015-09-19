#!/bin/bash

## uses raspberry pi camera module. See https://www.raspberrypi.org/help/camera-module-setup/
## takes a still photo every 2 seconds and saves it with a unique name in /home/pi/images/

filename=$(date -u +"%Y%m%d_%H%M%S")_%04d.jpg
#/opt/vc/bin/raspistill -o /home/pi/images/$filename -tl 2000 -t 7200000 > /home/pi/camera.log 2>&1
/opt/vc/bin/raspistill -rot 180 -ex sports -ISO 800 -o /home/pi/images/$filename -tl 2000 -t 7200000


