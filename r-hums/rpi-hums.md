<p align="center">
<img src="https://github.com/minitecnia/openhw-milcan/blob/master/logo-minitecnia.jpg" alt="SocketCAN logo" width=50% height=50% />
</p>

# Rpi-hums installation

Download the latest Raspbian image from:

https://www.raspberrypi.org/downloads/raspbian/

$ sudo nano /etc/modprobe.d/raspi-blacklist.conf

After first time boot up, do an update and upgrade:

$ sudo apt-get update 

$ sudo apt-get upgrade 

$ sudo reboot

Add the overlays by:

# Installing PiCAN Module

$ sudo nano /boot/config.txt

Add these 3 lines to the end of file:

dtparam=spi=on 

dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25 

dtoverlay=spi-bcm2835-overlay

Reboot Rpi-hums:

$ sudo reboot

# Installing RTC DS3231

$ sudo nano /boot/config.txt

Add lines:

dtparam=i2c_arm=on

dtoverlay=i2c-rtc,ds3231

# Configure RTC

Disabling the fake hardware clock

$ sudo apt-get -y remove fake-hwclock

$ sudo update-rc.d -f fake-hwclock remove

$ sudo nano /lib/udev/hwclock-set

Comment rule:

# Installing I2C MPU6050 IMU

$ sudo nano /etc/modules

If not present, add next lines:

i2c-bcm2708

i2c-dev

# Installing Web Server onto the Pi for remote access

This guide will tell you how to get your Raspberry Pi to host a web-server to host online services. 

Ensure Pi is up to date

$ sudo apt-get update -y

Install NodeJS onto the Pi and check installation

$ sudo apt-get install nodejs -y

$ nodejs -v

Install NPM and check installation

$ sudo apt-get install npm -y

$ npm -v

# Install the Express and Express generator

$ sudo npm install express -g

$ sudo npm install express-generator -g

Run the Express generator

This creates a folder with the necessary files needed for express to run. The default view engine will be Pug.

$ sudo express Raspizarro

Utilizing the default port, open a web browser and navigate to:

http://localhost:3000

# Installing Raspberry Pi monitoring panel

$ cd PIzarro

Follow next procedure:

https://github.com/GeekyTheory/Raspberry-Pi-Status
