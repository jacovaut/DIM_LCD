void Select(){
    lcd.setCursor(0,0);
    lcd.print("PRESS SELECT BUTTON");
    lcd.setCursor(0,1);
    lcd.print("TO STOP");
  
    delay(1000);
  
    lcd.clear();

    programStartTime = millis();

    tempTime = millis();//starting time
    
    while (read_LCD_buttons() != btnSELECT){//while no button is pressed

      if ((CUE2) == 7){reset(true);}
      
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
      if (read_LCD_buttons() == btnRIGHT && programPage < 3){programPage++; lcd.clear();}
      if (read_LCD_buttons() == btnLEFT && programPage > 0){programPage--; lcd.clear();}
      delay(150);

      switch (programPage){
        case 0:
        
          lcd.setCursor(0,0);
          lcd.print("SET SPEED");

          multiplier = 1;
    
          lcd.setCursor(0,1);
          lcd.print("      ");
          lcd.print("0" + String(multiplier) + "x");
          lcd.print(" RIGHT");
          lcd.write(byte(0));
        break;
        case 1:
          lcd.setCursor(0,0);
          lcd.print("SET SPEED");

          multiplier = 5;
    
          lcd.setCursor(0,1);
          lcd.write(byte(1));
          lcd.print("LEFT ");
          lcd.print("0" + String(multiplier) + "x");
          lcd.print(" RIGHT");
          lcd.write(byte(0));
        break;
        case 2:
          lcd.setCursor(0,0);
          lcd.print("SET SPEED");

          multiplier = 10;
    
          lcd.setCursor(0,1);
          lcd.write(byte(1));
          lcd.print("LEFT ");
          lcd.print(String(multiplier) + "x");
          lcd.print(" RIGHT");
          lcd.write(byte(0));
        break;
        case 3:
          lcd.setCursor(0,0);
          lcd.print("SET SPEED");

          multiplier = 60;
    
          lcd.setCursor(0,1);
          lcd.write(byte(1));
          lcd.print("LEFT ");
          lcd.print(String(multiplier) + "x");
          lcd.print("      ");
        break;
      }
    break;
      
    case 0:

      float arr [] = {0.49725, 0.9945, 3.5444999999999998, 3.984375, 7.96875, 15.9375, 31.875, 63.75, 127.5, 255.0};
        if (CUE2 == 1)  {
          if ((millis() - tempTime)/1000 >= 60 * 4 / multiplier && lap < sizeof(arr)/sizeof(arr[0]))
          {
            Serial.print("lap");
            Serial.println(multiplier);
            PWM = arr[lap];
            lap++;
            tempTime = millis();
          }
          analogWrite(LED1, PWM);
          analogWrite(LED2, PWM);
          analogWrite(LED3, PWM);
          analogWrite(LED4, PWM);
          }
//          else {
//            reset();
//          }
        break;
      }
      get_inputs();
    }
    reset(true);
    delay(200);
}
