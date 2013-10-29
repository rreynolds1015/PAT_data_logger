/*ADC voltages seen on A0 for the 5 buttons:

  Button        Voltage        8bit          10bit
  __________    __________     _________     __________
  RIGHT         0.00V          0             0
  UP            0.71V          36            145
  DOWN          1.61V          82            329
  LEFT          2.47V          126           505
  SELECT        3.62V          184           741
*/

// Function to determine which button was pressed
byte ReadButtons()
{
 unsigned int buttonVoltage;
 byte button = BUTTON_NONE;
 
 // Read the button ADC pin voltage
 buttonVoltage = analogRead( BUTTON_ADC );
 // Is the voltage within a valid range
 if (        buttonVoltage < ( RIGHT_10BIT + HYSTERESIS ))
 {
   button = RIGHT;
 }
 else if(    buttonVoltage >= ( UP_10BIT - HYSTERESIS )
          && buttonVoltage <= ( UP_10BIT + HYSTERESIS ))
 {
   button = UP;
 }
 else if(    buttonVoltage >= ( DOWN_10BIT - HYSTERESIS )
          && buttonVoltage <= ( DOWN_10BIT + HYSTERESIS ))
 {
   button = DOWN; 
 }
 else if(    buttonVoltage >= ( LEFT_10BIT - HYSTERESIS )
          && buttonVoltage <= ( LEFT_10BIT + HYSTERESIS ))
 {
   button = LEFT;
 } 
 else if(    buttonVoltage >= ( SELECT_10BIT - HYSTERESIS )
          && buttonVoltage <= ( SELECT_10BIT + HYSTERESIS ))
 {
   button = SELECT;
 }
 
 // Handle button flags for just pressed and just released events
 if ( (buttonWas == BUTTON_NONE ) && (button != BUTTON_NONE ) )
 {
   buttonJustPressed = true;
   buttonJustReleased = false;
 }
 if ( (buttonWas != BUTTON_NONE ) && (button == BUTTON_NONE ) )
 {
   buttonJustPressed = false;
   buttonJustReleased = true;
 }
 buttonWas = button;
 return(button);
}
