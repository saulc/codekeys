/*
  micro based keyboard 3 interupts.  7 pinchange interupt?
  spaceL  mc  spaceR  
  comment uncomment ([0, 0, 0]) 'custom'
  tab/return  copy/cut  paste/paste+return
    spacebar
*/ 
#include "Keyboard.h"
#include "button.h"
 void mclick();
 void aclick();
 void bclick();
 void spaceL();
 void spaceR();
 void dt();
 
Button x(2, aclick, true);
Button c(3, bclick, true);
Button v(7, mclick, true);

const int d = 11; //release delay
void mclick(){ 
    int t = v.tap();
    if(t==1)  commandKey(2); 
    else if(t == 2) dt();
}
void aclick(){ 
    int t = v.tap();
    if(t==1)  commandKey(1); 
    else if(t == 2) commandKey(0);
}
void bclick(){ 
    int t = v.tap();
    if(t==1)  dt(); 
    else if(t == 2) space(2);
} 

void setup() { 
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

   //setup interupts for buttons
   v.ini();  
   c.ini(); 
   x.ini(); 

//      pinMode(2, INPUT_PULLUP); 
  // initialize control over the keyboard:
  Keyboard.begin();
}

int p = 2;

int t = 0;
void loop() {  
//  if( digitalRead(p) == LOW) spaceL();    //to do test non interupt buttons.
  
//  if(t++ > 1000)    Keyboard.releaseAll(); //fixes command click after wake.!
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
    }
    
//    Keyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz
    Keyboard.press(KEY_LEFT_GUI);  // press and hold command macOS not X
//    Keyboard.press(KEY_LEFT_SHIFT);  //  hold Shift for testing!! 
    Keyboard.press(c);         

    kbrelease();
}

void spaceL(){ space(0); }
void spaceR(){ space(1); }
void space(int d){   
    Keyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz 
     if(d==2) Keyboard.press(KEY_UP_ARROW);   //spaces/mission control
     else    Keyboard.press( (d==0) ? KEY_LEFT_ARROW : KEY_RIGHT_ARROW);      //change spaces/destops
    
    kbrelease();
}

void dt(){  
    Keyboard.press(KEY_RETURN);  
    kbrelease();
}
void kbrelease(){
    delay(d);  //fixes command click after wake.!
    Keyboard.releaseAll(); 
}
