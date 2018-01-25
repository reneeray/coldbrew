

//Cold Coffee Drip Brew Tower
//John Edgar Park
//jp@jpixl.net


#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include "Adafruit_MotorShield.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Connect via SPI. For an Uno, Data pin is digital 11, Clock is digital 13 and Latch is digital 10 (code credit: Evan Feenstra)
Adafruit_LiquidCrystal lcd(11, 13, 12);
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *solenoid = AFMS.getMotor(4);


//const int ledPin = BUILTIN_LED;

const int openPin = A0;
const int closePin = A1;

int openValue = 187;//good default. if you don't use knobs, adjust here
int closeValue = 2500;//good default. if you don't use knobs, adjust here
int tempValue = 0;
int tempVoltageValue = 0;
float tempCent = 0.0;
float tempFahr = 0.0;



void setup() {
  
  //Debugging output
  Serial.begin(9600);
  //pinMode(valvePin, OUTPUT);
  //pinMode(ledPin, OUTPUT);

  /*
    The circuit:
   * 5V to Arduino 5V pin!!!!!!!!!!! not 3.3
   * GND to Arduino GND pin
   * CLK to SCK
   * DAT to MOSI
   * LAT to any digital pin
  */

  // set up the LCD's number of rows and columns:
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);

  //for adafruit motorshield v2
  AFMS.begin();
  solenoid->setSpeed(255);
  solenoid->run(RELEASE);

}

void loop() {
  //read the analog potentiometers
  openValue = analogRead(openPin);
  openValue = map(openValue, 0, 1023, 0, 4000);
  closeValue = analogRead(closePin);
  closeValue = map(closeValue, 0, 1023, 0, 8000);
  tempVoltageValue = analogRead(A3) * (3300 / 1024);
  tempCent = (tempVoltageValue - 500) / 10;
  tempFahr = (tempCent * 9 / 5.0) + 32;

  Serial.println("hi");
  //open
  //digitalWrite(ledPin, HIGH);
  //digitalWrite(valvePin, HIGH);
  solenoid->run(FORWARD);
  delay(1000);
  //delay(openValue);

  //close
  //digitalWrite(ledPin, LOW);
  //digitalWrite(valvePin, LOW);
  solenoid->run(RELEASE);
  delay(1000);
  //delay(closeValue);

  // Print Open parameter to LCD
  // set the cursor to column 0, line 0
  //(note: line 0 is the first row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("OP: ");
  lcd.setCursor(4, 0);
  lcd.print(openValue);

  //Print Close paramter to LCD
  lcd.setCursor(9, 0);
  lcd.print("CL: ");
  lcd.setCursor(13, 0);
  lcd.print(closeValue);

  //Print H20 Temp to LCD
  lcd.setCursor(1, 1);
  // Print a message to the LCD.
  lcd.print("H2O Temp: ");
  lcd.print(tempFahr);


}
