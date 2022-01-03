#include<stdio.h>
#include <stdlib.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include <Servo.h>
#include <Wire.h>

String data, pin, id, tt, tag;
int PIN;
int count = 0;
char c;
String id_list[]={"ABC12345","BAC12345","CAB12345", "AAA12345"};
LiquidCrystal_I2C lcd(0x27,16,2);
Servo lock_sl_1;Servo lock_sl_2;Servo lock_sl_3;Servo lock_sl_4;
File fileData; //khai bao file

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);Serial1.begin(9600);Serial2.begin(9600);Serial3.begin(9600);
  //led canh bao
  pinMode(2, OUTPUT);pinMode(3, OUTPUT);pinMode(4, OUTPUT);pinMode(5, OUTPUT);
  //hiển thị lên vitual terminal
  Serial.println("SLOT PIN 1");
  Serial1.println("SLOT PIN 2");
  Serial2.println("SLOT PIN 3");
  Serial3.println("SLOT PIN 4");
  //khoa dang dong
  lock_sl_1.attach(9);lock_sl_1.write(0);
  lock_sl_2.attach(8);lock_sl_2.write(0);
  lock_sl_3.attach(7);lock_sl_3.write(0);
  lock_sl_4.attach(6);lock_sl_4.write(0);
  pinMode(53, OUTPUT);
  SD.begin(53);
  fileData=SD.open("slot_1.txt",FILE_WRITE);  
  fileData.println("ABC12345|50|1");
  fileData.close();
  fileData=SD.open("slot_2.txt",FILE_WRITE);  
  fileData.println("BAC12345|70|1");
  fileData.close();
  fileData=SD.open("slot_3.txt",FILE_WRITE);  
  fileData.println("CAB12345|90|1");
  fileData.close();
  fileData=SD.open("slot_4.txt",FILE_WRITE);  
  fileData.println("AAA12345|20|1");
  fileData.close();
}


void loop(){
  // SLOT 1
  if(Serial.available()>0){  
    digitalWrite(5, HIGH);
    lock_sl_1.write(90);
    delay(2000);
    lock_sl_1.write(0);
    
    while(Serial.available()>0){
      fileData=SD.open("slot_1.txt");
      read_file();
      fileData.close();
         
      c = Serial.read();
      count++;
      tag += c;
      if(count == 8){
        for (int i = 0 ; i < 5 ; i++){
          String t =id_list[i];
          if(tag == t){
            Serial.println(id);
            Serial.println("   Valid TAG ");
            Serial.print("ID PIN:");Serial.println(id);
            Serial.print("PIN(%):");Serial.println(pin);
            Serial.print("ID PIN:");Serial.println(tt);
            lcd.setCursor(0, 0);lcd.print("ID:");
            lcd.setCursor(3, 0);lcd.print(id);
            lcd.setCursor(0, 1);lcd.print("Valid PIN"); 
            delay(5000);
            digitalWrite(5, LOW);
            lcd.clear();
            if (PIN < 80){
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(PIN);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(3000);
              lcd.setCursor(0, 1);lcd.print("  SWAP PIN!");
              delay(1000);
              digitalWrite(4, HIGH);
              lock_sl_2.write(90);
              delay(2000);
              digitalWrite(4, LOW); 
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !");
            }
            else{
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(PIN);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(1000);
              lcd.setCursor(0, 1);lcd.print("  RETURN PIN!");
              digitalWrite(5, HIGH);
              lock_sl_1.write(90);
              delay(2000);
              digitalWrite(5, LOW); 
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !");
            }
          break;
          }
          else{
          if(i==4){
            Serial.println("   Invalid TAG ");
            lcd.setCursor(0, 0);lcd.print("ID:");
            lcd.setCursor(3, 0);lcd.print(id);
            lcd.setCursor(0, 1);lcd.print("Invalid PIN");
            digitalWrite(5, HIGH);
            lock_sl_1.write(90);
            delay(2000);
            digitalWrite(5, LOW);
            break;
          }
          else continue;
          }       
        }
      }
    }
  }
 // SLOT 2
  else if(Serial1.available()>0){
    digitalWrite(4, HIGH);
    lock_sl_2.write(90);
    delay(2000);
    lock_sl_2.write(0);
    
    while(Serial1.available()>0){      
      fileData=SD.open("slot_2.txt");
      read_file();
      fileData.close();
      
      c = Serial1.read();
      count++;
      tag += c;
      if(count == 6)  {
        for (int i = 0 ; i < 5 ; i++){
          String t =id_list[i];
          if(tag == t){
            Serial1.println(id);
            Serial1.println("   Valid TAG ");
            Serial1.print("ID PIN:");Serial1.println(id);
            Serial1.print("PIN(%):");Serial1.println(pin);
            Serial1.print("ID PIN:");Serial1.println(tt);
            lcd.setCursor(0, 0);lcd.print("ID:");
            lcd.setCursor(3, 0);lcd.print(id);
            lcd.setCursor(0, 1);lcd.print("Valid PIN");
            // hiển thị thông tin khác 
            delay(5000);
            digitalWrite(4, LOW);
            lcd.clear();
            
            if (PIN < 80){      
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(pin);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(3000);
              lcd.setCursor(0, 1);lcd.print("  SWAP PIN!");
              delay(1000);
              digitalWrite(3, HIGH);
              lock_sl_3.write(90);
              delay(2000);
              digitalWrite(3, LOW);
              
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !"); 
            }
            else{
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(pin);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(1000);
              lcd.setCursor(0, 1);lcd.print("  RETURN PIN!");
              digitalWrite(4, HIGH);
              lock_sl_2.write(90);
              delay(2000);
              digitalWrite(4, LOW);
              
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !");
            }
            break;
          }
          else{
            if(i==5){
              Serial1.println("   Invalid TAG ");
              lcd.setCursor(0, 0);lcd.print("ID:");
              lcd.setCursor(3, 0);lcd.print(id);
              lcd.setCursor(0, 1);lcd.print("Invalid PIN");
              digitalWrite(4, HIGH);
              lock_sl_2.write(90);
              delay(2000);
              digitalWrite(4, LOW);
              break;
            }
            else continue;
          }
        }
      }
    };
  } 
  // SLOT 3 
  else if(Serial2.available()>0){
    digitalWrite(3, HIGH);
    lock_sl_3.write(90);
    delay(2000);
    lock_sl_3.write(0);
    
    while(Serial2.available()>0){      
      fileData=SD.open("slot_3.txt");
      read_file();
      fileData.close();
      
      c = Serial2.read();
      count++;
      tag += c;
      if(count == 6)  {
        for (int i = 0 ; i < 5 ; i++){
          String t =id_list[i];
          if(tag == t){
            Serial2.println(id);
            Serial2.println("   Valid TAG ");
            Serial2.print("ID PIN:");Serial2.println(id);
            Serial2.print("PIN(%):");Serial2.println(pin);
            Serial2.print("ID PIN:");Serial2.println(tt);
            lcd.setCursor(0, 0);lcd.print("ID:");
            lcd.setCursor(3, 0);lcd.print(id);
            lcd.setCursor(0, 1);lcd.print("Valid PIN");
            // hiển thị thông tin khác 
            delay(5000);
            digitalWrite(3, LOW);
            lcd.clear();
           
            if (PIN < 80){      
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(pin);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(3000);
              lcd.setCursor(0, 1);lcd.print("  SWAP PIN!");
              delay(1000);
              digitalWrite(2, HIGH);
              lock_sl_4.write(90);
              delay(2000);
              digitalWrite(2, LOW);
              
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !"); 
            }
            else{
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(pin);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(1000);
              lcd.setCursor(0, 1);lcd.print("  RETURN PIN!");
              digitalWrite(3, HIGH);
              lock_sl_3.write(90);
              delay(2000);
              digitalWrite(3, LOW);
              
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !");
            }
            break;
          }
          else{
            if(i==5){
              Serial2.println("   Invalid TAG ");
              lcd.setCursor(0, 0);lcd.print("ID:");
              lcd.setCursor(3, 0);lcd.print(id);
              lcd.setCursor(0, 1);lcd.print("Invalid PIN");
              digitalWrite(3, HIGH);
              lock_sl_3.write(90);
              delay(2000);
              digitalWrite(3, LOW);
              break;
            }
            else continue;
          }
        }
      }
    };
  }
  // SLOT 4
  else if(Serial3.available()>0){
    digitalWrite(2, HIGH);
    lock_sl_4.write(90);
    delay(2000);
    lock_sl_4.write(0);
    
    while(Serial3.available()>0){      
      fileData=SD.open("slot_4.txt");
      read_file();
      fileData.close();
      
      c = Serial3.read();
      count++;
      tag += c;
      if(count == 6)  {
        for (int i = 0 ; i < 5 ; i++){
          String t =id_list[i];
          if(tag == t){
            Serial3.println(id);
            Serial3.println("   Valid TAG ");
            Serial3.print("ID PIN:");Serial3.println(id);
            Serial3.print("PIN(%):");Serial3.println(pin);
            Serial3.print("ID PIN:");Serial3.println(tt);
            //hiển thi thông tin ID
            lcd.setCursor(0, 0);lcd.print("ID:");
            lcd.setCursor(3, 0);lcd.print(id);
            lcd.setCursor(0, 1);lcd.print("Valid PIN");
            // hiển thị thông tin khác 
            delay(5000);
            digitalWrite(2, LOW);
            lcd.clear();
           
            if (PIN < 80){      
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(pin);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(3000);
              lcd.setCursor(0, 1);lcd.print("  SWAP PIN!");
              delay(1000);
              digitalWrite(5, HIGH);
              lock_sl_1.write(90);
              delay(2000);
              digitalWrite(5, LOW);
              
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !"); 
            }
            else{
              lcd.setCursor(0, 0);lcd.print("Pin:");
              lcd.setCursor(4, 0);lcd.print(pin);
              lcd.setCursor(7, 0);lcd.print("%");
              delay(1000);
              lcd.setCursor(0, 1);lcd.print("  RETURN PIN!");
              digitalWrite(2, HIGH);
              lock_sl_4.write(90);
              delay(2000);
              digitalWrite(2, LOW);
              
              delay(2000);
              lcd.clear();
              lcd.setCursor(0, 1);lcd.print("  THANK YOU !");
            }
            break;
          }
          else{
            if(i==5){
              Serial3.println("   Invalid TAG ");
              lcd.setCursor(0, 0);lcd.print("ID:");
              lcd.setCursor(3, 0);lcd.print(id);
              lcd.setCursor(0, 1);lcd.print("Invalid PIN");
              digitalWrite(2, HIGH);
              lock_sl_4.write(90);
              delay(2000);
              digitalWrite(2, LOW);
              break;
            }
            else continue;
          }
        }
      }
    };
  }
  count = 0;
  id="";
  delay(500);
}
void read_file(){
  while(fileData.available()>0){
    char a = fileData.read();
    data +=a;
  }
  int len = data.length();
  if(len>0){
    id = data.substring(0,8);
    pin = data.substring(9,11);
    tt = data.substring(12,13);
    PIN =  pin.toInt(); 
  }
  return id,pin,tt;
}
