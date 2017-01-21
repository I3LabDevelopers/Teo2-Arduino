#include <SharpIR.h>
#include <NewPing.h>



#define SHARP_PIN       A8
#define SONAR_TRIGGER   7 
#define SONAR_ECHO      8
#define SONAR_REACH     400 //cm

#define SHARP_MODEL     1080
#define SHARP_SAMPLES_AVG   25
#define SHARP_SENSITIVITY   25


SharpIR irsensor(SHARP_PIN,SHARP_SAMPLES_AVG,SHARP_SENSITIVITY,SHARP_MODEL);
NewPing sonar (SONAR_TRIGGER, SONAR_ECHO, SONAR_REACH);


uint16_t measure_distance() {
        uint16_t ir, son;

        ir = irsensor.distance();
        son = sonar.ping_cm(400);
//
//        if (son > 70) return son;
//        
//        if (son > 10 && son < 70) {
//            if (ir < 70) return (ir+son)/2;
//            return son;
//        }
        if (son == 0) return 500;
        return son;
    
    }