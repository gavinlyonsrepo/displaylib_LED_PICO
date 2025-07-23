# TM1637 README

## Table of contents

  * [Overview](#overview)
  * [Hardware](#hardware)
  * [Software](#software)

## Overview

* Description: A Raspberry pi PICO SDK C++ library to drive TM1637 LED seven segment modules.

## Hardware

Connections to RPI:

1. GPIO  = CLK  = Clock
2. GPIO = DIO = Data input / output
3. VCC 3.3V (or 5V see Note)
4. GND


NOTE : If VCC is set to 5V, level shift GPIO to 3.3V or damage could result.

This library is tested on two variant of the TM1637. 

1. TM1637 (model 4) which has 4 digits with centred semi-colon.
2. TM1637 (model 6) which has 4 digits and decimal points for each digit.



Model 4: 

[![ model4 ](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/tm1637.jpg)](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/tm1637.jpg)

Model 6:

[![ model6 ](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/tm1637a.png)](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/tm1637a.png)

## Software

There is one example file. A table in file 'seven_segment_font_data.hpp' provides ASCII to Seven Segment data.
. gfedcba (seven segments ) In the gfedcba representation,
a byte value of 0x06 would turn on segments "c" and "b",
which would display a "1". https://en.wikipedia.org/wiki/Seven-segment_display

### Comms delay

The Serial Communications delay used is set by default to 75 uS,  user can change this in constructor parameters.

