# agv_driver
Driver for AGV robot using dsPIC33EP256MC502


#Speed Calculation

Speed is calculated using the QEI module.
The encoder used has 750 counts/revolution ==> which means resolution is res = 0.00838 rad.
The robot operates at relatively low velocities : The wheels don't exceed 30 rad/s,
this means that using VEL1CNT register for measuring velocities isn't enough : For example, if
speed is measured at 1kHz, and wheels are running at 3 rad/s then a change of 0.003 rad needs to be detected
but 0.003 rad < res.
To compensate for this instead of using VEL1CNT we use INT1 timer register which outputs a timer value between successive encoder counts, from which we can then define speed.
This also requires to determine a minimum speed, otherwise speed error accumulates because of integrator.

Direction is calculated using the position counter.

The speed is therefore calculated as such:

	-Calculate speed from INT1HLDL
	-Calculate the direction from previous value and current value of counter
	-If speed is inferior to MIN_VALUE then speed is set to zero
	-Integrator accumulator is reset if requested speed is inferior to minimum speed





#Plotting 

	It is possible to output plot data to serial (speed is configured at 500kbaud) bus using write_data function.  
user must append /n at the end of sending, this is used by the plotting function to detect end of transmission.  

Data can be plotted in real time using the 'ser.py' script. Make sure to enter the correct number of floats to be read (values sent need to be floats, 4 bytes long).

#Can Bus transmission

The CAN bus uses the standard 11-bit frame addressing. The microcontroller has Hex wheel switch (HEX_ADDRESS) for selecting the address.
Frame id's use the following scheme:
	HEX_ADRESS (4 bits) | REQUEST_ID (7 bits)

All the different messages can be found in can_message.h. The filter and masks are set so that it only responds to message id's starting with
the correct HEX_ADDRESS




