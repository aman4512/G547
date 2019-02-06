Assignment 1

Building and loading:

1. Driver
```
$ make all
$ sudo insmod adxldriver.ko
```
2. Userspace program:
```
$ make user
```

Usage:

The module gives values for 3 accelerometer axes. The required axis can be passed as a command line parameter.
Example:

`sudo ./adxl -x` (Replace `adxl` with name of object file generated)

will give x axis value output.

`sudo ./adxl -xyz`

will give values for all three axes.
Similarly any two axes can also be queried.
