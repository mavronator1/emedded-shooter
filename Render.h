#ifndef RENDER_H
#define RENDER_H

class Render {
    
    public:
    
    // constructor sets FOV
    Render(int fov);
    // renders Title
    void Title();
    // renders Menu
    void Menu();
    // renders Controls screen
    void Controls(int page);
    // renders Death screen, showing time played and number of kills
    void DeathScreen(float time, int kills);
    // renders Win screen:
    void WinScreen(float time, int kills);
    // renders wall in column of screen
    void Wall(int column, double l);
    // renders gun or gun animation
    void Gun(bool f);
    // renders enemy
    void Enemy(int column, double l);
    // refreshes LCD buffer, writing to screen
    void Write();
    // clears LCD buffer
    void Clear();
    
    
    private:
    
    double _distance; // distance from player to projection plane
    bool start; 
    
    
    
    
    
    
    
    
    
};
















#endif 