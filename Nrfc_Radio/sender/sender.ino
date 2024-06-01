#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(1, 4); // CE, CSN
const byte address[6] = "00001";
char xyData[32] = "";
String xAxis, yAxis;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  xAxis = String(analogRead(A5)); // Read Joysticks X-axis and convert to String
  yAxis = String(analogRead(A7)); // Read Joysticks Y-axis and convert to String
  
  // X value
  xAxis.toCharArray(xyData, 5); // Put the String (X Value) into a character array
  radio.write(&xyData, sizeof(xyData)); // Send the array data (X value)
  
  // Y value
  yAxis.toCharArray(xyData, 5); // Put the String (Y Value) into a character array
  radio.write(&xyData, sizeof(xyData)); // Send the array data (Y value)
  
  Serial.print("X: ");
  Serial.print(xAxis);
  Serial.print("\tY: ");
  Serial.println(yAxis);
  
  delay(20);
}

