#!/bin/bash
x=${1}

cd device_driver
make $x
cd ..

cd lcd_controller
make $x
cd ..

cd sensor
make $x
cd ..

cd crypto
make $x
cd ..
