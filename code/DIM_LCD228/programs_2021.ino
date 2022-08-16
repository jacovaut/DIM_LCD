// 2021 PROGRAMS
/*
  "Program0","CUE1, CUE2; LED1 - LED4 + H_LED",
  "Program1","CUE1; LED1; LED2 - LED4 + H_LED 50%",
  "Program2","CUE1; LED1; H_LED 8; LED2 - LED4 50%",
  "Program3","CUE1; LED1; LED2 - LED4",// for example, this description would be program[3][1]
  "Program4","CUE1; LED1; H_LED 8; LED2 - LED4 50%",
  "Program5","not operational",
  "Program6","not operational",
  "Program7","not operational",
  "Program8","not operational",
*/

/*
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
            if     (lap == 0) {
              PWM = PWM_6;
              lap++;
            }
            else if (lap == 1) {
              PWM = PWM_12;
              lap++;
            }
            else if (lap == 2) {
              PWM = PWM_25;
              lap++;
            }
            else if (lap == 3) {
              PWM = PWM_50;
              lap++;
            }
            else if (lap == 4) {
              PWM = PWM_100;
              lap++;
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
            if     (lap == 0) {
              PWM = 1;
              lap++;
            }
            else if (lap == 1) {
              PWM = 2;
              lap++;
            }
            else if (lap == 2) {
              PWM = 4;
              lap++;
            }
            else if (lap == 3) {
              PWM = 8;
              lap++;
            }
            else if (lap == 4) {
              PWM = 16;
              lap++;
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
            if     (lap == 0) {
              PWM = PWM_6;
              lap++;
            }
            else if (lap == 1) {
              PWM = PWM_12;
              lap++;
            }
            else if (lap == 2) {
              PWM = PWM_25;
              lap++;
            }
            else if (lap == 3) {
              PWM = PWM_50;
              lap++;
            }
            else if (lap == 4) {
              PWM = PWM_100;
              lap++;
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
          if (millis() - tempTime >= eight / 2)
          {
            if     (lap == 0) {
              PWM = 1;
              lap++;
            }
            else if (lap == 1) {
              PWM = 2;
              lap++;
            }
            else if (lap == 2) {
              PWM = 4;
              lap++;
            }
            else if (lap == 3) {
              PWM = 8;
              lap++;
            }
            else if (lap == 4) {
              PWM = 16;
              lap++;
            }
            if     (lap == 5) {
              PWM = PWM_6;
              lap++;
            }
            else if (lap == 6) {
              PWM = PWM_12;
              lap++;
            }
            else if (lap == 7) {
              PWM = PWM_25;
              lap++;
            }
            else if (lap == 8) {
              PWM = PWM_50;
              lap++;
            }
            else if (lap == 9) {
              PWM = PWM_100;
              lap++;
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
 */
