#Cross-compiler prefix for ARM
#CC :=  arm-linux-gnueabihf-gcc
 
#obj-m += platform_device.o
#obj-m += platform_setup.o
#PWD := $(CURDIR)
 
# Default target
#all:
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/aartidangar/bbb/linux/ M=$(PWD) modules
 
# Clean rule
#clean:
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/aartidangar/bbb/linux/ M=$(PWD) clean
 
obj-m += platform_driver.o
obj-m += platform_setup.o

PWD := $(CURDIR)
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

