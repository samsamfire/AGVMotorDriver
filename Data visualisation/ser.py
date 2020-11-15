from threading import Thread
import serial
import time
import collections
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import struct
import pandas as pd

#Code from https://www.thepoorengineer.com/en/arduino-python-plot/
#Modified for this application

class SerialPlot:
	def __init__(self, serialPort = '/dev/ttyUSB0', serialBaud = 38400, dataNumBytes = 2, nbValues = 1):
		self.port = serialPort
		self.baud = serialBaud
		self.dataNumBytes = dataNumBytes
		self.raw = 0
		self.nbValues = nbValues
		self.listValues=[i for i in range(nbValues)]
		self.data = [i for i in range(nbValues)]
		self.data_array =[collections.deque([0] * 100, maxlen=100) for i in range(nbValues)]
		self.isRun = True
		self.isReceiving = False
		self.thread = None
		self.plotTimer = 0
		self.previousTimer = 0
		self.csvData = []

		print('Trying to connect to: ' + str(serialPort) + ' at ' + str(serialBaud) + ' BAUD.')
		try:
			self.serialConnection = serial.Serial(serialPort, serialBaud, timeout=4)
			print('Connected to ' + str(serialPort) + ' at ' + str(serialBaud) + ' BAUD.')
		except:
			print("Failed to connect with " + str(serialPort) + ' at ' + str(serialBaud) + ' BAUD.')

	def readSerialStart(self):
		if self.thread == None:
			self.thread = Thread(target=self.backgroundThread)
			self.thread.start()
			print("Starting to read values")
		# Block till we start receiving values
		while self.isReceiving != True:
			time.sleep(0.1)

	def getSerialData(self, frame, lines, lineValueText, lineLabel, timeText):
		currentTimer = time.perf_counter()
		self.plotTimer = int((currentTimer - self.previousTimer) * 1000)     # the first reading will be erroneous
		self.previousTimer = currentTimer
		timeText.set_text('Plot Interval = ' + str(self.plotTimer) + 'ms')
		for i in range(self.nbValues):
			self.data_array[i].append(self.data[i])
			lines[i].set_data(range(100), self.data_array[i])
			lineValueText[i].set_text('[' + lineLabel[i] + '] = ' + str(self.data[i]))

		self.csvData.append([self.data[i] for i in range(self.nbValues)])


	def backgroundThread(self):    # retrieve data
		time.sleep(1.0)  # give some buffer time for retrieving data
		self.serialConnection.reset_input_buffer()
		self.raw = self.serialConnection.readline() #delete trash first value
		while (self.isRun):
			self.raw = self.serialConnection.readline()
			self.rawData = bytearray(self.raw)
			self.rawData.pop()
			if(len(self.rawData)==4*self.nbValues):
				for i in range(self.nbValues):
					self.listValues[i] = self.rawData[i*4:(i+1)*4]
					#rawData contains bytearray of all the sent floats

					self.data[i], = struct.unpack('f',self.listValues[i])
						
			self.isReceiving = True

	def close(self):
		self.isRun = False
		self.thread.join()
		self.serialConnection.close()
		print('Disconnected...')
		df = pd.DataFrame(self.csvData)
		df.to_csv('data.csv')

	def getData(self):

		return self.rawData




# ser = serial.Serial('COM8',baudrate=500000)

# ser.reset_input_buffer()
# while 1:

# 	raw = ser.readline()
# 	data = bytearray(raw)
# 	data.pop()

# 	if(len(data)==4):
# 		a = struct.unpack('f',data)
# 		print(a)
	
nbValues = 5
	
s = SerialPlot('COM8',500000,4,nbValues)
s.readSerialStart()

# plotting starts below
pltInterval = 50    # Period at which the plot animation updates [ms]
xmin = 0
xmax = 100
ymin = -(20)
ymax = 20
fig = plt.figure(figsize=(10, 8))


ax = plt.axes(xlim=(xmin, xmax), ylim=(float(ymin - (ymax - ymin) / 10), float(ymax + (ymax - ymin) / 10)))

ax.set_title('Dspic Read')
ax.set_xlabel("Time")
ax.set_ylabel("Speed")

lineLabel = [str(i) for i in range(nbValues)]
timeText = ax.text(0.70, 0.95, '', transform=ax.transAxes)
lines = []
lineValueText = []
style = ['r-', 'c-', 'b-','g-','y-']  # linestyles for the different plots





for i in range(nbValues):
	lines.append(ax.plot([], [],style[i], label=lineLabel[i])[0])
	lineValueText.append(ax.text(0.70, 0.90-i*0.05, '', transform=ax.transAxes))
	
anim = animation.FuncAnimation(fig, s.getSerialData, fargs=(lines,lineValueText, lineLabel, timeText), interval=pltInterval)

plt.legend(loc="upper left")
plt.show()







s.close()