int cnt;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  cnt = 0;
}

void loop() {
  //Serial.println('a' + cnt); // 이렇게 실행하면 어떻게 될까요?
  Serial.println(cnt);
  delay(1000);           
  cnt = cnt +1;
}
