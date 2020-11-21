import can
import time
import os
import math

FLASH_UNLOCK_KEY = 0x00AA0055

WRITE_FLASH = 0x02
SEND_UNLOCK_KEY = 0x0C
FLASH_DATA = 0x0D

START_LINE = ':'
#Command types
EXTENDED_ADDRESS = 0x04
DATA = 0x00
END_OF_FILE =0x01

bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=500000)

msg = can.Message(arbitration_id=6<<7|17,data=[0, 25, 0, 1, 3, 1, 4, 1],is_extended_id=False)

address_high = 0

bytes_can = bytearray(8)





def read_flash(can_address,flash_address,nbytes):
	flashll = flash_address & 0xFF
	flashlh = (flash_address >> 8)&0xFF
	flashhl = (flash_address >> 16)&0xFF
	flashhh = (flash_address >> 24)&0xFF

	nbytesl = nbytes&0xFF
	nbytesh = (nbytes >> 8)&0xFF

	msg = can.Message(arbitration_id=can_address<<7|0x01,data=[flashhh,flashhl,flashlh,flashll,nbytesh,nbytesl],is_extended_id=False)
	bus.send(msg)

def read_version(can_address):
	msg = can.Message(arbitration_id=can_address<<7|17,is_extended_id=False)
	bus.send(msg)

def create_flash_message(can_address,address,message_high,message_low):

	message_highll = message_high & 0xFF
	message_highlh = (message_high >> 8)&0xFF
	message_highhl = (message_high >> 16)&0xFF
	message_highhh = (message_high >> 24)&0xFF

	message_lowll = message_low & 0xFF
	message_lowlh = (message_low >> 8) & 0xFF
	message_lowhl = (message_low >> 16) & 0xFF
	message_lowhh = (message_low >> 24) & 0xFF

	return can.Message(arbitration_id=can_address<<7|FLASH_DATA,data=[message_highhh,message_highhl,message_highlh,message_highll,message_lowhh,message_lowhl,message_lowlh,message_lowll],is_extended_id=False)




def write_flash(can_address,flash_address,nbWords,words_array):

	nBytes = nbWords * 4
	flashll = flash_address & 0xFF
	flashlh = (flash_address >> 8)&0xFF
	flashhl = (flash_address >> 16)&0xFF
	flashhh = (flash_address >> 24)&0xFF
	nbytesl = nBytes&0xFF
	nbytesh = (nBytes >> 8)&0xFF

	i=0

	msg1 = can.Message(arbitration_id=can_address<<7|WRITE_FLASH,data=[flashhh,flashhl,flashlh,flashll,nbytesh,nbytesl],is_extended_id=False)

	bus.send(msg1)

	unlockll = FLASH_UNLOCK_KEY & 0xFF
	unlocklh = (FLASH_UNLOCK_KEY >> 8)&0xFF
	unlockhl = (FLASH_UNLOCK_KEY >> 16)&0xFF
	unlockhh = (FLASH_UNLOCK_KEY >> 24)&0xFF


	msg2 = can.Message(arbitration_id=can_address<<7|SEND_UNLOCK_KEY,data=[unlockhh,unlockhl,unlocklh,unlockll],is_extended_id=False)

	bus.send(msg2)

	nbMessages = nbWords
	
	if(nbMessages == 0):
		print("Trying to send zero messages error")
	elif(nbMessages == 1):
		message1 = create_flash_message(can_address,flash_address,words_array[0],0xFFFFFFFF)
		bus.send(message1)

	elif(nbMessages == 2):
		#Then we write 1 full message
		message1 = create_flash_message(can_address,flash_address,words_array[0],words_array[1])
		bus.send(message1)
	elif(nbMessages == 3):
		#Then we write 1 full message and 1 half message
		message1 = create_flash_message(can_address,flash_address,words_array[0],words_array[1])
		message2 = create_flash_message(can_address,flash_address,words_array[2],0xFFFFFFFF)
		bus.send(message1)
		bus.send(message2)

	elif(nbMessages == 4):
		#Then we write 2 full messages
		message1 = create_flash_message(can_address,flash_address,words_array[0],words_array[1])
		message2 = create_flash_message(can_address,flash_address,words_array[2],words_array[3])
		bus.send(message1)
		bus.send(message2)

	else:
		print("Number of messages superior to 4")





#read_flash(6)
#read_version(6)
#time.sleep(1)
#write_flash(6,0x1800,12192)
#time.sleep(1)
#read_flash(6,0x1810,16)
#time.sleep(1)
#read_version(6)ep(1)
#read_version(6))_version(6)




f = open('normblink.hex','r')

for a in f:

	if a[0] == START_LINE:

		nbBytes = int(a[1:3],16)
		
		address = int(a[3:7],16)
		
		cmd = int(a[7:9],16)

		if cmd == EXTENDED_ADDRESS:
			address_high = int(a[9:13],16)

		elif cmd == DATA:
			address_low = address
			calculated_address = int(int((address_high << 16) + address_low)/2)
			nbWords = int(nbBytes/4)
			#print("Nbytes {0}, Address hi {1}, Address lo {2}, Cmd {3}, Words {4}".format(nbBytes,address_high,calculated_address,cmd,words))

			words_array = []
			if(nbBytes%4 == 0):	
				for i in range(nbWords):
					word24 = int(a[9+8*i:9+8*(i+1)],16)
					words_array.append(word24)
				write_flash(6,calculated_address,len(words_array),words_array)
				time.sleep(0.01)

				print("Length of word array {0}".format(len(words_array)))

			else:
				print("Number of bytes not a multiple of 4")
				break

		elif cmd == END_OF_FILE:
			print("End of file reached")

		else:
			print("Unknown command")


# time.sleep(1)
# write_flash(6,0x1804,4,[6546413,4688764,464513,65846451])
# time.sleep(1)
# read_flash(6,0x1804,8)
# time.sleep(1)
# read_flash(6,0x19DE,16)
# read_flash(6,0x19E6,16)
# read_flash(6,0x19EE,16)
# read_flash(6,0x19F6,16)