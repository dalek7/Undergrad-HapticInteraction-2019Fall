
int saveCount;

void setup() {
  size(500, 500);
  saveCount = 0;
}

void draw() {
  background(204);
  line(0, 0, mouseX, mouseY);
}

void mousePressed() {
  //String filename = "line_" + str(frameCount) + ".jpg";
  String filename = "line_" + str(saveCount) + ".jpg";
  
  saveCount = saveCount + 1;
  save(filename);
  println("saved..." + filename);
}