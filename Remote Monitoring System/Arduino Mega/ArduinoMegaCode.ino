#include <DFRobot_MLX90614.h>
#include <DFRobot_SHT3x.h>

DFRobot_MLX90614_I2C sensor;   // Instantiate an object to drive the temperature sensor 
DFRobot_SHT3x sht3x;      // Instantiate an object to drive the humidity sensor 


// defines pins of motors
#define stepPinX 2
#define dirPinX 3 
#define enPinX 4
#define stepPinY 22
#define dirPinY 23
#define enPinY 24

bool shouldStart = false;
int zone=0;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  // Sets the two pins of motors
  pinMode(stepPinX,OUTPUT); 
  pinMode(dirPinX,OUTPUT);
  pinMode(stepPinY,OUTPUT); 
  pinMode(dirPinY,OUTPUT);
  pinMode(enPinX,OUTPUT); 
  pinMode(enPinY,OUTPUT);
  digitalWrite(enPinX,HIGH); 
  digitalWrite(enPinY,HIGH); 

  // Sensor initialization
  sensor.begin();
  sht3x.begin();
  delay(5000);

}


void loop() {

  if (Serial1.available() > 0) {
    String command = Serial1.readStringUntil('\n');
    command.trim(); // Add this line
    Serial.println(command);
    if (command == "START") {

      //Measure Zone A1-B1
      for (int n=0; n<4; n++){
        measureTempHumidityAverage();
        moveXForward();
        delay(20000);
      }

      measureTempHumidityAverage();

      //Move to the next line
      moveYForward();
      delay(20000);


      //Measure the Zone B2-A2 
      for (int m=0; m<4; m++){
        measureTempHumidityAverage();
        moveXBackward();
        delay(20000);
      }

      measureTempHumidityAverage();

      //Return to the initial position
      moveYBackward();
      
      zone=0;
    }
  }

}



void measureTempHumidityAverage() {
  float tempSum = 0;
  float humiditySum = 0;
  int readings = 20;

  for (int i = 0; i < readings; ++i) {
    //Get the surface temperature
    // Get object temperature in Celsius, range varies by sensor model
    // For MLX90614ESF-DCI: -70.01 °C to 270 °C
    // For MLX90614ESF-DCC: -70.01 °C to 380 °C
    float objectTemp = sensor.getObjectTempCelsius();

    //Get the surface humidity
    float humidity = sht3x.getHumidityRH();

    tempSum += objectTemp; // Add to temperature sum
    humiditySum += humidity; // Add to humidity sum

    delay(1000); // Wait for 1 second before the next reading
  }

  float averageTemp = tempSum / readings; // Calculate average temperature
  float averageHumidity = humiditySum / readings; // Calculate average humidity

  // Print the average temperature and humidity to the serial monitor
  Serial1.print(zone);
  Serial1.print(",");
  Serial1.print(averageTemp);
  Serial1.print(",");
  Serial1.print(averageHumidity);
  zone++;
}

void moveXForward() {
  digitalWrite(enPinX, LOW); 
  digitalWrite(dirPinX, HIGH);
  for (int x = 0; x < 1500; x++) {
    digitalWrite(stepPinX, HIGH); 
    delayMicroseconds(600);
    digitalWrite(stepPinX, LOW); 
    delayMicroseconds(600);
  }
  digitalWrite(enPinX, HIGH); 
}

void moveXBackward() {
  digitalWrite(enPinX, LOW); 
  digitalWrite(dirPinX, LOW);
  for (int x = 0; x < 1500; x++) {
    digitalWrite(stepPinX, HIGH); 
    delayMicroseconds(600);
    digitalWrite(stepPinX, LOW); 
    delayMicroseconds(600);
  }
  digitalWrite(enPinX, HIGH); 
}

void moveYForward() {
  digitalWrite(enPinY, LOW); 
  digitalWrite(dirPinY, HIGH);
  for (int x = 0; x < 300; x++) {
    digitalWrite(stepPinY, HIGH); 
    delayMicroseconds(600);
    digitalWrite(stepPinY, LOW); 
    delayMicroseconds(600);
  }
  digitalWrite(enPinY, HIGH); 
}

void moveYBackward() {
  digitalWrite(enPinY, LOW); 
  digitalWrite(dirPinY, LOW);
  for (int x = 0; x < 300; x++) {
    digitalWrite(stepPinY, HIGH); 
    delayMicroseconds(600);
    digitalWrite(stepPinY, LOW); 
    delayMicroseconds(600);
  }
  digitalWrite(enPinY, HIGH); 
}