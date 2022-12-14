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
  delay(500);

  return 0;
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
  RB_DcmotorOnBoard.run(-40,-40);
  delay(200);
  RB_DcmotorOnBoard.run(0,0);
  delay(500);
  tleft();
  //delay(1000);
  //tleft();
  
  //while (ul_distance <= 20)
  //{
  //  tleft();
  //  delay(400);
//
  //}
  
  RB_DcmotorOnBoard.run(50,50);
  delay(600);
  RB_DcmotorOnBoard.run(0,0);
  delay(500);
  tright();
  
  RB_DcmotorOnBoard.run(50,50);
  delay(1200);
  RB_DcmotorOnBoard.run(0,0);
  tright();
  delay(500);
  RB_DcmotorOnBoard.run(50,50);

  delay(500);
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
    
	
}





void loop() {
  	if (digitalRead(USER_KEY_Pin)==LOW){
      moveobj();
    }
    RGBLED.setColor(0, 173, 215, 218);
	  RGBLED.show();
    int mem = 1;
    
    ul_distance = ul.Uldistance();
    Serial.println(ul_distance);
    
    ul.RB_Ultrasonic_SetRGB(0X40, 0XA1, 245, 0, 201);
    if (ul_distance <= 25){
      moveobj();
    }
    if (getLineType(LineFollower_2.ReadSensors(),3)) { //bright ; bright
    if (mem == 1){

    
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(-45);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(45);
      delay(100);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
    }
    if (mem == 2){
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(-45);
      delay(100);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
    }
    }

   
  //  if (getLineType(LineFollower_2.ReadSensors(),3)) { //bright ; bright
  //    RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(-45);
  //    RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(45);
  //    //delay(100);
  //    //RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
  //    //RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
	//} 
 
  while(!(getLineType(LineFollower_2.ReadSensors(),0))){
    	if (digitalRead(USER_KEY_Pin)==LOW){
        moveobj();
      }
    if (ul_distance <= 25){
      moveobj();
    }
    if (getLineType(LineFollower_2.ReadSensors(),3)) { //bright ; bright
      if (mem == 1){

      
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(-45);
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(45);
        delay(100);
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
      }
      if (mem == 2){
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(-45);
        delay(100);
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
        RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
      }
  } 
  if (getLineType(LineFollower_2.ReadSensors(),2)) { //dark ; bright
    RGBLED.setColor(2, 255, 0, 0);
    RGBLED.show();
    RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
    RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
    //delay(500);
    RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);
    RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
    mem = 2;
    
  

    
	  } 
    if (getLineType(LineFollower_2.ReadSensors(),1)) { //bright ; dark
      RGBLED.setColor(1, 255, 0, 0);
      RGBLED.show();
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
      //delay(500);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
      RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(45);
      mem = 1;




	  }

  }
  if (getLineType(LineFollower_2.ReadSensors(),0)){
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(45);
  RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(45);
  }
  //RB_DcmotorOnBoard.RB_DcmotorOnBoardM1_Run(0);
  //RB_DcmotorOnBoard.RB_DcmotorOnBoardM2_Run(0);
}
