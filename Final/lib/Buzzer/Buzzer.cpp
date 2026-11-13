#include "Buzzer.h"

// call these function to get buzzer sounds

void Buzzer::bscroll(){ 
    tone(BUZZER_PIN, 988, 100);
}

void Buzzer::bback (){
    tone(BUZZER_PIN, 740, 200);
}

void Buzzer::bdot(){
    tone(BUZZER_PIN, 830, 60);
}

void Buzzer::bdash(){
    tone(BUZZER_PIN, 830, 180);
}

void Buzzer::bselect(){
    tone(BUZZER_PIN, 1244, 200);
}

void Buzzer::bmsent(){
    tone(BUZZER_PIN, 988, 100);
}

void Buzzer::bmfailed(){
    tone(BUZZER_PIN, 740, 200);
}

void Buzzer::bmrecieved(){
    tone(BUZZER_PIN, 830, 60);
}