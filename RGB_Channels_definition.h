#pragma once

#include <RGBHandler.h>


//RGB Channel1 ={0,0,0  };//use the TimerHandler library structure
RGB Channel1_Updater = RGB();

RGBChannel Channel1 = RGBChannel{ 0,0,0,true };
RGBChannel Channel2 = RGBChannel{ 0,0,0,true };
RGBChannel Channel3 = RGBChannel{ 0,0,0,true };
RGBChannel Channel4 = RGBChannel{ 0,0,0,true };

///Below just for small test 

int gbv = Channel1.Red;
int gbv2 = Channel1.Green;
int gbv3 = Channel1.Blue;

/*

void RGB_Set(RGBChannel uji){

	if (uji.State) {
		int myint1 = uji.Red;
		int myint2 = uji.Green;
		int myint3 = uji.Blue;
	
	}

	else {
		Serial.println("RGB_Channel not activated");
	}
}

*/
