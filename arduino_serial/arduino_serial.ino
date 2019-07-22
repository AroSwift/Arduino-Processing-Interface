#include <NewPing.h> // By Tim Eckel

const int trigger_pin = 6;
const int echo_pin = 5;
const int max_distance = 200;
const byte joy_switch_btn = 2;
const byte joy_switch_x = A0;
const byte joy_switch_y = A1;
volatile int r_color = 0;
volatile int g_color = 0;
volatile int b_color = 0;
volatile byte click_counter = -1;
int current_distance = 0;

// NewPing setup of pins and maximum distance
NewPing sonar(trigger_pin, echo_pin, max_distance);

void setup() {
  Serial.begin(9600);
  // Interrupt #, method, Falling/Rising/Change
  attachInterrupt(0, change_color, FALLING);

  pinMode(joy_switch_btn, INPUT_PULLUP);
}

void loop() {
  delay(50); // Arbitrarily chose 50 milliseconds
  
  current_distance = sonar.ping_cm();

  Serial.print(r_color);
  Serial.print(", ");
  Serial.print(g_color);
  Serial.print(", ");
  Serial.print(b_color);
  Serial.print(", ");
  Serial.print(current_distance);
  Serial.print(", ");

  int x_pos = analogRead(joy_switch_x);
  int y_pos = analogRead(joy_switch_y);
  
  Serial.print(x_pos);
  Serial.print(", ");
  Serial.println(y_pos);
}

void change_color() {
  click_counter++;

  if(click_counter == 0) {
    r_color = random(0, 255);
    g_color = random(0, 255);
    b_color = random(0, 255);
  } else if(click_counter > 3) {
    click_counter = -1;
  }
}

