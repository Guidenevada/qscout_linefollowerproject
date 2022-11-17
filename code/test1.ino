#include "RB_QMIND.h"

RB_LineFollower LineFollower(2);
uint8_t val;
RB_DcmotorOnBoard RB_DcmotorOnBoard;
RB_Ultrasonic  ul(2);
double ul_distance =0;
RB_RGBLed RGBLED(2,2);
RB_Buzzer Buzzer(4);


int motorinit(){
    try{
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);
	    RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(-45);
        delay(1000);
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);
	    RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(-45);
        delay(1000);
        return 0;
    }
    catch(){
        RB_DcmotorOnBoard.RB_DcmotorOnBoard_Init();
        return 1;
    }
}


void setup() {
    ul.RB_Ultrasonic_SetRGB(0x40,0xA1,200,0,0);
    delay(1000);
    ul.RB_Ultrasonic_SetRGB(0x40,0xA1,0,200,0);
    delay(1000);
     ul.RB_Ultrasonic_SetRGB(0x40,0xA1,0,0,200);
    delay(1000);  
    ul.RB_Ultrasonic_SetRGB(0x40,0xA1,0,0,0);
	Serial.begin(115200);
	RB_DcmotorOnBoard.RB_DcmotorOnBoard_Init();
	delay(500);
    motorinit()
    while (motorinit() == 1){
        motorinit();
    }
	RGBLED.setColor(0, 173, 215, 218);
	RGBLED.show();
}


void loop() {
    val = LineFollower.ReadSensors();
    ul_distance = ul.Uldistance();
    Serial.println(ul_distance);
    delay(500);
    if (ul_distance <= 20){
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);
	    RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(-45);
        delay(500);
    }
    else{
        
        if (val <= 50){
            int valr = val;
            RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(-45);
            if (val < valr){
                RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(70);
                if (val > valr){
                    Serial.println("GOOD"); 
                }
            }
        }
        if (val >= 50){
            int valr = val;
            RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(90);
            RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(90);
            delay(500);

        }
        else {
            Serial.println("There is an error in line follower");
        }
    }

}
