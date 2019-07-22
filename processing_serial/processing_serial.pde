import processing.serial.*;
Serial port;
//int screen_width = 0;
//float screen_height = 0;
float r_color = 150;
float g_color= 150;
float b_color = 150;
float side_length = 50;
float prev_side_length = 50;
float x_pos = 0;
float y_pos = 0;


void SerialEvent(Serial port) {
  String read_string = port.readStringUntil('\n');
  println("Value: " + read_string);
  
  if(read_string != null) {
      read_string = trim(read_string);
      float[] values = float(split(read_string, ","));
      
      if(values.length >= 6) {
        r_color = values[0];
        g_color = values[1];
        b_color = values[2];
        side_length = values[3];
        x_pos = values[4];
        y_pos = values[5];
        
        side_length = 200 - side_length;
        x_pos = map(x_pos, 0, 1023, 0, 700);
        y_pos = map(y_pos, 0, 1023, 0, 700);
        
        println(side_length);
        
      }
  }
}

// run once
void setup() {
  // Screen size
  size(700, 700);
  printArray(Serial.list());
  port = new Serial(this, Serial.list()[1], 9600);
  port.bufferUntil('\n');
}

// forever loop
void draw() {
  if(port.available() > 0) {
    SerialEvent(port);
  }
  
  // rgb 0-255
  background(250, 75, 75);
  
  // fill color for a box (r, g, b)
  fill(255 - r_color, 255 - g_color, 255 - b_color);
  // x, y, width, height
  float half = side_length / 2;
  rect(x_pos - half, y_pos - half, side_length, side_length);
}