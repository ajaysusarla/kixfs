obj-m := kixfs.o
ccflags-y :=

PHONY += clean

all: ko

ko:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
