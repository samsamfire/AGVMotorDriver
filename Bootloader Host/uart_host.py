import serial 

command = b"\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00"


ser = serial.Serial('COM8', 9600, timeout=0)


f = open('blink.hex')

ser.write(command)

a = ser.read(10)

print(a)