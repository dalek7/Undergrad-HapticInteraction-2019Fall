int cnt1 = 0;
void setup() {
  Serial.begin(9600);
}

// 1초마다 PC로 숫자를 보내는 예제
void loop() {
  char buf[255];
  sprintf(buf, "%d", cnt1);
  // "%d" 를 "%c" 로 바꾸면 어떻게 될까요?
  
  Serial.println(buf);
  cnt1++;
  
  delay(1000);
}
