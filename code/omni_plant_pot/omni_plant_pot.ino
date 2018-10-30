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

void setup() {
  // put your setup code here, to run once:

}

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
  // Writing the corresponding direction pins as desired
  switch(dir){
    case FORWARD:
      digitalWrite(left, HIGH);
      digitalWrite(right, HIGH);
      break;
    case BACKWARD:
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
      break;
    case LEFT:
      digitalWrite(left, LOW);
      digitalWrite(right, HIGH);
      break
    case RIGHT:
      digitalWrite(left, HIGH);
      digitalWrite(right, LOW);
      break //why not
    default: break
  }
}

void set_power( char group, int power) {
  // somewhat unnecessary abstraction, but I'll include for consistency with interface.
  if (group == 'A'){
    analogWrite(AP, power);
  }
  if (group == 'B'){
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
    
}

void brake(){
  set_motor_group('A', FORWARD, 0);
  set_motor_group('B', FORWARD, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
