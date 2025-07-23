# MAX7219 7 Segment Readme

[![ max image ](https://github.com/gavinlyonsrepo/MAX7219_7SEG_RPI/blob/main/extra/image/max.jpg)](https://github.com/gavinlyonsrepo/MAX7219_7SEG_RPI/blob/main/extra/image/max.jpg)

## Table of contents

  * [Overview](#overview)
  * [Software](#software)
  * [Hardware](#hardware)
  * [Notes and Issues](#notes-and-issues)
	  * [Cascaded Displays](#cascaded-displays)


## Overview

* Name: MAX7219 
* Author: Gavin Lyons.

* Description:

A library to display data on MAX7219 seven segment module.
Raspberry Pi PICO SDK  C++ library.
Hardware or software SPI, Shutdown mode, test mode and Brightness control supported.

## Software

### File system

Example files list:

| List No | Example file name | Description | 
| ------ | ------ | ------ |
| 1 | src/tests/main.cpp | test sequence |
| 2 | src/bcdmode/main.cpp | Shows use of BCD built-in font |
| 3 | src/cascade_demo/main.cpp | simple Demo showing use of cascaded displays |

There are three examples files(main.cpp) in example folder, To select the one that builds 
comment it's path in, in the CMakeLists.txt file, section add_executable section.
Comment one path in and one ONLY.

## Hardware

To select between hardware and software SPI in examples files see USER OPTION SPI SELECTION section.

### Software SPI

For Software SPI Pick any GPIO you want.
CommDelay variable (uS Communication delay). This is a communications delay used in Software SPI clocking,
default 0.

### Hardware SPI

For Hardware SPI the user must use fixed SPI pins for clock and data, user can choice any GPIO 
for chip select. The clock and MOSI lines will be linked to the chosen interface i.e spi0, spi1 etc
The datasheet says it's a 10 MHZ device, In hardware SPI user can pick SPI bus speed.

### Connections to PICO:

| Pin no  | PICO SW SPI | PICO HW SPIX | Pin function |
| --- | --- | --- | --- |
| 1 | any GPIO output | spiX CLK |  CLK = Clock |
| 2 | any GPIO output | any GPIO output | CS = Chip select |
| 3 | any GPIO output | spiX TX |  DIN = Data in |


VCC 5V in theory but works at 3.3V in testing, albeit with a dimmer display.
Logic seems to work fine at 3.3V , It safe as it is all one way communications
From PICO to MAX. User can adjust brightness from 0x00 to 0x0F by default it is 0x08. 0x0F being brightest

## Notes and Issues

### Cascaded Displays

Support for Cascaded Displays is shown in one of examples files. Multiple displays can be connected together. Cascaded Displays are displays connected together.  CS and CLK lines are tied together.
The DIN line is connected to the first display only. The DOUT line of the first display is then connected to the DIN line of the next display and so on. Diagram below shows how to connect two displays together. Specify number of displays in constructor parameter.

![img Cascade](https://github.com/gavinlyonsrepo/displaylib_LED_PICO/blob/main/extra/image/max7219cascade.png)
