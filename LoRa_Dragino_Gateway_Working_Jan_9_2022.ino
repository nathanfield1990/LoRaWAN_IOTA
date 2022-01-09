//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  2        /* Time ESP32 will go to sleep (in seconds) */

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//#define BAND 915E6
#define BAND 902.1E6

unsigned long new_time,old_time=0;
//int txPower = 3;
int txPower = 10;
// set sensor pin
int sensor = 0;
int val = 0;


int incomingByte = 0;

void setup() {
  //set pins
  pinMode(sensor, INPUT);
  //initialize Serial Monitor
  Serial.begin(115200);

  // Set LoRa tx power
  LoRa.setTxPower(txPower);
  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // Setup Spreading Factor (6 ~ 12)
  LoRa.setSpreadingFactor(7);

  // Setup BandWidth, option: 7800,10400,15600,20800,31250,41700,62500,125000,250000,500000
  //Lower BandWidth for longer distance.
  LoRa.setSignalBandwidth(125000);

  // Setup Coding Rate:5(4/5),6(4/6),7(4/7),8(4/8) 
  LoRa.setCodingRate4(5);
  LoRa.setSyncWord(0x34);    
  Serial.println("LoRa Initializing OK!");
  delay(2000);
}

void SendData()
{
     LoRa.beginPacket();
     //LoRa.print((char *)datasend);
     LoRa.print("<4567>");
     LoRa.print("Hello");
     LoRa.endPacket();
     Serial.println("Sent data");
}

void loop()
{
    /*if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
  }
  */
    new_time=millis();
    if (new_time - old_time >= 3000 || old_time == 0)
    {
      old_time = new_time;
      val = digitalRead(sensor);
      Serial.println("Current value is: " + String(val));
      //Serial.print(" ");
      if (val == 1){
        SendData();}
      }
      
    }
