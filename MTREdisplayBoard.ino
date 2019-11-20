
/*
 * Mechatronics display board
 * 
 * 
 * adopted ServoMoodIndicator sketch to fit our needs, reading an infrared range finder instead of a pot
 * 
 * 
 */

 #include<Servo.h>


Servo displayServo;  // create a servo object

int const rangePin = A0; // analog pin used to connect the range finder
int rangeVal;  // variable to read the value from the analog pin
int angle;   // variable to hold the angle for the servo motor
int loopCounter = 0; //average control
int sumRangeVal = 0 ; //running sum of range value
int averageRangeVal; //averages range



void setup() {
  // put your setup code here, to run once:
  displayServo.attach(9); // attaches the servo on pin 9 to the servo object
  Serial.begin(9600); // open a serial connection to your computer
  
}

void loop() {

  //read and average range to denoise range sensor input
  rangeVal = analogRead(rangePin); // read the value of the potentiometer
  loopCounter++;
  sumRangeVal += rangeVal;
  averageRangeVal = sumRangeVal/loopCounter;
  if (loopCounter > 10){
    loopCounter = 0;
    sumRangeVal =0;
  }
  
  // print out the value to the Serial Monitor
  Serial.print("averageRangeVal: ");
  Serial.print(averageRangeVal);
  

  // scale the numbers from the range sensor
  angle = map(averageRangeVal, 0, 500, 179, 0);

  // print out the angle for the servo motor
  Serial.print(", angle: ");
  Serial.println(angle);

  // set the servo position
  displayServo.write(angle);

  // wait for the servo to get there
  delay(50);

}
