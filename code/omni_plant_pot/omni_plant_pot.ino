// Holonomic Light-Seeking Plant Pot
// Copyright 2018 Matthew Fan

// pinouts for motor control
#define AL 2
#define AR 4
#define AP 3
#define BL 5
#define BR 7
#define BP 6

// analog sensing pins in for light sensing
#define L1 1
#define L2 2
#define L3 3
#define L4 4

// named constants
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4


void set_direction( char group, int dir){
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
  Serial.print("Left pin is ");
  Serial.println((String) left);
  Serial.print("Right pin is ");
  Serial.println((String) right);
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

void set_power( char group, int power) {
  // somewhat unnecessary abstraction, but I'll include for consistency with interface.
  Serial.println((String)group);
  if (group == 'A'){
    Serial.print("Setting A power to ");
    Serial.println((String)power);
    analogWrite(AP, power);
  }
  if (group == 'B'){
    Serial.print("Setting B power to ");
    Serial.println((String)power);
    analogWrite(BP, power);
  }
}

void set_motor_group( char group, int dir, int power){
  set_direction(group, dir);
  set_power(group, power);
  
  
}


void setup() {
  pinMode(AL, OUTPUT);
  pinMode(AR, OUTPUT);
  pinMode(AP, OUTPUT);
  Serial.begin(9600);
  set_motor_group('A', FORWARD, 200);
//  digitalWrite(AL, HIGH);
//  digitalWrite(AR, LOW);
//  analogWrite(AP, 255);
}

void holonomic_seek_step(){
  // Set the the bot to holonomically seek the light source at the specific instance in time
  // Should be wrapped in a control block to adjust precision
    
}

void brake(){
  set_motor_group('A', FORWARD, 0);
  set_motor_group('B', FORWARD, 0);
}

void loop() {
  
}
