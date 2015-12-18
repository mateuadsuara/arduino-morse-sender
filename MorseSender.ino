#include <morse.h>

#define MORSE_PIN 13
LEDMorseSender sender(MORSE_PIN);

void setup() {
    Serial.begin(9600);
  
    sender.setup();
}

String readBuffer = "";
String readReturn = "";
String* readUntil(char delimiter) {
  int available = Serial.available();
  
  while (available > 0) {
    char c = Serial.read();
    available--;
    
    if (c == delimiter) {
      readReturn = readBuffer;
      readBuffer = "";
      return &readReturn;
    } else {
      readBuffer += c;
    }
  }
  return NULL;
}

void loop() {
    String* line = readUntil(';');
    if (line) {
      Serial.println("Sending as morse: " + *line);
      sender.setMessage(*line);
      sender.startSending();
    }
  
    sender.continueSending();
}
