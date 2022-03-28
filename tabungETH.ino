#include <Wire.h>
#include "print.h"
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Ethernet.h>


const int triggerPin = 4;
const int echoPin  = 6;

int jarak;
int volume;
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte mac[] = { 0x40, 0x9F, 0x38, 0x13, 0xBB, 0xEF};
IPAddress server(10,19,3,199);//   alamat IP  komputer yg terinstall webserver  + mysql

IPAddress ip(10,19,3,201);
EthernetClient client;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println();
  Serial.print(" Connect to : ");
 
  if (Ethernet.begin(mac) == 0) 
  {Ethernet.begin(mac, ip);
  // Client melakukan request koneksi ke server dengan IP Adreess dan port yg didefinisikan
  client.connect(server, 7000);}
  delay(1000);
  Serial.println("connecting…");
} 
 
void loop() {
 float duration, jarak, jarak1, panjang, jarijari, panjangAB, garisYB,garisYX,garisYK,garisYZ, nn, as, amn, au, lingkaran, juring, segitiga, tembereng, volum, panjangAB1, garisYB1,garisYX1,garisYK1,garisYZ1, nn1, as1, amn1, au1, lingkaran1, juring1, segitiga1, tembereng1, volum1, tangkipenuh, volume;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  panjang = 290;
  jarijari = 62.5;
  jarak1 =  ((duration/58.2) + 1.7);
  jarak = 125 - jarak1;

  panjangAB = jarijari - jarak;       // rumus untuk tinggi air dibawah 1/2 ukuran tabung
  garisYZ = (pow(jarijari,2)); 
  garisYX = (pow(panjangAB,2));
  garisYK = garisYZ - garisYX;
  garisYB = pow(garisYK, 0.5);
  nn = garisYB * 2;
  as = (2 * (pow(jarijari,2)) - (pow(nn, 2)))/(2 * (pow(jarijari, 2))); 
  amn = acos(as);
  au = amn * 180 / (3.1415);
  lingkaran = (3.1415) * jarijari * jarijari;
  juring = (au / 360) * lingkaran;
  segitiga = (nn * panjangAB)/2;
  tembereng = (juring - segitiga);
  volum = (tembereng * panjang)/ 1000;
 
  
  panjangAB1 = jarijari - jarak1;       // rumus untuk tinggi air 1/2 ke atas tabung
  garisYZ1 = (pow(jarijari,2)); 
  garisYX1 = (pow(panjangAB1,2));
  garisYK1 = garisYZ1 - garisYX1;
  garisYB1 = pow(garisYK1, 0.5);
  nn1 = garisYB1 * 2;
  as1 = (2 * (pow(jarijari,2)) - (pow(nn1, 2)))/(2 * (pow(jarijari, 2))); 
  amn1 = acos(as1);
  au1 = amn1 * 180 / (3.1415);
  lingkaran1 = (3.1415) * jarijari * jarijari;
  juring1 = (au1 / 360) * lingkaran1;
  segitiga1 = (nn1 * panjangAB1)/2;
  tembereng1 = (juring1 - segitiga1);
  volum1 = (tembereng1 * panjang)/ 1000;
  tangkipenuh = 3.1415 * jarijari * jarijari * panjang / 1000;
  volume = tangkipenuh - volum1;

  if (jarak < 66)
  {
  lcd.setCursor(0,0);
  lcd.print("Minyak: ");
  lcd.print(jarak);
  lcd.print(" cm");
  lcd.setCursor(0,1);
  lcd.print("V1: ");
  lcd.print(volum);
  lcd.print(" L");
  delay(5000);
  lcd.clear();
  
    if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /jarak.php?Jarak=");
    client.print("GET /jarak.php?Jarak=");     //YOUR URL
    Serial.println(jarak,2);
    client.print(jarak,2);
    client.print("&volume=");
    Serial.println("&volume=");
    Serial.println(volum,1);
    client.print(volum,1);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:192,168,56,1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  if (client.available())
  {
  char c = client.read();
  Serial.print(c);
  }

// if the server’s disconnected, stop the client:
  if (!client.connected())
  {
  Serial.println();
  Serial.println("disconnecting.");
  client.stop();

// do nothing forevermore:
   while (true);
}
  delay(5000);
  }
 
  
  else if (65 <jarak < 130) 
  {
  lcd.setCursor(0,0);
  lcd.print("Minyak: ");
  lcd.print(jarak);
  lcd.print(" cm");  
  lcd.setCursor(0,1);
  lcd.print("V2 : ");
  lcd.print(volume);
  lcd.print(" L");

    if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /jarak.php?Jarak=");
    client.print("GET /jarak.php?Jarak=");     //YOUR URL
    Serial.println(jarak,2);
    client.print(jarak,2);
    client.print("&volume=");
    Serial.println("&volume=");
    Serial.println(volume,1);
    client.print(volume,1);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:192,168,56,1");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  if (client.available())
  {
  char c = client.read();
  Serial.print(c);
  }

// if the server’s disconnected, stop the client:
  if (!client.connected())
  {
  Serial.println();
  Serial.println("disconnecting.");
  client.stop();

// do nothing forevermore:
   while (true);
}
  delay(5000);
  
  }

  
  else{
  lcd.setCursor(0,0);
  lcd.print("air penuh");
    if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /jarak.php?Jarak=");
    client.print("GET /jarak.php?Jarak=");     //YOUR URL
    Serial.println(jarak,2);
    client.print(jarak,2);
    client.print("&volume=");
    Serial.println("&volume=");
    Serial.println(volume,1);
    client.print(volume,1);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:192,168,56,1");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 if (client.available())
  {
  char c = client.read();
  Serial.print(c);
  }

// if the server’s disconnected, stop the client:
  if (!client.connected())
  {
  Serial.println();
  Serial.println("disconnecting.");
  client.stop();

// do nothing forevermore:
   while (true);
}
  delay(5000);
    }
 
  delay(5000);
  lcd.clear();

}

void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   
 }
