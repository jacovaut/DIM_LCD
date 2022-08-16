# This is an example of how a program should be made for the DIM_LCD boards
1. First of all, all the programs have to be in the select function, in the programs folder, in the select function, in the while (read_LCD_buttons() != btnSELECT) loop, and in switch (currentPage)
2. The case number has to the same as the position in the program array
 ```
 String program[][2] = {
  "SAT9N","CUE2; LED1 - LED4 4",
  "program 2", "blah blah"
  };
 ```
    SAT9N is at position 0, so we have to use case 0
4. I recomend putting all of your values in an array
```
float arr [] = {0.49725, 0.9945, 3.5444999999999998, 3.984375, 7.96875, 15.9375, 31.875, 63.75, 127.5, 255.0};
```
5. Check for CUE start
```
if (CUE2 == 1)
```
    can also be if (CUE2 == b001)
6. run every certain amount of time. if lap is bigger than the size of the array, do not run
```
if ((millis() - tempTime)/1000 >= 60 * 4 / multiplier && lap < sizeof(arr)/sizeof(arr[0]))
```
7. PWM vairable is equal to the value of the array that is at the lap position
```
PWM = arr[lap];
```
8. augment lap
```
lap++;
```
9. reset time
```
tempTime = millis();
```
10. update leds
```
analogWrite(LED1, PWM);
analogWrite(LED2, PWM);
analogWrite(LED3, PWM);
analogWrite(LED4, PWM);
```
### full code
** I removed some code to make it eassyer to read **
```
void select(){
  while (read_LCD_buttons() != btnSELECT){      
      switch (currentPage) {)
      case 0:

        float arr [] = {0.49725, 0.9945, 3.5444999999999998, 3.984375, 7.96875, 15.9375, 31.875, 63.75, 127.5, 255.0};

          if (CUE2 == 1)  {
            if ((millis() - tempTime)/1000 >= 60 * 4 / multiplier && lap < sizeof(arr)/sizeof(arr[0]))
            {
              PWM = arr[lap];
              lap++;
              tempTime = millis();
            }
            analogWrite(LED1, PWM);
            analogWrite(LED2, PWM);
            analogWrite(LED3, PWM);
            analogWrite(LED4, PWM);
            }
        break;
}
```
