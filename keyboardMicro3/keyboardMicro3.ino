/*
  micro based keyboard 3 interupts. 1-2 digital, 1 pinchange interupt?
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
    if(t==1)  commandKey(0); 
    else if(t == 2) space(1);
}
void bclick(){ 
    int t = v.tap();
    if(t==1)  commandKey(1); 
    else if(t == 2) space(0);
} 

void setup() { 
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

   //setup interupts for buttons
   v.ini();  
   c.ini(); 
   x.ini(); 

  // initialize control over the keyboard:
  Keyboard.begin();
}

int t = 0;
void loop() {  
  
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
//    Keyboard.press(KEY_LEFT_SHIFT);  //  hold Shift for testing. lol
    Keyboard.press(KEY_LEFT_GUI);  // press and hold command macos not X
    Keyboard.press(c);         
    delay(d);  //fixes command click after wake.!
    Keyboard.releaseAll(); 
}

void spaceL(){ space(0); }
void spaceR(){ space(1); }
void space(int d){   
    Keyboard.press(KEY_LEFT_CTRL);  // press and hold control windoz 
     
    Keyboard.press( (d==0) ? KEY_LEFT_ARROW : KEY_RIGHT_ARROW);      
    delay(d);  //fixes command click after wake.!
    Keyboard.releaseAll(); 
}

void dt(){  
    Keyboard.press(KEY_RETURN);  
    delay(d); 
    Keyboard.releaseAll(); 
}
