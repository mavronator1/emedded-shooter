#ifndef SHOOTING_H
#define SHOOTING_H


class Shooting {
    
    public:
    
    // constructor sets enemy column to 0 and starts time
    Shooting();
    // sets enemy column
    void setColumn(int column);
    // checks if player shooting has hit enemy 
    bool hitDetect(); 
    // checks if player has been hit by enemy 
    bool recieve_hit_detect();
    
    private:
    
    int enemy_column;   // screen column which enemy has been rendered 
    
    
    
    
    
    
    
    
};

















#endif