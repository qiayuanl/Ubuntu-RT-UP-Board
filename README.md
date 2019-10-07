# Ubuntu-RT-UP-Board
The RT-PREEMPT 4.4 kernel of ubuntu for UP board.

Support:
* GPIO
* LEDs
* UART
* SPI
* I2C

Unsupport:
* HDMI Audio
# Set up on UP board
## Install ubuntu
1. Download Ubuntu 16.04.6 ISO from the Ubuntu download page (works with desktop and server edition)

    http://releases.ubuntu.com/16.04/ubuntu-16.04.6-desktop-amd64.iso
    http://releases.ubuntu.com/16.04/ubuntu-16.04.6-server-amd64.iso

2. Burn the downloaded image on a USB stick. We suggest to use etcher for doing that. You can download it from:

    https://etcher.io

3. Insert the USB installer disk in a empty USB port and proceed with a normal Ubuntu installation.
## Get and replace the kernel
After install the ubuntu we need to get and replace the kernel for real time properties and the to be able to use the GPIO, PWM, SPI, I2C and uart.
### Download from release
1. Download the `UP-board-4.4.86-rt99.deb.tar.xz` debian packages from release

    https://github.com/QiayuanLiao/Ubuntu-RT-UP-Board/releases/download/UP-board-4.4.86-rt99/UP-board-4.4.86-rt99.deb.tar.xz
2. Uncompress


### Build from source
1. Get the source:
    ```
    git clone git@github.com:QiayuanLiao/Ubuntu-RT-UP-Board.git
    cd Ubuntu-RT-UP-Board
    ```
2. Config the kernel:
    ```
    cp .config kernel
    cd kernel
    make menuconfig
    ```
    selet save and exit

3. Make the kernel
    ```
    make -j`nproc` && make -j`nproc` bindeb-pk
    ```
Then you will get:

```
linux-firmware-image-4.4.86-rt99_4.4.86-rt99-1_amd64.deb
linux-headers-4.4.86-rt99_4.4.86-rt99-1_amd64.deb
linux-image-4.4.86-rt99_4.4.86-rt99-1_amd64.deb
linux-libc-dev_4.4.86-rt99-1_amd64.deb
```

### Replace the kernel
1. Copy the debian packages to UP board

2. Remove all the generic installed kernel
```
sudo apt-get autoremove --purge 'linux-.*generic'
```
3. Go to the file of debian packages and install the kernel:

```
sudo dpkg -i linux-*.deb
```
4. Reboot
```
sudo reboot
```