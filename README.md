# 📟Canteen Food Ordering System🍽️

Thank you for visiting our CSE 316 Microcontroller project. We have put in place a cashless, automated food ordering system after being fed up with the lengthy lines that formed during peak hours in our ECE canteen.

## Key Features
- Secure login using Personal RFID Card and Password
- Communication via bluetooth with a python server for sensitive user info
- Food Order Using Keypad and LCD Screen
- Order Confirmation Message to user's personal phone using Python API
- Persistent Balance of users using SQLite Server

## Components
- Arduino Mega 2560 - 1
- 20x4 LCD Screen with I2C converter - 1
- HC05 Bluetooth Module - 1
- MRFC522 RFID Card Reader - 1
- 4x4 Matrix Keypad - 1

## Circuit Diagram
![image](https://user-images.githubusercontent.com/76593389/187836317-9e5e074a-a65a-47fb-923a-020202c7fd76.png)

## Recreating Using our Code
Our Code is divided into two parts. 
1. The **Python Codes** folder hold the necessary codes for maintaining bluetooth connection, sending message and maintaining the database.
2. Arduino Codes were written using Platform IO extension in VSCode. External libraries include-
	- [MFRC522 Library](https://github.com/miguelbalboa/rfid?utm_source=platformio&utm_medium=piohome)
	- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C?utm_source=platformio&utm_medium=piohome)
	- [Keypad Library](https://playground.arduino.cc/Code/Keypad/)
3. To start with arduino,open the whole project in vscode. With platformio extension added, simply go to src, then run main.cpp and burn it into arduino from the bottom ribbon in platformio. You need to connect ypur pc's bluetooth to the module of our project. To do so,while arduino is running and the hc05 bluetooth module is blinking, open your bluetooth and search for hc05 in new devices. Then pair with the module. The blinking pattern will change and now it'll blink one every three seconds.
4. You need to install pyserial from command to continue. To do so,run the command from command prompt : 
```bash
pip install pyserial
```
5. After connecting the module, run and burn main.cpp again. now open python codes and go to server.py. Run the program and you should be able to do the rest according to the video.
6. Pyserial uses serial ports. Bluetooth module may have different port serials. To know which serial your paired module is using, run findport.py.  then change the port in the server.py program and run.


## Challenges
We had no prior experience communicating between Python and HC05. Most of our hours were spent toiling at different python libraries. After trying out different ones, we settled on using [Python's Serial](https://pyserial.readthedocs.io/en/latest/pyserial.html) library and writing our own codes catered to our needs.

We found our serial communication was receiving garbage values on both ends. Filtering out correct values, on both ends, took a long time.

## Shortcomings
Bluetooth and the RFID card reader occasionally stopped working. It started working once more after manually reconnecting the Arduino's RX1 and TX1 pins. We were unable to identify a suitable remedy. Any recommendations are welcome.

## Group Members
1. Sheikh Hasanul Banna (1805094) 
2. Partho Kunda (1805107) 
3. Udayon Paul Dhrubo (1805109) 


## Supervised By
1. Md. Shariful Islam Bhuyan, Assistant Professor, CSE, BUET 
2. Sukarna Barua, Assistant Professor, CSE, BUET 
3. Md. Masum Mushfiq, Lecturer, CSE, BUET 

