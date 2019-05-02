//arduino side
#include <SoftwareSerial.h>

//pilih sesuai dengan board yang dipakai
//SoftwareSerial s(10,11);//rx,tx ;untuk arduino mega
SoftwareSerial s(5,6); //rx, tx; untuk arduino uno
//deklarasi variabel
int data;
int velocity;
char data2[6];
char data3[1];
int command;

//memulai setup
void setup() 
{
//mulai koneksi s ke nodemcu dengan baud rate 115200
s.begin(115200);
Serial.begin(9600);
}
 
void loop() 
{
//data = command; 1 = maju, 2 = mundur, 3= kiri, 4 = kanan, 5 = stop
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
   velocity = floor(data/100); 
   Serial.print("command : "); 
   Serial.println(command);
   Serial.print("velocity : "); 
   Serial.println(velocity);
  //meghapus memori yang digunakan di data dan di array saat menerima pesan
  data=0;
  for(int i = 0;i<6;i++)
    {
    data2[i]=0;
    }
   }
  }
}
