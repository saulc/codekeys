/*
 * mini keyboard - code keys 3 x 3
  micro based keyboard 3 interupts.  7 pinchange interupt? 6!
  pins: int: 2,3,7 pcint: 8,9,10, 14, 15, 16   
  spaceL  mc  spaceR        macOS
  comment uncomment ([0, 0, 0]) 'custom openscad'
  tab/return  copy/cut  paste/paste+return

//        
*/    

#include "Keyboard.h"
#include "button.h"
 void cclick();
 void aclick();
 void bclick(); 
 void one();
 void two();
 void three();
 void four();
 void five();
 void six(); 
 
Button a1(8, one, false);
Button a2(9, two, false);
Button a3(10, three, false);
Button b1(14, four, false);
Button b2(15, five, false);
Button b3(16, six, false);
Button a(2, aclick, true);
Button b(3, bclick, true);
Button c(7, cclick, true);

const int d = 11; //release delay
//interupt callbacks
void aclick(){ 
    int t = a.tap();
    if(t==1)  commandKey(2); 
    else if(t == 2) dt(1);
}
void bclick(){ 
    int t = b.tap();
    if(t==1)  commandKey(1); 
    else if(t == 2) commandKey(0);
}    
void cclick(){ 
    int t = c.tap();
    if(t==1)  dt(0);
    else if(t == 2)  dt(1); 
}   

 //pin change interupt callbacks
void one(void){
    int t = a1.tap();
    if(t==1)  macro("([0, 0, 0]) ");        
//    else if(t == 2) dt();
}
void two(void){
    int t = a2.tap();
    if(t==1) commandKey(4); 
    else if(t == 2) commandKey(5); 
}
void three(void){
    int t = a3.tap();
    if(t==1) commandKey(3); 
}   
void four(void){
    int t = b1.tap();
    if(t==1) spaceR();
}
void five(void){
    int t = b2.tap();
    if(t==1) space(2);
}
void six(void){ 
    int t = b3.tap();
    if(t==1) spaceL();
}   

void setup() { 
  //turn off the builtin led
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
   //setup interupts for buttons
   v.ini();  
   c.ini(); 
   x.ini(); 
   a1.ini();
   a2.ini();
   a3.ini();
   b1.ini();
   b2.ini();
   b3.ini();
  // initialize control over the keyboard:
  Keyboard.begin();
}
 
void loop() {  
//  RGB control goes here lol
}

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
        Keyboard.press(KEY_RIGHT_SHIFT); 
        break;
        case 5: c = '/';
        break;
        case 6: c = 'z';
        break;  
        
    }     
    
//    Keyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz
//    Keyboard.press(KEY_RIGHT_SHIFT);  //  hold Shift for testing!! 
    Keyboard.press(KEY_LEFT_GUI);  // press and hold command macOS not X
    Keyboard.press(c);          
        kbrelease();
}
//change spaces/destops
void spaceL(){ space(0); }
void spaceR(){ space(1); }
void space(int d){   
  //ctrl shift tab /ctrl tab  - switch chrome tabs left right 
    Keyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz 
     if(d==2) Keyboard.press(KEY_UP_ARROW);   //spaces/mission control
     else    Keyboard.press( (d==0) ? KEY_LEFT_ARROW : KEY_RIGHT_ARROW);      
    
    kbrelease();
}
 //single key shortcuts
void dt(int a){  
    if(a == 0) Keyboard.press(KEY_TAB); 
    else if(a == 1) Keyboard.press(KEY_RETURN);  
    else if(a == 2) Keyboard.press(KEY_BACKSPACE);  
    kbrelease();
}
//write keystrokes 
void macro(String s){
  for(int i=0; i<s.length()-1; i++)
           Keyboard.write(s[i]); 
}
void kbrelease(){
    delay(d);  //fixes command click after wake.!
    Keyboard.releaseAll(); 
}
