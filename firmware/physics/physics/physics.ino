#include <Arduino.h>
const float MAX_SPEED = 51;
const float MIN_SPEED = 2;
const float FRICTION = .8;
const float ACCELERATION = 5;
const float TEMPO_NUMENATOR = 1000;

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
void friction(){
	speed *= FRICTION;
	if(speed < MIN_SPEED)
		speed = 0;
}
int8_t direction=0;
void loop(){
	if(speed == 0){
		tempo = 1;
	}else{
		tempo=1./speed;
		pr();
	}
	if(checkSpeed() == 0){
		if(direction>0)
			speed = speed + tempo*ACCELERATION;
		else if(direction<0)
			speed = speed - tempo*ACCELERATION;
		else
			friction();
	}
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
			inputString = "";
		}
	}
}

