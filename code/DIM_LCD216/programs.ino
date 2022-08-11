void Select(){
    lcd.setCursor(0,0);
    lcd.print("PRESS ANY BUTTON");
    lcd.setCursor(0,1);
    lcd.print("TO STOP");
  
    delay(1000);
  
    lcd.clear();

    programStartTime = millis();

    tempTime = millis();//starting time
    
    while (analogRead(A0) > 1000){//while no button is pressed

      if ((CUE1 + CUE2) == 14){reset(true);}
      
      switch (currentPage) {
    case 99:
    ///Pour tester le système va flashé toutes les lumières en séquence et ensuite passer de PWM = 0% a PWM = 100% et denouveau a 0% graduelment
    
        lcd.setCursor(0,0);
        lcd.print("test1");
          
      /*  LED1  */
        lcd.setCursor(0,1);
        lcd.print("LED1");
        lcd.print("  Blink: 1/1");
        digitalWrite(LED1, HIGH);
        if(del(500)){break;}
        digitalWrite(LED1, LOW);
        if(del(500)){break;}
      /*  LED1  */
    
      /*  LED2  */
        for(int i = 0; i < 2; i++){
          lcd.setCursor(0,1);
          lcd.print("LED2");
          lcd.print("  Blink: " + String(i+1) + "/2");
          digitalWrite(LED2, HIGH);
          if(del(500)){break;}
          digitalWrite(LED2, LOW);
          if(del(500)){break;}
        }
      /*  LED2  */
    
      /*  LED3  */
        for(int i = 0; i < 3; i++){
          lcd.setCursor(0,1);
          lcd.print("LED3");
          lcd.print("  Blink: " + String(i+1) + "/3");
          digitalWrite(LED3, HIGH);
          if(del(500)){break;}
          digitalWrite(LED3, LOW);
          if(del(500)){break;}
        }
      /*  LED3  */
    
      /*  LED4  */
        for(int i = 0; i < 4; i++){
          lcd.setCursor(0,1);
          lcd.print("LED4");
          lcd.print("  Blink: " + String(i+1) + "/4");
          digitalWrite(LED4, HIGH);
          if(del(500)){break;}
          digitalWrite(LED4, LOW);
          if(del(500)){break;}
        }
      /*  LED4  */
    
      /*  LED5  */
        for(int i = 0; i < 5; i++){
          lcd.setCursor(0,1);
          lcd.print("LED5");
          lcd.print("  Blink: " + String(i+1) + "/5");
          digitalWrite(LED5, HIGH);
          if(del(500)){break;}
          digitalWrite(LED5, LOW);
          if(del(500)){break;}
        }
      /*  LED5  */
    
      /*  H_LED  */
        for(int i = 0; i < 6; i++){
          lcd.setCursor(0,1);
          lcd.print("H_LED");
          lcd.print(" Blink: " + String(i+1) + "/6");
          digitalWrite(H_LED, HIGH);
          if(del(500)){break;}
          digitalWrite(H_LED, LOW);
          if(del(500)){break;}
        }
      /*  H_LED  */
    
          for (int i = 0; i <= 255; i++){//augment PWM for every light
            analogWrite(LED1, i);
            analogWrite(LED2, i);
            analogWrite(LED3, i);
            analogWrite(LED4, i);
            analogWrite(LED5, i);
            analogWrite(H_LED, i);
            lcd.setCursor(0,1);
            lcd.print("PWM:" + String(int(float(i)/255*100)) + "%          ");//print PWM value
            if(del(100)){break;}
          }
          for (int i = 255; i >= 0; i--){//decrement PWM for every light
            analogWrite(LED1, i);
            analogWrite(LED2, i);
            analogWrite(LED3, i);
            analogWrite(LED4, i);
            analogWrite(LED5, i);
            analogWrite(H_LED, i);
            lcd.setCursor(0,1);
            lcd.print("PWM:" + String(int(float(i)/255*100)) + "% ");
            if(del(100)){break;}
          }
         break;
         
    case 999:
    ///Pour tester l'output de la tour
    
      lcd.setCursor(0,0);
      lcd.print("test2");
    
        lcd.setCursor(6,0);
        lcd.print("CUE1: ");
        
        printBinary(CUE1);
                
        lcd.setCursor(6,1);
        lcd.print("CUE2: ");

        printBinary(CUE2);
      
         break;
    
      case 0:
          // Mode range 2-5 selects the LED
          // "CUE1" selects the intensity in increments of 20%
          // Switch to Mode=6 before setting the new state (i.e. Mode=6, State=100%, Mode=1.... Mode=6, State=20%, Mode=2)
          // if(Mode == 1) {LED = LED1;}
          Serial.println("case 0");
          
          if (CUE2 == 2) {
            LED = LED1;
          }
          if (CUE2 == 3) {
            LED = LED2;
          }
          if (CUE2 == 4) {
            LED = LED3;
          }
          if (CUE2 == 5) {
            LED = LED4;
          }
          if (CUE1 == B001) {
            analogWrite(LED, PWM_100);
          }
          if (CUE1 == B100) {
            analogWrite(LED, PWM_50);
          }
          if (CUE1 == B010) {
            analogWrite(LED, PWM_25);
          }
          if (CUE1 == B101) {
            analogWrite(LED, PWM_12);
          }
          if (CUE1 == B011) {
            analogWrite(LED, PWM_6);
          }
          if (CUE1 == B000) {
            analogWrite(LED, PWM_0);
          }
          break;
          
      case 1:
        Serial.println("case 1");
          
          // Light scale #2
          if     (CUE1 == B001) {
            analogWrite(LED1, 16); // 6.25%  // tower red light is on
          }
          else if (CUE1 == B100) {
            analogWrite(LED1, 8); // 3.125% // tower yellow light is on
          }
          else if (CUE1 == B010) {
            analogWrite(LED1, 4); // 1.563% // tower green light is on
          }
          else if (CUE1 == B101) {
            analogWrite(LED1, 2); // 0.781% // tower red and yellow lights are on
          }
          else if (CUE1 == B011) {
            analogWrite(LED1, 1); // 0.391% // tower red and green lights are on
          }
          else if (CUE1 == B000) {
            analogWrite(LED1, 0); // 0%     // tower red, yellow and green lights are off
          }
          else  {
            analogWrite(LED1, PWM_0);
          }
          analogWrite(H_LED, PWM_50);
          analogWrite(LED2, PWM_50);
          analogWrite(LED3, PWM_50);
          analogWrite(LED4, PWM_50);
          break;
    
    case 2:
        //control middle light and augment house light every 8 minutes
        Serial.println("case 2"); 
          
          if (millis() - tempTime >= eight)
          {
            if     (num == 0) {
              PWM = PWM_6;
              num++;
            }
            else if (num == 1) {
              PWM = PWM_12;
              num++;
            }
            else if (num == 2) {
              PWM = PWM_25;
              num++;
            }
            else if (num == 3) {
              PWM = PWM_50;
              num++;
            }
            else if (num == 4) {
              PWM = PWM_100;
              num++;
            }
            analogWrite(H_LED, PWM);
            tempTime = millis();
          }
          if     (CUE1 == B001) {
            analogWrite(LED1, PWM_100); // tower red light is on
          }
          else if (CUE1 == B100) {
            analogWrite(LED1, PWM_50); // tower yellow light is on
          }
          else if (CUE1 == B010) {
            analogWrite(LED1, PWM_25); // tower green light is on
          }
          else if (CUE1 == B101) {
            analogWrite(LED1, PWM_12); // tower red and yellow lights are on
          }
          else if (CUE1 == B011) {
            analogWrite(LED1, PWM_6); // tower red and green lights are on
          }
          else if (CUE1 == B000) {
            analogWrite(LED1, 0); // tower red, yellow and green lights are off
          }
          else  {
            analogWrite(LED1, PWM_0);
          }
          analogWrite(LED2, PWM_50);
          analogWrite(LED3, PWM_50);
          analogWrite(LED4, PWM_50);
          break;
    
     case 3:
          // Light scale #1
          // This is Frédéric's requested prefered mode of operation.
          // This mode will run on power up even if the secondary Tower CNTRL_B Mode pins are not connected
          // 6 increments of 20%; from 0% "OFF" to 100% "ON"
          // All other LEDs will be at 50% so LED1 can be used to contrast above and below the other LEDs
          // PD 2021-08-20 - added else statements and catch all statement
         Serial.println("case 3"); 
          
          if     (CUE1 == B001) {
            analogWrite(LED1, PWM_100); // tower red light is on
          }
          else if (CUE1 == B100) {
            analogWrite(LED1, PWM_50); // tower yellow light is on
          }
          else if (CUE1 == B010) {
            analogWrite(LED1, PWM_25); // tower green light is on
          }
          else if (CUE1 == B101) {
            analogWrite(LED1, PWM_12); // tower red and yellow lights are on
          }
          else if (CUE1 == B011) {
            analogWrite(LED1, PWM_6); // tower red and green lights are on
          }
          else if (CUE1 == B000) {
            analogWrite(LED1, 0); // tower red, yellow and green lights are off
          }
          else  {
            analogWrite(LED1, PWM_0);
          }
          analogWrite(LED2, PWM_50);
          analogWrite(LED3, PWM_50);
          analogWrite(LED4, PWM_50);
          break;
    
    
        case 4:
          // control middle light
          // house light stays on for 8 min, blinks for 8 min, then repeats
        Serial.println("case 4");
               
          
          if (millis() - tempTime >= eight)
          {
            if (boolian == true) {
              boolian = false;
            }
            else {
              boolian = true;
            }
            tempTime = millis();
          }
          else if (boolian == true)
          {
            digitalWrite(H_LED, HIGH);
            if(del(500)){break;}
            digitalWrite(H_LED, LOW);
            if(del(500)){break;}
          }
          else if (boolian == false)
          {
            digitalWrite(H_LED, HIGH);
          }
          if     (CUE1 == B001) {
            analogWrite(LED1, PWM_100); // tower red light is on
          }
          else if (CUE1 == B100) {
            analogWrite(LED1, PWM_50); // tower yellow light is on
          }
          else if (CUE1 == B010) {
            analogWrite(LED1, PWM_25); // tower green light is on
          }
          else if (CUE1 == B101) {
            analogWrite(LED1, PWM_12); // tower red and yellow lights are on
          }
          else if (CUE1 == B011) {
            analogWrite(LED1, PWM_6); // tower red and green lights are on
          }
          else if (CUE1 == B000) {
            analogWrite(LED1, 0); // tower red, yellow and green lights are off
          }
          else  {
            analogWrite(LED1, PWM_0);
          }
          analogWrite(LED2, PWM_50);
          analogWrite(LED3, PWM_50);
          analogWrite(LED4, PWM_50);
          break;
    
    
     case 5:
          //control middle light and augment house light every 8 minutes
            
        if (CUE2 == 1)  {
          if (millis() - tempTime >= eight)
          {
            if     (num == 0) {
              PWM = 1;
              num++;
            }
            else if (num == 1) {
              PWM = 2;
              num++;
            }
            else if (num == 2) {
              PWM = 4;
              num++;
            }
            else if (num == 3) {
              PWM = 8;
              num++;
            }
            else if (num == 4) {
              PWM = 16;
              num++;
            }
            analogWrite(H_LED, PWM);
            analogWrite(LED1, PWM);
            analogWrite(LED2, PWM);
            analogWrite(LED3, PWM);
            analogWrite(LED4, PWM);
            tempTime = millis();
          }
    /*      if     (State == B00100000) {
            analogWrite(LED1, PWM_100); // tower red light is on
          }
          else if (State == B10000000) {
            analogWrite(LED1, PWM_50); // tower yellow light is on
          }
          else if (State == B01000000) {
            analogWrite(LED1, PWM_25); // tower green light is on
          }
          else if (State == B10100000) {
            analogWrite(LED1, PWM_12); // tower red and yellow lights are on
          }
          else if (State == B01100000) {
            analogWrite(LED1, PWM_6); // tower red and green lights are on
          }
          else if (State == B00000000) {
            analogWrite(LED1, 0); // tower red, yellow and green lights are off
          }
          else  {
            analogWrite(LED1, PWM_0);
          }
          analogWrite(LED2, PWM_50);
          analogWrite(LED3, PWM_50);
          analogWrite(LED4, PWM_50);
      */    
          }
          else {
            reset();
          }
          break;
    
    
    
    case 6:
          //control middle light and augment house light every 8 minutes
        Serial.println("case 6");
          
          if (CUE2 == 1)  {
          if (millis() - tempTime >= 1000)
          {
            if     (num == 0) {
              PWM = PWM_6;
              num++;
            }
            else if (num == 1) {
              PWM = PWM_12;
              num++;
            }
            else if (num == 2) {
              PWM = PWM_25;
              num++;
            }
            else if (num == 3) {
              PWM = PWM_50;
              num++;
            }
            else if (num == 4) {
              PWM = PWM_100;
              num++;
            }
            analogWrite(H_LED, PWM);
            analogWrite(LED1, PWM);
            analogWrite(LED2, PWM);
            analogWrite(LED3, PWM);
            analogWrite(LED4, PWM);
            tempTime = millis();
          }
          }
          else {
            reset();
          }
          break;
    
    
    case 7:
          //control middle light and augment house light every 4 minutes
          if (CUE2 == 1)  {
          if (millis() - tempTime >= 1000)
          {
            if     (num == 0) {
              PWM = 1;
              num++;
            }
            else if (num == 1) {
              PWM = 2;
              num++;
            }
            else if (num == 2) {
              PWM = 4;
              num++;
            }
            else if (num == 3) {
              PWM = 8;
              num++;
            }
            else if (num == 4) {
              PWM = 16;
              num++;
            }
            if     (num == 5) {
              PWM = PWM_6;
              num++;
            }
            else if (num == 6) {
              PWM = PWM_12;
              num++;
            }
            else if (num == 7) {
              PWM = PWM_25;
              num++;
            }
            else if (num == 8) {
              PWM = PWM_50;
              num++;
            }
            else if (num == 9) {
              PWM = PWM_100;
              num++;
            }
            analogWrite(H_LED, PWM);
            analogWrite(LED1, PWM);
            analogWrite(LED2, PWM);
            analogWrite(LED3, PWM);
            analogWrite(LED4, PWM);
            tempTime = millis();
          }
          }
          else {
            reset();
          }
          break;
    
    
        case 8:
          // all LEDs have the same State intensity level in 8 equal increments of 13%; from 0% "OFF" to 88% "ON"
         Serial.println("case 8");
//          
//          State = State | B00011111;
//    
//          analogWrite(LED1, State);
//          analogWrite(LED2, State);
//          analogWrite(LED3, State);
//          analogWrite(LED4, State);
          break;
      
      case 9:

      float arr [] = {0.49725, 1.99155, 3.5444999999999998, 3.984375, 7.96875, 15.9375, 31.875, 63.75, 127.5, 255.0};
        if (CUE2 == 1)  {
          if ((millis() - tempTime)/1000 >= 60 * 4)
          {
            PWM = arr[num];
            num++;
            if (num > sizeof(arr)/sizeof(arr[0])){reset(true);}
            tempTime = millis();
          }
          analogWrite(LED1, PWM);
          analogWrite(LED2, PWM);
          analogWrite(LED3, PWM);
          analogWrite(LED4, PWM);
          }
          else {
            reset();
          }
        break;
      }
      get_inputs();
    }
    reset(true);
    delay(200);
}
