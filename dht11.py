import time
import urllib.request as urllib2
import Adafruit_DHT

myAPI=''
baseURL='https://api.thingspeak.com/update?api_key=%s'%myAPI

sensor=Adafruit_DHT.DHT11
pin=4

while(1):
    try:
        humidity,temperature=  Adafruit_DHT.read_retry(sensor,pin)
        print("Humidity="+str(humidity))
        print("Temperature="+str(temperature))
        time.sleep(5)
        conn=urllib2.urlopen(baseURL+'&field1=%s&field2=%s'%(humidity,temperature)
        print("Data sent to cloud")
    except ValueError:
        print("Unable to read data")
