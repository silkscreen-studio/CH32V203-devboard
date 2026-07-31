/*
 *   CH32V203 devboard demo code | Silkscreen Studio | by C.G. | https://github.com/silkscreen-studio/CH32V203-devboard
 *   Charlieplexed 7x8 LED matrix
 *
 *   After creating a new Mounriver Studio project and selecting the chip 'CH32V203C8U', the following main.c file can be replaced with the following code (in User>main.c)
 *   as the devboard doesn't comes with an external oscillator, the file 'system_ch32v00x.c has to be modified, changing the code as below:
 *            //#define SYSCLK_FREQ_HSE    HSE_VALUE
 *            //#define SYSCLK_FREQ_48MHz_HSE  48000000
 *            //#define SYSCLK_FREQ_56MHz_HSE  56000000
 *            //#define SYSCLK_FREQ_72MHz_HSE  72000000
 *            //#define SYSCLK_FREQ_96MHz_HSE  96000000             Default line that should be commented
 *            //#define SYSCLK_FREQ_120MHz_HSE  120000000
 *            //#define SYSCLK_FREQ_144MHz_HSE  144000000
 *            //#define SYSCLK_FREQ_HSI    HSI_VALUE
 *            //#define SYSCLK_FREQ_48MHz_HSI  48000000
 *            //#define SYSCLK_FREQ_56MHz_HSI  56000000
 *            //#define SYSCLK_FREQ_72MHz_HSI  72000000
 *            //#define SYSCLK_FREQ_96MHz_HSI  96000000
 *            //#define SYSCLK_FREQ_120MHz_HSI  120000000
 *            #define SYSCLK_FREQ_144MHz_HSI  144000000           // This line can be uncommented (or any other HSI line)
 */

#include "debug.h"


uint32_t DELAY_FRAME = 1000000;  // 1000 ms
uint8_t stateLED = 0;

typedef struct {
    GPIO_TypeDef *PORT;
    uint16_t PIN;
} PinSetup;

PinSetup pinMap[] = {

    {GPIOB, GPIO_Pin_5 }, //  0  L1
    {GPIOA, GPIO_Pin_15}, //  1  L2
    {GPIOB, GPIO_Pin_12}, //  2  L3
    {GPIOB, GPIO_Pin_8 }, //  3  L4
    {GPIOA, GPIO_Pin_14}, //  4   L5
    {GPIOB, GPIO_Pin_9 }, //  5   L6
    {GPIOB, GPIO_Pin_3 }, //  6   L7
    {GPIOB, GPIO_Pin_4 }, //  7   L8

    {GPIOB, GPIO_Pin_15}, // 8   FPC 1
    {GPIOB, GPIO_Pin_14}, // 9    .
    {GPIOB, GPIO_Pin_13}, // 10   .
    {GPIOB, GPIO_Pin_11}, // 11
    {GPIOB, GPIO_Pin_10}, // 12
    {GPIOA, GPIO_Pin_3 }, // 13
    {GPIOA, GPIO_Pin_2 }, // 14   .
    {GPIOA, GPIO_Pin_1 }, // 15   .
    {GPIOA, GPIO_Pin_0 }, // 16  FPC 9

    {GPIOC, GPIO_Pin_13}, // 17
    {GPIOC, GPIO_Pin_14}, // 18
    {GPIOC, GPIO_Pin_15}, // 19
    {GPIOD, GPIO_Pin_1 }, // 20
    {GPIOA, GPIO_Pin_4 }, // 21
    {GPIOA, GPIO_Pin_5 }, // 22
    {GPIOA, GPIO_Pin_6 }, // 23
    {GPIOA, GPIO_Pin_7 }, // 24
    {GPIOB, GPIO_Pin_2 }, // 25
    {GPIOB, GPIO_Pin_0 }, // 21
    {GPIOB, GPIO_Pin_1 }, // 22
    {GPIOB, GPIO_Pin_7 }, // 23
    {GPIOB, GPIO_Pin_6 }, // 24
    {GPIOA, GPIO_Pin_8 }, // 25
    {GPIOA, GPIO_Pin_9 }, // 26
    {GPIOA, GPIO_Pin_10}, // 27
};

// Any LED matrix pattern can be displayed with 7 bytes arrays. It could also be updated from SPI/I2C/USB where I packet for 1 frame needs 7 bytes.

static const uint8_t FULL_ON[7] = {
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
};

static const uint8_t CHECKERBOARD[7] = {
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
};

static const uint8_t FULL_OFF[7] = {
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

static const uint8_t SMILEY[7] = {
    0b00000000,
    0b01100110,
    0b01100110,
    0b00000000,
    0b01000010,
    0b00111100,
    0b00000000,
};

static const uint8_t CHECKMARK[7] = {
    0b00000000,
    0b00000011,
    0b00000110,
    0b11001100,
    0b01111000,
    0b01110000,
    0b00100000,
};

uint8_t slidingLine[7] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
};

void pinMode (uint8_t pin_number, GPIOMode_TypeDef mode) {
    if (pin_number > 27)
        return;

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = pinMap[pin_number].PIN;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (pinMap[pin_number].PORT, &GPIO_InitStructure);
}

void digitalWrite (uint8_t pin_number, uint8_t bit_state) {
    if (pin_number > 27)
        return;
    if (bit_state == 1) {
        GPIO_SetBits (pinMap[pin_number].PORT, pinMap[pin_number].PIN);
    } else {
        GPIO_ResetBits (pinMap[pin_number].PORT, pinMap[pin_number].PIN);
    }
}

uint8_t digitalRead (uint8_t pin_number) {
    if (pin_number > 27)
        return 0;
    return GPIO_ReadInputDataBit (pinMap[pin_number].PORT, pinMap[pin_number].PIN);
}

void updateDisplay (const uint8_t LED_Matrix[7]) {

    for (uint8_t c = 0; c < 8; c++) {
        pinMode (c, GPIO_Mode_Out_PP);
        digitalWrite (c, 0);

        for (uint8_t l = 0; l < 8; l++) {

            if (l > c) {
                uint8_t bit = (LED_Matrix[l - 1] >> (8 - c - 1)) & 0b0000001;
                if (bit == 1) {
                    pinMode (l, GPIO_Mode_Out_PP);
                    digitalWrite (l, 1);
                }
            }

            if (l < c) {
                uint8_t bit = (LED_Matrix[l] >> (8 - c - 1)) & 0b0000001;
                if (bit == 1) {
                    pinMode (l, GPIO_Mode_Out_PP);
                    digitalWrite (l, 1);
                }
            }
        }

        Delay_Us (DELAY_FRAME);
        for (uint8_t pin = 0; pin < 8; pin++) {
            pinMode (pin, GPIO_Mode_IN_FLOATING);
        }
    }
}

int main (void) {
    SystemCoreClockUpdate();
    Delay_Init();
    Delay_Ms (4000);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig (GPIO_Remap_SWJ_Disable, ENABLE);
    Delay_Ms (600);
    pinMode (0, GPIO_Mode_IN_FLOATING);
    pinMode (1, GPIO_Mode_IN_FLOATING);
    pinMode (2, GPIO_Mode_IN_FLOATING);
    pinMode (3, GPIO_Mode_IN_FLOATING);
    pinMode (4, GPIO_Mode_IN_FLOATING);
    pinMode (5, GPIO_Mode_IN_FLOATING);
    pinMode (6, GPIO_Mode_IN_FLOATING);
    pinMode (7, GPIO_Mode_IN_FLOATING);
    Delay_Ms (400);

    while (1) {
        for (uint16_t i = 0; i < 3000; i++) {
            updateDisplay (FULL_ON);
            if (DELAY_FRAME > 150) {
                DELAY_FRAME = DELAY_FRAME / 2;
            }
        }

        for (uint16_t i = 0; i < 3000; i++) {
            updateDisplay (CHECKMARK);
        }

        for (uint16_t i = 0; i < 60; i++) {
            for (uint8_t row = 0; row < 8; row++) {
                if (slidingLine[row] == 0b10000000) {
                    slidingLine[row] = 0b00000001;
                }
                else {
                    slidingLine[row] = slidingLine[row] * 2;
                }
                
            }
            for (uint16_t i = 0; i < 100; i++) {
                updateDisplay (slidingLine);
            }
        }

        for (uint16_t i = 0; i < 3000; i++) {
            updateDisplay (CHECKERBOARD);
        }

        for (uint16_t i = 0; i < 3000; i++) {
            updateDisplay (SMILEY);
        }
    }
}
