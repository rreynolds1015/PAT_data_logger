// Includes
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
#include <SoftwareSerial.h>
#include <Time.h>
#include "definitions.h"

// Variable definitions
RTC_DS1307 rtc;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Variables for button events
byte buttonJustPressed = false;
byte buttonJustReleased = false;
byte buttonWas = BUTTON_NONE;

// Variables for ORP
const byte ORPrx = 2;
const byte ORPtx = 3;
SoftwareSerial orpSerial (ORPrx,ORPtx);
char sensor_data[20];
float ORP = 0;
float ORPvalue = 0;
float avgORP = 0;
byte string_received = 0;
byte received_from_sensor = 0;
int offset = 0;

// Variables for data logger
const byte logPin = 12;
boolean logData=false;
unsigned long nextDataPoint;
long logFreq = 5;

// Variables for data smoothing
const byte numReadings = 10;
float readings[numReadings];
byte index = 0;
float total = 0;
float average = 0;

// Variables for debugging with PC
byte received_from_computer = 0;
char computerdata[20];

// Setup section for Arduino framework
void setup()
{
 // Start the I2C functions for the RTC
 Wire.begin();
  
 // Set button input
 pinMode( BUTTON_ADC, INPUT );
 digitalWrite( BUTTON_ADC, LOW );      // Ensure the internal pullup is off
 
 // Set the pin for supplying power to the OpenLog board
 pinMode( logPin, OUTPUT );
 digitalWrite( logPin, LOW);
 
 // Turn on the LCD backlight
 pinMode( BACKLIGHT, OUTPUT );
 BACKLIGHT_ON();
 
 // Initialize the RTC
 rtc.begin();
 setSyncProvider(syncProvider);
 
 // Start the on-board serial and the software serial
 Serial.begin(38400);
 orpSerial.begin(38400);
 orpSerial.print("C/r");

 // Start the LCD and print a quick message
 lcd.begin(16,2);
 lcd.print("Starting up...");
 
 // Initialize the smoothing array to all 0's
 for (int thisReading = 0; thisReading < numReadings; thisReading++)
   readings[thisReading] = 0;
}

void loop()
{
  // Start with a fresh canvas every time
  lcd.clear();
  
  // Get the time for this cycle and print it to the LCD
  DateTime now = rtc.now();
  print_date (&now);
  print_time (&now);
  
  // Continually look for a button press event and react to it
  byte button;
  button = ReadButtons();
  
  // On a button press event, clear the area of the LCD for feedback
  if ( buttonJustPressed || buttonJustReleased )
  {
    lcd.setCursor(0,1);
    lcd.print( "       " );
  }
  
  // What's the status of the button press
  switch( button )
  {
    case BUTTON_NONE:
    { 
      break; 
    }
    case RIGHT:
    {
      startCalibration();
      break;
    }
    case UP:
    {
      break;
    }
    case DOWN:
    { break; }
    case LEFT:
    {
      setLogFreq();
      break;
    }
    case SELECT:
    {
      logData = !logData;
      if (logData == true)
      { 
        digitalWrite(logPin, HIGH);
        LogData(ORPvalue,&now);
        nextDataPoint = now.unixtime() + logFreq;
      }
      else
      { 
        digitalWrite(logPin, LOW); 
      }
      break;
    }
    default:
    { 
      break; 
    }
    
    // Reset the flags for if a button was pressed
    if ( buttonJustPressed )
      buttonJustPressed = false;
    if ( buttonJustReleased )
      buttonJustReleased = false;
   }
  
  ORPvalue = getORPdata();
   
  byte orpPos = getORPPos(ORPvalue);
   
  lcd.setCursor(orpPos,1);
  lcd.print(ORPvalue,0);
  lcd.setCursor(14,1);
  lcd.print("mV");
  
  // Check if we should be logging data to the SD card
  if (logData == true)
  {
    lcd.setCursor(0,1);
    lcd.print("Logging");
    // Okay, we should be logging data, but is it the time for the next datapoint?
    if (now.unixtime() >= nextDataPoint)
    {
      LogData(ORPvalue,&now);
      nextDataPoint = now.unixtime() + logFreq;
    }
  }
  delay(100);
}
