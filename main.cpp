#include "mbed.h"
#include "N5110.h"
#include "Bitmap.h"
#include "Render.h"
#include "Joystick.h"
#include "Raycaster.h"
#include "Control.h"
#include "Enemy.h"
#include "Shooting.h"

Timer global;
InterruptIn buttonA(p29);

volatile int flag = 0;

bool kill = false;
bool enemy1;
bool enemy2;
bool enemy3;
bool enemy4;
bool enemy5;
bool enemy6;


void Gameloop();
bool Spawner(int x, int y, bool kill);


void TitleScreen();
int Menu();
void DeathScreen(float timer, int kills);
void WinScreen(float timer, int kills);
void Controls();
void buttonA_isr();


/// PRE GAME INITIALISATION: SETS FOV, STARTING PLAYER COORDINATES AND CLASS OBJECTS ///
double fov = 60;
Raycaster raycaster(fov);
Render render(fov);
Control control;
Enemy enemy;
Shooting shoot;    


/*
    N = 180, E = 270, S = 0, W = 90

*/

/* const int map[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
    {1,1,1,0,1,0,1,0,0,0,0,0,0,0,1,1,1,0,1,1},
    {1,0,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1,0,x,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,0,1,1,1,1},
    {1,1,0,0,x,0,1,0,0,0,0,1,1,1,1,0,1,x,0,1},
    {1,1,0,1,0,0,0,0,1,1,0,1,1,x,1,x,1,1,0,1},
    {1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1},
    {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1},
    {1,1,1,1,1,x,1,1,0,1,0,x,1,1,1,x,0,0,0,1},
    {1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,x,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

*/

static const int map[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
    {1,1,1,0,1,0,1,0,0,0,0,0,0,0,1,1,1,0,1,1},
    {1,0,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1},
    {1,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,0,1,1,1,1},
    {1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,1},
    {1,1,0,1,0,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1},
    {1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1},
    {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1},
    {1,1,1,1,1,0,1,1,0,1,0,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int main() {
        
        TitleScreen();

        while(1) {      
        
          int option = Menu();  
        
          switch(option) {
              case 1:
                Gameloop();
                break;
              case 2:
                Controls();
                break;
              case 3:
                main();
                break;
               
         }
    }
}


void Gameloop() {
    
    int kills = 0;
    global.start();
    enemy1 = true;
    enemy2 = true;
    enemy3 = true;
    enemy4 = true;
    enemy5 = true;
    enemy6 = true;
    
    control.spawnPlayer(25,25,270);
    
    bool dead = false;
    bool win = false;
    
    while (dead == false && win == false ) {
    
    ///// READS INPUTS  /////
    
        control.get_xya();
        control.check_collision(map);
        position player = control.return_xya(); 
        control.ammoCounter();
        control.Reload();
        control.Reload();
        dead = control.Health(shoot.recieve_hit_detect());
        
        if(control.Check_Fire()) {
             render.Gun(true);      // gun shooting animaition  
             if(shoot.hitDetect()) {    // checks if enemy has been hit 
                 kill = true;
                 kills++;
             }    
         } else {
             render.Gun(false);     // normal gun animation
         }
        
        ///// SPAWNS ENEMY //////////
        
        bool spawned = Spawner(player.x, player.y, kill);
        
        if(kill) {
            kill = false;
        }
        
        ///// SEND PLAYER COORDINATES TO RAYCASTER, RUNS RAYCASTER LOOP //////
        
        raycaster.Pos(player.x, player.y, player.a);  
        raycaster.Raycast_Loop(map);
        
        //// RENDERS ENEMY AND WALLS /////
        
        if(spawned) {
            render.Enemy(raycaster.get_enemy_column(),raycaster.get_enemy_distance());  
            shoot.setColumn(raycaster.get_enemy_column());
        } else {
            shoot.setColumn(0);
        }
        for(int column = 0; column < 84; column++) {
            render.Wall(column,raycaster.get_wall_distance(column));
            render.Write();
        }
        
        wait_ms(20);
        render.Clear();
        
        if (player.x > 100 && player.x < 140 && player.y < 5) {
            win = true;
        }
        printf("PX = %d, PY = %d\n", player.x, player.y);
     }
     global.stop();
     if (dead == true) {
        DeathScreen(global.read(), kills);
     }
     else if (win == true) {
         WinScreen(global.read(),kills);
     }
     global.reset();
}  


void TitleScreen() {
    render.Title();
    render.Write();
    wait(3);
    render.Clear();
}

int Menu() {
   int input = 0;
   while(1) {
       render.Menu();
       render.Write();
       input = control.Menu();
       if (input > 0) {
           render.Clear();
           break;
        }
    }
    return input;  
}

void Controls() {
    int page = 1;
    buttonA.rise(&buttonA_isr);
    buttonA.mode(PullNone);
    
    while(1) {
        
        render.Controls(page);
        render.Write();
        wait_ms(500);
        
        if(flag == 1) {
            flag = 0;
            render.Clear();
            page++;
        }
        if(page == 6) {
            render.Clear();
            break;
        }       
    }
}

void buttonA_isr() {
    flag = 1;
}

void DeathScreen(float timer, int kills) {
    
    buttonA.rise(&buttonA_isr);
    buttonA.mode(PullNone);
    
    while(1) {
        
        render.DeathScreen(timer, kills);
        render.Write();
        
        if(flag == 1) {
            flag = 0;
            render.Clear();
            break;
        }
        
    }
}

void WinScreen(float timer, int kills) {
    
    buttonA.rise(&buttonA_isr);
    buttonA.mode(PullNone);
    
    while(1) {
        
        render.WinScreen(timer, kills);
        render.Write();
        
        if(flag == 1) {
            flag = 0;
            render.Clear();
            break;
        }
        
    }
}







bool Spawner(int x, int y, bool kill) {
    
    if (y > 130 && y < 190 && x < 100 && enemy1 == true) {
            enemy.spawn(60,160);
            enemy2D soldier = enemy.Position();   
            raycaster.EnemyPos(soldier.x, soldier.y, true);
            
            if(kill == true) {
                enemy1 = false;
            }
            
            return true;
    }
    
    else if (y > 260 && y < 290 && x < 120 && enemy2 == true) {
            enemy.spawn(80,260);
            enemy2D soldier = enemy.Position();   
            raycaster.EnemyPos(soldier.x, soldier.y, true);
            
            if(kill == true) {
                enemy2 = false;
            }
            
            return true;
    }
    
    else if (y > 339 && y < 360 && x > 40 && x < 80 && enemy3 == true) {
            enemy.spawn(60,360);
            enemy2D soldier = enemy.Position();   
            raycaster.EnemyPos(soldier.x, soldier.y, true);
            if(kill == true) {
                enemy3 = false;
            }
            
          return true;
    }
    
    else if (y > 280 && y < 320 && x > 119 && x < 200 && enemy4 == true) {
            enemy.spawn(200,300);
            enemy2D soldier = enemy.Position();   
            raycaster.EnemyPos(soldier.x, soldier.y, true);
            if(kill == true) {
                enemy4 = false;
            }
            
          return true;
    }
    
    else if (y < 279 && y > 246 && x < 239 && x > 179 && enemy5 == true) {
            enemy.spawn(200,260);
            enemy2D soldier = enemy.Position();   
            raycaster.EnemyPos(soldier.x, soldier.y, true);
            if(kill == true) {
                enemy5 = false;
            }
            return true;
    }
    
    else if (y < 101 && y > 60 && x < 220 && x > 140 && enemy6 == true) {
            enemy.spawn(180,80);
            enemy2D soldier = enemy.Position();   
            raycaster.EnemyPos(soldier.x, soldier.y, true);
            if(kill == true) {
                enemy6 = false;
            }
            return true;
    }
    
    
    
    else {
         raycaster.EnemyPos(0, 0, false);
         return false;
    }
}


            
    
    