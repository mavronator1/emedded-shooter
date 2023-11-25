#ifndef RAYCASTER_H
#define RAYCASTER_H






class Raycaster {
    
    public:
    
    // constructor sets fov for raycasting 
    Raycaster(double fov); 
    // sets player position
    void Pos(double x, double y, double a);  
    // sets enemy position, if flag = false raycaster will ignore enemy pos
    void EnemyPos(int x, int y, bool flag); 
    // runs full raycast loop for 84 columns of screen, calls Cast, WallHitCheck and EnemyHitCheck
    void Raycast_Loop(const int (&map)[20][20]); 
    
        // casts ray, map passed by reference 
        void Cast(int column, const int (&map)[20][20]); 
       
        // checks if ray hits wall, wall lengths are stored in array
        void WallHitCheck(int column, const int (&map)[20][20], double ray_angle, double hx, double hy, 
                      double dhx, double dhy, double vx, double vy, double dvx, double dvy, bool vc, bool hc); 
        // checks if ray hits enemy
        void EnemyHitCheck(int column, const int (&map)[20][20], double ray_angle, double hx, double hy, 
                      double dhx, double dhy, double vx, double vy, double dvx, double dvy, bool vc, bool hc); 
    
    // returns wall distance in array[i]
    double get_wall_distance(int i);   
    // returns enemy distance
    double get_enemy_distance();
    // returns enemy column
    int get_enemy_column(); 
    
    
    
    private:
    
    double _fov; 
    double _da; // angle per column of screen (fov/84)

    bool hit;
    
    double _x;  // player xya
    double _y;
    double _a;
    
    int _ex;    
    int _ey;
    bool _flag; 

    
    double wall_distances[84];
    double enemy_distances[84];
    
    int enemy_column;
    bool ehit;  // if enemy is hit by ray
    
    

};
    
    






#endif