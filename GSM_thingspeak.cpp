#include "GSM_thingspeak.hpp"

SoftwareSerial SIM800(2,3);

void GSM_Thingspeak::Init(){
  SIM800.begin(9600);
}

void GSM_Thingspeak::connect_to_server(){
  SIM800.println("AT");
  delay(200);

  SIM800.println("AT+CPIN?");
  delay(200);

  SIM800.println("AT+CREG?");
  delay(200);

  SIM800.println("AT+CGATT?");
  delay(200);

  SIM800.println("AT+CIPSHUT");
  delay(200);

  SIM800.println("AT+CIPSTATUS");
  delay(1000);

  SIM800.println("AT+CIPMUX=0");
  delay(1000);

  ShowSerialData();

  SIM800.println("AT+CSTT=\"i\"");//start task and setting the APN,
  delay(200);

  ShowSerialData();
   
  SIM800.println("AT+CIICR");//bring up wireless connection
  delay(2000);

  ShowSerialData();

  SIM800.println("AT+CIFSR");//get local IP adress
  delay(2000);

  ShowSerialData();

  SIM800.println("AT+CIPSPRT=0");
  delay(1000);

  ShowSerialData();

  SIM800.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(2000);

  ShowSerialData();

  SIM800.println("AT+CIPSEND");//begin send data to remote server
  delay(2000);
  ShowSerialData();
}

void GSM_Thingspeak::Field1(int data){
   String str = "GET http://api.thingspeak.com/update?api_key=xxxxxxxxxxxxx&field1=" + String (data);
  SIM800.println(str);//begin send data to remote server

  delay(2000);
  ShowSerialData();
  SIM800.println((char)26);//sending
  delay(4000);//waitting for reply, important! the time is base on the condition of internet
  SIM800.println();

  ShowSerialData();
}

void GSM_Thingspeak::end_connection(){
   SIM800.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}
void GSM_Thingspeak::ShowSerialData(){
  while(SIM800.available()!=0)
    Serial.write(SIM800.read());
}
