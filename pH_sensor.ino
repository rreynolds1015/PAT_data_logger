float getpHdata()
{
  // Insert code here to get and return the pH value
  return 1;
}

void calibratepH()
{
  // Set up variables to determine when the buffer value has been stored
  byte seven = 0;
  byte four = 0;
  byte ten = 0;
  // Variable to hold the value returned from ReadButtons
  byte button;
  
  // Clear the LCD and start giving the user messages
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("pH Calibration");
  
  do 
  {
    pHValue = getpHdata();
    byte pHPos = getpHpos(pHValue);
    lcd.setCursor(pHPos,1);
    lcd.print(pHvalue,0);
    lcd.setCursor(14,1);
    lcd.print("pH");
    
    if (seven == 0)
    {
      lcd.setCursor(0,1);
      lcd.print("pH 7");
    }
    else if (four == 0)
    {
      lcd.setCursor(0,1);
      lcd.print("pH 4");
    }
    else if (ten == 0)
    {
      lcd.setCursor(0,1);
      lcd.print("pH 10");
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("LFT=EXIT");
    }
    
    button = ReadButtons();
    if (button == RIGHT)
    {
      if (seven == 0)
      {
        pHserial.print("s\r");
        seven = 1;
      }
      else if (four == 0)
      {
        pHserial.print("f\r");
        four = 1;
      }
      else if (ten == 0)
      {
        pHserial.print("t\r");
        ten = 1;
      }
    }
    if (button == SELECT) pHserial.print("x\r");
  }
  while (button !=LEFT)
}
