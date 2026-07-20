#include <HardwareBLESerial.h>

HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();

char packet[6];
int packetIndex = 0;

void ledOff() {
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void setRed() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void setGreen() {
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
}

void setBlue() {
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
}

void setYellow() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
}

void setup() {
  Serial.begin(9600);

  while (!bleSerial.beginAndSetupBLE("SF55"));

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  ledOff();

  Serial.println("Ready");
}

void loop() {

  bleSerial.poll();

  while (bleSerial.available()) {

    char c = bleSerial.read();

    packet[packetIndex++] = c;

    if (packetIndex == 5) {

      packet[5] = '\0';

      Serial.print("Packet: ");
      Serial.println(packet);

      char button = packet[2];
      char state  = packet[3];

      if (state == '1') {

        switch (button) {

          case '5':
            setRed();
            break;

          case '6':
            setBlue();
            break;

          case '7':
            setGreen();
            break;

          case '8':
            setYellow();
            break;

          case '1':
            ledOff();
            break;
        }
      }

      packetIndex = 0;
    }
  }
}