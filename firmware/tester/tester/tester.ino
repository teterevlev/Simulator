int32_t coord = 0;
static const int16_t a[505] = {1, 4, 9, 16, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155, 165, 175, 185, 195, 205, 215, 225, 235, 245, 255, 265, 275, 285, 295, 305, 315, 325, 335, 345, 355, 365, 375, 385, 395, 405, 415, 425, 435, 445, 455, 465, 475, 485, 495, 505, 515, 525, 535, 545, 555, 565, 575, 585, 595, 605, 615, 625, 635, 645, 655, 665, 675, 685, 695, 705, 715, 725, 735, 745, 755, 765, 775, 785, 795, 805, 815, 825, 835, 845, 855, 865, 875, 885, 895, 905, 915, 925, 935, 945, 955, 965, 974, 982, 990, 998, 1005, 1011, 1017, 1023, 1028, 1032, 1036, 1040, 1043, 1045, 1047, 1049, 1050, 1050, 1050, 1050, 1049, 1047, 1045, 1043, 1040, 1036, 1032, 1028, 1023, 1018, 1013, 1008, 1003, 998, 993, 988, 983, 978, 973, 968, 963, 958, 953, 948, 943, 938, 933, 928, 924, 919, 915, 910, 906, 902, 898, 894, 890, 887, 883, 880, 876, 873, 870, 867, 864, 861, 858, 855, 853, 850, 848, 845, 843, 841, 839, 837, 835, 834, 832, 831, 829, 828, 827, 826, 825, 824, 823, 822, 822, 821, 821, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 820, 821, 823, 826, 830, 835, 841, 848, 856, 865, 875, 885, 895, 905, 915, 925, 935, 945, 955, 965, 975, 985, 995, 1004, 1012, 1019, 1025, 1030, 1034, 1037, 1039, 1040, 1040, 1039, 1037, 1034, 1030, 1025, 1019, 1012, 1004, 996, 988, 980, 972, 964, 956, 948, 940, 932, 924, 916, 908, 900, 892, 884, 876, 868, 860, 852, 844, 836, 828, 820, 812, 804, 796, 788, 780, 772, 764, 756, 748, 740, 732, 724, 716, 708, 700, 692, 684, 676, 668, 660, 652, 644, 636, 628, 620, 612, 604, 596, 589, 583, 578, 574, 571, 569, 568, 568, 568, 568, 569, 569, 570, 570, 571, 572, 573, 574, 575, 576, 577, 579, 580, 582, 583, 585, 587, 589, 591, 593, 596, 598, 601, 603, 606, 609, 612, 615, 618, 621, 624, 627, 630, 633, 636, 639, 642, 645, 648, 651, 654, 657, 660, 663, 666, 669, 672, 675, 678, 681, 684, 687, 690, 693, 695, 696, 696, 695, 693, 690, 686, 681, 675, 668, 660, 651, 641, 631, 621, 611, 601, 591, 581, 571, 561, 551, 541, 531, 521, 511, 501, 491, 481, 471, 461, 451, 441, 431, 421, 411, 401, 391, 381, 371, 361, 351, 341, 331, 321, 311, 301, 291, 281, 271, 261, 251, 241, 231, 221, 211, 201, 191, 181, 171, 161, 151, 141, 131, 122, 114, 107, 101, 96, 92, 88, 85, 82, 80, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 3};
void setup()
{
	Serial.begin(115200);
	Serial1.begin(115200);
	while(!Serial.available());
}
bool oldStep = 0;
void loop()
{
	while(0){
		pins();
	}
	uint32_t m = 0;
	while(!Serial.available()){
		pins();
		if(m<=millis()){
 			Serial.print("\t");
 			Serial.println(coord, DEC);
			m = millis()+10;
		}
	}
	
	while(Serial.available()){
		Serial.read();
	}
	for(int16_t i=0;i<400;i++){
		uint32_t m = millis()+10;
		int16_t p = a[i];
 		Serial.print(p, DEC);
 		Serial.print("\t");
 		Serial.println(coord, DEC);
		Serial1.print(p, DEC);
		Serial1.print("\n");
		while(m > millis()){
			pins();
		}
	}
	while(0);
}
uint32_t m, oldM;
void pins(){
			bool step = digitalRead(2);
			if(step && !oldStep){
				if(digitalRead(3)) coord++;
				else coord--;
			}
			oldStep = step;
	
}