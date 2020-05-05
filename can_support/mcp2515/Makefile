# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m := mcp2515_can.o 

# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else

	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD  := $(shell pwd)

default: clean
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install: default
	cp mcp2515_can.ko  /lib/modules/$(shell uname -r)/kernel/drivers/platform/x86
	depmod -A
	chmod +x mcp2515_can
	cp mcp2515_can /etc/init.d/
	ln -s /etc/init.d/mcp2515_can /etc/rc.d/rc3.d/Smcp2515_can || true  	
	ln -s /etc/init.d/mcp2515_can /etc/rc.d/rc5.d/Smcp2515_can || true
	modprobe mcp2515_can

uninstall:
	modprobe -r mcp2515_can
	rm -f /lib/modules/$(shell uname -r)/kernel/drivers/platform/x86/mcp2515_can.*
	depmod -A
	rm -f /etc/init.d/mcp2515_can
	rm -f /etc/rc.d/rc3.d/Smcp2515_can
	rm -f /etc/rc.d/rc5.d/Smcp2515_can
clean:
	rm -rvf *.ko *.o .*.cmd *.mod.c *.order *.symvers .*tmp_versions
endif

