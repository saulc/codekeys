/*
 * Code keys v1 - 2022/8/8 Saul C.
 * 
 * mini keyboard - code keys 3 x 3
  micro based keyboard 3 interupts.  7 pinchange interupt? 6!
  pins: int: 2,3,7 pcint: 8,9,10, 14, 15, 16   
  spaceL  mc  spaceR        macOS
  comment uncomment ([0, 0, 0]) 'custom openscad'
  tab/return  copy/cut  paste/paste+return
  
*/    

//#include "Keyboard.h"
#include "analog.h"
#include "button.h"
#include <BleKeyboard.h>

analog batt(BATT_MONITOR);

BleKeyboard bleKeyboard("Acme3x3Keybored");
 
/*   
 *    Don't Change These after pcb setup.
 */
const int pins[9] = {   21, 12, 27, 
                        33, 15, 32, 
                        14, 25,  26   };
                       
//hardware interupts
Button a( pins[0] );
Button b( pins[1] );
Button c( pins[2] );
Button a1( pins[3] );
Button a2( pins[4] );
Button a3( pins[5] );
Button b1( pins[6] );
Button b2( pins[7] );
Button b3( pins[8] );
const int d = 11; //release delay

/*   
 *    Edit key actions here.
 */
//interupt callbacks// top row
void IRAM_ATTR aclick(){ 
    int t = a.tap();
    if(t==1) commandKey(1); 
    else if(t >= 2) commandKey(0);
   
}
void IRAM_ATTR bclick(){ 
    int t = b.tap();
    if(t==1)   commandKey(2);
    else  if(t >= 2) dt(1);
    
}    
void IRAM_ATTR cclick(){ 
    int t = c.tap();
    if(t==1) commandKey(6);  //
}   
 
 //pin change interupt callbacks
 //middle row
void IRAM_ATTR one(void){
    int t = a1.tap();
    if(t==1) dt(0);
    else if(t >= 2)  dt(1);
}   
        
void IRAM_ATTR two(void){
    int t = a2.tap();
    if(t>=1) ar(2);  //up
//    else if(t>=2)  for(int i=0; i<4; i++) ar(2);
}
void IRAM_ATTR three(void){
    int t = a3.tap(); 
    if(t==1) dt(2); 
    else if(t >= 2)  dt(3);
}  
//bottom row  fliped
void IRAM_ATTR four(void){
    int t = b1.tap(); 
    if(t==1)  ar(1); //right      
    else if(t >= 2) ar(5);
}
void IRAM_ATTR five(void){
    int t = b2.tap();
    if(t>=1)   ar(3); //down    
//    else if(t>=2)  for(int i=0; i<4; i++) ar(3);
    
} 
void IRAM_ATTR six(void){ 
    int t = b3.tap();
    if(t==1)  ar(0); //left
    else if(t >= 2) ar(4);
}   


void checkBattLevel(){
  bleKeyboard.setBatteryLevel(batt.getVal());
}
 
void setup() { 
//  //turn off the builtin led
//  pinMode(13, OUTPUT);
//  digitalWrite(13, LOW);
   //initialize interupts for buttons
   a.ini();
   attachInterrupt(a.getPin(), aclick, FALLING ); 
   b.ini();
   attachInterrupt(b.getPin(), bclick, FALLING ); 
   c.ini();
   attachInterrupt(c.getPin(), cclick, FALLING ); 
   a1.ini();
   attachInterrupt(a1.getPin(), one, FALLING ); 
   a2.ini();
   attachInterrupt(a2.getPin(), two, FALLING ); 
   a3.ini();
   attachInterrupt(a3.getPin(), three, FALLING ); 
   b1.ini();
   attachInterrupt(b1.getPin(), four, FALLING ); 
   b2.ini();
   attachInterrupt(b2.getPin(), five, FALLING ); 
   b3.ini();
   attachInterrupt(b3.getPin(), six, FALLING ); 
   
  // initialize control over the keyboard:
//  Keyboard.begin();
  Serial.begin(115200);
  Serial.println("Acme Ble Keys");
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();  
  checkBattLevel();
}
 int t = 0, tt = 0;
 volatile int mm = 0;
void loop() {  
//  RGB control goes here lol
  if(t++ >100000){      //don't flood the console, esp32 is fast...
       t = 0;
       tt++;
      if(bleKeyboard.isConnected())  Serial.println("Connected ...");

  }
  if(tt > 2 and mm !=0){
//    Serial.println("  key tapped...");
      checkBattLevel();  
 //updated the battery level if the user tapped a button. (don't wake from sleep)
       mm = 0;
       tt = 0;
  }
}
/* 
 * ----------------Short cuts --------------------
 */
void commandKey(int a){
  
  char c = 'x';
    switch(a){
      case 0: c = 'x';
        break;
      case 1: c = 'c';
        break;
      case 2: c = 'v';
        break;
        case 3: c = 'd';
        break; 
        case 4: c = 'd';    
        bleKeyboard.press(KEY_RIGHT_SHIFT); 
        break;
        case 5: c = '/';
        break;
        case 6: c = 'z';
        break;  
        
    }     
    
//    bleKeyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz
//    bleKeyboard.press(KEY_RIGHT_SHIFT);  //  hold Shift for testing!! 
    bleKeyboard.press(KEY_LEFT_GUI);  // press and hold command macOS not X
    bleKeyboard.press(c);          
        kbrelease();  
         mm++; //key pressed flag
}
//change spaces/destops
void spaceL(){ space(0); }
void spaceR(){ space(1); }
void space(int d){   
  //ctrl shift tab /ctrl tab  - switch chrome tabs left right 
    bleKeyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz 
    if(d==2) bleKeyboard.press(KEY_UP_ARROW);   //spaces/mission control
    else    bleKeyboard.press( (d==0) ? KEY_LEFT_ARROW : KEY_RIGHT_ARROW);      
    
    kbrelease();  
     mm++;
}
void ar(int a){
  
  char c = 'a'; 
  switch(a){
    case 0: c = KEY_LEFT_ARROW; break;   
    case 1: c = KEY_RIGHT_ARROW; break;
    case 2: c = KEY_UP_ARROW; break;
    case 3: c = KEY_DOWN_ARROW; break;
    case 4: c = KEY_LEFT_ARROW; 
              bleKeyboard.press(KEY_LEFT_ALT);
              break;
    case 5: c = KEY_RIGHT_ARROW; 
              bleKeyboard.press(KEY_LEFT_ALT);
              break;
  }
  bleKeyboard.press(c);      
  bleKeyboard.release(c);   
  if(a >= 4)  bleKeyboard.release(KEY_LEFT_ALT);
//  kbrelease();
   mm++;
}
 //single key shortcuts
void dt(int a){  
    int k = 0;
    switch(a){
      case 0: k = KEY_TAB;    break;
      case 1: k = KEY_RETURN;  break;
      case 3: bleKeyboard.press(KEY_LEFT_ALT);
      case 2: k = KEY_BACKSPACE;  break;

    }
      bleKeyboard.press(k); 
      bleKeyboard.release(k);   
      if(a > 2)  bleKeyboard.release(KEY_LEFT_ALT);
    mm++;
} 


/* 
 * ----------------end Short cuts --------------------
 */     
 
//write keystrokes or just use print
void macro(String s){
  for(int i=0; i<s.length(); i++)
           bleKeyboard.write(s[i]); 
}
void kbrelease(){
    delay(d);  //fixes command click after wake.!
    bleKeyboard.releaseAll(); 
}
