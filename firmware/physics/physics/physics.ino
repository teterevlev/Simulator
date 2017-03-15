#include <Arduino.h>
const uint16_t MAX_ACCELERATION = 10;
const uint16_t MAX_SPEED = 10;
uint16_t speed = 1;
int32_t coord = 0;
int32_t targetCoord = 0;
String inputString = "";
void setup() {
	Serial.begin(115200);
	inputString.reserve(200);
}
void step(int16_t speed){
	coord+=speed;
	Serial.println(coord);
}
void loop() {
	uint32_t m = millis()+100;
	if(coord>targetCoord) step(-speed);
	else if(coord<targetCoord) step(speed);
	while(m>millis());
	
}
void serialEvent() {
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		//if(isDigit(inChar))
		inputString += inChar;
		if (inChar == '\n') {
			//Serial.println(inputString.toInt()+1);
			targetCoord = inputString.toInt();
			inputString = "";
		}
	}
}

