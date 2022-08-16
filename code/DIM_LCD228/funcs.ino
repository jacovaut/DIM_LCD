// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  
  #ifdef V1 //voltage values for V1 boards
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 195)  return btnUP; 
  if (adc_key_in < 380)  return btnDOWN; 
  if (adc_key_in < 555)  return btnLEFT; 
  if (adc_key_in < 790)  return btnSELECT;
  #endif

  #ifdef V2 //voltage values for V2 boards
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT; 
  #endif

  return btnNONE;
}

void get_inputs(){
      
      show();
      // Note:  all the CNTRL signals are inverted, so we invert them here to get positive logic
  
      // read State of LED
      bitWrite(CUE1, 0, !digitalRead(CNTRL_A1)); // Red light
      bitWrite(CUE1, 2, !digitalRead(CNTRL_A2)); // Yellow light
      bitWrite(CUE1, 1, !digitalRead(CNTRL_A3)); // Green light
  
      // read Mode of operation
      bitWrite(CUE2, 0, !digitalRead(CNTRL_B1));
      bitWrite(CUE2, 2, !digitalRead(CNTRL_B2));
      bitWrite(CUE2, 1, !digitalRead(CNTRL_B3));

      if (read_LCD_buttons() == btnDOWN || currentPage == 99 || currentPage == 999){digitalWrite(lcd_light, HIGH);}
      else {digitalWrite(lcd_light, LOW);}
}

void printBinary(byte inByte)
{
  for (int i = 0;i < 3; i++)
  {
    lcd.print(bitRead(inByte, i));
  }
}

//delay function
bool del(unsigned long long mil){//mis is the amount of delay, in milliseconds
  
  unsigned long long startTime = millis();//get the start time

  while (millis() - startTime < mil){//if the difference between now and the start time, then wait
    if (analogRead(A0) < 1000){return true;}//if a button is pressed, exit
      get_inputs();
      show();
    }
}

void show(){
  if (currentPage == 99 || currentPage == 999){return;}// we don't want to show this for the tests
  
  if (read_LCD_buttons() != btnNONE && millis() - timeShow >= 150){
    if (read_LCD_buttons() == btnRIGHT && programPage < 2){programPage++;}
    if (read_LCD_buttons() == btnLEFT && programPage > 0 ){programPage--;}
    lcd.clear(); timeShow = millis();
  }

  switch (programPage){
    case 0:

      lcd.setCursor(0,0);
      lcd.print(String(program[currentPage][0]));
    
      lcd.setCursor(0,1);
      lcd.print("SPEED:");
      if (multiplier <= 10){lcd.print("0");}
      lcd.print(String(multiplier) + "x");
    break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("LAP:" + String(lap));
      
      lcd.setCursor(0,1);
      // print the elapsed time
      lcd.print("ELAPSED T: " + String(int((millis() - programStartTime)/1000/60)) + ":" + String(int(((float(millis() - programStartTime))/1000/60 - (millis() - programStartTime)/1000/60)*60)) + " ");//bruh
    break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("PWM var:" + String(float(PWM) / 255 * 100) + "%");

      lcd.setCursor(0,1);
      lcd.print("C1:");     
      printBinary(CUE1);
                    
      lcd.setCursor(9,1);
      lcd.print("C2:");
      printBinary(CUE2);
    break;
  }
}

//function to the reset program
void reset(bool full = false){//tempTime is used to reset the tempTime in the switch

    
  tempTime = 99999999;
  if (full){
    lcd.clear();
    
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(H_LED, LOW);
    
    scrollNo = 0;
    lap = 0;
    PWM = 0;

    programStartTime = millis();

    programPage = 0;

    Serial.println("full");
  }
}
