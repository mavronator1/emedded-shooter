#include "Render.h"
#include "mbed.h"
#include "N5110.h"
#include "Bitmap.h"
#include "math.h"
#define D2R 0.01745329f
#include <string>

N5110 lcd(p8,p9,p10,p11,p13,p21);


Timer tr; 

static int title1[] {
    
    0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
    0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0,
    0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,0,0,
    0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,

};
/*
static int title2[] {
    
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
    1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
    0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,1,1,0,0,
    0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,1,0,1,1,0,0,
    0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,
    0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,
    0,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,
    1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,
    1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,
    0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,
    0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,
    0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,1,0,1,1,0,0,
    0,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1,0,0,1,1,0,0,
    1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,


};

*/


static int gun[] {

            0,0,0,0,0,0,1,0,0,1,0,0,0,
            0,0,0,0,0,0,1,0,0,1,0,0,0,
            0,0,0,0,0,0,1,1,1,1,0,0,0,
            0,0,0,0,0,0,1,1,1,1,0,0,0,
            0,0,0,0,0,1,0,0,0,0,1,0,0,
            0,0,0,0,0,1,0,1,0,0,1,0,0,
            0,0,0,0,0,1,0,1,1,0,1,0,0,
            0,0,0,0,0,1,0,1,1,0,1,1,1,
            0,0,1,1,1,1,0,0,0,0,1,0,1,
            0,0,1,0,0,1,1,0,0,0,1,0,1,
            0,1,0,0,0,0,1,1,1,1,1,0,1,
            0,1,0,0,0,0,0,0,0,0,0,0,1,
            0,0,0,0,0,0,0,0,0,0,0,0,0,

};

static int gun_fire[] {
    
    0,0,0,1,1,0,0,0,
    0,0,0,1,1,0,0,0,
    0,0,0,1,1,0,0,0,
    1,1,1,0,0,1,1,1,
    1,1,1,0,0,1,1,1,
    0,0,0,1,1,0,0,0,
    0,0,0,1,1,0,0,0,
    0,0,0,1,1,0,0,0,
            
};

 static int enemy[] {
    
    0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,1,1,1,0,0,
    0,0,1,0,0,0,0,1,0,0,
    0,1,1,1,1,1,1,1,1,0,
    0,1,1,0,0,0,0,1,1,0,
    0,0,1,0,0,0,0,1,0,0,
    0,0,1,1,1,1,1,1,0,0,
    1,1,1,1,0,0,0,1,1,1,
    1,0,0,1,1,1,0,0,0,1,
    1,1,1,1,0,1,1,1,1,1,
    1,1,1,1,1,1,0,1,1,0,
    0,1,1,0,0,0,0,1,1,0,
    0,0,1,1,1,1,1,0,0,0,
    0,0,0,1,1,1,1,0,0,0,
    0,0,0,1,1,1,1,0,0,0,
    0,0,0,1,1,1,1,0,0,0,
    0,0,0,1,1,1,1,0,0,0,
    0,0,1,1,1,1,1,1,0,0,
    0,0,1,1,1,1,1,1,0,0,
    


};




Render::Render(int fov) {
    start = 0;
    lcd.init();
    _distance = 42/tan(fov/2*D2R);
}


void Render::Title() {
    lcd.printString("George Mavro's",1,0);
    Bitmap Title(title1,13,84);
    Title.render(lcd,0,18,1);
    lcd.printString("201333891",15,5);
}

void Render::Menu() {
    lcd.printString("A: Play",0,1);
    lcd.printString("B: Controls",0,2);
    lcd.printString("C: Back",0,4);
}

void Render::Controls(int page) {
    
    switch(page) {
        
        case 1:
    
            lcd.printString("JOYSTICK:",0,0);
            lcd.printString("Moves player",0,2);
            lcd.printString("around map",0,3);
            lcd.printString("Press A",0,5);
            break;

        case 2: 
            lcd.printString("BUTTONS:",0,0);
            lcd.printString("C turns left",0,2);
            lcd.printString("A turns right",0,3);
            lcd.printString("Press A",0,5);
            break;
            
        case 3:
            lcd.printString("BUTTONS:",0,0);
            lcd.printString("B shoots",0,2);
            lcd.printString("D reloads",0,3);
            lcd.printString("Press A",0,5);
            break;
            
        case 4:
            lcd.printString("7 SEG DISP:",0,0);
            lcd.printString("Shows ammo",0,2);
            lcd.printString("Press A",0,5);
            break;
            
        case 5:
            lcd.printString("LED:",0,0);
            lcd.printString("Shows HP",0,1);
            lcd.printString("RED = LOW",0,2);
            lcd.printString("YELLOW = MID",0,3);
            lcd.printString("GREEN  = FULL",0,4);
            lcd.printString("Press A",0,5);
            break;
    }
}

void Render::DeathScreen(float timer, int kills) {
    lcd.printString("YOU DIED!",0,0);
    lcd.printString("You Survived:",0,1);
    char buffer[14];
    sprintf(buffer,"%.2f seconds",timer); 
    lcd.printString(buffer,0,2);
    lcd.printString("Killing:",0,3);
    sprintf(buffer,"%d enemies",kills);
    lcd.printString(buffer,0,4);    
    
}

void Render::WinScreen(float timer, int kills) {
    lcd.printString("CONGRATS!!",0,0);
    lcd.printString("You Escaped In:",0,1);
    char buffer[14];
    sprintf(buffer,"%.2f seconds",timer); 
    lcd.printString(buffer,0,2);
    lcd.printString("Killing:",0,3);
    sprintf(buffer,"%d enemies",kills);
    lcd.printString(buffer,0,4);    
    

}
void Render::Wall(int column, double l) {
   
   if(l != 0) {
   
        double wall_height = (10/l)*_distance;  // height of wall to be rendered on screen
   
        if (wall_height > 48) { // limits max height to 48
            wall_height = 48;
        }   
        
        int z = wall_height/2; 
    
        lcd.drawLine(column,(24-z),column,(24+z),2);    // draws wall on screen
    }
}

void Render::Gun(bool f) {
    
    // creates Bitmap object for the gun and the fire animation
    
    Bitmap sprite(gun,13,13);      
    Bitmap fire(gun_fire,8,8);  
    
    if (start == 0) {
        start = 1;
        tr.start(); // starts timer on first run
    }
    
    if(f) { // if player has fired gun 
        sprite.render(lcd,38,41,1);
        fire.render(lcd,42,24,1);
        
    }
    
    
    else if (tr.read() > 0.5) { // every 0.5 second changes gun location - gives breathing effect 
        sprite.render(lcd,41,37,1);
        tr.reset();
    }
    
    else {
        sprite.render(lcd,40,38,1); // normal gun render
    }
    
}
    

         
 

void Render::Enemy(int column, double l) {
    
 
     
    if (l != 0) {        
    
//        printf("Recieved Column = %d, Recieved Distance = %f\n", column, l);
            
        double height = ((10/l)*_distance)/2;   // height of enemy to be rendered 
    
        if (height > 24) { 
                height = 24;    // caps height at 24
            }
        if (height < 8) {
                height = 8; // minimum height 8
        }
            
        int sf = height/8;  // scaling factor to render enemy 
        
        
    
    
        Bitmap sprite(enemy, 19, 10);   // create bitmap object
        sprite.render(lcd,column,20,sf);   
        
    }    
     
}
void Render::Write() {
     lcd.refresh();
}   

void Render::Clear() {
    lcd.clear();
    lcd.refresh();
}