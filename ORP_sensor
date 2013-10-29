// Functions for accessing the Atlas Scientific ORP module

// Function that looks for events on the serial interface.  Easiest method to 
// send calibration events to the Atlas ORP
void serialEvent()
{
  received_from_computer = Serial.readBytesUntil(13,computerdata,20);
  computerdata[received_from_computer] = 0;
  orpSerial.print(computerdata);
  orpSerial.print('\r');
}

// Function to get (and return) the value from the ORP sensor
float getORPdata()
{
  if (orpSerial.available() > 0)
  {
    received_from_sensor=orpSerial.readBytesUntil(13,sensor_data,20);
    sensor_data[received_from_sensor]=0;
    string_received=1;
  }
  if (string_received==1)
  {
    ORP=atof(sensor_data) + offset;
    string_received = 0;
  }
  
  // Average multiple ORP readings to try and stabilize the output
  total = total - readings[index];
  readings[index] = ORP;
  total = total + readings[index];
  index = index++;
  if (index >= numReadings) index = 0;
  average = total / numReadings;
  
  return average;
}

// Function to send calibration commands to the ORP board. May still be buggy.
// Calibration not functioning.  Can increase or decrease by 1 mV; but no more.
void startCalibration()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibration");
  lcd.setCursor(0,1);
  lcd.print("LFT=EXIT");
  byte button;
  do 
  {
    ORPvalue = getORPdata();
   
    byte orpPos = getORPPos(ORPvalue);
 
    lcd.setCursor(orpPos,1);
    lcd.print(ORPvalue,0);
    lcd.setCursor(14,1);
    lcd.print("mV");
    
    button = ReadButtons();
    if (button == UP) offset = offset++;
    if (button == DOWN) offset = offset--;
    if (button == SELECT) 
    {
      orpSerial.print("X\r");
      offset = 0;
    }
    delay(100);
  }
  while (button != LEFT);
}

byte getORPPos(float ORPvalue)
{
  byte orpPos;
  
  if (abs((ORPvalue / 1000)) >= 1)
    orpPos = 9;
  else if (abs((ORPvalue / 100)) >= 1)
    orpPos = 10;
  else if (abs((ORPvalue / 10)) >= 1)
    orpPos = 11;
  else
    orpPos = 12;
    
  if (ORPvalue < 0) orpPos = orpPos--;
  
  return orpPos;
}
