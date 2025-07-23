/*!
	@file main.cpp
	@author Gavin Lyons
	@brief A demo file library for Max7219 seven segment displays
		Carries out tests on BCD decode mode 3. BCD mode uses the built in font Code B
		this font has BCD code B (0-9, E, H, L, P, and -) 
		Hardware SPI , The ASCII font is NOT referenced and can be discarded when using this mode
		to save memory 
	@details See USER OPTION SPI SELECTION , comment out define hardwareSPI for software SPI.
	@test
		-# Test 1000 BCD character
		-# Test 1001 BCD string
*/

// Libraries 
#include <cstdio> // Used for printf
#include <cstdlib> //exit function
#include "displaylib_LED_PICO/max7219.hpp" 

/// @cond

// *** USER OPTION SPI SELECTION ***
#define hardwareSPI //hardware SPI , comment for software SPI
// ***
uint8_t totalDisplays = 1; // Total number of displays in cascade

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

// Function Prototypes
void Setup(void);
void myTest(void);
void EndTest(void);

// Main loop
int main() 
{
	Setup();
	myTest();
	EndTest();
	return 0;
}
// End of main

// Function Space

// Setup test
void Setup(void)
{
	printf("Test Begin BCD\r\n");
	myMAX.InitDisplay(myMAX.ScanEightDigit, myMAX.DecodeModeBCDThree);
	myMAX.ClearDisplay();
}

// Clean up before exit
void EndTest(void)
{
	myMAX.DisplayEndOperations();
	printf("Test End\r\n");
}

void myTest(void)
{
	// Test BCD Char
	myMAX.DisplayBCDChar(7, myMAX.CodeBFontH); // Digit 7 LHS of display
	myMAX.DisplayBCDChar(6, myMAX.CodeBFontE);
	myMAX.DisplayBCDChar(5, myMAX.CodeBFontL);
	myMAX.DisplayBCDChar(4, myMAX.CodeBFontP);
	myMAX.DisplayBCDChar(3, myMAX.CodeBFontSpace);
	myMAX.DisplayBCDChar(2, myMAX.CodeBFontFour);
	myMAX.DisplayBCDChar(1, myMAX.CodeBFontDash);
	myMAX.DisplayBCDChar(0, myMAX.CodeBFontOne); // Digit 0 RHS
	busy_wait_ms(5000);
	myMAX.ClearDisplay();
	
	// Test BCD string 
	char teststring1[] = "PH  3-14";
	myMAX.DisplayBCDText(teststring1);
	busy_wait_ms(5000);
	myMAX.ClearDisplay();
}

/// @endcond
