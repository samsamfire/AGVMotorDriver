import time

START_LINE = ':'
#Command types
EXTENDED_ADDRESS = 0x04
DATA = 0x00
END_OF_FILE =0x01


words_array =[0 for i in range(4)]

address_high = 0


f = open('normblink.hex','r')

#a=f.readline()

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
			if(calculated_address%4 != 0):
				print("Address not multiple of 4")
				print("Address value is {0}".format(calculated_address))
			nbWords = int(nbBytes/4)
			#print("Nbytes {0}, Address hi {1}, Address lo {2}, Cmd {3}, Words {4}".format(nbBytes,address_high,calculated_address,cmd,words))

			words_array = []
			if(nbBytes%4 == 0):	
				for i in range(nbWords):
					word24 = int(a[9+8*i:9+8*(i+1)],16)
					words_array.append(word24)
				print("Length of word array {0}".format(len(words_array)))

			else:
				print("Number of bytes not a multiple of 4")
				break

		elif cmd == END_OF_FILE:
			print("End of file reached")

		else:
			print("Unknown command")

	
	





	