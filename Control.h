#ifndef CONTROL_H
#define CONTROL_H

#include "Joystick.h"

struct position {   // player x, player y, player angle
    int x;
    int y;
    int a;
};



class Control {
    
    public:
    
    // constructor initalises components
    Control();    
    // spawns player, sets ammo and health
    void spawnPlayer(int x, int y, int a);
    // reads button inputs for Menu, returns 1 for A, 2 for B, 3 for C.
    int Menu();
    // reads joystick and buttons B and D, obtains new player coordinates (tx, ty) and angle 
    void get_xya(); 
    // checks if new player coordinates will hit wall by taking map by reference, if so does not set x,y to tx, ty
    void check_collision(const int (&map)[20][20]); 
    // returns new player position and angle
    position return_xya();  
    // checks if player has and can shoot and returns if shot was succesful
    bool Check_Fire();  
    // check if reload button has been pressed and reloads gun
    void Reload();  
    // updates seven segment display with ammo count 
    void ammoCounter(); 
    // reduces player HP if hit, heals player if 5 seconds have passed since last hit, sets colour of RGB
    bool Health(bool hit); 
    
    bool A();
    
    
   
    private:
    
    int _x;     // player x
    int _y;     // player y  
    int _a;     // player angle
    int _v;      // player velocity
    
    int tx;     // temporary x
    int ty;     // temporary y
     
    int ammo; // 1 - 9 
    int HP; // 1 - 3
    
    

  
};

#endif 