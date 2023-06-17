const int IRsensor1 = A0;
const int IRsensor2 = A1;
const int IRsensor3 = A2;

const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;
const int IN3 = 7;
const int IN4 = 6;
const int ENB = 5;

const float Kp = 0.1;  

const int white = 25;
const int black = 480;
int setpoint = ((white + black) / 2);

int speed = 70;

void setup() {
  pinMode(IRsensor1, INPUT);
  pinMode(IRsensor2, INPUT);
  pinMode(IRsensor3, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  Serial.begin(9600);
}

void default_write(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA,200);
  analogWrite(ENB,200);
}


void turnR(float steering, int power) {
  int Lspeed = power - power * steering;
  int Rspeed = power + power * steering;

  Lspeed = min(max(Lspeed, 0), 255);
  Rspeed = min(max(Rspeed, 0), 255);

  analogWrite(ENA, Rspeed);
  analogWrite(ENB, Lspeed);
}

void turnL(float steering, int power){
  int Lspeed = power + power * steering;
  int Rspeed = power - power * steering;

  Lspeed = min(max(Lspeed, 0), 255);
  Rspeed = min(max(Rspeed, 0), 255);

  analogWrite(ENA, Rspeed);
  analogWrite(ENB, Lspeed);
}

void right(){
  analogWrite(ENA,0);
  analogWrite(ENB,255);
  delay(1000);
}

void right2(){
  analogWrite(ENA,0);
  analogWrite(ENB,255);
  delay(1400);
}

void stopper(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  delay(100000);
}
int counter = 0;
int stop = 0;

void loop() {
  int sensorData1 = analogRead(IRsensor1);
  int sensorData2 = analogRead(IRsensor2);
  int sensorData3 = analogRead(IRsensor3);

  default_write();

  int error = sensorData2 - setpoint;
  float steering = error * Kp;


  if(counter == 0 && sensorData1>setpoint){
    right();
    counter = 1;
  }else if(counter == 1 && sensorData1>setpoint){
    right2();
    counter = 2;
  }
  
  turnL(steering,speed);

  if (sensorData1>setpoint && sensorData2>setpoint && sensorData3>setpoint && stop == 0){
    stop = 1;
  }else if(sensorData1>setpoint && sensorData2>setpoint && sensorData3>setpoint && stop == 1){
    stop = 2;
  }else if (sensorData1>setpoint && sensorData2>setpoint && sensorData3>setpoint && stop == 2){
    stopper();
  }
  
}




