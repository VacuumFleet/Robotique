#include <Servo.h>
#include <NewPing.h>
#define SERVO_PIN     11 // Servomotor

#define IN1  7    // Right motor (K1/K2)
#define IN2  8    // Right motor (K1/K2)
#define IN3  9    // Left motor (K3/K4)
#define IN4  10   // Left motor (K3/K4)
#define ENA  5    // ENA PWM right motor (K1/K2) - D5
#define ENB  6    // ENB PWM left motor (K3/K4) - D6

#define Echo_PIN    2 // Ultrasonic Echo pin - D2
#define Trig_PIN    3 // Ultrasonic Trig pin - D3

#define SPEED  80 


const int MAX_OBSTACLE_DISTANCE = 30; //distance limit for obstacles in front           
const int UTURN_DELAY = 1500; // Time to wait for a u-turn to be completed using BACK_SPEED
const int MAX_SONAR_PING_DELAY = 30; // Minimum time between two sonar pings

static bool should_move = false;
static char next_turn_direction = 'R';
static int last_obstacle_distance = 200;

unsigned long start_turn_millis = 0UL;
unsigned long last_watch_millis = 0UL;

Servo head;
NewPing sonar (Trig_PIN, Echo_PIN, 200); //Initialistion du capteur ultrasons

void set_motor_forward() {
  digitalWrite(IN4,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN2,HIGH );
  digitalWrite(IN1,LOW);
}
void set_motor_backwards() {
  digitalWrite(IN4,LOW);
  digitalWrite(IN3,HIGH); 
  digitalWrite(IN2,LOW);
  digitalWrite(IN1,HIGH);
}
void set_motor_stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
  set_motor_speed(0,0);
}
void set_motor_right() {
  digitalWrite(IN4,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN1,HIGH);
  set_motor_speed(SPEED,0);
  
}
void set_motor_left() {
  digitalWrite(IN4,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN1,LOW);
  set_motor_speed(0,SPEED);
 
}

void set_motor_speed(int lspeed,int rspeed) {
  analogWrite(ENB,lspeed); // lspeed: 0 - 255
  analogWrite(ENA,rspeed); // rspeed: 0 - 255   
}

int watch() {
  return sonar.ping_cm();
}

void movement_tick() {
  if(millis() - start_turn_millis > UTURN_DELAY) {
    int obstacle_distance;
    if(millis() - last_watch_millis > MAX_SONAR_PING_DELAY) {
      obstacle_distance = watch();
      last_obstacle_distance = obstacle_distance;
      last_watch_millis = millis();
    } else {
      obstacle_distance = last_obstacle_distance;
    }

    if (obstacle_distance <= MAX_OBSTACLE_DISTANCE) {
      set_motor_stop();
      
      if(next_turn_direction == 'R') { 
        set_motor_right();
        next_turn_direction = 'L';
      }
      else { 
        set_motor_left();
        next_turn_direction = 'R'; 
      }

      start_turn_millis = millis();
    } else {
      set_motor_speed(SPEED, SPEED);
      set_motor_forward();
    }
  }
}

char bluetooth_tick() {
  char data = 0;
  if(Serial.available() > 0) 
  {
    data = Serial.read();
  }

  return data;
}

void setup() {
  // Motors
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);

  set_motor_stop();

  // Ultrasonic
  pinMode(Trig_PIN, OUTPUT); 
  pinMode(Echo_PIN,INPUT); 

  // Servomotor
  head.attach(SERVO_PIN); 
  head.write(90);

  delay(2000);
  Serial.begin(9600);
}

void loop() {
    const char res = bluetooth_tick();
    if(res == '1') {
      should_move = true;
    } else if(res == '0') {
      should_move = false;
      set_motor_stop();
    }

    if(should_move) {
      movement_tick();
    }
}
