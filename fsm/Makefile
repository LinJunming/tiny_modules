MODULE_NAME:=scanHsm
obj-m:=$(MODULE_NAME).o
scanHsm-objs:=scanner.o
scanHsm-objs+=fsm.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean