README
COSC1114 Operating Systems Principles Assignment 2

AUTHORS
Rei Ito - s3607050

CONTRIBUTORS
SolidusCode (soliduscode.com/)
Derek Molloy (derekmolloy.ie/)

FILES
Makefile
S3607050Device.c
S3607050Device.h
S3607050UserApplication.c
S3607050UserApplication.h

INSTALL
(as super user):
- make
- insmod S3607050Device.ko
- dmesg (get device number)
- mknod /dev/S3607050Device c device^number 0
- chmod 666 /dev/S3607050Device
- exit
(as regular user):
- ./UserApp

BUGS
- Non known at this time
