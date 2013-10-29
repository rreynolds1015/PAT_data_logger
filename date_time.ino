// Function to print a preceding 0 to the LCD for date/time less than 10
void print_padded_digit(int value)
{
  if (value < 10) {
    lcd.print('0');
  }
  lcd.print(value,DEC);
}

// Function to print the date to the LCD
void print_date(DateTime *now)
{
  lcd.setCursor(DATE_COL,DATE_ROW);
  print_padded_digit(now->month());
  lcd.print('/');
  print_padded_digit(now->day());
}

// Function to print the time to the LCD
void print_time(DateTime *now)
{
  lcd.setCursor(TIME_COL, TIME_ROW);
  print_padded_digit(now->hour());
  lcd.print(':');
  print_padded_digit(now->minute());
  lcd.print(':');
  print_padded_digit(now->second());
}

// Function to allow setting Arduino's time using Time.h
time_t syncProvider() { return rtc.now().unixtime(); }
