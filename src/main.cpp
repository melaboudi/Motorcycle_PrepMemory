#include <Arduino.h>

#include "Adafruit_FRAM_I2C.h"
Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();
uint16_t          framAddr = 0;
unsigned int framWritePosition = 0;
#include <SoftwareSerial.h>
SoftwareSerial ss = SoftwareSerial(0, 1);
char* d1="AT+CGNSPWR=1";                //12
char* d2="AT+CREG?";                 //8
char* d3="AT+CGNSPWR?";                  //11
char* d4="AT+CGNSINF";                 //10
char* d5="<Track Imei=\"";               //13
char* d6="\" Fc=\"WGS84\" FixPosition=\"";       //26
char* d7="\" Lat=\"";                  //7  
char* d8="\" Lon=\"";                //7
char* d9="\" Vit=\"";                  //7
char* d10="\" Sat=\"";                 //7
char* d11="\" Cap=\"";                 //7
char* d12="\" BatteryLevel=\"";              //16
char* d13="\" Dh=\"";                  //6
char* d14="\"/>";                    //3
char* d15="AT+CFUN=1";                 //9
char* d16="AT+CPIN?";                  //8
char* d17="AT+CSTT=\"iamgprs1.ma\",\"\",\"\"";     //27
char* d18="AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";     //29
char* d19="AT+SAPBR=1,1";                //12
char* d20="AT+CIICR";                  //8
char* d21="AT+CIFSR";                  //8
char* d22="AT+HTTPTERM";               //13
char* d23="AT+HTTPINIT";               //13
char* d24="AT+HTTPPARA=\"CID\",1"  ;         //19
char* d25="AT+HTTPPARA=\"URL\",\"http://casa-interface.casabaia.ma/commandes.php\"";     //67
char* d26="AT+HTTPPARA=\"CONTENT\",\"application/xml"; //38
char* d27="AT+HTTPDATA=";                 //14
char* d28="<?xml version=\"1.0\" encoding=\"UTF-8\"?><Commandes idclient=\"76\" imei=\"";    //69
String d29=" ";             //15
char* d30="\"><Commande id=\"2142\" Nom=\"ADD_TRACKING\"><Param><Tracks>"  ;         //56
char* d31="</Tracks></Param></Commande></Commandes>";  //40
char* d32="AT+HTTPACTION=" ;             //14
char* d33="AT+CGATT=0";                  //10
char* d34="AT+HTTPPARA=\"URL\",\"http://velovolt.ddns.net:8080/datasnap/rest/Tdata/rep\""; //73
char* d35="AT+HTTPPARA=\"CONTENT\",\"application/json"; //39
char* d36="AT+CREG=1";                 //9
char* d37="AT+CFUN=0";                 //9

void flushSim();
void writeDataFram(char* dataFram);
void writeDataFramDebug(char* dataFram, long p1);
String returnImei();
void flushSim();
void powerKey();



void setup() {
  fram.begin();
  pinMode(3, OUTPUT);//VIO
  pinMode(A3, INPUT);//sim Power Status
  pinMode(0, INPUT);//SS RX
  pinMode(1, OUTPUT);//SS TX
  pinMode(6, OUTPUT);//sim Reset
  digitalWrite(6, HIGH); 
  digitalWrite(3, HIGH);
  powerKey();
  ss.begin(4800);
  delay(100);
  d29 = returnImei();
   for (uint16_t a = 0; a < 32768; a++) {
      fram.write8(a, 0);
  } 
  
 
  writeDataFramDebug(d1,31000);//12 "AT+CGNSPWR=1";
  writeDataFramDebug(d2,31012);//8 "AT+CREG?";
  writeDataFramDebug(d3,31020);//11 "AT+CGNSPWR?";
  writeDataFramDebug(d4,31031);//10 "AT+CGNSINF";
  writeDataFramDebug(d5,31041);//13 "<Track Imei=\"";    
  writeDataFramDebug(d6,31054);//26 "\" Fc=\"WGS84\" FixPosition=\"";
  writeDataFramDebug(d7,31080);//7 "\" Lat=\"";
  writeDataFramDebug(d8,31087);//7 "\" Lon=\"";
  writeDataFramDebug(d9,31094);//7 "\" Vit=\"";
  writeDataFramDebug(d10,31101);//7 " Sat=\"";
  writeDataFramDebug(d11,31108);//7 "\" Cap=\"";
  writeDataFramDebug(d12,31115);//16 "\" BatteryLevel=\"";
  writeDataFramDebug(d13,31131);//6 "\" Dh=\"";
  writeDataFramDebug(d14,31137);//3 "\"/>";
  writeDataFramDebug(d15,31140);//9 "AT+CFUN=1";
  writeDataFramDebug(d16,31149);//8 "AT+CPIN?";  
  writeDataFramDebug(d17,31157);//27  "AT+CSTT=\"iamgprs1.ma\",\"\",\"\"";
  writeDataFramDebug(d18,31184);//29 "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";
  writeDataFramDebug(d19,31213);//12 "AT+SAPBR=1,1";
  writeDataFramDebug(d19,31213);//12 "AT+SAPBR=1,1";
  writeDataFramDebug(d20,31225);//8 "AT+CIICR";
  writeDataFramDebug(d21,31233);//8 "AT+CIFSR";
  writeDataFramDebug(d22,31241);//13 "AT+HTTPTERM";
  writeDataFramDebug(d23,31254);//13 "AT+HTTPINIT";
  writeDataFramDebug(d24,31267);//19 "AT+HTTPPARA=\"CID\",1"  ;
  writeDataFramDebug(d25,31286);//67 "AT+HTTPPARA=\"URL\",\"http://casa-interface.casabaia.ma/commandes.php\"";
  writeDataFramDebug(d26,31353);//38 "AT+HTTPPARA=\"CONTENT\",\"application/xml";
  writeDataFramDebug(d27,31391);//14 "AT+HTTPDATA=";
  writeDataFramDebug(d28,31405);//69 "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Commandes idclient=\"76\" imei=\"";
  writeDataFramDebug(d29.c_str(),31474);//15 "869170031699599";
  writeDataFramDebug(d30,31489);//56 "\"><Commande id=\"2142\" Nom=\"ADD_TRACKING\"><Param><Tracks>"  ;
  writeDataFramDebug(d31,31545);//40 "</Tracks></Param></Commande></Commandes>";
  writeDataFramDebug(d32,31585);//14 "AT+HTTPACTION=" ;
  writeDataFramDebug(d33,31599);//10 "AT+CGATT=0";
  writeDataFramDebug(d34,31609);//73 "url VV";
  writeDataFramDebug(d35,31682);//39 "AT+HTTPPARA=\"CONTENT\",\"application/json";
  writeDataFramDebug(d36,31721);//9  "AT+CREG=1";
  writeDataFramDebug(d37,31730);//9  "AT+CFUN=0";
  
 

  for(long i=32010;i<32080;i++){
  writeDataFramDebug("0",i);}
  for(long i=32000;i<32003;i++){
  writeDataFramDebug("0",i);}
  
  while(1);

 
}
void loop() {

}

void powerKey(){
  int powerKeyCounter = 0;
  while (analogRead(A3) < 200) {
    powerKeyCounter++;
    pinMode(5, OUTPUT);//PWR KEY
    digitalWrite(5, LOW);
    delay(2000);
    pinMode(5, INPUT_PULLUP);
    delay(100);
  }
}
void writeDataFram(char* dataFram) {
  uint8_t dataFramSize = strlen(dataFram);
  for (unsigned long i = framWritePosition; i <= (dataFramSize + framWritePosition); i++)
  {
    fram.write8(i, dataFram[(i - framWritePosition)]);
  } framWritePosition += (dataFramSize) ;
}
void writeDataFramDebug(char* dataFram, long p1) {
  for (unsigned long i = p1; i <= (p1 + strlen(dataFram)); i++)
  {
    fram.write8(i, dataFram[(i - p1)]);
  }
}


String returnImei() {
  flushSim();
  ss.println("AT+GSN");
  String tempGSM = ss.readString();
  String imei1 = strstr(tempGSM.c_str(), "8");
  String imei2 = imei1.substring(0, 15);
  return imei2;
}
void flushSim(){
  uint16_t timeoutloop = 0;
  while (timeoutloop++ < 40) {
    while (ss.available()) {
      ss.read();
      timeoutloop = 0;  // If char was received reset the timer
    }
    delay(1);
  }
}
