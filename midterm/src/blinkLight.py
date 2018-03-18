import sys
import json
from telnetlib import Telnet
import serial

try:
	# Access info from MindWave Headset using TCP. The port number is 13854.
	tn = Telnet('localhost', 13854)
	# Serial port for Arduino
	ser = serial.Serial('/dev/cu.usbmodem1421', 9600)
except:
	print("MindWave Headset or Arduino is not connected. Exiting...")
	sys.exit()
# Request json output from mindwave
tn.write('{"enableRawOutput": true, "format": "Json"}'.encode())

while True:
	blinkStrength = 0

	line = tn.read_until(b"\r\n")
	# line = line[:-2]

	# ignore raw eeg reading
	if len(line) > 20:	
		# convert json to dict
		dict = json.loads(str(line.decode('utf-8')))

		# this occurs when a blink occurs
		if "blinkStrength" in dict:
			blinkStrength = dict['blinkStrength']

			print("Blink Strength: %d" % (blinkStrength))

			# send a char to the Arduino 
			if int(blinkStrength) > 0:
				ser.write(b'1')

ser.close();
tn.close();