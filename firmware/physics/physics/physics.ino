#include <Arduino.h>
const float MAX_SPEED = 51;
const float MIN_SPEED = 2;
const float FRICTION = 2;
const float ACCELERATION = 5;
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
void step(){
	if(speed>0)
	coord ++;
	else if(speed<0)
	coord--;
}
void friction(){
	if(speed>0){
		speed -= tempo*FRICTION;
		if(speed < MIN_SPEED)
			speed = 0;
	}else if(speed<0){
		speed += tempo*FRICTION;
		if(speed > -MIN_SPEED)
			speed = 0;
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
		pr();
	}
	step();
	delay(tempo*1000);
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
			Serial.print("\t");
			Serial.print(targetCoord);
			Serial.print("\t");
			Serial.println(targetSpeed);
			run = true;
			inputString = "";
		}
	}
}

