#include "DFRobot_BME280.h"
#include "Wire.h"

// Initialize the BME280 sensor using the I2C interface
DFRobot_BME280_IIC bme(&Wire, 0x77); // Change 0x77 to 0x76 if needed

void setup() {
  Serial.begin(115200);
  Serial.println("BME280 Sensor initialization...");

  // Attempt to initialize the BME280 sensor
  if (bme.begin() != DFRobot_BME280_IIC::eStatusOK) {
    Serial.println("Failed to initialize the BME280 sensor! Check wiring.");
    while (1); // Stop execution if the sensor cannot be initialized
  }
  Serial.println("BME280 Sensor initialized successfully.");
}

void loop() {
  // Read temperature and humidity from the BME280 sensor
  float temperature = bme.getTemperature();
  float humidity = bme.getHumidity();

  // Print the temperature and humidity readings to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Wait for one second before the next read
  delay(1000);
}

