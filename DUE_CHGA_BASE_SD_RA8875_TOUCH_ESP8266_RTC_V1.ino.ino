

// include the SD library:
#include "keypad.h"
#include <SPI.h>
#include <SD.h>

//Charles versions of handlers 

// #include <DS3231.h> include for arduino

//#include <TimerHandler.h>
#include "Timers_definition.h"//not sure if needed

#include <RGBHandler.h>
#include "RGB_Channels_definition.h"//not sure if needed

//test
#include <Wire.h>
#include "Temporary_timers.h" ////only temporary here this actually will be replaced with Timers & RGB channels handlers .h 
#include <RA8875.h>
#include <DS3231.h>//RTC


// driver for the GSL1680 touch panel
// Information gleaned from https://github.com/rastersoft/gsl1680.git and various other sources
// firmware for the specific panel was found here:- http://www.buydisplay.com/default/5-inch-tft-lcd-module-800x480-display-w-controller-i2c-serial-spi
// As was some test code.
// This is for that 800X480 display and the 480x272 from buydisplay.com
// Thanks to wolfmanjm for the source code this lib is bassed on : https://github.com/wolfmanjm/GSL1680

/*
Pin outs
the FPC on the touch panel is six pins, pin 1 is to the left pin 6 to the right with the display facing up

pin | function  | Arduino Uno
-----------------------------
1   | SCL       | A5
2   | SDA       | A4
3   | VDD (3v3) | 3v3
4   | Wake      | 4
5   | Int       | 2
6   | Gnd       | gnd
*/

#include <GSL1680.h>
#include <Wire.h>

// Pins
#define WAKE 47
#define INTRPT 25

GSL1680 TS = GSL1680();
//


// Init the DS3231 using the hardware interface
DS3231  rtc(SDA1, SCL1);
// Init a Time-data structure
Time  t;
////////

/////////////XBEE///////
/**
* Copyright (c) 2009 Andrew Rapp. All rights reserved.
*
* This file is part of XBee-Arduino.
*
* XBee-Arduino is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* XBee-Arduino is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <XBee.h>

/*
This example is for Series 1 XBee (802.15.4)
Receives either a RX16 or RX64 packet and sets a PWM value based on packet data.
Error led is flashed if an unexpected packet is received
*/

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();



uint8_t option = 0;
uint8_t data = 0;

/////


////////////ONBOARD SD CARD//////CHGA
#define SDCSPIN     4//for SD
#define SDPRESENT     22//for SD

						  //////////////////////////////////////////////////////////////////////////////////
						  //#include <TimeLib.h>

						  ////////////LEDS//////CHGA

#define LED1 5   //Teensy-LED
#define LED2 7   //red
#define LED3 9   //orange
#define LED4 44   //green

						  //////////////////////////////////////////////////////////////////////////////////
						  ////////////RA8875//////CHGA
#define BUFFPIXEL 30
#define RA8875_CS 52
#define RA8875_RESET 255//any pin or nothing!



RA8875 tft = RA8875(RA8875_CS, RA8875_RESET);

long Flash_image_Start_address = 0;
short Flash_image_width = 0;
short Flash_image_height = 0;
File     bmpFile;
Sd2Card card;
SdVolume volume;
SdFile root;
File commandFile;
//File     bmpFile;
boolean btn_continous_press = false;



unsigned long currentMillis = 0;
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 2000;           // interval at which to blink (milliseconds)
///////////////////////////////////////////////////////////////////////////////////
//*********************MENUS RELATED********************************************///
int MENU_NR = 0;
int Menu_item = 0;

boolean Valid_button_menu_touch = false;////new chaga
boolean SCREEN_UPDATE = true;//////just for X_COL_2
boolean SUB_SCREEN_UPDATE = false;//////just for X_COL_2
int Settings_Menu_button_number = 0;
int i = 0;
///////////////////////////////////////////////////////////////////////////////////
//////////////////TOUCH CAPACITIVE////////////////////////////////////////////////////////////
boolean valid_touch = false;
boolean DO_I_NEED_TOUCH = false;
int Temp_TOUCH_X_VAL = 0;
int Temp_TOUCH_Y_VAL = 0;
int Temp_touch_FINGER = 0;
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////VIRTUAL KEYPAD RELATED///////////////////////////////////////
int KPD_Button_SIZE_X = 80; // 80x80 pixels
int KPD_Button_SIZE_Y = 50; // 80x80 pixels
int KPD_Button_PITCH_X = 90; // pitch between buttons 100 pixels
int KPD_Button_PITCH_Y = 60; // pitch between buttons 100 pixels
float KPD_Back_color = RA8875_RED;
float KPD_Button_color_touched = RA8875_WHITE;
float KPD_Button_color = RA8875_RED;
float KPD_TEXT_color = RA8875_BLACK;
boolean KEYPAD_UPDATE = false;//////just for X_COL_2
int KEYPAD_XPOS_VAL = 10;
int KEYPAD_YPOS_VAL = 10;
///////////////////////////////////////////////////////////////////////////////////


#include "All_75_Pic_65K.h"
#include "Buttons_handler_CHGA.h"
#include "RGB_settings_menu.h"
#include "CHGA_Keypad.h"
#include "Test_Menu.h"
#include "TESTING_EEPROM_HANDLER.h"
#include "Lable_handler_CHGA.h"

////////////ESP8266//////CHGA

#define WLAN_SERIAL     Serial1
#define WLAN_SERIAL_BAUD_INIT 74880
#define WLAN_SERIAL_BAUD 115200
#define WLAN_RESET      57
#define WLAN_ENABLE     255//not used  //CH_PD
#define WLAN_CTS        0  //GPIO15
#define WLAN_RTS        0   //GPIO13
#define WLAN_GPIO0      0   //
#define WLAN_GPIO13     WLAN_RTS
#define WLAN_GPIO15     WLAN_CTS
#define HAVE_ESP12E   1 // 0= not available / 1=available
#define BUFFER_SIZE 1024
#define SSID  "Marsaxlokk"      // change this to match your WiFi SSID
#define PASS  "Liam@3004"  // change this to match your WiFi password
#define PORT  "123"
#define NTPSERVER  "192.168.1.4"

const int timeZone = -4;  // Eastern DST (USA)
#define BUFFER_SIZE 1024


///////////////////////////////////////////////////////////////////////////////////
char buffer[BUFFER_SIZE], query[48];

byte binfind(char *str) {
  unsigned long t = millis();
  bool found = false;
  int i = 0, j = 0, len = strlen(str);
  char c;
  while (millis() < t + 5000) {
    if (Serial1.available()) {
      c = Serial1.read();
      if (c == str[i]) {
        i++;
        if (i == len) return true;
      } else i = 0;
    }
  }
  return found;
}


// By default we are looking for OK\r\n
char OKrn[] = "OK\r\n";

byte wait_for_esp_response(int timeout, char* term = OKrn) {
  unsigned long t = millis();
  bool found = false;
  int i = 0;
  int len = strlen(term);
  // wait for at most timeout milliseconds
  // or if OK\r\n is found
  while (millis() < t + timeout) {
    if (Serial1.available()) {
      buffer[i++] = Serial1.read();
      if (i >= len) {
        if (strncmp(buffer + i - len, term, len) == 0) {
          found = true;
          break;
        }
      }
    }
  }
  buffer[i] = 0;
  Serial.print(buffer);
  return found;
}
bool resetWLAN() {
#if HAVE_ESP12E

  Serial.println("INIT ESP12E");

  WLAN_SERIAL.begin(WLAN_SERIAL_BAUD);

  pinMode(WLAN_RESET, OUTPUT);
 

  
  digitalWrite(WLAN_ENABLE, LOW);

  //Reset ESP
  digitalWrite(WLAN_RESET, LOW);
  delay(15);
 
  digitalWrite(WLAN_RESET, HIGH);



  bool ret = WLAN_SERIAL.findUntil("ready", "");

 

  //Disable all used pins if no response from ESP
  if (!ret) {
    pinMode(WLAN_RESET, INPUT);
    pinMode(WLAN_ENABLE, INPUT);
    pinMode(WLAN_CTS, INPUT);
  }

  return ret;
#endif


}

/////////////////////
void setupWiFi() {

  // turn on echo
  Serial1.println("ATE1");
  wait_for_esp_response(1000);

  // set mode 1 (client)
  Serial1.println("AT+CWMODE=3");
  wait_for_esp_response(1000);

  // reset WiFi module
  Serial1.print("AT+RST\r\n");
  wait_for_esp_response(1500);

  //join AP
  Serial1.print("AT+CWJAP=\"");
  Serial1.print(SSID);
  Serial1.print("\",\"");
  Serial1.print(PASS);
  Serial1.println("\"");
  wait_for_esp_response(5000);

  //Create UDP ports
  Serial1.println("AT+CIPMUX=1");
  wait_for_esp_response(1000);

  String cmd = "AT+CIPSTART=4,\"UDP\",\"";
  cmd += NTPSERVER;
  cmd += "\",";
  cmd += PORT;
  cmd += ",4321,0";
  Serial1.println(cmd);
  wait_for_esp_response(1000);

  query[0] = 0x1B;    // NTP request
  Serial.println("UDP ready");
}



void setup()
{


  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(SDPRESENT, INPUT);

  tft.begin(RA8875_800x480);//init tft 
  delay(200);
  Wire1.begin();

  digitalWrite(LED3, HIGH);   // turn the LED on (HIGH is the voltage level)



  Serial.begin(9600);

  TS.begin(WAKE, INTRPT);                 // Startup sequence CONTROLER part TOUCH controller GSL1680

  delay(500);
  Serial1.println("AT+CIFSR");
  wait_for_esp_response(1000);

  ////// init Xbee and assign serial port 
  Serial2.begin(9600);
  xbee.setSerial(Serial2);
  ////

////init SD 
  if (SDPRESENT == HIGH) {


	  if (!SD.begin(SDCSPIN)) {

		  Serial.println("SD failed!");
		  return;
	  }
	  Serial.println("SD Card OK!");
  }
	  else {
		  Serial.println("SD Card NOT INSERTED !");
	  }

//////

  }



void loop(void) {
  unsigned long currentMillis = millis();
 
  if (digitalRead(INTRPT) == HIGH) { //if touched(true) detach isr
    digitalWrite(LED2, HIGH);   // turn the LED on (HIGH is the voltage level)
    GET_TOUCH_XY_VALUE ();
    delay(150);
    RESET_Temp_touch_values ();
   // delay(100);
    //cts.touched(false);
  }
  

  // wait for a second

  digitalWrite(LED2, LOW);    // turn the LED off by making the voltage LOW

  if (SCREEN_UPDATE == true) {


    switch (MENU_NR) {
      case 0:    // your hand is on the sensor
        Serial.println("TFT MENU 0 Needs update");
        TFT_MAIN_PANEL();
        break;
      case 1:    // your hand is close to the sensor
        Serial.println("ENTER TFT MENU SETTINGS");
        TFT_MENU_SETTINGS();
        break;
      case 2:    // your hand is a few inches from the sensor
        Serial.println("ENTER TFT LED SETTINGS");
       // TFT_MENU_LED();
        break;
      case 3:    // your hand is nowhere near the sensor
        Serial.println("ENTER TFT RGB CONFCH 1 ");
        TFT_MENU_RGB_01(true, 0,MENU_NR);
        break;
      case 4:    // your hand is a few inches from the sensor
		  Serial.println("ENTER TFT RGB CONFCH 2 ");
		  TFT_MENU_RGB_01(true, 0, MENU_NR);
        break;
      case 5:    // your hand is nowhere near the sensor
		  Serial.println("ENTER TFT RGB CONFCH 3 ");
		  TFT_MENU_RGB_01(true, 0, MENU_NR);
        break;
      case 6:    // your hand is nowhere near the sensor
		  Serial.println("ENTER TFT RGB CONFCH 4 ");
		  TFT_MENU_RGB_01(true, 0, MENU_NR);
        break;
      case 7:    // your hand is nowhere near the sensor

        Serial.println("ENTER TFT MENU ABOUT");
		update_label_values_from_int();

     TFT_MENU_ABOUT(true, 0, MENU_NR);
        //  Numeric_Keypad_TFT(100, 10);


        break;

	  case 8:    // your hand is nowhere near the sensor

		  Serial.println("ENTER TFT MENU ABOUT");
		  TFT_MENU_ABOUT(true, 0, MENU_NR);
		  //  Numeric_Keypad_TFT(100, 10);
		  break;
    }

	//RGB_Set(Channel1);
  }

 
}



