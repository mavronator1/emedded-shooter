#include "Shooting.h"
#include "mbed.h"
#include <stdlib.h>


Timer enemy_shoot_time; 

Shooting::Shooting() {
    enemy_column = 0;
    enemy_shoot_time.start();
}

void Shooting::setColumn(int column) {
    enemy_column = column;
    
}


bool Shooting::hitDetect() {    
    
        // enemy hit if shot in middle of screen 
        if (enemy_column > 34 && enemy_column < 50) {
            return true;
        }
        else {
            return false;
        }
        
}

bool Shooting::recieve_hit_detect() {
    
    // enemy must be spawned and can only shoot every 2 seconds 
    
    if (enemy_column != 0 && enemy_shoot_time.read() > 2) {
        
        enemy_shoot_time.reset();
        srand (time(NULL));
        int random = rand() % 9;    // generates random number 0 to 9;
        printf("rand %d \n", random);
        if (random > 1) {   // 90% chance of hitting player 
            return true;
        }      
        else {
            return false;
        }
    }
    else {
        return false;
    }
            
}   