# Ubuntu-RT-UP-Board
The RT-PREEMPT 4.4 kernel of ubuntu for UP board.
# Set up on UP board
## Install ubuntu
* Download Ubuntu 16.04.6 ISO from the Ubuntu download page (works with desktop and server edition)
```
http://releases.ubuntu.com/16.04/ubuntu-16.04.6-desktop-amd64.iso
http://releases.ubuntu.com/16.04/ubuntu-16.04.6-server-amd64.iso
```
* Burn the downloaded image on a USB stick. We suggest to use etcher for doing that. You can download it from
```
https://etcher.io
```
* Insert the USB installer disk in a empty USB port and proceed with a normal Ubuntu installation.
## Get and replace the kernel
After install the ubuntu we need to get and replace the kernel for real time properties and the to be able to use the GPIO, PWM, SPI, I2C and uart.
### Download from release
Download the debian packages from 
### Build from source