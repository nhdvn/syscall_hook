obj-m += hooker.o

kdir = /lib/modules/`uname -r`/build

all:
	make -C $(kdir) M=`pwd` modules
clean:
	make -C $(kdir) M=`pwd` clean