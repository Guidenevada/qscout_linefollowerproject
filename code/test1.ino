#include "RB_QMIND.h"


uint8_t val;
RB_DcmotorOnBoard RB_DcmotorOnBoard;
RB_Ultrasonic  ul(3);
double ul_distance =0;
RB_RGBLed RGBLED(2,2);
RB_Buzzer Buzzer(4);

RB_LineFollower LineFollower_2(2);

int tleft(){
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(50);
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(-50);
  delay(400);
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
  return 0;
  delay(500);
}
int tright(){
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(-50);
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(50);
  delay(400);
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
  delay(500);
  return 0;
}
int moveobj(){
  RB_DcmotorOnBoard.run(0,0);
  delay(1000);
  tleft();
  if (ul_distance <= 20){
    tright();
    tright();
  }
  
  RB_DcmotorOnBoard.run(50,50);
  delay(800);
  RB_DcmotorOnBoard.run(0,0);
  delay(500);
  tright();
  RB_DcmotorOnBoard.run(50,50);
  delay(800);
  RB_DcmotorOnBoard.run(0,0);
  delay(500);
  tright();
  RB_DcmotorOnBoard.run(50,50);
  delay(800);
  RB_DcmotorOnBoard.run(0,0);
  delay(500);
  tleft();
  return 0;
}

int getLineType (int line,int type){
  switch(type){
    case 0:
      if (line==0) return 1; //left dark ; right dark
      Serial.println("left dark ; right dark");
      break; 
    case 1:
      if (line==1) return 1; // left dark ; right bright
      Serial.println("left dark ; right bright");
      break;
    case 2:
      if (line==2) return 1; // left bright ; right dark
      Serial.println(" left bright ; right dark");
      break;
    case 3:
      if (line==3) return 1; // left bright ; right bright
      Serial.println("left bright ; right bright");
      break;
    default:
      return 0;
  }
  return 0;
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
    
	RGBLED.setColor(0, 173, 215, 218);
	RGBLED.show();
}





void loop() {
    
    
    ul_distance = ul.Uldistance();
    Serial.println(ul_distance);
    
    
    if (ul_distance <= 20){
      moveobj();
    }
    else{
        
        
        
        Serial.println("There is an error in line follower");
        
    }
    if (getLineType(LineFollower_2.ReadSensors(),3)) { //bright ; bright
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(-45);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(45);
      delay(100);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
	} 
  if (getLineType(LineFollower_2.ReadSensors(),1)) { //dark ; bright
   
    RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(45);
    

    
	} 
  if (getLineType(LineFollower_2.ReadSensors(),2)) { //bright ; dark
    RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);

    


	}
  if (getLineType(LineFollower_2.ReadSensors(),0)) //dark ; dark
  {
    RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(50);
	  RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(50);
  }

}
