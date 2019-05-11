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
int command;
int IN1 = 16;
int IN2 = 5;
int IN3 = 4;
int IN4 = 0;
int pin;
int servoNum = 12;
char inputCommand ;         // a string to hold incoming data
boolean inputComplete = false;

//memulai setup
void setup() 
{
//mulai koneksi s ke nodemcu dengan baud rate 115200
s.begin(115200);
Serial.begin(115200);
myservo.begin();
myservo.setVelocity(150);
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
   }
  }
servoCommand();
 serialEvent();
if (inputComplete) {
Serial.print("Your command is: "); Serial.println(inputCommand); Serial.println("");
    controlServo(inputCommand);
     //clear the command:
    inputCommand = 0;
   inputComplete = false;
  }

  //menghapus memori yang digunakan di data dan di array saat menerima pesan
  data=0;
  for(int i = 0;i<6;i++)
    {
    data2[i]=0;
    }
  
}

void servoCommand(){
  if(command == 0){maju();analogWrite(pin, velocity);}
    else if(command == 1){mundur();analogWrite(pin, velocity);}
    else if(command == 2){kiri();analogWrite(pin, velocity);}
    else if(command == 3){kanan();analogWrite(pin, velocity);}
    else if(command == 4){stops();}
    else if(command == 5){myservo.write(10, angle);}
    else if(command == 6){myservo.write(11, angle);}
    else if(command == 7){myservo.write(12, angle);}
  }

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      inputComplete = true;
      break;
    }
    inputCommand += inChar;
  }
}

void controlServo(char val) {
  
  
  switch (val) {
    case 'p':
      myservo.write(254, 300);
      myservo.write(52, 300);
      myservo.write(23, 300);
      myservo.write(10, angle);
     /* for (int servoNum = 240; servoNum < 255; servoNum++) {
        myservo.write( servoNum, 300);
       Serial.println(servoNum);
       delay(300);
      }
      */
      Serial.print("Servo 300 : ");
      Serial.println(servoNum);
     //ID:1  Pos:300  velocity:150
      delay(3000);
      myservo.write(254, 0);
       myservo.write(52, 0);
       myservo.write(23, 0);
        myservo.write(10, 0);
    /*  for (int servoNum = 240; servoNum < 255; servoNum++) {
        myservo.write( servoNum, 0);
       Serial.println(servoNum);
       delay(300);
      } */
      delay(3000);
      Serial.println("ok");
      //ID:1  Pos:0  velocity:150
      break;
    case 'v':
      myservo.setVelocity(100);// set velocity to 100(range:0-300) in Servo mode
      break;
    case 'm':
      myservo.rotate(servoNum, 150); //   Anti CW    ID:1  Velocity: 150_middle velocity  300_max
      delay(2000);
      myservo.rotate(servoNum, -150); //  CW     ID:1  Velocity: -150_middle velocity  -300_max
      delay(2000);
      myservo.rotate(servoNum, 0); //Stop
      myservo.Reset(servoNum);    //Only Dynamixel AX need this instruction while changing working mode
      //CDS55xx don't need this, it can switch freely between its working mode
      break;
    case 'r':
      myservo.Reset(servoNum);//Restore ID2 servo to factory Settings ( ID:1  Baud rate:1000000)
      break;
    case 'i':
            myservo.SetID(50,10);//ID:1   newID:2
    //        break;
    case 'd':  //Reset servo to ID>>servoNum. If you don't know your Servo ID, please send "d".
      Serial.print("Please wait..");
      for (int buf = 0; buf < 255; buf++) {
        myservo.SetID( buf, servoNum);
        if (buf % 50 == 0) Serial.print(".");
      }
      delay(2000);
      Serial.println("");   Serial.println("Please close the monitor and re-open it to play your servo! ");
      break;
    default:
      Serial.println("Please give me an available instruction:");
      Serial.println("  Servo mode: p_Set position; v_Set velocity.");
      Serial.println("  Motor mode: m_Rotate; v_Set velocity.");
      Serial.println("  Others: r_Reset servo to factory settings; i_Change servo ID."); Serial.println("");
  }
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
