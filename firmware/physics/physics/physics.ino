#include <Arduino.h>
const int16_t MAX_ACCELERATION = 100;
const int16_t MAX_SPEED = 100;
const int16_t FRICTION = 5;
const int16_t POWER = 10;

int16_t speed = 0;
int32_t coord = 0;
int32_t targetCoord = 0;
String inputString = "";
void setup() {
	Serial.begin(115200);
	inputString.reserve(200);
}
void step(int16_t s){
	coord+=s;
	Serial.print(coord);
	Serial.print("\t");
	Serial.println(speed);
}
int8_t checkSpeed(){
	if(speed > MAX_SPEED) return 1;
	if(speed < -MAX_SPEED) return -1;
	return 0;
}
void friction(){
	if(speed>0)
	speed -= FRICTION;
	else if(speed<0)
	speed += FRICTION;
}
bool isFar(){
	if(abs(coord - targetCoord) <= FRICTION) return false;
	return true;
}
void loop() {
	uint32_t m = millis()+100;
	if(isFar()){
		if(coord>targetCoord){
			if(checkSpeed() >= 0){
				speed -= POWER;
			}
		}else if(coord<targetCoord){
			if(checkSpeed() <= 0){
				speed += POWER;
			}
		}
		friction();
		step(speed);
	}else{
		coord = targetCoord;
	}
	while(m>millis());
	
}
void serialEvent() {
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		//if(isDigit(inChar))
		inputString += inChar;
		if (inChar == '\n') {
			Serial.println(inputString.toInt());
			targetCoord = inputString.toInt();
			inputString = "";
		}
	}
}

