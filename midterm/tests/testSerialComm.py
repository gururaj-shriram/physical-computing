import serial
import time 

ser = serial.Serial('/dev/cu.usbmodem1421', 9600)

while True:
	ser.write(b'1')
	time.sleep(5)
