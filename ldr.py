import urllib.request as urllib2
import RPi.GPIO as GPIO
import time

myAPI=''
baseURL='https://api.thingspeak.com/update?api_key=%s'%myAPI

GPIO.setmode(GPIO.BCM)
GPIO.setup(13,GPIO.IN)
light_sensor_pin=13
light_value=0

while True:
    try:
        print("Scanning for sensor data...")
        time.sleep(2)
        light_value = GPIO.input(light_sensor_pin)
        if light_value==0:
            print('Light detected')
        else:
            print('Light not detected')
        time.sleep(2)
        conn=urllib2.urlopen(baseURL+'&field1=%s'%(light_value))
        print("Data sent to cloud")
        time.sleep(5)
    except:
        print("Iteration completed")
