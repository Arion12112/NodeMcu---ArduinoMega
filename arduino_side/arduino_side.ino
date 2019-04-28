//arduino side
#include <SoftwareSerial.h>
SoftwareSerial s(10,11);//rx,tx
SoftwareSerial s2(12,13);
String content;
int data;
int data2;
void setup() {
s.begin(115200);
s2.begin(115200);
Serial.begin(9600);
}
 
void loop() {
//data = command; 1 = maju, 2 = mundur, 3= kiri, 4 = kanan, 5 = stop

  s.listen();
  delay(2);
   if(s.available()>0)
  {
    data=s.read();
    Serial.println(data);
  }
  s2.listen();
  delay(2);
  if(s2.available()>0)
  {
    data2=s2.read();
    Serial.println(data2);
  }
  

 
}
