void setup() {
  size(100, 100);
}

void draw() {
  background(204);
  line(0, 0, mouseX, mouseY);
}

void mousePressed() {
  save("line.jpg");
  println("saved...");
}