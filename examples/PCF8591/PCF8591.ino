#include <Adafruit_PCF8591.h>

Adafruit_PCF8591 pcf = Adafruit_PCF8591();

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("# Adafruit PCF8591 demo");
  if (! pcf.begin()) {
    Serial.println("# Adafruit PCF8591 not found!");
    while (1) delay(10);
  }
  Serial.println("# Adafruit PCF8591 found");
  pcf.enableDAC(true);

  Serial.println("AIN0, AIN1, AIN2, AIN3");
}

uint8_t dac_counter = 0;

void loop() {
  // Make a triangle wave on the DAC output
  pcf.analogWrite(dac_counter++);

  // Read the 4 inputs
  Serial.print(pcf.analogRead(0));
  Serial.print(", ");
  Serial.print(pcf.analogRead(1));
  Serial.print(", ");
  Serial.print(pcf.analogRead(2));
  Serial.print(", ");
  Serial.print(pcf.analogRead(3));
  Serial.println();
  delay(100);
}
