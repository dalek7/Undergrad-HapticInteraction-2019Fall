
int sensorPosPin = A2; // input pin for MR sensor
int rawPos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//9600
  pinMode(sensorPosPin, INPUT); // set MR sensor pin to be an input

}

void loop() {
  // put your main code here, to run repeatedly:
  calculatePosition();
  Serial.println(rawPos);
}


void calculatePosition()
{
  rawPos = analogRead(sensorPosPin);
  
}
