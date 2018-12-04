import processing.serial.*;

Serial port; 
String val;  

void setup()
{
  String portName = Serial.list()[0];
  port = new Serial(this, portName, 9600);
  size(800, 800);
}

void predict_light_source(int up, int down, int left, int right){
  int x = ((right-left)*400)/1023 + 400;
  int y = ((down-up)*400)/1023 + 400;
  int intensity = ((up+down+left+right)*255)/(1023*4);
  //System.out.println(intensity);
  noStroke();
  background(intensity);
  int max_intensity = max(up,down,max(left,right))*255/1023;
  int b2 = (max_intensity-intensity)/3 + intensity;
  int b1 = ((max_intensity-intensity)*2)/3 + intensity;
  int b0 = max_intensity;
  fill(b2);
  ellipse(x, y, max_intensity, max_intensity);
  fill(b1);
  ellipse(x, y, max_intensity*2/3, max_intensity*2/3);
  fill(b0);
  ellipse(x, y, max_intensity/3, max_intensity/3);
  stroke(255,255,0);
  line(400, 390, 400, 410);
  line(390, 400, 410, 400);
  textSize(20);
  color green = color(30, 255, 0);
  color red = color(255,30,30);
  if (intensity > 128){
    fill(0);
  }else{
    fill(255);
  }
  text("System Health: ", 30, 750); 
  if (up == 0) {
    fill(red);
  } else {
    fill(green);
  }
  text("UP", 200, 750); 
  if (down == 0) {
    fill(red);
  } else {
    fill(green);
  }
  text("DOWN", 260, 750); 
  if (left == 0) {
    fill(red);
  } else {
    fill(green);
  }
  text("LEFT", 360, 750); 
  if (right == 0) {
    fill(red);
  } else {
    fill(green);
  }
  text("RIGHT", 440, 750); 
}
void draw()
{
  if ( port.available() > 0) 
  {  // If data is available,
  String s = port.readStringUntil('\n');
  if (s != null){
      System.out.println(s);
     String[] vals = splitTokens(s.trim(), "  "); //split trimmed input
    if (vals.length == 4) {
      int up = int(vals[0]);
      int down = int(vals[1]);
      int left = int(vals[2]);
      int right = int(vals[3]);
      predict_light_source(up,down,left,right);
    }else{
      background(0,0,255);
      fill(255);
      text("No Connection", 400,400);
    }
  }
  
} 
  
}
