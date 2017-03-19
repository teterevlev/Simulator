uint16_t coord = 0;
uint16_t speed = 10;
void setup()
{
	Serial.begin(115200);
	Serial1.begin(115200);
}

void loop()
{
	uint32_t m = millis()+1000;
	Serial.print("-----------------------\t");
	Serial.println(coord);
	Serial1.println(coord);
	coord += speed;
	while(m > millis()){
		while(Serial1.available()){
			char c = Serial1.read();
			Serial.write(c);
		}
	}
}
