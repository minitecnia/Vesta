<p align="center">
<img src="https://github.com/minitecnia/openhw-milcan/blob/master/logo-minitecnia.jpg" alt="SocketCAN logo" width=50% height=50% />
</p>

# Installing Web Server onto the Pi for remote access

This guide will tell you how to get your Raspberry Pi to host a web-server to host online services. 

# Ensure Pi is up to date

$ sudo apt-get update -y

# Install NodeJS onto the Pi and check installation

$ sudo apt-get install nodejs -y

$ nodejs -v

# Install NPM and check installation

$ sudo apt-get install npm -y

$ npm -v

# Install the Express and Express generator

$ sudo npm install express -g

$ sudo npm install express-generator -g

# Run the Express generator

This creates a folder with the necessary files needed for express to run. The default view engine will be Pug.

$ sudo express Raspizarro

Utilizing the default port, open a web browser and navigate to:

http://localhost:3000
