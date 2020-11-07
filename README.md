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
	-Integrator accumulator is reset



