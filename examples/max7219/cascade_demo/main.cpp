/*!
	@file main.cpp
	@author Gavin Lyons
	@brief A demo file library for Max7219 seven segment displays
			Shows simple example with two cascades displays
			Hardware SPI Project Name: Display_Lib_RPI
	
	@note NOT fully tested as only one display available
	@test
		-# Test 410 Cascade demonstration 
*/

// Libraries 
#include <cstdio> // Used for printf
#include <cstdlib> //exit function
#include "displaylib_LED_PICO/max7219.hpp" 

/// @cond

// Delays for testing
#define TEST_DELAY5 5000
#define TEST_DELAY2 2000
#define TEST_DELAY1 1000

// *** USER OPTION SPI SELECTION ***
#define hardwareSPI //hardware SPI , comment for software SPI
// ***

uint8_t totalDisplays = 2; // Total number of displays in cascade

#ifdef hardwareSPI // Hardware SPI setup
	int8_t SDIN = 19; 
	int8_t SCLK = 18; 
	int8_t CS   = 2 ;  
	uint32_t SCLK_FREQ =  8000 ; // Spi freq in KiloHertz , 1000 = 1Mhz
	// Constructor object 
	MAX7219plus_model5 myMAX(SCLK, CS, SDIN , SCLK_FREQ, spi0, totalDisplays);
#else // Software SPI setup
	int8_t SDIN = 4; 
	int8_t SCLK = 3; 
	int8_t CS   = 2 ;  
	uint16_t CommDelay = 0; //uS software SPI delay.
	// Constructor object 
	MAX7219plus_model5 myMAX(SCLK, CS,SDIN, CommDelay, totalDisplays);
#endif

// Main loop
int main() 
{
	// Init USB output 38400 baud (optional, test messages and any errors)
	stdio_init_all();
	busy_wait_ms(TEST_DELAY1);
	printf("Test Begin demo\r\n");

	// Some test data defined
	char teststr1[] = "Display1";
	char teststr2[] = "Display2";
	
	// Init the displays
	// -Init Display one 
	myMAX.SetCurrentDisplayNumber(1);
	myMAX.InitDisplay(myMAX.ScanEightDigit, myMAX.DecodeModeNone);
	myMAX.ClearDisplay();
	// -Init Display Two
	myMAX.SetCurrentDisplayNumber(2);
	myMAX.InitDisplay(myMAX.ScanEightDigit, myMAX.DecodeModeNone);
	myMAX.ClearDisplay();

	// Write to Display one 
	myMAX.SetCurrentDisplayNumber(1);
	printf("Display 1\r\n");
	myMAX.DisplayText(teststr1, myMAX.AlignRight);
	busy_wait_ms(5000);
	
	// Write to Display Two 
	myMAX.SetCurrentDisplayNumber(2);
	printf("Display 2\r\n");
	myMAX.DisplayText(teststr2, myMAX.AlignRight);
	busy_wait_ms(5000);
	
	// Write to Display one again
	myMAX.SetCurrentDisplayNumber(1);
	printf("Display 1 again, 111\r\n");
	myMAX.DisplayIntNum(111, myMAX.AlignRight);
	busy_wait_ms(5000);

	// Write to Display two again
	myMAX.SetCurrentDisplayNumber(2);
	printf("Display 2 again, 222\r\n");
	myMAX.DisplayIntNum(222, myMAX.AlignRight);
	busy_wait_ms(5000);
	
	// Clear the displays 
	printf("Clear the displays\r\n");
	// -Clear Display one 
	myMAX.SetCurrentDisplayNumber(1);
	myMAX.ClearDisplay();
	busy_wait_ms(2500);
	// -Clear DisplayTwo 
	myMAX.SetCurrentDisplayNumber(2);
	myMAX.ClearDisplay();
	busy_wait_ms(500);
	
	// End operations
	myMAX.DisplayEndOperations();
	printf("Test End\r\n");
	return 0;
} 
// End of main

/// @endcond
