void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // get incoming byte:
    int inByte = Serial.read();

    if(inByte=='0')
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    else if(inByte=='1')
      digitalWrite(LED_BUILTIN, HIGH); 
  }
}
