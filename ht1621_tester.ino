/**
  HT1261-based 7segment LCD display test program
  2015/09/26 morecat_lab

  X3msnake 2016/10/24 - Added TEST_PATTERN changed clear memory to fill memory in order to have a full lit display on initialization
 */

#include "Arduino.h"
#include "HT1621.h"

HT1621 ht(2,13,4,5); // data,wr,rd,cs

 //#define TS120
 //#define TS125
 //#define TS174
 //#define TS119
 //#define TS206

#define TEST_SEGMENT
#define TEST_PATTERN
// #define TEST_SMALL_SEGMENT

//// LCD 7segment character pattern
//#if defined(TS120) || defined(TS206)
//#define LARGE_NUM_DIGIT 9
//#define LARGE_NUM_START 6
//#define SMALL_NUM_DIGIT 2
//#define SMALL_NUM_START 2
//char pattern[] = {
//  0x5F, 0x50, 0x3D, 0x79, 0x72, 0x6B, 0x6F, 0x51,
//  0x7F, 0x7B, 0x77, 0x6E, 0x0F, 0x7C, 0x3F, 0x27 };
//#endif
//
//#if defined(TS125)
//#define LARGE_NUM_DIGIT 8
//#define LARGE_NUM_START 0
//#define SMALL_NUM_DIGIT 2
//#define SMALL_NUM_START 16
//char pattern[] = {
//  0xEB, 0x60, 0xC7, 0xE5, 0x6C, 0xAD, 0xAF, 0xE0,
//  0xEF, 0xED, 0xEE, 0x2F, 0x8B, 0x67, 0x8F, 0x8E };
//#endif
//
//#if defined(TS119) || defined(TS174)
//#define LARGE_NUM_DIGIT 7
//#define LARGE_NUM_START 2
//#define SMALL_NUM_DIGIT 1
//#define SMALL_NUM_START 0
//char pattern[] = {
//  0xAF, 0xA0, 0xCB, 0xE9, 0xE4, 0x6D, 0x6F, 0xA8,
//  0xEF, 0xED, 0xEE, 0x67, 0x0F, 0xE3, 0x4F, 0x4E };
//#endif
//
//void setNum(char adr, char num) {
//  ht.writeMem(adr, pattern[num] &0xf);
//  ht.writeMem(adr+1, pattern[num] >> 4);
//}
//
//// print large segment
//void printNum(long num) {
//  for (int i = 1 ; i <= LARGE_NUM_DIGIT ; i++) {
//    int adr = (LARGE_NUM_DIGIT - i) * 2 + LARGE_NUM_START;
//    setNum(adr, num % 10);
//    num /= 10;
//  }
//}
//
//// print small segment (if any)
//void printsNum(long num) {
//  for (int i = 1 ; i <= SMALL_NUM_DIGIT ; i++) {
//    int adr = (SMALL_NUM_DIGIT - i) * 2 + SMALL_NUM_START;
//    setNum(adr, num % 10);
//    num /= 10;
//  }
//}

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  ht.begin();
//  ht.sendCommand(HT1621::RC256K);
  ht.sendCommand(HT1621::BIAS_THIRD_4_COM);  // FOR TS119
//  ht.sendCommand(HT1621::BIAS_HALF_4_COM);
  ht.sendCommand(HT1621::SYS_EN);
  ht.sendCommand(HT1621::LCD_ON);

  // Fill RAM
  for (int i = 0 ; i < 32 ; i++) {
    ht.writeMem(i, 0xF);
  }


#ifdef TEST_SEGMENT
  // test segment
  for (int i = 0 ; i < 32 ; i++) {
    for (int j = 0 ; j <= 4 ; j++) {
      ht.writeMem(i, 1<<j);
      
      Serial.println("i="+String(i)+" j="+String(j));
      delay(100);
    }
  } 
#endif

#ifdef TEST_PATTERN
// Test Pattern
    for (int j = 0 ; j <= 15 ; j++) {
      for (int i = 0 ; i < 32 ; i++) {
    ht.writeMem(i, j);
    delay(100);
    }
}
#endif

  // Fill RAM
  for (int i = 0 ; i < 32 ; i++) {
    ht.writeMem(i, 0xF);
    delay(500);
  }

//  // test count
//  for (long i = 0 ; i < 1000000 ; i++) {
//    printNum(i);
//#ifdef TEST_SMALL_SEGMENT
//    printsNum(i % 100);
//#endif
//    delay(100);
//  }
}


void loop()
{}
