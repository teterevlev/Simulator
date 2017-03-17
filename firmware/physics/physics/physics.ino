#include <Arduino.h>
const float MAX_SPEED = 51;
const float MIN_SPEED = 2;
const float FRICTION = 2;
const float ACCELERATION = 5;
const float TEMPO_NUMENATOR = 1000;

bool run = false;
float speed = 0;
float speed1 = 0;
float oldSpeed = 0;
float tempo = 1;
float coord = 0;
float targetCoord = 0;
String inputString = "";
void setup() {
	Serial.begin(115200);
	inputString.reserve(200);
}
void pr(){
	Serial.print(millis());
	Serial.print("\t");
	Serial.print(coord);
	//Serial.print("\t");
	//Serial.print(10000*(oldSpeed-speed)/tempo);
	Serial.print("\t");
	Serial.println(speed);
}
int8_t checkSpeed(){
	if(speed > MAX_SPEED) return 1;
	if(speed < -MAX_SPEED) return -1;
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

int8_t direction=0;
void loop(){
	if(speed < MIN_SPEED && speed > -MIN_SPEED){
		tempo = 1;
	}else{
		tempo=abs(1./speed);
		pr();
	}
	if(run){
		if(targetCoord > coord){
			if(checkSpeed() == 0){
				speed = speed + tempo*ACCELERATION;
			}
			if(direction<0) run=false;
		}else if(targetCoord < coord){
			if(checkSpeed() == 0){
				speed = speed - tempo*ACCELERATION;
			}
			if(direction>0) run=false;
		}
	}else{
		friction();
	}
	step();
	delay(tempo*1000);
}
/*
при получении цели задается направление, скорость начинает нарастать в нужном направлении
при достижении цели направление обращается в 0, скорость плавно падает
*/
void serialEvent() {
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		//if(isDigit(inChar))
		inputString += inChar;
		if (inChar == '\n') {
			//Serial.println(inputString.toInt());
			targetCoord = inputString.toInt();
			if(targetCoord > coord){
				direction = 1;
			}else if(targetCoord < coord){
				direction = -1;
			}
			run = true;
			inputString = "";
		}
	}
}

