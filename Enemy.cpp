#include "Enemy.h"
#include "mbed.h"
#include <stdlib.h>

Timer t;


void Enemy::spawn(int x, int y) {  
    
    t.start();  // starts timer when enemy is spawned in
    _ex = x;
    _ey = y;
}

enemy2D Enemy::Position() {
    enemy2D position = {_ex, _ey};
    return position;
}
       
 
void Enemy::Move() {
    
    // enemy moves every 2 seconds
    // moves randomly +1 or -1 on y axis 
    
    if (t.read() > 2) {
        
        srand (time(NULL));
        int random = rand() % 10 - 5;
        srand (time(NULL));
        int random2 = rand() % 10 - 5;
        
        _ey = _ey + random;
        _ex = _ex + random;
       
        
        t.reset();    
    
    }
}