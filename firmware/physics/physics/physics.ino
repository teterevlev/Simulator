#include <Arduino.h>
const float MAX_SPEED = 20;
const float MIN_SPEED = 2;
const float FRICTION = .5;
const float ACCELERATION = .2;
const float TEMPO_NUMENATOR = 1000;
int8_t direction=0;

bool run = false;
float speed = 0;
float speed1 = 0;
float oldSpeed = 0;
float tempo = 1;
float coord = 0;
float targetCoord = 0;
float targetSpeed = 0;
String inputString = "";
void setup() {
	Serial.begin(115200);
	inputString.reserve(200);
	Serial.println("time\tcoord\tspeed\tdir\trun\ttargetSpeed");
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(13, OUTPUT);
}
void pr(){
	Serial.print(millis());
	Serial.print("\t");
	Serial.print(coord);
	Serial.print("\t");
	Serial.print(speed);
	Serial.print("\t");
	Serial.print(direction);
	Serial.print("\t");
	Serial.print(run);
	Serial.print("\t");
	Serial.println(targetSpeed);
}
int8_t checkSpeed(){
	if(speed > 0 && speed >= targetSpeed) return 1;
	if(speed < 0 && speed <= -targetSpeed) return -1;
	return 0;
}
void motor(bool up){
	static int8_t phase;
	if(up) phase++;
	else phase--;
	if(phase>=4)
		phase = 0;
	else if(phase<0)
		phase = 3;
	switch (phase){
		case 0: digitalWrite(A1, HIGH);digitalWrite(A0, LOW);break;
		case 1: digitalWrite(A2, HIGH);digitalWrite(A1, LOW);break;
		case 2: digitalWrite(A3, HIGH);digitalWrite(A2, LOW);break;
		case 3: digitalWrite(A0, HIGH);digitalWrite(A3, LOW);break;
	}
	digitalWrite(13, digitalRead(A4)^1);
}
void stop(){
	digitalWrite(A0, LOW);
	digitalWrite(A1, LOW);
	digitalWrite(A2, LOW);
	digitalWrite(A3, LOW);
	Serial.print("stop at ");
	Serial.println(coord);
}
void step(){
	if(speed>0){
		coord ++;
		motor(1);
	}else if(speed<0){
		coord--;
		motor(0);
	}
}
void friction(){
	if(speed>0){
		speed -= tempo*FRICTION;
		if(speed < MIN_SPEED){
			speed = 0;
			stop();
		}
	}else if(speed<0){
		speed += tempo*FRICTION;
		if(speed > -MIN_SPEED){
			speed = 0;
			stop();
		}
	}
}
void limitSpeed(){
	if(speed > 0) speed = targetSpeed;
	else speed = -targetSpeed;
}
void loop(){
	if(run){
		if(targetCoord >= coord){
			if(checkSpeed() == 0){
				speed = speed + tempo*ACCELERATION;
			}else{
				limitSpeed();
			}
			if(direction<0) run=false;
		}else{
			if(checkSpeed() == 0){
				speed = speed - tempo*ACCELERATION;
			}else{
				limitSpeed();
			}
			if(direction>0) run=false;
		}
	}else{
		friction();
	}
	if(speed < MIN_SPEED && speed > -MIN_SPEED){
		tempo = 1;
	}else{
		tempo=abs(1./speed);
		//pr();
	}
	step();
	delayMicroseconds(tempo*20000);
}

void serialEvent() {
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		//if(isDigit(inChar))
		inputString += inChar;
		if (inChar == '\n') {
			//Serial.println(inputString.toInt());
			targetCoord = inputString.toInt();
			targetSpeed = targetCoord - coord;
			if(targetSpeed > 0){
				direction = 1;
			}else if(targetSpeed < 0){
				direction = -1;
			}
			targetSpeed = abs(targetSpeed);
			if(targetSpeed > MAX_SPEED)
				targetSpeed = MAX_SPEED;
				/*
			Serial.print("\t");
			Serial.print(targetCoord);
			Serial.print("\t");
			Serial.println(targetSpeed);*/
			run = true;
			inputString = "";
		}
	}
}

