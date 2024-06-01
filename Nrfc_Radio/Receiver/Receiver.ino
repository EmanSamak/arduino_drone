#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
char receivedData[32] = "";
int xAxis, yAxis;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) { // If the NRF24L01 module received data
    radio.read(&receivedData, sizeof(receivedData)); // Read the data and put it into character array
    xAxis = atoi(&receivedData[0]); // Convert the data from the character array to integer (X value)
    Serial.print("X: ");
    Serial.print(xAxis);
    
    radio.read(&receivedData, sizeof(receivedData)); // Read the next set of data
    yAxis = atoi(&receivedData[0]); // Convert the data from the character array to integer (Y value)
    Serial.print("\tY: ");
    Serial.println(yAxis);
    
    delay(20);
  }
}

 
