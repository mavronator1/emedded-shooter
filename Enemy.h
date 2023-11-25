#ifndef ENEMY_H
#define ENEMY_H

struct enemy2D {    
    int x;
    int y;   
    
};




class Enemy {
    
    public:
    
    void spawn(int x, int y);  // spawns enemy at a coordinate
    enemy2D Position(); // returns position of enemy in map coordinates 
    void Move(); // moves enemy
    
    
    
    private:
    
    int _ex;
    int _ey;
    
    
    
    
};









#endif