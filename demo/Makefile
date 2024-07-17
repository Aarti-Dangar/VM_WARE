#obj-m +=hello1.o
#obj-m +=task1.o
#obj-m +=task2.o
#obj-m +=task3.o
#obj-m +=task4.o
#obj-m +=task5.o
#obj-m +=task6.o
#obj-m +=task7.o
#obj-m +=task8.o
#obj-m +=task9.o
#obj-m +=task10.o
#obj-m +=task11.o
#obj-m +=task12.o
#obj-m +=task14.o
#obj-m +=task15.o
#obj-m +=task15_2.o
#obj-m +=task16.o
#obj-m +=task17.o
obj-m +=task13.o
#obj-m +=module_info.o
PWD :=$(CURDIR)
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
