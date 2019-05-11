//arduino side
#include <SoftwareSerial.h>
#include <SPI.h>
#include<ServoCds55.h>
ServoCds55 myservo;

//pilih sesuai dengan board yang dipakai
//SoftwareSerial s(10,11);//rx,tx ;untuk arduino mega
SoftwareSerial s(5,6); //rx, tx; untuk arduino uno
//deklarasi variabel dan pin
int data;
int angle;
int velocity;
char data2[6];
char data3[1];
int command;
int IN1 = 16;
int IN2 = 5;
int IN3 = 4;
int IN4 = 0;
int pin;

//memulai setup
void setup() 
{
//mulai koneksi s ke nodemcu dengan baud rate 115200
s.begin(115200);
Serial.begin(9600);
myservo.begin();
}

void maju(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  
}


void mundur(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void kiri(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void kanan(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stops(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
}
 
void loop() 
{
//data = command; 0 = maju, 1 = mundur, 2= kiri, 3 = kanan, 4 = stop, 5 = dynamixel 1
//6 = dyanmixel 2, 7 = dynamixel 3
  //listen ke port s dengan delay 2 second untuk menghindari error
  s.listen();
  delay(2);
  //memulai penerimaan pesan ASCII yang difragmentasi dari nodemcu
  int i =0;
   while(s.available()>0)
  {
    data2[i]=s.read();
    i++;
  //mengubah pesan ASCII menjadi bentuk integer  
   if(s.available()==0)
   {
   data = atoi(data2);
  //menerima topic dari pesan yang dikirim oleh nodemcu
   command = data%10;
  //menerima message dari pesan yang dikirim oleh nodemcu
   velocity = angle = floor(data/100);
   
   Serial.print("command : "); 
   Serial.println(command);
   Serial.print("angle : "); 
   Serial.println(angle);
  
   if(command==0){
    
    }
    else if(command = 0){maju();analogWrite(pin, velocity);}
    else if(command = 1){mundur();analogWrite(pin, velocity);}
    else if(command = 2){kiri();analogWrite(pin, velocity);}
    else if(command = 3){kanan();analogWrite(pin, velocity);}
    else if(command = 4){stops();}
    else if(command = 5){myservo.write(1, angle);}
    else if(command = 6){myservo.write(2, angle);}
    else if(command = 7){myservo.write(3, angle);}
  //menghapus memori yang digunakan di data dan di array saat menerima pesan
  data=0;
  for(int i = 0;i<6;i++)
    {
    data2[i]=0;
    }
   }
  }
}
