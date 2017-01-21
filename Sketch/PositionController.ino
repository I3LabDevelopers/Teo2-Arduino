#include <Encoder.h>

#define _L        (0.175f)    // Wheel distance from body origin [m]
#define _R        (0.035f)    // Wheel radius [m]

#define _C60    (0.500000000f)   // cos(60°) 
#define _C30    (0.866025404f)   // cos(30°)
#define _2PI     (6.283185307f)
#define _TICKS_REV (1632.67f)
#define _TOLERANCE  100

#define WHEEL1Y_PIN 2
#define WHEEL1W_PIN 3
#define WHEEL2Y_PIN 18
#define WHEEL2W_PIN 44
#define WHEEL3Y_PIN 19
#define WHEEL3W_PIN 34


Encoder enc1(WHEEL1Y_PIN,WHEEL1W_PIN);
Encoder enc2(WHEEL2Y_PIN,WHEEL2W_PIN);
Encoder enc3(WHEEL3Y_PIN,WHEEL3W_PIN);

//================== BLOCKING METHODS ============================//

// command a rotation of angle (degrees) and wait till is done. Positive angle is counter-clockwise.
void rotate_wait(float angle) {
        int ticks = (int)((-_L/_R)*(angle*_TICKS_REV/360)); 
        uint8_t _speed = angle < 0? -3:3;
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go(0,0,_speed);

        while (abs(ticks - enc1.read()) > _TOLERANCE);

        Stop();
    }

//command a forward translation of distance meters. Positive distance is moving ahead.
void moveForward_wait(float distance) {
        int wheel1, wheel2;
        float _speed = distance > 0? -1:1;
        
        wheel1 = (int)((_C30/_R)*distance*(_TICKS_REV/_2PI));
        wheel2 = (int)((-_C30/_R)*distance*(_TICKS_REV/_2PI));
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (0,_speed,0);
        while ( abs(wheel1-enc1.read()) > _TOLERANCE && abs(wheel2-enc2.read()) > _TOLERANCE );
        Stop();
        
    }


void moveLateral_wait(float distance) {     // positive distance is movement to the right
        int wheel1, wheel2, wheel3;
        float _speed = distance > 0? 1:-1;
        
        wheel1 = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel2 = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel3 = (int)((-1/_R)*distance*(_TICKS_REV/_2PI));
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (_speed,0,0);
        while (abs(wheel1-enc1.read()) > _TOLERANCE && abs(wheel2-enc2.read()) > _TOLERANCE && abs(wheel3-enc3.read()) > _TOLERANCE);
        Stop();
    
    }


//===================== NON-BLOCKING METHODS ==========================
/*
    When a non-blocking method is used to command a new position, the "refreshPositionControl" method 
    must be used to poll the position of Teo and to ensure that it stops when the commanded
    new position is reached. If not done, Teo will continue to move indefinitely.
*/
typedef struct {
        int ticks;
        int8_t sign;
} WheelTicks;


WheelTicks wheel1, wheel2, wheel3;

enum typeCommandEnum {
        none, rotation, forward, lateral
    };
    
 typeCommandEnum commanded = none;

void positionControlInit() {
        commanded = none;
        wheel1.ticks = 0;
        wheel1.sign = 0;
        wheel2.ticks = 0;
        wheel2.sign = 0;
        wheel3.ticks = 0;
        wheel3.sign = 0;
    }

boolean positionCommanded() {
        return commanded != none;
}

void stop_position_control() {
  Stop();
  commanded = none;
}

void refreshPositionControl() {
        boolean w1 = false, w2 = false, w3 = false;
        
        if(!commanded) return;
       
        wheel1.ticks -= enc1.read();
        enc1.write(0);

        if (sign(wheel1.ticks) != wheel1.sign)
            w1 = true;
            
        wheel2.ticks -= enc2.read();
        enc2.write(0);
        if (sign(wheel2.ticks) != wheel2.sign)
            w2 = true;

        wheel3.ticks -= enc3.read();
        enc3.write(0);
        if (sign(wheel3.ticks) != wheel3.sign)
            w3 = true;

        switch (commanded) {
        
            case rotation:
            case lateral:
                if (w1 || w2 || w3) {
                        Stop();
                        commanded = none;
                 }
                 break;
            case forward:
                if (w1 || w2) {
                        Stop();
                        commanded = none;
                    }
                break;
        }
    }

// command a rotation of angle (degrees) and wait till is done. Positive angle is counter-clockwise.
void rotate (float angle, float vel) {
        float _speed = angle < 0? -abs(vel):abs(vel);
        
        if (commanded) return;

        wheel1.ticks = (int)((-_L/_R)*(angle*_TICKS_REV/360));
        wheel1.sign = sign(wheel1.ticks);
        wheel2.ticks = wheel1.ticks;
        wheel2.sign = wheel1.sign;
        wheel3.ticks = wheel1.ticks;
        wheel3.sign = wheel1.sign;
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go(0,0,_speed);

        commanded = rotation;
    }
//command a forward translation of distance meters. Positive distance is moving ahead.
void moveForward(float distance,float vel) {
        float _speed = distance > 0? -abs(vel):abs(vel);
        
        if (commanded) return;
        
        wheel1.ticks = (int)((_C30/_R)*distance*(_TICKS_REV/_2PI));
        wheel1.sign = sign(wheel1.ticks);
        wheel2.ticks = (int)((-_C30/_R)*distance*(_TICKS_REV/_2PI));
        wheel2.sign = sign(wheel2.ticks);
        wheel3.ticks = 0;
        wheel3.sign = 0;
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (0,_speed,0);

        commanded = forward;
    }
    
// positive distance is movement to the right
void moveLateral(float distance,float vel) {
    
        float _speed = distance > 0? abs(vel):-abs(vel);
        
        if (commanded) return;
        
        wheel1.ticks = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel1.sign = sign(wheel1.ticks);
        wheel2.ticks = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel2.sign = sign(wheel2.ticks);
        wheel3.ticks = (int)((-1/_R)*distance*(_TICKS_REV/_2PI));
        wheel3.sign = sign(wheel3.ticks);
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (_speed,0,0);
        commanded = lateral;
    }

inline int8_t sign(int x) {
        if (x == 0) return 0;
        return (x > 0? 1:-1);
    }