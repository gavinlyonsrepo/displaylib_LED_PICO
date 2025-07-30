/*!
	@file main.cpp
	@author Gavin Lyons
	@brief A demo file library for TM1637 module Works on Model 4 (tm1637 Model 4 semi-colon)
			Carries out series of tests demonstrating library.
	@details
			setSegments function those not touch the ASCII font table and takes raw data
			Segment data used by other functions is is from the ASCII table in font file 
			gfedcba (seven segments ) In  gfedcba representation,
			a byte value of 0x06 would turn on segments "c" and "b", which would display a "1".
			https://en.wikipedia.org/wiki/Seven-segment_display
	@note
			Only tested on 4 digit + semi colon model, 
	@test
		-# Test 1 setSegments and encode digit functions
		-# Test 2 decimal number testing
		-# Test 3 string display
		-# Test 4 Brightness & on/off
*/

// === Libraries ===

#include "pico/stdlib.h"
#include <cstdio>
#include "displaylib_LED_PICO/tm1637.hpp" 

///@cond

// === Setup ===

// Timing display intervals
// For test timing setup
#define  myTestDelay  5000
#define  myTestDelay1 1000
// Misc
const uint StatusLEDPin = 25; // PICO on_board Status LED

// tm1637 setup
#define  CLOCK_TM       3  // clock = GPIO connected to clock line of module
#define  DIO_TM         4  // data = GPIO connected to data line of module
#define  COMM_DELAY_US  75 // Internal Serial Communications delay in uS
#define  NUM_OF_DIGITS  4  // number of digits in display.
#define  SEMI_COLON_ON (0x40)

// Constructor object 
TM1637plus_modelX myTM(CLOCK_TM, DIO_TM, COMM_DELAY_US, NUM_OF_DIGITS);

// === Function Prototypes ===
void Setup(void);
void Test1(void);
void Test2(void);
void Test3(void);
void Test4(void);
void Test5(void);
void EndTests(void);

// === Main ====
int main()
{
	Setup();
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	EndTests();
	return 0;
}
// === End  of main ===


// === Function Space ===
// Function to setup 
void Setup(void)
{
	busy_wait_ms(100);
	// Initialize Status LED pin
	gpio_init(StatusLEDPin);
	gpio_set_dir(StatusLEDPin, GPIO_OUT);
	gpio_put(StatusLEDPin, true);
	// Init USB output 38400 baud (optional)
	stdio_init_all();
	//init tm1637
	myTM.displayBegin();
	myTM.setBrightness(0x07, true);
	busy_wait_ms(myTestDelay1);
	printf("Test Begin :: TM1637\r\n");
	gpio_put(StatusLEDPin, false);
}

void EndTests(void)
{
	myTM.displayClear();
	myTM.setBrightness(0x00, false);
	myTM.displayClose();
	printf("Test End\r\n");
}

void Test1(void)
{
	printf("Test 1A: SetSegments 1 2 3 4 \r\n");
	uint8_t data[] = {0x06, 0x5B, 0x4F, 0x66 };
	myTM.setSegments(data,4,0);
	busy_wait_ms(myTestDelay);

	printf("Test 1B: encode digits  5 6 7 8 \r\n");
	// Selectively set different digits
	data[0] = myTM.encodeCharacter('5');
	data[1] = myTM.encodeCharacter('6');
	data[2] = myTM.encodeCharacter('7');
	data[3] = myTM.encodeCharacter('8');
	myTM.setSegments(data,4,0);
	busy_wait_ms(myTestDelay);

	printf("Test 1C: SetSegments H E L P \r\n");
	data[0] = 0x76;
	data[1] = 0x79;
	data[2] = 0x38;
	data[3] = 0x73;
	myTM.setSegments(data,4,0);
	busy_wait_ms(myTestDelay);

}

void Test2(void)
{

	printf("Test 2A: decimal number leading zeros off\r\n");
	myTM.DisplayDecimal(1, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimal(23, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimal(784, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimal(6281, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);

	printf("Test 2B: decimal number leading zeros on\r\n");
	myTM.DisplayDecimal(1, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimal(23, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimal(784, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimal(6281, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);

	printf("Test 2C: decimal number leading zeros off,  with semi:colon on \r\n");
	myTM.DisplayDecimalwDot(1, SEMI_COLON_ON, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimalwDot(23, SEMI_COLON_ON, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimalwDot(784, SEMI_COLON_ON, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimalwDot(6281, SEMI_COLON_ON, false, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);

	printf("Test 2D: decimal number leading zeros on ,  with semi:colon on\r\n");
	myTM.DisplayDecimalwDot(1, SEMI_COLON_ON, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimalwDot(23, SEMI_COLON_ON, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimalwDot(784, SEMI_COLON_ON, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.DisplayDecimalwDot(6281, SEMI_COLON_ON, true, NUM_OF_DIGITS, 0);
	busy_wait_ms(myTestDelay);
	myTM.displayClear();
}

void Test3(void)
{
	printf("Test 3A: string 3 digit\r\n");
	char number[] = "-23";
	myTM.DisplayString(number, 0,  3, 1); // Display " -23" starting at position 1
	busy_wait_ms(myTestDelay);

	printf("Test 3B: string 2 digit + semi colon\r\n");
	char min[] = "07";
	char sec[] = "53";
	myTM.DisplayString(min, SEMI_COLON_ON, 2, 0); // Display "07" starting at position 0
	myTM.DisplayString(sec, SEMI_COLON_ON, 2, 2); // Display "53" starting at position 2
	busy_wait_ms(myTestDelay);

	printf("Test 3C: string 4 digit\r\n");
	char string[] = "OPEN";
	myTM.DisplayString(string, 0, NUM_OF_DIGITS, 0); // Display "OPEN" starting at position 0
	busy_wait_ms(myTestDelay);
	myTM.displayClear();

	printf("Test 3D: string 1 digit\r\n");
	char Astring[] = "2";
	myTM.DisplayString(Astring, 0,  1, 3); // Display "   2" starting at position 4
	busy_wait_ms(myTestDelay);

}

void Test4(void)
{
	printf("Test 4A: brightness\r\n");
	uint8_t i = 0;
	uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF };  // 8888
	for(i = 0; i < 7; i++) 
	{
		myTM.setBrightness(i, true);
		myTM.setSegments(data,4,0);
		busy_wait_ms(myTestDelay1);
	}
	
	printf("Test 4B: on/off\r\n");
	//off
	myTM.setBrightness(7, false);
	myTM.setSegments(data,4,0);
	busy_wait_ms(myTestDelay);
	//on
	myTM.setBrightness(7, true);
	myTM.setSegments(data,4,0);
	busy_wait_ms(myTestDelay1);
	//off
	myTM.setBrightness(7, false);
	myTM.setSegments(data,4,0);
	busy_wait_ms(myTestDelay1);
}

void Test5(void)
{
	printf("Test 5: Error check, except errors and warnings\r\n");
	myTM.setBrightness(7, true);
	// 1. Null ptr
	if(myTM.DisplayString(nullptr, 0, NUM_OF_DIGITS, 0) == -2)
	{
		printf("Test 5A: PASSED\n");
	}else{
		printf("Test 5A: FAILED\n");
	}
	busy_wait_ms(myTestDelay1);
	// 2. Too many digits
	char string[] = "OPEN";
	if(myTM.DisplayString(string, 0,  NUM_OF_DIGITS+1, 0) == -3)
	{
		printf("Test 5B: PASSED\n");
	}else{
		printf("Test 5B: FAILED\n");
	}
	busy_wait_ms(myTestDelay1);
	// 3. Too few digits
	if(myTM.DisplayString(string, 0,  NUM_OF_DIGITS-1, 0) == -3)
	{
		printf("Test 5C: PASSED\n");
	}else{
		printf("Test 5C: FAILED\n");
	}
	busy_wait_ms(myTestDelay1);
	// 4. String to long
	char string1[] = "OPEN1";
	if(myTM.DisplayString(string1, 0, NUM_OF_DIGITS, 0) == -3)
	{
		printf("Test 5D: PASSED\n");
	}else{
		printf("Test 5D: FAILED\n");
	}
	busy_wait_ms(myTestDelay1);

	// Test 5E
	// Edge case ASCII range, {} outside range of font, should be replaced by zero with warning
	// Should display "z 00" with two warnings, z and ' ' are edges cases.
	char string2[] = "z {}";
	myTM.DisplayString(string2, 0, NUM_OF_DIGITS, 0); 
	busy_wait_ms(myTestDelay);
}
///@endcond
