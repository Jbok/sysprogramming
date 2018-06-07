PWD := $(shell pwd)

default:
	gcc -o sensor sensor.c pi_2_mmio.c common_dht_read.c -lwiringPi
clean:
	rm -rf sensor
