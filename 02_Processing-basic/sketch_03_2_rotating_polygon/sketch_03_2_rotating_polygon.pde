void setup() 
{
	size(640, 360);
}

void draw() 
{
	background(102);
	pushMatrix();
  	translate(width*0.5, height*0.5);
    rotate(frameCount / 50.0); // 50? 200? 
  	polygon(0, 0, 82, 3);  // Triangle
	popMatrix();
}


void polygon(float x, float y, float radius, int npoints)
{
	float angle = TWO_PI / npoints;
	beginShape();
	for (float a = 0; a < TWO_PI; a += angle) 
	{
		float sx = x + cos(a) * radius;
		float sy = y + sin(a) * radius;
		vertex(sx, sy);
	}
	endShape(CLOSE);
}