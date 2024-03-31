
#include <DFRobot_SHT3x.h>

DFRobot_SHT3x sht3x;
void setup() {
Serial.begin(9600);
//Initialize the chip
while (sht3x.begin() != 0) {
Serial.println("Failed to Initialize the chip, please confirm the wire connection");
delay(1000);
}

Serial.print("Chip serial number");
Serial.println(sht3x.readSerialNumber());

if(!sht3x.softReset()){
Serial.println("Failed to Initialize the chip....");
}


Serial.println("------------------Read adta in single measurement mode-----------------------");
}
void loop() {
  float temperature = sht3x.getTemperatureC();
  float humidity = sht3x.getHumidityRH();

  // Send the temperature and humidity data as a comma-separated string
  Serial.print("T:");
  Serial.print(temperature);
  Serial.print(",H:");
  Serial.println(humidity);

  delay(1000); // Delay for a second before reading again
}
