obj-m := adxldriver.o
#EXTRA_CFLAGS += -Wno-incompatible-pointer-types

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm adxl

user:
	gcc adxl_user.c -o adxl
