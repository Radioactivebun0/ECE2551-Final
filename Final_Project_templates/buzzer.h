#ifndef BUUZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
    public:
    explicit Buzzer(int buzzerpin) : BUZZER_PIN(buzzerpin) {
        pinMode(BUZZER_PIN, OUTPUT);
    }

    void bscroll(){
        //tone function for BUZZER_PIN at 988 Hz for 100 ms)
    }

    void bback (){
       //tone function for BUZZER_PIN at 740 Hz for 200 ms)
    }

    void bdot(){
        //tone function for BUZZER_PIN at 830 Hz for 60 ms)
    }

    void bdash(){
	//tone function for BUZZER_PIN at 830 Hz for 180 ms)
    }

    void bselect(){
        //tone function for BUZZER_PIN at 1244 Hz for 200 ms)
    }
    private:
    const int BUZZER_PIN;
};



#endif // BUZZER_H