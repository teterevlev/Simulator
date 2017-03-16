#include <Arduino.h>
const int16_t MAX_SPEED = 51;
const int16_t FRICTION = 3;
int16_t acceleration = FRICTION*2;
const int16_t TEMPO_NUMENATOR = 1000;

int8_t direction = 1;
int16_t speed = 0;
int16_t oldSpeed = 0;
int16_t tempo = 1000;
int32_t coord = 0;
int32_t targetCoord = 0;
String inputString = "";
void setup() {
	Serial.begin(115200);
	inputString.reserve(200);
}
void step(){
	if(speed>0)
		coord++;
	else if(speed<0)
		coord--;
	Serial.print(millis());
	Serial.print("\t");
	Serial.print(coord*10);
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
bool speedSignChanged(){
	if(speed == 0) return true;
	if(oldSpeed<0 && speed>0) return true;
	if(oldSpeed>0 && speed<0) return true;
	return false;
}
void loop() {
	bool far = isFar();
	if(coord>targetCoord){
		//if(speedSignChanged()) direction = -1;
		if(checkSpeed() >= 0 && far){
			speed -= acceleration;
		}
	}else if(coord<targetCoord){
		//if(speedSignChanged()) direction = 1;
		if(checkSpeed() <= 0 && far){
			speed += acceleration;
		}
	}

	friction();
	if(speed)
		tempo = abs(TEMPO_NUMENATOR/speed);
	step();
	uint32_t m = millis()+tempo;
	while(m>millis());
	
	oldSpeed = speed;
	
}
void serialEvent() {
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		//if(isDigit(inChar))
		inputString += inChar;
		if (inChar == '\n') {
			//Serial.println(inputString.toInt());
			targetCoord = inputString.toInt();
			inputString = "";
		}
	}
}

