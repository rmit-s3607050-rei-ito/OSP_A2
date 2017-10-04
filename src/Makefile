obj-m:=S3607050Device.o

KERNEL_DIR = /usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
	gcc -Wall -pedantic S3607050UserApplication.c -o UserApp

clean:
	rm -rf *.o *.ko *.mod *.mod.c *.symvers *.order *~ UserApp
