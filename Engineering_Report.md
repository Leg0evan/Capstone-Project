Drone Engineering Report
![IMG_8348](https://github.com/Leg0evan/Capstone-Project/assets/99287638/2b036e9b-b298-4ed7-b70d-894ffb8c203f)
Evan Buck & Piercen Lewis
5/8/2023

The drone has 4 brushless motors on the ends of legs that are connected to an ESP8266 along with an altimeter to get the altitude of the drone itself and 10 1.2v batteries to power said motors all controlled with an app called Blynk. The motors are connected to ESCs so we are able to control them without a motor controller and with an arduino. We have an altimeter that sends the altitude to Blynk and displays it and the altitude also dictates the landing and take-off functions. We have functions to take off the drone, land the drone, and go left, right, forward, and backward automatically when we tell it to. I think our design of the drone is ok for how quickly it was put together and constructed, if we had a little more time I think we researched more and had more time we could have done a lot better. I think we learned a lot of lessons, like the differences between brushed and brushless motors, how to use the internet with an arduino and much more. 

Steps:
Print the onShape files
Assemble the circuitry according to the wiring diagram
Screw the legs on along with the top base
Glue the rods to the top of the legs and the battery packs to the top plate
Screw the motors onto the ends of the legs and wrap the wires around the legs till their short enough
Put batteries in the battery packs and connect your phone to Blynk
Have fun and don't crash 


Parts & Links:
4 Brushless Motors

4 Electronic Speed Controllers(ESCs)

GYBMEP 280(Altimeter)

4 Steel Rods

ESP8266


Wires

10 1.2v Rechargeable Batteries

5 Battery Pack

M3 Screws and Nuts

PetG 3D Printed Parts

CAD Files:
[Files](https://cad.onshape.com/documents/65fef8c32d5ee98ec42242e7/w/a6ffd23002c7c7c04be48fc9/e/db9459acc91e294560bce7f8?renderMode=0&uiState=645912929d99114163089fca)

Four_motors:
 The main code that we put everything onto, it connects to Blynk, and runs functions depending on the inputs from Blynk as well as getting the altitude

Altimeter.ino:
The example code for the BMP280 and the code from this got stripped down to the basics so it would take less lines of code

Capstone_Project_Code_Test.ino:
The original test code from before we had the motors themselves and when we thought we would need a motor controller to make work

Gyroscope_Test.ino:
The example code for the gyroscope that we originally planned on using but decided not to use due to budget constraints

Motor.ino:
The original code we made controls a singular motor and not 4. We messed around with this code to learn how to make 4 motors work
