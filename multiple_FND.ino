#include "FndDisplay.h"
static uint8_t fndPin[]={23,22,21,19,17,16,18,5};
FndDisplay fnd1(fndPin[0],fndPin[1]);
FndDisplay fnd2(fndPin[2],fndPin[3]);
FndDisplay fnd3(fndPin[4],fndPin[5]);
FndDisplay fnd4(fndPin[6],fndPin[7]);
long n=0,n2=9999,n3=1;
void setup() {
  
}

void loop() {
  fnd1.writeNumber(n);
  fnd2.writeNumber(n2);
  fnd3.writeNumber(n3);
  fnd4.writeNumber(n);
  delay(100);
  n++;
  n2--;
  n3*=2;
  if(n>9999)n=0;
  if(n2<0)n2=9999;
  if(n3>9999)n3=1;
}
