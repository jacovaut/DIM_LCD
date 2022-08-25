//Version control
// DIM_LCD137: by Jacob Vautour. Original version of DIM_LCD. Code for diferent modes is based off of DIM316
// DIM_LCD216: changed State and CMD to CUE1 and CUE2 respectively; inprooved del(); fixed bug with lcd; improved reset(); created printBinary(); created get_inputs(); added program SAT9N; added kill; put all functions in an other file and the Select function in it's own file
// DIM_LCD217: added way to control the lcd's light; added second page to lcd while the program is running
// DIM_LCD222: added way to choose the speed of the program; added third page to lcd while the program is running; fixed bugs with main menu; created new format for the description of a program
// DIM_LCD228: fixed bugs to do with LAP and SAT9N; added old_programs page
// DIM_LCD237: added code for white noise; added second tempTime variable;

// Suggested Arduino firmware tracking nomenclature:
// ex.  DIM 232 A 1
// <name> <day of the year> <version of the day> <board count>



// INTRODUCTION
/*
 * Programe qui permet d'utiliser les modules DIM V2
 * pour faire des stimulis avec jusqu'a 5 LED diférentes.
 * Des combinaisons de CUE provenant de la tour va permettre
 * de faire des niveaux de stimulation diff�rent (par des PWM)
 */
/*  
  Programme qui fonctionne avec SAT4 5niv de stimuli
  7 aout 2021, Fr�d�ric Hupp�-Gourgues U. Moncton
  Des combinaisons de CUE provenant de la tour va permettre
  de faire des niveaux de stimulation diff�rent (par des PWM)
*/

/*
  Ce code est compatible avec la version origial à Frédéric lors du "Power Up"

  Les modifications inclus:
  - différents mode d'opérations qui sont controler par un deuxième câble prévu de la tour
  - contrôl de six LED au lieu d'une
  - lcd qui permet de choisir entre une sélection de programmes
  - un test pour les LEDs et un test pour la tour
*/

// DIRECTIONS POUR LCD
/*  
  le bouton "reset" sur l'arduino est inaccessible, mais il y en a un sur le LCD qui fonctionne
  
  Les boutons UP et DOWN sont utilisés pour changer le programme qui est imprimé sur l'écran et
  le bouton SELLECT est utilisé pour débuter ou arèter le programe. 

  voici la notation utilisée pour les descriptions de programmes:
    CUE1 et/ou CUE2 : quel des fils doit être branchés pour ce programme
    LED# (#)(#%): LED qui fait une tache quelconque (change a toute les # minutes) (intensité fixte a #%) (si il n'y a rien, l'LED est contrôler par la tour)
    not operational : programme ne fonctionne pas
    
    Exemple : CUE1, CUE2; LED1 - LED4 50%; LED5; H_LED 4
    explications : CUE1 et CUE2 doivent être branchés; LED1, LED2, LED3 et LED4 restent à 50%; LED5 se fait contrôler par la tour; H_LED change à toute les 4 minmin
    
  
  le bouton RIGHT débute le test 1, qui consiste à :
  - faire chaque LED clignoter leur lapéro (LED1 blink une fois, LED2 blink deux fois, ..., H_LED blink 6 fois)
  - graduellement passer d'une luminosité de 0% à 100%
  - graduellement passer d'une luminosité de 100% à 0%

  Le bouton LEFT vous laisse choisir la vitesse à laquelle le programme va.

  Lorsqu'un programme est actif, la lumière du LCD s'éteint. pour la rallumer, il faut tout simplement peser le bouton DOWN

  Lorsqu'un programme est actif,le LCD montre une de trois pages:
  1. le nom du programme et la vitesse du programme.
  2. l'itération et le temps depuis le début du programme.
  3. la variable PWM (en pourcentage) et les signaux de la tour
*/

// DIRECTIONS POUR PROGRAMER
/*
  pour rajouter un programme, il faut simplement rajouter son nom et une déscription (OPTIONEL) dans la variable "program".
  il faut ensuite tout simplement rajouter le code dans la page programs

  ***ATTENTION*** LE lapÉRO D'UN PROGRAME DANS LE SWITCH DEVRAIS ÊTRE LE MÊME QUE LA POSITION D'UN PROGRAME DANS "program"

  ***ATTENTION*** NE PAS UTILISER "delay()" DANS LE "switch", AU LIEU, UTILISER "if(del()){break;}"
  EXEMPLE : pour un delay de 1 sec : if(del(1000)){break;};
  les delay nomales font en sorte que les bouttons ne peuvent pas être utilisés lors du delay
*/


#define eight 480000 // variable that is equal to 8 minutes in millisecons
#define four 240000 
#define SEC_30 30000 // variable that is equal to 8 minutes in millisecons

#define kill B111111

unsigned long long programStartTime = 0;
unsigned long long tempTime1 = 0;
unsigned long long tempTime2 = 0;
int lap = 0;
float PWM = 0;
bool boo = false;

int CUE1 = 0;
int CUE2 = 0;

// CUE1 pins
const int CNTRL_A1 = A15;  // red wire
const int CNTRL_A2 = A14;  // green wire
const int CNTRL_A3 = A13;  // yellow wire

const int CNTRL_B1 = A12;  // red wire
const int CNTRL_B2 = A11;  // green wire
const int CNTRL_B3 = A10;  // yellow wire

const int H_LED = 44;
const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 11;
const int LED4 = 2;
const int LED5 = 3;
int LED;

int multiplier = 1;

const int PWM_MAX = 254;  // not sure if the arduino PWM accepts 255; use 254 to make sure and test later
const int PWM_100 = 254; // 1.0 * 256;  100%
const int PWM_80 =  204; // 0.8 * 256;  80%
const int PWM_60 =  154; // 0.6 * 256;  60%
const int PWM_40 =  102;  // 0.4 * 256; 40%
const int PWM_20 =  51;  // 0.2 * 256;  20%
const int PWM_0 =   0;   // 0.0 * 256;  0%

const int PWM_50 =  128; // 0.5 * 256;  50%
const int PWM_25 =  64; // 0.25 * 256;  25%
const int PWM_12 =  32; // 0.12 * 256;  12%
const int PWM_6 =  16; // 0.06 * 256;   6%


/* LCD SETUP*/
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte right_arrow[8] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11100,
  B11000,
  B10000,
};

byte left_arrow[8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B00111,
  B00011,
  B00001,
};

int adc_key_in  = 0;
int currentPage = 0;
int programPage = 0;
int numberPages;
long long menuTime = millis();
int scrollNo = 0;
bool isRunning = false;
unsigned long long timeShow = millis();

const int lcd_light = 33;

//rajouter nom de programe et description ici
String program[][2] = { // 2D array, firts "[]" is the rows and the second is for coloms 
  ////MAXIMUM OF 16 CHARS FOR THE NAME, AND 39 CHARS FOR THE DESCRIPTION
  "SAT9N","CUE2; LED1 - LED4 4",
  "SATson","CUE2; PLUG5 8"
  };
  
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define V1 /*CHANGE TO V2 FOR THE VERSION 2 LCDs*/

/* LCD SETUP END */

/* WHITE NOISE SETUP */
#include <Entropy.h> // Required Library

uint32_t Rnd;

byte LowBit;
/* WHITE NOISE SETUP END */

void setup()
{
  Serial.begin(9600);

  // Enable internal pull-up resistors for tower interface
  // CNTRL_A Cable for LED dimming "CUE1"
  pinMode(CNTRL_A1, INPUT_PULLUP);
  pinMode(CNTRL_A2, INPUT_PULLUP);
  pinMode(CNTRL_A3, INPUT_PULLUP);

  // CNTRL_A Cable for LED dimming "CUE2"
  pinMode(CNTRL_B1, INPUT_PULLUP);
  pinMode(CNTRL_B2, INPUT_PULLUP);
  pinMode(CNTRL_B3, INPUT_PULLUP);

  // Configure output driver pins for LED PWM
  pinMode(H_LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(LED5, HIGH);
  
  pinMode(lcd_light, OUTPUT);

  digitalWrite(lcd_light, HIGH);

  lcd.createChar(0, right_arrow);
  lcd.createChar(1, left_arrow);


  lcd.begin(16, 2); //init LCD
  numberPages = sizeof(program)/sizeof(program[1]); //the number of pages is equal to the size of the "program" array.
  lcd.setCursor(0,0);
  lcd.print(program[currentPage][0]);
  printMain();
  delay(1000);

  Entropy.initialize();

  pinMode(H_LED, OUTPUT); // Set D8 as Output
  
  uint32_t Seed = Entropy.random();
  
  randomSeed(Seed);
  
  do {Rnd = random();} while (!Rnd); // Get non-zero initial value
  }

void loop()
{
  digitalWrite(lcd_light, HIGH);
    
    printMain();
    action();
}

void action(){// function to determine what to do when a button is pressed
     switch (read_LCD_buttons())
 {
   case btnRIGHT:
     {
      int temp = currentPage;//store the page number, so we don't loose it
      currentPage = 99; //set current page to 99 (TEST1)
      lcd.clear();
      Select();//start the program
      currentPage = temp;//re set the page number
     break;
     }
   case btnLEFT:
     {
      // same thing as case btnRIGHT, but with the page 999
      int temp = currentPage;
      currentPage = 999;
      lcd.clear();
      Select();
      currentPage = temp;
     break;
     }
   case btnUP:
     {
      scrollNo = 0;
      lcd.clear();
      if(currentPage - 1 >= 0){//go to the previous page if it exists
        currentPage--;
      }
      menuTime = millis();
      lcd.print(program[currentPage][0]);
      printMain();
      delay(500);
     break;
     }
   case btnDOWN:
     {
      scrollNo = 0;
      lcd.clear();
      if(currentPage + 1 < numberPages){//go to the next page if it exists
        currentPage++;
      }
      menuTime = millis();
      lcd.print(program[currentPage][0]);
      printMain();
      delay(500);
     break;
     }
   case btnSELECT:
     {
     lcd.clear();
     Select();//start the program with the current page number
     break;
     }
     case btnNONE://if nothing is pressed
     return;
   }
   delay(150);
}

void printMain(){
    /*print program name/description*/
  lcd.setCursor(0,1);
  lcd.print(program[currentPage][1]);//print the description
  if (program[currentPage][1].length() > 16){// if the description is too long, then scroll
    if (millis() - menuTime > 750){// only execute every second
      if (scrollNo >= 39) {scrollNo = 0;}//the lcd contains a max of 40 chars. we have to reset it e
      else {scrollNo++;}
      if (scrollNo + program[currentPage][0].length() > 40){
        lcd.setCursor(scrollNo,0);
        lcd.print(program[currentPage][0]); 
        lcd.setCursor(0,0);
        for (int i = 40 - scrollNo; i < program[currentPage][0].length(); i++){
          lcd.print(program[currentPage][0][i]);
        }
      }
      else{
        lcd.setCursor(0,0);
        lcd.print("                                        ");
        lcd.setCursor(scrollNo,0);
        lcd.print(program[currentPage][0]); 
      }
      lcd.scrollDisplayLeft();
      menuTime = millis();
    }
  }
  else {
      lcd.setCursor(0,0);
      lcd.print(program[currentPage][0]);
      scrollNo = 0;
  }
}
