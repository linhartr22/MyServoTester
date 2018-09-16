/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
// Create Servo Object.
Servo myservo;
// Servo Digital Output Pin.
int servoPin = 10;
// Servo Value (0-180).
int servoVal;

// Dial Analog Input Pin.
int dialPin = 0;
// Dial Number of Samples.
#define DIAL_SAMPLES 5
// Dial Value Samples.
int dialVals[DIAL_SAMPLES];
// Dial Value Samples Index.
int dialValsX = 0;
// Dial Value Samples Total.
int dialValsTot = 0;
// Dial Value (0 - 1024).
int dialVal;
// Dial Value Last.
int dialValLast;
// Dial Delta.
int dialDelta = 1024*0.025;

void dialValSmooth() {
  // Remove Last Sample from Total.
  dialValsTot -= dialVals[dialValsX];
  // Get Current Sample.
  dialVals[dialValsX] = analogRead(dialPin);
  // Add Current Sample to Total.
  dialValsTot += dialVals[dialValsX];
  // Increment Index.
  dialValsX += 1;
  if (dialValsX >= DIAL_SAMPLES) {
    dialValsX = 0;
  }
  dialVal = dialValsTot/DIAL_SAMPLES;
}

void setup() {
  // Init Dial Samples.
  for (int i=0;i<DIAL_SAMPLES;i++) {
    dialVals[i] = analogRead(dialPin);
    // Update Dial Samples Total.
    dialValsTot += dialVals[i];
  }
  // Init Dial Value & Dial Value Last.
  dialVal = dialValsTot/DIAL_SAMPLES;
  dialValLast = dialVal;
  // Attach Servo to Servo Object.
  myservo.attach(servoPin);
  // Get Initial Servo Setting.
  if (dialVal < (1024/3)) {
    servoVal = 0;
  }
  else if (dialVal > (1024/3)*2) {
    servoVal = 180;
  }
  else {
    servoVal = 90;
  }
  myservo.write(servoVal);
}

void loop() {
  // Smooth Dial Value.
  dialValSmooth();
  // Dial Value Changed?
  if (abs(dialVal - dialValLast) >= dialDelta) {
    // Reduce Dial Delta.
    dialDelta = 1;
    // Dial Value Last = Current Dial Value
    dialValLast = dialVal;
    // Yes, Map Dial Value to Servo Scale.
    servoVal = map(dialVal, 0, 1023, 0, 180);
    // Update Servo.
    myservo.write(servoVal);
  }
  // Wait for Servo.
  delay(15);
}
