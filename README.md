Arduino Library for 32x4 LCDs via software SPI (or SPI like communication)

With Test files to cycle all segments and reverse video here > https://youtu.be/1nOSXn8DHw4

**WHY:**

The HT1621 is in many old lcd appliances and can be directly adressed to write to old salvaged lcds that are driven by this chip.
It has an integrated 2Khz/4Khz Buzzer and any 48-pi SSOP with 1621 on it's name is probably a a HT.
You can buy the chips from ebay from less than 20.cents a piece.
*ebay search:* goo.gl/qw28xx

**WHAT:**

The HT1621 is a 128 pattern (32x4), memory mapping, and multi-function LCD driver. 
The S/W configuration feature of the HT1621 makes it suitable for multiple LCD applications including LCD modules and display subsystems.
Only three or four lines are required for the interface between the host controller and the HT1621.
The HT1621 contains a power down command to reduce power consumption.
Operating voltage: 2.4V~5.2V

*datasheet:* http://www.seeedstudio.com/document/HT1621.pdf

Note: RD pin is optional


**HOW:**

The idea is to give to create and collect the info, libraries and boards to allow anyone to reverse and reuse old salvaged LCDs either ones that already have the chip as a driver or other ones that can be hacked to use with this chip 

---
**TODO:** 
- Make OpenSourceVersion of a HT1621 Breakoutboard
- Find the best method to reverse the codes for unknown LCDs
- Create documenta page for collecting this knowlage
- Test the lib in a OpenDay @ the Lab, dedicated to arduino display hacking and writing 

---
**REFERENCE LINKS**
(HT1621 BreakoutBoard) http://blog.ankitdaf.com/ht1621b-display-controller-breakout-board/ 
http://arduino.ru/forum/apparatnye-voprosy/podklyuchenie-i-ispolzovanie-zhk-segmentnogo-indikatora

--- 
**Original Source: https://github.com/marc-gist/HT1621**
Mostly from: macduino.blogspot.com, thanks!
modified to add print like statments for easy digit display
