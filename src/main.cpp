#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
SoftwareSerial DF1201SSerial(2, 3);  //RX  TX

DFRobot_DF1201S DF1201S;
void setup(void){
  Serial.begin(115200);
  DF1201SSerial.begin(115200);
  while(!DF1201S.begin(DF1201SSerial)){
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  DF1201S.setVol(5);
  Serial.print("VOL:");
  Serial.println(DF1201S.getVol());
  DF1201S.switchFunction(DF1201S.MUSIC);
  delay(2000);
  /*Set playback mode to "repeat all"*/
  DF1201S.setPlayMode(DF1201S.SINGLE);
  Serial.print("PlayMode:");
  /*Get playback mode*/
  Serial.println(DF1201S.getPlayMode());
  
  pinMode(7, INPUT);
}

void loop(){
  int curFile = DF1201S.getCurFileNumber();
  Serial.println(curFile);
  if (curFile != 3){
    DF1201S.playFileNum(3);
  }
  int val = digitalRead(7);
  if (!val){
    Serial.println("Start playing");
    /*Start playing*/
    int rand = random(1, 2);
    DF1201S.playFileNum(rand);
    int totaltime = DF1201S.getTotalTime() * 1000;
    Serial.println(totaltime);
    delay(totaltime + 500);
    DF1201S.pause();
  }
  delay(500);
}
