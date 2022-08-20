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

#include "Keyboard.h"
#include "button.h"
 void one();
 void two();
 void three();
 void four();
 void five();
 void six(); 
 void cclick();
 void aclick();
 void bclick(); 

const int pins[9] = {   2,  3,   7 , 
                        8,  9,   10, 
                        14, 15,  16   };
                      
//todo software rotate. easy rotate...
int rp(int i){
  int n = i;
    if(n % 3 == 0) 
  return n;
}

// pin change interups
Button a1( pins[3] , one, false);
Button a2( pins[4] , two, false);
Button a3( pins[5] , three, false);
Button b1( pins[6] , four, false);
Button b2( pins[7] , five, false);
Button b3( pins[8] , six, false);
//hardware interupts
Button a( pins[0] , aclick, true);
Button b( pins[1] , bclick, true);
Button c( pins[2] , cclick, true);

const int d = 11; //release delay
//interupt callbacks
void aclick(){ 
    int t = a.tap();
    if(t==1)  macro("1");      
    else if(t == 2) macro("rule #2");
}
void bclick(){ 
    int t = b.tap();
    if(t==1)  macro("2");
}    
void cclick(){ 
    int t = c.tap();
    if(t==1)  macro("3");
}   
 
 //pin change interupt callbacks
void one(void){
    int t = a1.tap();
    if(t==1) macro("4");
}   
        
void two(void){
    int t = a2.tap();
      if(t==1)   macro("5");
}
void three(void){
    int t = a3.tap();
    if(t==1) macro("6");
}  
//top row   

void four(void){
    int t = b1.tap();
    if(t==1) macro("7");
     
}
void five(void){
    int t = b2.tap();
    if(t==1) macro("8");
    
} 
void six(void){ 
    int t = b3.tap();
    if(t==1) macro("9");
}   

void setup() { 
  //turn off the builtin led
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
   //initialize interupts for buttons
   a.ini();  
   b.ini(); 
   c.ini(); 
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
void ar(int a){
  char c = 'a'; 
  switch(a){
    case 0: c = KEY_LEFT_ARROW; break;   
    case 1: c = KEY_RIGHT_ARROW; break;
    case 2: c = KEY_UP_ARROW; break;
    case 3: c = KEY_DOWN_ARROW; break;
    case 4: c = KEY_LEFT_ARROW; 
              Keyboard.press(KEY_LEFT_ALT);
              break;
    case 5: c = KEY_RIGHT_ARROW; 
              Keyboard.press(KEY_LEFT_ALT);
              break;
  }
  Keyboard.press(c);
  kbrelease();
  
}
 //single key shortcuts
void dt(int a){  
    if(a == 0) Keyboard.press(KEY_TAB); 
    else if(a == 1) Keyboard.press(KEY_RETURN);  
    else if(a >= 2)   {
      if(a == 3) Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_BACKSPACE); 
    }
    kbrelease();
} 
/* 
 * ----------------end Short cuts --------------------
 */     


 
//write keystrokes 
void macro(String s){
  for(int i=0; i<s.length(); i++)
           Keyboard.write(s[i]); 
}
void kbrelease(){
    delay(d);  //fixes command click after wake.!
    Keyboard.releaseAll(); 
}
