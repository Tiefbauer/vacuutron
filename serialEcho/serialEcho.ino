int angleMap[360];
byte package[42]; //package[0]:= FA
byte packagePointer =0;
bool isSynced=false;


void setup() {
  Serial.begin(230400);
  lidarInit();
  for(int i = 0; i < 360; i++){
    char p[10];
     
    sprintf(p,"%04i,", i);
    Serial.print(p);
  }
  
  Serial.println("");
}

void loop() {
  if(Serial1.available()){
    pullSensor();
  }
  
  if(Serial.available()){
      if(Serial.read() == 'o') outputAngle();//Ausgabe mit o
    }
  
}

void lidarInit(){
  Serial1.begin(230400);
  Serial1.print('b');
  }

void reset(){
  
  }

bool validate(){
  if(package[0] != 0xFA){
    //Serial.println("syncFailed");
    isSynced = false;
    return false;    
  }
  byte sum=0; 
  for(byte i=0;i<40;i++)sum+=package[i];  
  if(0xFF - sum==package[40]&& 0xFF - sum==package[41]) return true;//Zweiter check redundant-
  Serial.println("chkFailed");
  return false;
}

void pushToMap(){
  //Serial.println("Pushing map");
  if(validate()) {
    for(int i = 0; i < 6; i++){
       //Serial.println((package[1]-160)*6);
       int val=(package[7+i*6]*256)+package[6+i*6];
       if (val) angleMap[(package[1]-160)*6+i]=val; //value 0= fehler bzw zu nah, daher skip
    }
    
  }
}

void  pullSensor(){
  if(isSynced){
    while(Serial1.available()){
      package[packagePointer]=Serial1.read();
        if(packagePointer==41){
          pushToMap();
          packagePointer = 0;
          return;
        }
      packagePointer++;
    }
  }
  else{
    while(Serial1.available()){
      if(Serial1.read()== 0xFA){
        packagePointer=0;
        package[packagePointer]= 0xFA;
        packagePointer++;
        isSynced=true;
        return;
      }
    }
  }
}

void outputAngle() {
  
  for(int i = 0; i < 360; i++){
    char p[10];
     
    sprintf(p,"%04i,", angleMap[i]);
    Serial.print(p);
  }
  Serial.println("");
  
  
}



//void angleIdx(){
//  byte test = 0xFA;
//  while(!Serial1.available()){}
//  while(Serial1.read() != 0xFA){
//    while(!Serial1.available()){
//      }
//  }
//  Serial.println("---------------------------------------------");
//  //Synced:::
//  for(int idx1 = 0; idx1 < 39; idx1++){
//    //Serial.println("DEBUGG#03");
//    while(!Serial1.available()){}
//    test += Serial1.read();
//  }
//  Serial.println(0xFF - test, HEX);
//  while(!Serial1.available()){}
//  Serial.println(Serial1.read(), HEX);
//  while(!Serial1.available()){}
//  Serial.println(Serial1.read(), HEX);
//  
// }
// 
