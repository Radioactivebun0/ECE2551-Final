#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include "Memory.h"
#include "Message.h"
#include "Contact.h"
#include "Entropy.h"
#include "EEPROM.h"
#include "LCD.h"
#include <SPI.h>
#include "buzzer.h"


Buzzer mybuzzer(4);
EntropyClass myentropy();

//Hint: try coding first with hard wired name and uuid and then make it random (in case randomizing gives you any error).
//char you_name[10] = {'y','o','u',' ',' ',' ',' ',' ',' ',' '};
//uint8_t you_uuid[5] = {'0','1','A','1','3'};
Contact me(you_uuid,you_name);

Memory memory(me);




RF24 myradio(A1,A2);
//const byte add[][6] = {"N1" , "N2"}; Pipe address



void setup(){
  Serial.begin(9600);
  myscreen.begin(16,2);
  myscreen.setCursor(0,0);
  myscreen.print("Welcome!");
  myscreen.setCursor(0,1);


myradio.setPALevel(RF24_PA_LOW);
myradio.setDataRate(RF24_250KBPS);
myradio.setChannel(100);
myradio.openReadingPipe(1, add[0]);   
//Other  useful function for radio is myradio.openWritingPipe(); mytadio.stopListenting(); myradio.read(); myradio.write(); myradio.begin()
myradio.startListening();
}

void loop(){
  //myscreen.hasbeenPushed();

}