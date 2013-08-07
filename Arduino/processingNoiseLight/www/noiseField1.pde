float time;
float maxDiameter = 20;
float targetDiameter = 20;

void setup() {
  size(500, 500);
}

void draw() {
  background(0);  
  noStroke();        

  for (int i=0; i <= width; i+=20) {
    for (int j = 0; j <= height; j+=20) {

      //bi-dimensional noise: 
      //0 < n < 1, so it's multiplied by maxDiameter
      float diameter = noise(i+time, j+time) * maxDiameter;

      //larger circles are brighter
      fill(diameter*15);
      ellipse(i, j, diameter, diameter);
    }
  }

  //smooth transitions
  maxDiameter += (targetDiameter - maxDiameter) * 0.1;

  //play with the time 
  time += 0.01;
}

void setDiameter(float d) {
  d = map(d, 0, 1023, 0, 40);
  targetDiameter = d;
}
