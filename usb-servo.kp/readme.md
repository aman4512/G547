Servo Motor Control using ATmega8A

Summary:

The main aim of this project is to control servo motor connected to ATmega8 using CLI. Servos are connected with three-wire-cables. A red and a black one for the power, and a yellow one for the signal. Power has to be between 4.8 and 6 volts, so the 5 volts from the USB-port is in the range. The angle of the servo is controlled with pulse width modulation (PWM).

Directory tree:

usb-servo
|
|------firmware
|------commandline-ioctl
|------commandline-libusb
|------common

Schematic:
 

Prototype

Compiling & Uploading the firmware:

This project requires avr-gcc and avr-libc. 

Set the fuse-bits to enable the external crystal as clock source:

`$ avrdude -p atmega8 -P /dev/parport0 -c stk200 -U hfuse:w:0xC9:m -U lfuse:w:0x9F:m`

To compile and flash to the device:

`$ make program`

Compiling & Inserting Kernel Module:
To compile the module go to the directry servo_ioctl & run following:
    $ make all
To  insert the module in kernel:
    $ sudo insmod servo_ioctl.ko


Compiling & Executing User Space Code:
To compile user space code go to the directory   & write following:
    $ gcc -o 
To execute the user space code:
    $ /xyz.out

Test Commands:
