// Holonomic Light-Seeking Plant Pot
// Copyright 2018 Matthew Fan

// pinouts for motor control
#define AP 3
#define AL 4
#define AR 5
#define BP 10
#define BL 9                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
#define BR 8
#define WHISTLE 1

#define AL1 4
#define AL2 5
#define AR1 6
#define AR2 7

#define BL1 9
#define BL2 8
#define BR1 11
#define BR2 12
// analog sensing pins in for light sensing
#define L_U 0
#define L_D 1
#define L_L 2
#define L_R 3

// named constants
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4

int light_up, light_down, light_left, light_right;

void update_photocells() {
  light_up = analogRead(L_U);
  light_down = analogRead(L_D);
  light_left = analogRead(L_L);
  light_right = analogRead(L_R); 
}

void set_direction_DEPRECATED( char group, int dir){
  //deprecated 2-pin version
  int left, right;
  // Set pins to corresponding group.
  if (group == 'A'){
    left = AL;
    right = AR;
  }
  if (group == 'B'){
    left = BL;
    right = BR;
  }
//  Serial.print("Left pin is ");
//  Serial.println((String) left);
//  Serial.print("Right pin is ");
//  Serial.println((String) right);
  // Writing the corresponding direction pins as desired
  switch(dir){
    case FORWARD:
      Serial.println("forwards");
      digitalWrite(left, HIGH);
      digitalWrite(right, HIGH);
      break;
    case BACKWARD:
      Serial.println("backwards");
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
      break;
    case LEFT:
      Serial.println("left");
      digitalWrite(left, LOW);
      digitalWrite(right, HIGH);
      break;
    case RIGHT:
      Serial.println("right");
      digitalWrite(left, HIGH);
      digitalWrite(right, LOW);
      break; //why not
    default: break;
  }
}

void set_direction( char group, int dir){
  //new version with 4 pin explicit output
  int l1, l2, r1, r2;
  // Set pins to corresponding group.
  if (group == 'A'){
    l1 = AL1;
    l2 = AL2;
    r1 = AR1;
    r2 = AR2;
  }
  if (group == 'B'){
    l1 = BL1;
    l2 = BL2;
    r1 = BR1;
    r2 = BR2;
  }
//  Serial.print("Left pin is ");
//  Serial.println((String) left);
//  Serial.print("Right pin is ");
//  Serial.println((String) right);
  // Writing the corresponding direction pins as desired
  switch(dir){
    case FORWARD:
      Serial.println("forwards");
      digitalWrite(l1, HIGH);
      digitalWrite(r1, HIGH);
      digitalWrite(l2, LOW);
      digitalWrite(r2, LOW);
      break;
    case BACKWARD:
      Serial.println("backwards");
      digitalWrite(l1, LOW);
      digitalWrite(r1, LOW);
      digitalWrite(l2, HIGH);
      digitalWrite(r2, HIGH);
      break;
    case LEFT:
      Serial.println("left");
      digitalWrite(l1, LOW);
      digitalWrite(r1, HIGH);
      digitalWrite(l2, HIGH);
      digitalWrite(r2, LOW);
      break;
    case RIGHT:
      Serial.println("right");
      digitalWrite(l1, HIGH);
      digitalWrite(r1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(r2, HIGH);
      break; //why not
    default: break;
  }
}

void set_power( char group, int power) {
  // somewhat unnecessary abstraction, but I'll include for consistency with interface.
//  Serial.println((String)group);
  if (group == 'A'){
//    Serial.print("Setting A power to ");
//    Serial.println((String)power);
    analogWrite(AP, power);
  }
  if (group == 'B'){
//    Serial.print("Setting B power to ");
//    Serial.println((String)power);
    analogWrite(BP, power);
  }
}

void set_motor_group( char group, int dir, int power){
  set_direction(group, dir);
  set_power(group, power);
  
  
}

void holonomic_seek_step(){
  // Set the the bot to holonomically seek the light source at the specific instance in time
  // Should be wrapped in a control block to adjust precision
  update_photocells();
  int y_diff = ((light_up - light_down) * 255) / 1023;
  int x_diff = ((light_right - light_left) * 255) / 1023;
  if (y_diff > 0) {
    set_motor_group('A', FORWARD, y_diff);
  } else {
    set_motor_group('A', BACKWARD, y_diff * -1);
  }
  if (x_diff > 0) {
    set_motor_group('B', FORWARD, x_diff);
  } else {
    set_motor_group('B', BACKWARD, x_diff * -1);
  }  
}

int ambient_light(){
  update_photocells();
  return min(min(light_up, light_down), min(light_left, light_right));
}



void rotational_seek_step_fine(){
  // Set the the bot to rotationally seek the light source at the specific instance in time
  // Should be wrapped in a control loop
  update_photocells();
  int forward = light_up;
  set_motor_group('A', LEFT, 255);
  set_motor_group('B', LEFT, 255);
  delay(100);
  update_photocells();
  int left = light_left;
  set_motor_group('A', RIGHT, 255);
  set_motor_group('B', RIGHT, 255);
  delay(200);
  update_photocells();
  int right = light_right;
  if (forward > right){
      set_motor_group('A', LEFT, 255);
      set_motor_group('B', LEFT, 255);
      delay(100);
  }
   if (left > forward){
      set_motor_group('A', LEFT, 255);
      set_motor_group('B', LEFT, 255);
      delay(100);
  }
}
boolean rotational_seek_step_coarse(){
  // Set the the bot to rotationally seek the light source at the specific instance in time
  // Should be wrapped in a control loop
  update_photocells();
  if (light_left > light_right){
    if (light_up < light_left) {
      set_motor_group('A', LEFT, 255);
      set_motor_group('B', LEFT, 255);
      delay(100);
      return true;
    }
  } else {
    if (light_up < light_right) {
      set_motor_group('A', RIGHT, 255);
      set_motor_group('B', RIGHT, 255);
      delay(100); 
      return true;    
    }    
  }
  return false;
}

void holonomic_seek(int threshold, int step_length){
  while (ambient_light() < threshold){
    holonomic_seek_step();
    delay(step_length);
  }
}

void rotational_seek(int threshold) {
  while (ambient_light() < threshold) {
    while(rotational_seek_step_coarse() == true){}
    for (int i = 0; i < 20; i++){
      rotational_seek_step_fine(); //fine correction
    }
    set_motor_group('A', FORWARD, 255);
    delay(100);
    set_motor_group('A', FORWARD, 0);
  }
}

void set_motors_manual(int power){
   char key;
   if (Serial.available()) {
     key = Serial.read(); 
   }
   switch(key){
    case 'w':
      set_motor_group('A', FORWARD, power);
      set_motor_group('B', FORWARD, 0);
      break;
    case 'a':
      set_motor_group('A', FORWARD, 0);
      set_motor_group('B', BACKWARD, power);
      break;
    case 's':
      set_motor_group('A', BACKWARD, power);
      set_motor_group('B', FORWARD, 0);
      break;
    case 'd':
      set_motor_group('A', FORWARD, 0);
      set_motor_group('B', FORWARD, power);
      break;
    case 'q':
      set_motor_group('A', LEFT, power);
      set_motor_group('B', LEFT, power);
      break;
    case 'e':
      set_motor_group('A', RIGHT, power);
      set_motor_group('B', RIGHT, power);
      break;
    case 'x':
      set_motor_group('A', FORWARD, 0);
      set_motor_group('B', FORWARD, 0);
      break;
    default:
      break;
   }
   delay(10);
}

void brake(){
  set_motor_group('A', FORWARD, 0);
  set_motor_group('B', FORWARD, 0);
}

void bask(){
  set_motor_group('A', LEFT, 80);
  set_motor_group('B', LEFT, 80);
}

/**
 * Send data over to be used in  processing.
 */
void serial_processing(){
//    Serial.print("up: ");
  Serial.print(analogRead(L_U));
  Serial.print("  ");
  Serial.print(analogRead(L_D));
  Serial.print("  ");
  Serial.print(analogRead(L_L));
  Serial.print("  ");
  Serial.println(analogRead(L_R));
  delay(30);
}

void setup() {
  pinMode(AL, OUTPUT);
  pinMode(AR, OUTPUT);
  pinMode(AP, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(BR, OUTPUT);
  pinMode(BP, OUTPUT);
  pinMode(AL1, OUTPUT);
  pinMode(AR1, OUTPUT);
  pinMode(AL2, OUTPUT);
  pinMode(AR2, OUTPUT);
  pinMode(BL1, OUTPUT);
  pinMode(BR1, OUTPUT);
  pinMode(BL2, OUTPUT);
  pinMode(BR2, OUTPUT);

  Serial.begin(9600);
  set_motor_group('A', FORWARD, 0);
  set_motor_group('B', FORWARD, 0);
}

void loop() {
//  serial_processing();
//  set_motors_manual(120);
  holonomic_seek();
}
