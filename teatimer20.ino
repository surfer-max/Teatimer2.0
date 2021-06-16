 /* ///////////////////////////////////////////////////////////////////////////////////
  Teatimer2.0 - by Max Reinecke & family
  Created: May 2021
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  /////////////////////////////////////////////////////////////////////////////////*/
  
#define VERSION 2.0
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <Servo.h> 
#include <Bounce2.h>
#include <DFPlayerMini_Fast.h> // + firetimer.h bib
#include <avr/sleep.h>

//###############################################################################################################
// to be adapted by the user
#define MIN_HEIGHT 68 // maximum height of the arm
#define MAX_HEIGHT 7 // minimum height of the arm
#define START_HEIGHT 20 // start height of the arm - usefull if set to the maximum height
#define LANGUAGE 0// 0 - German, 1 - English
#define MP3_VOLUME 30 // volume of MP3 - range 0-30
#define INTERVALL_SHUTDOWN 15 // time intervall in minutes until system goes into standby
//###############################################################################################################

// Servo
#define SERVO_PIN 8
Servo teaServo;

// rotary encoder
#define ROTARY_SW 3
#define ROTARY_DT 10
#define ROTARY_CLK 11
Bounce  myRotaryEncoderButton = Bounce();
static uint8_t prevNextCode_ROT = 0;
static uint16_t store_ROT=0;
static int8_t val_ROT; 

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// MP3 player
DFPlayerMini_Fast myMP3;

long myBrewingDuration = 0; // brewing duration in milliseconds
bool myBrewingDurationChanged = false; // has the user changed the brewing duration during brewing?
long myStartTime = 0; // time in milliseconds when brewing started
long myRemainingTime = 0; // time remaining of brewing in milliseconds 

const byte myMinHeight = MIN_HEIGHT;
const byte myMaxHeight = MAX_HEIGHT;
byte myStartHeight = START_HEIGHT;
byte myCurrentHeight = myStartHeight;

long myLastDisplayTime = 0;
byte myDisplayStatus = 0; // 0 - welcome // 1 - set arm height // 2 - set time // 3 - brewing // 4 - end
long myIntervallTillShutdown = INTERVALL_SHUTDOWN * 60000; // time intervall in milliseconds until system goes into standby 
long myIdleTime = 0; // time without user interaction or brewing - used for standby
long myLastPressedTime = 0;

byte myLanguage = LANGUAGE; // 0 - German, 1 - English

//###############################################################################################################
void setup() 
{
  lcd.init(); 
 
  // Rotary Encoder Button
  pinMode(ROTARY_SW,INPUT_PULLUP); 
  myRotaryEncoderButton.attach(ROTARY_SW);
  myRotaryEncoderButton.interval(10); // 10ms zum Entprellen  

  Serial.begin(9600);
  Serial1.begin(9600);

  myMP3.begin(Serial1);
  myMP3.volume(MP3_VOLUME);  //Set volume value. From 0 to 30
  
  // Rotary Encoder
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DT, INPUT);

  welcome();
}
//###############################################################################################################

//###############################################################################################################
void loop() 
{ 
  updateRotaryEncoderButton();
  
  if(val_ROT=read_rotary_ROT()) rotaryEncoderTurned(val_ROT); 
    
  if(myDisplayStatus == 3) brewing();

  // in all cases except of brewing go to standby in case of long idle time
  if (myIdleTime != 0 && (millis() - myIdleTime > myIntervallTillShutdown) && myDisplayStatus != 2) 
  {
    goInStandBy();
  }
}
//###############################################################################################################

// on each button press the display is changed & some action is done
void changeDisplayStatus()
{
  myIdleTime = millis();
   
  if (myDisplayStatus == 0) // 0 - welcome --> 1 - set arm height 
  {
    lcd.clear();
    myStartHeight = myMaxHeight;
    setStartHeight(0);
    myDisplayStatus = 1; 
  }
  else if (myDisplayStatus == 1) // 1 - set arm height --> 2 - set time
  {
    lcd.clear();
    setBrewingTime(0);
    myBrewingDuration = 0;
    myDisplayStatus = 2;
  }
  else if (myDisplayStatus == 2) // 2 - set time --> 3 - brewing 
  { 
    if (myBrewingDuration > 0)
    {
      lcd.clear();
      myStartTime = millis();
      myDisplayStatus = 3; 
    }
  }
  else if (myDisplayStatus == 4) // 4 - end --> 0 - welcome
  {
    myBrewingDuration = 0;
    myDisplayStatus = 0; 
    welcome();
  }
}

void setStartHeight(int dir)
{
  myStartHeight = myStartHeight + dir * 3;
  if (myStartHeight > myMinHeight) myStartHeight = myMinHeight;
  if (myStartHeight < myMaxHeight) myStartHeight = myMaxHeight;
  
  teaServo.write(myStartHeight);
  myCurrentHeight = myStartHeight;

  lcd.setCursor(0,0);
  if (myLanguage == 0) lcd.print(F("Starthoehe"));
  if (myLanguage == 1) lcd.print(F("Start height"));
  lcd.setCursor(0,1);
  lcd.print("      ");
  lcd.setCursor(0,1);
  lcd.print(myCurrentHeight);
}

void setBrewingTime(int dir)
{
  myIdleTime = millis();
  myBrewingDuration = myBrewingDuration + dir * 30000;
  if (myBrewingDuration < 0) 
  {
    myBrewingDuration = 0;
  }
  lcd.setCursor(0, 0);
  if (myLanguage == 0) lcd.print(F("Ziehzeit")); 
  if (myLanguage == 1) lcd.print(F("Brewing time")); 
  lcd.setCursor(0,1); 
  printTimeInMinutesSeconds(myBrewingDuration);
}

void changeBrewingDuration(int dir)
{
   myBrewingDurationChanged = true;
   myBrewingDuration = myBrewingDuration + dir * 30000;
   if (myBrewingDuration < 0) myBrewingDuration = 0;
}

void brewing()
{
  myRemainingTime = myBrewingDuration - (millis() - myStartTime);
  
  if (myRemainingTime > 0)
  {
    if (millis() - myLastDisplayTime > 1000 || myBrewingDurationChanged)
    {
      myBrewingDurationChanged = false;
      myLastDisplayTime = millis();
      
      lcd.setCursor(0, 0);
      if (myLanguage == 0) lcd.print(F("Restzeit")); 
      if (myLanguage == 1) lcd.print(F("Remaining")); 
      lcd.setCursor(0,1); 
      printTimeInMinutesSeconds(myRemainingTime);
    }
  }
  else
  {
    myIdleTime = millis();   
    myMP3.play(2);  //Play the second mp
    lcd.clear();
    lcd.setCursor(0, 0);
    if (myLanguage == 0) lcd.print(F("Tee ist fertig! :)")); 
    if (myLanguage == 1) lcd.print(F("Tea is ready! :)")); 
    myDisplayStatus = 4; 
    slowlyUpToEndPos();
  }
}

void welcome()
{
  myMP3.play(1);  //Play the first mp3
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  if (myLanguage == 0) lcd.print(F("Hallo Mama 2.0")); 
  if (myLanguage == 1) lcd.print(F("Hello Mama 2.0")); 
  teaServo.attach(SERVO_PIN); 
  goToMaxPos();
  myIdleTime = 0; // set to zero - to allow startup after standby
}

void goInStandBy()
{
  lcd.clear();
  lcd.noBacklight(); // save power
  teaServo.detach(); // save power
  myBrewingDuration = 0;
  myIdleTime = 0;
  myDisplayStatus = 4;
}

void goToMaxPos()
{
   teaServo.write(myMaxHeight);   
}

void slowlyUpToEndPos()
{
  for (myCurrentHeight; myCurrentHeight >= myMaxHeight; myCurrentHeight = myCurrentHeight - 1)
  {
    teaServo.write(myCurrentHeight);   
    delay(50);
  }
}

void printTimeInMinutesSeconds(long milliseconds)
{
  int seconds = ((milliseconds/1000)%60);
  int minutes = (milliseconds /1000)/60;
  if(minutes < 10) lcd.print("0");  
  lcd.print(minutes);
  lcd.print(":");
  if(seconds < 10) lcd.print("0");
  lcd.print(seconds);
}

void updateRotaryEncoderButton()
{
  myRotaryEncoderButton.update(); 
  if (myRotaryEncoderButton.fallingEdge()) // button pressed 
  {
    myIdleTime = millis();
    myLastPressedTime = millis();
    changeDisplayStatus();
  }
  if (myRotaryEncoderButton.risingEdge()) // button released
  {
    if (millis() - myLastPressedTime > 2000) goInStandBy(); // long press > 5 Sec --> standby
  }
}

void rotaryEncoderTurned(int dir)
{
  dir = dir * -1; // reverse direction for better HMI
  if (myDisplayStatus == 0) changeDisplayStatus();
  if (myDisplayStatus == 1) setStartHeight(dir);
  if (myDisplayStatus == 2) setBrewingTime(dir);
  if (myDisplayStatus == 3) changeBrewingDuration(dir);
  myIdleTime = millis();
}

 // A vald CW or  CCW move returns 1, invalid returns 0.
int8_t read_rotary_ROT() {
  static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  prevNextCode_ROT <<= 2;
  if (digitalRead(ROTARY_DT)) prevNextCode_ROT |= 0x02;
  if (digitalRead(ROTARY_CLK)) prevNextCode_ROT |= 0x01;
  prevNextCode_ROT &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[prevNextCode_ROT] ) {
      store_ROT <<= 4;
      store_ROT |= prevNextCode_ROT;
      if ((store_ROT&0xff)==0x2b) return -1;
      if ((store_ROT&0xff)==0x17) return 1;
   }
   return 0;
}
