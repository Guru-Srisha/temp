import urllib.request as urllib2
import RPi.GPIO as GPIO
import time

myAPI='';
baseURL='https://api.thingspeak.com/update?api_key=%s'%myAPI

GPIO.setmode(GPIO.BCM)
TRIG=19
ECHO=26
GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)

while True:
  GPIO.output(TRIG,False)
  print("Waitng For sensor to settle")
  time.sleep(2)
  GPIO.output(TRIG,True)
  time.sleep(0.00001)
  GPIO.output(TRIG,False)
  while GPIO.input(ECHO)==0:
    pulse_start=time.time()
  while GPIO.input(ECHO)==1:
    pulse_end=time.time()
  pulse_duration=pulse_end-pulse_start
  distance=pulse_duration*17150
  distance=round(distance,2)
  conn=urllib2.urlopen(baseURL+'&field1=%s'%(distance))
  print("Data sent to cloud")
  if distance>2 and distance<400:
    print("Distance:",distance-0.5,"cm")
  else:
    print("Out of range")
