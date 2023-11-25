#include "Raycaster.h"
#include <math.h> 
#include <iostream>

#define D2R 0.01745329f

// Raycaster based on:
// Ray-Casting Tutorial For Game Development And Other Purposes, by F. Permadi - https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/


Raycaster::Raycaster(double fov) {
    _fov = fov;
    _da = fov/84;
}

void Raycaster::Pos(double x, double y, double a) {
    _x = x;
    _y = y;
    _a = a;
}

void Raycaster::EnemyPos(int x, int y, bool flag) {
    _ex = x/20;
    _ey = y/20;
    _flag = flag;

//    printf("EX %i, EY %i",_ex,_ey);
}

void Raycaster::Raycast_Loop(const int (&map)[20][20]) {
    
     /* 
            Raycaster Summary:
            
            -> Raycaster uses 20x20 map with horizontal lines and vertical lines
            -> Ray is cast from players position, with 84 rays being cast (1 for each column on screen)
            -> fov is 60 degrees so angle between each ray is 60/84 (incrementation value)
            -> ray intercepts horizontal lines on map (hx, hy) and vertical lines (vx, vy)
            -> distance is calculated between two horizontal intercepts (dhx, dhy) and 
               two vertical intercepts (dvx, dvy) using basic trig
            -> distance is added continuously, tracing the ray's interceptions on both horizontal and vertical lines
            -> if ray hits a wall, the shorter length of the vertical or horizontal distance is used as the 
               distance of the player to the wall. This value is multipled by cos(player angle - ray angle) to remove 
               fish eye effect.
            -> if ray doesn't hit wall and number of iterations is up (ray has reached maximum distance) then angle
               increment is added and next ray is cast
            
            */
    
    ehit = false;     

    for(int i = 0; i < 84; i++) {
        Cast(i,map);
    }
    
}


void Raycaster::Cast(int column, const int (&map)[20][20]) {
    
        
           


            double ray_angle; // angle of ray cast
            double hx, hy;  // x and y on horziontal lines of grid
            double dhx, dhy;    // difference between x and y on horizontal lines of grid
            double vx, vy;  // x and y on vertical lines of grid
            double dvx, dvy;    // difference between x and y on vertical lines of grid
            bool hc = false;    // ignores horizontal lines if true
            bool vc = false;    // ignores vertcial lines if true

            ray_angle = _a+(_fov/2 - (column*_da));
            
            // makes sure ray angle stays between 0 and 359 degrees
            
            if (ray_angle > 359) {
                ray_angle = ray_angle - 359;
            };
            
            if (ray_angle < 0) {
                ray_angle = ray_angle + 360;
            };
            
            ////// INTERSECTIONS ON HORIZONTAL GRID LINES ///////// 
            
            
            if (ray_angle < 180) {   // FACING UP       
                hy = ((floor(_y/20)) * 20) - 1; 
                
                // RAY MOVES UP
                
                dhy = -20;  
                dvy = -abs(20*tan(ray_angle*D2R));
                
            } else {    // FACING DOWN
                hy = ((floor(_y/20)) * 20) + 20; 
            
                // RAY MOVES DOWN
            
                dhy = 20;  
                dvy = abs(20*tan(ray_angle*D2R));
              
            }
                                              
            hx = _x+((_y-hy)/tan(ray_angle*D2R));
            
            ///// INTERSECTIONS ON VERTICAL GRID LINES /////////
            
            if (ray_angle > 90 && ray_angle < 270) {    // FACING LEFT
                vx = ((floor(_x/20))*20) - 1;
                
                // RAY MOVES LEFT:
                
                dvx = -20;  
                dhx = -abs(20/tan(ray_angle*D2R));
                
            } else {    // FACING RIGHT: 
                vx = ((floor(_x/20))*20) + 20;
                
                // RAY MOVES RIGHT:
                
                dvx = 20;
                dhx = abs(20/tan(ray_angle*D2R));
            }
            
            vy = _y + ((_x-vx)*tan(ray_angle*D2R));
            
            // checks if a special condition should be triggered
            
            
            if(ray_angle == 90 || vy < 0 || ray_angle == 270) {
                vc = true; 
            }
            if(ray_angle == 180 || vx < 0 || ray_angle == 0) {
                hc = true;
            }
            
            // calls WallHitCheck to check if ray hits wall
            
            WallHitCheck(column,map, ray_angle, hx, hy, dhx, dhy, vx, vy, dvx, dvy, vc, hc);
            
            // only calls EnemyHitCheck if enemy is spawned
            if(_flag == true) {
                EnemyHitCheck(column, map, ray_angle, hx, hy, dhx, dhy, vx, vy, dvx, dvy, vc, hc);
            }
}

void Raycaster::WallHitCheck(int column, const int (&map)[20][20], double ray_angle, double hx, double hy, double dhx, double dhy, double vx, double vy, double dvx, double dvy, bool vc, bool hc) {
    
        

    bool max = false; // if ray goes out of bounds of map stop extending ray 
    
    int hmx, hmy;   // integer variable for x and y on horziontal lines of grid (used in checking if there is a hit on the map)
    int vmx, vmy;   // integer variables for vertical lines 
    
    // lengths from player to hit wall on horizontal line or hit on vertical line
    double hl = 0;  
    double vl = 0;
    
    double l;
    
   
    if(hc == false) {   // no special cases on horizontal line therefore look if wall is hit on ray path through horizontal lines
        
        for(int i = 0; i < 10; i++) {
        
            hmx = hx/20;    // converts horizontal intercepts to integer and to map grid form
            hmy = hy/20;     
            
            // checks if ray is out of bounds, if it is set it so it isn't out of map (will crash game otherwise)  
            
            if (hmx > 20 || hmy > 20 || hmx < 0 || hmy < 0) {   
                max = true;
                if (hmx > 20) {
                  hmx = 20;
                }
                if (hmy > 20) {
                  hmy = 20;
                }
                if (hmx < 0)  {
                  hmx = 0;
                }
                if (hmy < 0) {
                  hmy = 0;
                }
            }
            if(map[hmx][hmy] == 1) {    // hit!
                hl = sqrt(pow((hx-_x),2) + pow((hy-_y),2)); // length from player to hit
                l = hl*cos((_a-ray_angle)*D2R); // applies fish eye correction
                break;  
                    
            } else if (max == false) {
                hx = hx + dhx;  // if no hit, increment (cast ray further)
                hy = hy + dhy;

            } else {
                  break;
            }
        }
    }
    
    max = false;    // sets max to default value for vertical check
    
    // same process as before but just using the ray's interceptions on the vertical grid lines
    
    if(vc == false) { // no special cases on vertical line therefore look if wall is hit on ray path through vertical lines
    
        for(int i = 0; i < 10; i++) {         

                vmx = vx/20;
                vmy = vy/20;

                if (vmx > 20 || vmy > 20 || vmx < 0 || vmy < 0) {
                    max = true;

                    if (hmx > 20) {
                      hmx = 20;
                    }
                    if (hmy > 20) {
                      hmy = 20;
                    }
                    if (hmx < 0)  {
                      hmx = 0;
                    }
                    if (hmy < 0) {
                      hmy = 0;
                    }

                }
                
                if(map[vmx][vmy] == 1) {
//                    printf("VMX %d, VMY %d\n", vmx, vmy);
                    vl = sqrt(pow((vx-_x),2) + pow((vy-_y),2));
                    l = vl*cos((_a-ray_angle)*D2R);
                    break;

                } else if (max == false) {
                    vx = vx + dvx;
                    vy = vy + dvy;

                }   else {
                    break;
                }
        }
         
    }       
                
                
    if(vc == false && hc == false && hl > 0 && vl > 0) {    // checks if the ray has hit a wall on both the vertical and horizontal line
        if(vl > hl) {   // finds which is the shorter length
            l = hl*cos((_a-ray_angle)*D2R);

        } else {
            l = vl*cos((_a-ray_angle)*D2R);
        }
    }
    
    // writes the distance calculated to array, position in ray corrisponds to ray cast
    
    wall_distances[column] = l;
    
}
    

void Raycaster::EnemyHitCheck(int column, const int (&map)[20][20], double ray_angle, double hx, double hy, double dhx, double dhy, double vx, double vy, double dvx, double dvy, bool vc, bool hc) {

    // performs ray cast searching for enemies 
    
    // extends enemy cooridnates to +- 2 of the ex, ey
    // testing showed this was the optimum distance to get accurate ray hits    
    
    int upper_ex = (_ex*20)+2;
    int lower_ex = (_ex*20)-2;
    int upper_ey = (_ey*20)+2;
    int lower_ey = (_ey*20)-2;

    double ehd = 0; // enemy from player distance using horizontal ray intercepts
    double evd = 0; // enemy from player distance using vertical ray intercepts

    double enemy_distance = 0;

    // similiar process to checking for walls:

    if (hc == true) { // no special horizontal cases
      for(int i = 0; i < 5; i++) {

        if(hx > lower_ex && hx < upper_ex && hy > lower_ey && hy < upper_ey) {
          ehd = sqrt(pow((hx-_x),2) + pow((hy-_y),2));
          enemy_distance = ehd*cos((_a-ray_angle)*D2R); // applies fish eye correction
//          printf("HORIZONTAL HIT!\nhx = %f, hy = %f, distance = %f\n",hx, hy, enemy_distance);
          ehit = true;
          break;
        }

        hx = hx + dhx;
        hy = hy + dhy;

      }
    }
    if (vc == false) {
      
      for(int i = 0; i < 5; i++) {

        
        if(vx > lower_ex && vx < upper_ex && vy > lower_ey && vy < upper_ey) {
          evd = sqrt(pow((vx-_x),2) + pow((vy-_y),2));
          enemy_distance = evd*cos((_a-ray_angle)*D2R); // applies fish eye correction
          ehit = true;
//          printf("VERTICAL HIT!\nvx = %f, vy = %f, distance = %f\n",vx, vy, enemy_distance);
          break;
        }

        vx = vx + dvx;
        vy = vy + dvy;

      }

    }
    
    // determines which distance is shorter if both have a hit

    if(evd > 0 && ehd > 0) {
      
      if (evd > ehd) {
        enemy_distance = ehd*cos((_a-ray_angle)*D2R);
      }
      else {
        enemy_distance = evd*cos((_a-ray_angle)*D2R);
      }

    }
    
    // writes enemy distance to column, will write 0 if no hit 

    enemy_distances[column] = enemy_distance;

}   
  

    
double Raycaster::get_wall_distance(int i) {
   return wall_distances[i];
}

double Raycaster::get_enemy_distance() {

  // if raycaster does not detect enemy return 0    

  if (ehit == true) {
      
    // this section loops through the array of calculated enemy distances and 
    // takes the middle distance of the distances calculated

    bool x = false; // true when a distance > 0 is detected (lower boundry)

    int lb; // lower boundry
    int ub; // upper boundry 

    for (int i = 0; i < 84; i++) {

      if(enemy_distances[i] != 0 && x == false) {
        lb = i; // sets lower boundry
        x = true;
      } 
      if(enemy_distances[i] == 0 && x == true) {
        ub = i-1;   // sets upper boundry
        break;
      }
      if(i == 83) {
        if(enemy_distances[i] != 0) {
          ub = 83;  // if last value is not zero then this must be upper boundry
        }
      }

    }

    enemy_column = (ub+lb)/2;   // middle value is half way between the two

    return enemy_distances[enemy_column];   // returns the distance
  
  } else {
    
    return 0;
  }
  
}

int Raycaster::get_enemy_column() {
    return enemy_column;
}



    
    
    
    