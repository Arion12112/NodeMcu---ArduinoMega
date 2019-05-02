//arduino side
#include <SoftwareSerial.h>


SoftwareSerial s(10,11);//rx,tx
//SoftwareSerial s2(12,13);
int data;
int velocity;
char data2[6];
char data3[1];
int command;
void setup() {
s.begin(115200);
//s2.begin(115200);
Serial.begin(9600);
}
 
void loop() {
//data = command; 1 = maju, 2 = mundur, 3= kiri, 4 = kanan, 5 = stop

  s.listen();
  delay(2);
  int i =0;
   while(s.available()>0)
  {
    data2[i]=s.read();
    i++;
    
    if(s.available()==0){
   data = atoi(data2);
   command = data%10;
   
   Serial.println(data);
   data=0;
  for(int i = 0;i<6;i++){
    data2[i]=0;
    }
      }

  }
}
