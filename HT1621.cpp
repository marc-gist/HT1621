/**
 * \file HT1621.cpp
 * \brief Implementation of a class for dealing with the Holtek HT1621 chip.
 * \author Enrico Formenti
 * \date 31 january 2015
 * \version 1.0
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 *  <br><br>
 *  See macduino.blogspot.com for more details.
 *
 */

#include "HT1621.h"

byte setDigits( long number, byte *d, byte len ) // returns # of digits
{
  static byte  idx; // static stays

  long  fullrange = number;

  if ( fullrange < 0L )
  {
    fullrange *= -1L;
  }

  for ( idx = 0; idx < len; idx++ )
  {
    d[ idx ] = 0;
  }

  //                        Here is the actual conversion to array
  idx = 0;
  while (( fullrange ) && ( idx < len ))
  {
    d[ idx++ ] = fullrange % 10;
    fullrange /= 10;
  }
  //                        Finished actual conversion to array

  if( number < 0 && idx < len ) {
    d[ idx++ ] = 11;
  }


  return idx;
}

void HT1621::clear(int places) 
{
    for (uint8_t i = 0; i < places; i++)
        write(i, 0);
}

void HT1621::flush() 
{
    clear();
}

void HT1621::begin()
{
    pinMode(_DATA_pin, OUTPUT);
    pinMode(_RW_pin, OUTPUT);
    pinMode(_CS_pin, OUTPUT);
 
    digitalWrite(_CS_pin, HIGH);
    digitalWrite(_RW_pin, HIGH);
    digitalWrite(_DATA_pin, HIGH);

#ifndef __HT1621_READ
    register uint8_t i;
    
    for(i=0; i<16; i++)
        ram[i] = 0;
#endif

    delay(10);
    clear();
    
}

// OCIO !!!
// nell'esempio dopo ogni write viene dato un delay
// di 20 microsecondi...
void HT1621::writeBits(uint8_t data, uint8_t cnt)
{
    register uint8_t i;

    for(i=0;i<cnt;i++,data <<=1)
    {
        digitalWrite(_RW_pin, LOW);
        delayMicroseconds(20);
        digitalWrite(_DATA_pin, data&0x80 ? HIGH : LOW);
        delayMicroseconds(20);
        digitalWrite(_RW_pin, HIGH);
        delayMicroseconds(20);
    }
}

#ifdef __HT1621_READ

uint8_t HT1621::readBits(uint8_t cnt)
{
    uint8_t data, i, state;
    
    
    pinMode(_DATA_pin, INPUT);
    
    for(i=0, data=0; i<cnt; data <<= 1, i++) {
        digitalWrite(_RW_pin, LOW);
        delayMicroseconds(20);
        data |= (digitalRead(_DATA_pin) == HIGH);
        digitalWrite(_RW_pin, HIGH);
        delayMicroseconds(20);
    }
    
    pinMode(_DATA_pin, OUTPUT);
    
    return data;
}

#endif

void HT1621::sendCommand(uint8_t cmd, bool first, bool last)
{
    if (first) {
        TAKE_CS();
        writeBits(COMMAND_MODE, 4);
    }
    
    writeBits(cmd, 8);
    
    if (last)
        RELEASE_CS();
}

void HT1621::write(uint8_t address, uint8_t data)
{
    TAKE_CS();
    
    writeBits(WRITE_MODE, 3);
    writeBits(address<<3, 6); // 6 is because max address is 128
    writeBits(data, 8);
#ifndef __HT1621_READ
    ram[address] = data;
#endif
    
    RELEASE_CS();
}
void HT1621::writeChar(uint8_t address, uint8_t c, bool decimal)
{
    TAKE_CS();
    if( decimal )
        write(address, charMap[c]|DECIMAL);
    else
        write(address, charMap[c]);
    RELEASE_CS();
}

void HT1621::write(uint8_t address, uint8_t data, uint8_t cnt)
{
    register uint8_t i;
    
    TAKE_CS();
    
    writeBits(WRITE_MODE, 3);
    writeBits(address<<3, 6);
    for (i = 0; i < cnt; i++) {
        writeBits(data, 8);
#ifndef __HT1621_READ
        ram[i] = data;
#endif
    }
    
    RELEASE_CS();
}

void HT1621::write(uint8_t address, uint8_t *data, uint8_t cnt)
{
    register uint8_t i;
    
    TAKE_CS();
    
    writeBits(WRITE_MODE, 3);
    writeBits(address<<3, 6);
    for (i = 0; i < cnt; i++) {
        writeBits(data[i], 8);
#ifndef __HT1621_READ
        ram[i] = data[i];
#endif
    }
    
    RELEASE_CS();
}

#ifdef __HT1621_READ

uint8_t HT1621::read(uint8_t address)
{
    uint8_t data;
    
    TAKE_CS();
    
    writeBits(READ_MODE, 3);
    writeBits(address<<3, 6);
    data = readBits(8);
    
    RELEASE_CS();
    
    return data;
}

void HT1621::read(uint8_t address, uint8_t *data, uint8_t cnt)
{
    register uint8_t i;
    
    TAKE_CS();
    
    writeBits(READ_MODE, 3);
    writeBits(address<<3, 6);
    for (i = 0; i < cnt; i++)
        data[i] = readBits(8);
    
    RELEASE_CS();
}

#else

uint8_t HT1621::read(uint8_t address)
{
    return ram[address];
}

void HT1621::read(uint8_t address, uint8_t *data, uint8_t cnt)
{
    register uint8_t i;
    
    for (i = 0; i < cnt; i++)
        data[i] = ram[address+i];
}

void HT1621::printNumber(long number, int places, int dec, bool flushdisplay)
{
  if ( flushdisplay ) clear();
  byte d[ places ];
  byte converted;
  int decpoint = places - dec - 1;
  int len = setDigits( number, d, places );
  int pos = places - 1; //-1 as we start at index LEN-1 (end)
  for (int i = 0; i < len; i++) {
    bool addDec = false;
    if ( pos == decpoint ) addDec = true;
    writeChar(pos, d[i], addDec);
    pos--;
    if ( pos < 0 ) break;
  }
}

void HT1621::printFloat(double number, int places, int decimalplaces, bool flushdisplay) 
{
    long num = (long)(number * pow(10, decimalplaces));
    printNumber(num, places, decimalplaces, flushdisplay);
}


#endif