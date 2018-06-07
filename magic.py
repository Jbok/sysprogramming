import RPi.GPIO as GPIO  
import time  
  
GPIO.setmode(GPIO.BCM)  
  
# init list with pin numbers  
  
pinList = [17]  
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(17, GPIO.OUT)

# loop through pins and set mode and state to 'low'  
  
#for i in pinList:   
#  GPIO.setup(i, GPIO.OUT)   
#  GPIO.output(i, GPIO.LOW)  
  
# time to sleep between operations in the main loop  
  
SleepTimeL = 2  
i=0
  
# main loop  
state = GPIO.input(21)
#print state
GPIO.output(17, 1-int(state))

time.sleep(0.002)
#if i == 10:
#  break
i += 1

#
#
#  
#try:
#
#  print GPIO.input(12)
#  GPIO.output(17, GPIO.LOW)
#  print "ONE"  
#  time.sleep(SleepTimeL);   
#  GPIO.output(17, GPIO.HIGH)
#  print "TWO"  
#  time.sleep(SleepTimeL)
#  GPIO.cleanup()
#  print "Good bye!"  
#  
## End program cleanly with keyboard  
#except KeyboardInterrupt:  
#  print " Quit"  
#  
#  # Reset GPIO settings  
#GPIO.cleanup()
