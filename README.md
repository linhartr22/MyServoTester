# MyServoTester
Uses an Arduino as a Server/ESC Tester. 

I used a 50K Ohm potentiometer I had sitting around. The two outside legs connect to VCC and ground. The center leg connects to an Arduino Analog input (I used A0). The servo motor connects to VCC and ground and the signal wire connects to an Arduino Digital Output (I used pin 10). If the servo rotates reverse of the dial you can swap the VCC and ground legs of the potentiometer.

The code maintains an average of a number of samples to smooth the Analog input.

The code will start with the servo in one of three positions, depending on the position of the dial. Anywhere near the center to begin with the server exactly at center. Anywhere to the far left or right and it will begin at the full extent of that side. The servo will hold this position until a significant amount of movement of the dial. This feature is used to put the servo in a known orientation
