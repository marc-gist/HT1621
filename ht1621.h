/* HT1621 - Holtek RAM Mapping 32x4 LCD Controller */
#ifndef HT1621_H
#define HT1621_H

#include <inttypes.h>

class HT1621 {
public:
    enum {
        SYS_DIS   = 0b00000000,
        SYS_EN    = 0b00000001,
        LCD_OFF   = 0b00000010,
        LCD_ON    = 0b00000011,
        TIMER_DIS = 0b00000100,
        WDT_DIS   = 0b00000101,
        TIMER_EN  = 0b00000110,
        WDT_EN    = 0b00000111,
        TONE_OFF  = 0b00001000,
        TONE_ON   = 0b00001001,
        
        //Set bias to 1/2 or 1/3 cycle
        //Set to 2,3 or 4 connected COM lines
        BIAS_HALF_2_COM  = 0b00100000,
        BIAS_HALF_3_COM  = 0b00100100,
        BIAS_HALF_4_COM  = 0b00101000,
        BIAS_THIRD_2_COM = 0b00100001,
        BIAS_THIRD_3_COM = 0b00100101,
        BIAS_THIRD_4_COM = 0b00101001,
        
        //Don't use
        TEST_ON   = 0b11100000,
        TEST_OFF  = 0b11100011
    } Commands;

    HT1621(uint8_t data, uint8_t wr, uint8_t rd, uint8_t cs) : 
        data_pin(data), wr_pin(wr), rd_pin(rd), cs_pin(cs) {}

    bool begin();

    void sendCommand(uint8_t cmd, bool first = true, bool last = true);

    void write(uint8_t address, uint8_t *data, uint8_t cnt);
    void read(uint8_t address, uint8_t *data, uint8_t cnt);

    void writeMem(uint8_t address, uint8_t data);
    uint8_t readMem(uint8_t address);

    void memset(uint8_t address, uint8_t data, uint8_t cnt);

private:
    void writeBits(uint8_t data, uint8_t cnt);
    uint8_t readBits(uint8_t cnt);

    inline void initControlBus();
    inline bool testMem();
    
    uint8_t data_pin;
    uint8_t wr_pin;
    uint8_t rd_pin;
    uint8_t cs_pin;
};

#endif //HT1621_H
