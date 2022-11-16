#include "RB_QMIND.h"

RB_DcmotorOnBoard RB_DcmotorOnBoard;

RB_RGBLed RGBLED(2,2);
RB_Buzzer Buzzer(4);


int motorinit(){
    try{
        RB_DcmotorOnBoard.run(90,-90);
        delay(500);
        RB_DcmotorOnBoard.run(-90,90);
        return 0;
    }
    catch(){
        RB_DcmotorOnBoard.RB_DcmotorOnBoard_Init();
        return 1;
    }
}

void setup() {
	Serial.begin(115200);

	RB_DcmotorOnBoard.RB_DcmotorOnBoard_Init();
	delay(500);

    motorinit()
    while (motorinit() == 1){
        motorinit();
    }
    

	RGBLED.setColor(0, 173, 215, 218);
	RGBLED.show();
	Buzzer.tone(262, 500);

}

void loop() {

}