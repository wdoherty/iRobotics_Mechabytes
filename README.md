# Mechabytes
MRDC Team 2020

This repository contains all code developed for the Mechabytes MRDC competition team. 

Code is broken into two sections that work in tandem to run the robot: 

Driver Station software is run on a laptop. This takes input from a USB gamepad controller, 
turns that information into a packet, and sends it to the robot wirelessly via XBee serial communication.

The main robot code is run by our microcontroller, which is currently a Raspberry Pi 3. 
This processes the controller input, along with sensor feedback, to set motor and solenoid outputs.

For more information, contact us at mechabytes.robotics@gmail.com
