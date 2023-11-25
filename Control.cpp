#include "Control.h"
#define D2R 0.01745329f
#include "ShiftReg.h"  



Timer fire_time;    // time between player gun shots
Timer heal_time;    // time for healing 

ShiftReg shift;
Joystick joystick(p20,p19); // MOVE 

DigitalIn button_A(p29);    // SHOOT
DigitalIn button_C(p27);    // RELOAD
DigitalIn button_B(p28);    // TURN LEFT   
DigitalIn button_D(p26);    // TURN RIGHT
BusOut rgb_led(p24,p23,p22);    // HEALTH (GREEN, YELLOW, RED)



Control::Control() {
    
    button_A.mode(PullNone);
    button_B.mode(PullNone);
    button_C.mode(PullNone);
    button_D.mode(PullNone);
    shift.write(0x00);
    fire_time.start();
    joystick.init();   
//    dac.init();
    rgb_led.write(111); 
    _v = 5;
    
}

void Control::spawnPlayer(int x,int y, int a) {
    _x = x;
    _y = y;
    _a = a;
    ammo = 9;
    HP = 3;
}


int Control::Menu() {
    
    int i = 0;
    
    if (button_A.read() == 1) {
        i = 1;
    }
    else if (button_B.read() == 1) {
        i = 2;
    } 
    else if (button_C.read() == 1) {
        i = 3;
    }
    return i;
}



void Control::get_xya() {
    
    double mag = joystick.get_mag();
    double angle = joystick.get_angle();
    double Rx = _v*(mag*cos((90-angle)*D2R)); // resolved into x component * velocity;
    double Ry = _v*(mag*sin((90-angle)*D2R)); // resolved into y component * velocity;
    
    // makes sure moving joystick foward always moves player forward relative to the direction they are facing
    
    if (_a > 45 && _a < 135) {    
        tx = _x + (Rx);
        ty = _y - (Ry);
        
    } else if (_a > 135 && _a < 225) {
        tx = _x - (Ry);
        ty = _y - (Rx);
        
    } else if (_a > 225 && _a < 315) {
        tx = _x - (Rx);
        ty = _y + (Ry);
       
        
    } else if (_a > 315 || _a < 45) {
        tx = _x + (Ry);
        ty = _y + (Rx);
        
    }
    
    // turns player left or right
    if (button_A.read() == 1) {
      _a = _a - 10;
    } else if (button_C.read() == 1) {
        _a = _a + 10;
    }
    // makes sure angle does not go past 359 or below 0 
    if (_a > 359 ) {
        _a = _a - 360;
    }
    if (_a < 0) {
        _a = _a + 360;
    }
    
//    printf("PX = %d, PY = %d, PA = %d\n",_x,_y,_a);

}

bool Control::Check_Fire() {
    
    
    if (button_B.read() == 1 && ammo > 0 && fire_time.read() > 1) {
        ammo = ammo - 1;
//        dac.play(250,500);
        fire_time.reset();  // timer restricts firing to 1 shot a second
        return true;   
        
    } else {
        return false;
    }
}

void Control::Reload() {
    
    if (button_D.read() == 1) {
        ammo = 9;
    }

}

void Control::ammoCounter() {
    
    // hex values 0 to 9 in array 
    
    int seven_seg_array [] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
    shift.write(seven_seg_array[ammo]); 
    
}

bool Control::Health(bool hit) {
    
    if (hit) {
        HP = HP - 1;
        heal_time.reset();  // heal time reset every time player is shot 
        heal_time.start();
        
        if (HP < 1) {
            return true;
        }
    }
    
    if(heal_time.read() > 5 && HP < 3) {
        HP = HP + 1;
        heal_time.reset();
    }
    
    switch (HP) {
        
        case 1:
            rgb_led.write(0b110);   // HP 1 -> LED RED
            break;
        case 2:
            rgb_led.write(0b100);   // HP 2 -> LED YELLOW
            break;
        case 3:
            rgb_led.write(0b101);   // HP 3 -> LED GREEN
            
            
    }
    
    return false;
    
}
    
    


void Control::check_collision(const int (&map)[20][20]) {
    
    // map passed by reference, won't update player coordinates if new coordinates put player in wall 
    
    if(map[tx/20][ty/20] != 1) {
        _x = tx;
        _y = ty;
    }
    
}

position Control::return_xya() {
    position player = {_x,_y,_a};
    return player;
}


    
    
    

 








