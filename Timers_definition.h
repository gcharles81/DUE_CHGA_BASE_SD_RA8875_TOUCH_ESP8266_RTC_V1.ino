#pragma once


/*
#include <DS3231.h>

DS3231  rtc2(SDA, SCL);
Time  my_time;
*/

boolean Use_Debug_RTC_Serial = false; // set false to disable serial print 

typedef struct {
	uint8_t Hour_On;
	uint8_t Min_On;
	uint8_t Hour_Off;
	uint8_t Min_off;
	uint8_t duration;
	boolean State;
} Timer;

// Timers name definition  

Timer Sunrise = { 0, 0, 0 ,0 ,0 ,true };//use the TimerHandler library structure
Timer Sunset = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Day1 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Day2 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Day3 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Neon1 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Neon2 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Neon3 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Night1 = { 0, 0, 0 ,0 ,0 ,true };//use the TimerHandler library structure
Timer Night2 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Uv1 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure
Timer Uv2 = { 0, 0, 0 ,0 ,0 ,false };//use the TimerHandler library structure

									 //

uint8_t my_Hour = 0;
uint8_t my_Minute = 0;
uint8_t my_Second = 0;

/*
void Start_my_rtc() {

	rtc2.begin();

	//  The following lines can be uncommented to set the date and time

	//	rtc2.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
	//	rtc2.setTime(07, 40, 0);     // Set the time to 12:00:00 (24hr format)
	//	rtc2.setDate(13, 5, 2018);   // Set the date to January 1st, 2014


}

void RTC_Get_time() {

	my_time = rtc2.getTime();//Gets time and fill my time buffer 

	my_Hour = my_time.hour;

	my_Minute = my_time.min;

	my_Second = my_time.sec;
}




String RTC_Get_day()
{
	String day = (rtc2.getDOWStr());

	if (Use_Debug_RTC_Serial) {

		Serial.print(rtc2.getDOWStr()); //Gets day of week eg : Monday , Tuesday etc  
	}

	return day;
}


String RTC_Get_date()
{
	String date = (rtc2.getDateStr());

	if (Use_Debug_RTC_Serial) {

		Serial.print(rtc2.getDateStr()); //Gets day of week eg : Monday , Tuesday etc  
	}

	return date;
}


boolean Timer_ON(uint8_t time, Timer) {

	if (time == 2) {

		return true;
	}

	else {
		return false;
	}

}
*/
