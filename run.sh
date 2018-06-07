#!/bin/bash

infloop() {
time=$1
shift
while :
do
  sleep $time
  $@
  #if [[ $? -eq 0 ]]; then
  #  break
  #fi
done
}

# initialize
redis-cli set humidity 0
redis-cli set temperature 0
redis-cli set button 0

infloop 0.3 python ./magic.py &

# run
## device_driver
cd device_driver
./run.sh
cd ..
## lcd_controller
cd lcd_controller
infloop 0.5 ./lcd_controller.sh &
cd ..
## sensor
cd sensor
./sensor &
cd ..
## crypto
cd crypto
infloop 1 ./crypto &
cd ..
