// 받은 것을 다시 보냄 --> Echo
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() {
  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    //char inChar = (char)Serial.read();
    int v = Serial.read();
    //v = v+1; // 이 부분의 역할은?
    char vChar = (char) v;
    
    Serial.println(vChar);
  }

}
