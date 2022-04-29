#include <WiFi.h>
#include <WiFiUdp.h>
#include "FndDisplay.h"

const char* ssid     = "MESH";
const char* password = "mesh2704";

const char * udpAddress = "192.168.0.87";
const int udpPort = 44444;
WiFiUDP udp;

static uint8_t fndClkPin[] = {23,21,17,18 };
static uint8_t fndDioPin[] = {22,19, 16, 5};
FndDisplay fnd1(fndClkPin[0], fndDioPin[0]);
FndDisplay fnd2(fndClkPin[1], fndDioPin[1]);
FndDisplay fnd3(fndClkPin[2], fndDioPin[2]);
FndDisplay fnd4(fndClkPin[3], fndDioPin[3]);
long n = 0, n2 = 9999, n3 = 1, n4 = 0;
#define T 12
#define T2 14
#define LED 4
#define LED2 0
#define H1 26
#define H2 25
long cmils = 0, pmils = 0, pmils2 = 0, pmils3 = 0,udpmils=0;
char buf[1024]="";
void setup() {
  pinMode(T, INPUT_PULLUP);
  pinMode(T2, INPUT_PULLUP);
  
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(H1,INPUT_PULLUP);
  pinMode(H2,INPUT_PULLUP);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("UDP start");
  udp.begin(udpPort);
}

void loop() {
  cmils = millis();
  if (cmils - pmils > 1000) {
    fnd1.writeNumber(n);
    fnd2.writeNumber(n2);

    n++;
    n2--;

    if (n > 9999)n = 0;
    if (n2 < 0)n2 = 9999;

    pmils = cmils;
  }
  if (cmils - pmils2 > 100) {
    fnd4.writeNumber(n4);
    n4++;
    if (n4 > 9999)n4 = 0;
    pmils2 = cmils;
  }
  if (cmils - pmils3 > 500) {
    fnd3.writeNumber(n3);
    n3 += 2;
    if (n3 > 9999)n3 = 0;
  }
 
  int sig = digitalRead(T);
  digitalWrite(LED, sig);
  int sig2 = digitalRead(T2);
  digitalWrite(LED2, !sig2);
  int Hsig1=digitalRead(H1);
  int Hsig2=digitalRead(H2);
  Serial.println(String(Hsig1)+" "+String(Hsig2));
  if(cmils-udpmils>1){
  String k=String(Hsig1)+" "+String(Hsig2);
  //char   strcpy (buf, k.c_str);
  //buf[1024] =(char)k.c_str();
  for(int i=0;i<k.length();i++){
    buf[i]=k[i];
  }
  //udp.beginPacket(udpAddress, udpPort);
  //udp.write((uint8_t *)buf, strlen(buf));
  //udp.endPacket();
  udpmils=cmils;
  
  }
}
