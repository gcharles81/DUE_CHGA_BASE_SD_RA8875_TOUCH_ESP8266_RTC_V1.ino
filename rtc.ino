void RTC_CHGA() {
//
	Serial.println("Previous TEENSY FUNCTION PLEAE UPDATE FOR DUE");
}

void digitalClockDisplay() {

	// Get data from the DS3231
	t = rtc.getTime();

  // digital clock display of the time
  Serial.print(t.hour,DEC);
  Serial.print(":");
  Serial.print(t.min,DEC);
  Serial.print(":");
  Serial.print(t.sec,DEC);
  Serial.print(":---------:");
  Serial.print(" ");
  Serial.print(t.date,DEC);
  Serial.print(" ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" ");
  Serial.print(t.year,DEC);
  Serial.println(); 
}


void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
