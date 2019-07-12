const byte movementLedPin = 13;
const byte sensorLedPin = 12;
const byte movementIntPin = 2;
const byte blindIntPin = 3;
volatile byte movementState = LOW;
volatile byte sensorState = LOW;
int movementRead = 0;
int sensorRead = 0;
unsigned long movementTimeIni;
unsigned long elapsed;
unsigned long sensorTimeIni;


void setup() {
  pinMode(movementLedPin, OUTPUT);
  pinMode(sensorLedPin, OUTPUT);
  //Button or
  pinMode(movementIntPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(movementIntPin), movement, RISING);
  //Sensor pin
  pinMode(blindIntPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(blindIntPin), sensor, FALLING);
  Serial.begin(9600); //Enable serial?
}

void loop() {
  digitalWrite(movementLedPin, movementState);
  digitalWrite(sensorLedPin, sensorState);
  movementRead = digitalRead(movementIntPin);
  sensorRead = digitalRead(blindIntPin);

  //Debug print
  Serial.print(" movement: ");
  Serial.print(movementState);
  Serial.print(movementRead);
  Serial.print(" sensor: ");
  Serial.print(sensorState);
  Serial.println(!sensorRead);
  

  
  //Look if car is moving
  if(movementRead == HIGH){
    movementTimeIni = millis();
  }else{
    if(millis() - movementTimeIni > 50000 ){
      movementState = 0;
    }  
  }

  //If car is moving, look if blindspot sensor is active.
  if(movementState && sensorRead == LOW){
    sensorTimeIni = millis();
    sensorState= 1;
  }else{
    if(millis()-sensorTimeIni > 1000){
      sensorState =0;
    }  
  }
  
  
  
  
}

//Interrupt for movement (this enables the blind sensor interrupt)
void movement() {
  movementState = 1;
  movementTimeIni = millis();
}


void sensor() {
  if(movementState){
    sensorState= 1;
    sensorTimeIni = millis();  
  }
  
}
