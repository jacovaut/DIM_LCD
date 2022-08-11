# DIM_LCD
Code, instructions and files for the DIM_LCD modules

## Introduction
Programe qui permet d'utiliser les modules DIM V2 pour faire des stimulis avec jusqu'a 5 LED diférentes.
Des combinaisons de CUE provenant de la tour va permettre
de faire des niveaux de stimulation diff�rent (par des PWM)
 
Programme qui fonctionne avec SAT4 5niv de stimuli
7 aout 2021, Fr�d�ric Hupp�-Gourgues U. Moncton
Des combinaisons de CUE provenant de la tour va permettre
de faire des niveaux de stimulation diff�rent (par des PWM)

Ce code est compatible avec la version origial à Frédéric lors du "Power Up"

Les modifications inclus:
- différents mode d'opérations qui sont controler par un deuxième câble prévu de la tour
- contrôl de six LED au lieu d'une
- lcd qui permet de choisir entre une sélection de programmes
- un test pour les LEDs et un test pour la tour

## Directions pour LCD
le bouton "reset" sur l'arduino est inaccessible, mais il y en a un sur le LCD qui fonctionne
  
Les boutons UP et DOWN sont utilisés pour changer le programme qui est imprimé sur l'écran et
le bouton SELLECT est utilisé pour débuter ou arèter le programe. 

voici la notation utilisée pour les descriptions de programmes:
- CUE1 et/ou CUE2 : quel des fils doit être branchés pour ce programme
- LED# (#)(#%): LED qui fait une tache quelconque (change a toute les # minutes) (intensité fixte a #%) (si il n'y a rien, l'LED est contrôler par la tour)
- not operational : programme ne fonctionne pas   

  ### Exemple:
  ```
  CUE1, CUE2; LED1 - LED4 50%; LED5; H_LED 4
  ```
  
  ### explications : 
  ```
  CUE1 et CUE2 doivent être branchés; LED1, LED2, LED3 et LED4 restent à 50%; LED5 se fait contrôler par la tour; H_LED change à toute les 4 minmin
  ```

le bouton RIGHT débute le test 1, qui consiste à :
- faire chaque LED clignoter leur lapéro (LED1 blink une fois, LED2 blink deux fois, ..., H_LED blink 6 fois)
- graduellement passer d'une luminosité de 0% à 100%
- graduellement passer d'une luminosité de 100% à 0%

Le bouton LEFT vous laisse choisir la vitesse à laquelle le programme va.

Lorsqu'un programme est actif, la lumière du LCD s'éteint. pour la rallumer, il faut tout simplement peser le bouton DOWN

Lorsqu'un programme est actif, le LCD montre une de trois pages:
1. le nom du programme et la vitesse du programme.
2. l'itération et le temps depuis le début du programme.
3. la variable PWM (en pourcentage) et les signaux de la tour
