#obj-m +=sample.o
#obj-m +=2.o
#obj-m +=3.o
#obj-m +=class_device.o
#obj-m +=class_device2.o
#obj-m +=device_file.o
#obj-m +=device_file2.o
#obj-m +=device_file3.o
#obj-m +=fops4.o
#obj-m +=fops7b.o
#obj-m +=fops8.o
obj-m +=fops81.o
#obj-m +=fops9.o
#obj-m +=fops10.o
#obj-m +=fops11.o
#obj-m +=fops12.o
#obj-m +=hello15.o
PWD :=$(CURDIR)
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

