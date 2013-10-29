// Function to write data to the SD card via the serial port
void pad_serial (int value)
{
  if (value < 10) {
    Serial.print('0');
  }
  Serial.print(value,DEC);
}

void LogData(float ORPvalue, DateTime *now)
{
  pad_serial(now->month());
  Serial.print('/');
  pad_serial(now->day());
  Serial.print('/');
  Serial.print(now->year());
  
  Serial.print(',');
  pad_serial(now->hour());
  Serial.print(':');
  pad_serial(now->minute());
  Serial.print(':');
  pad_serial(now->second());
  Serial.print(',');
  
  Serial.print(ORPvalue,2);
  Serial.print('\n');
}

// Function to use the button shield to set the frequency for data logging.
void setLogFreq()
{ 
  byte button;
  do
  {
    button = ReadButtons();
    if (button == UP) logFreq = logFreq + 5;
    if (button == DOWN) logFreq = logFreq - 5;
    if (logFreq < 5) logFreq = 5;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set log freq");
    lcd.setCursor(0,1);
    lcd.print("RT=EXIT");
    lcd.setCursor(13,1);
    lcd.print("sec");
    if (logFreq < 10)
    { lcd.setCursor(11,1); }
    else if (logFreq < 100)
    { lcd.setCursor(10,1); }
    else
    { lcd.setCursor(9,1); }
    lcd.print(logFreq);
    delay(200);
  }
  while (button != RIGHT);
}
