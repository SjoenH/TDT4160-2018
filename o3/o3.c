#include "o3.h"
#include "gpio.h"
#include "systick.h"

//porters for knapper og led
#define LED_PORT GPIO_PORT_E
#define LED_PIN 2
#define PB0_PORT GPIO_PORT_B
#define PB0_PIN 9
#define PB1_PORT GPIO_PORT_B
#define PB1_PIN 10

#define STATE_SET_SEC 0
#define STATE_SET_MIN 1
#define STATE_SET_HOUR 2
#define STATE_COUNT_DOWN 3
#define STATE_ALARM 4

struct time_t {
    int h, m, s;
};

typedef struct {
    word CTRL;
    word MODEL;
    word MODEH;
    word DOUT;
    word DOUTSET;
    word DOUTCLR;
    word DOUTTGL;
    word DOUTIN;
    word PINLOCKN;
} gpio_port_t;

volatile struct gpio_t{
    gpio_port_t ports[6];
    word unused_space[10];
    word EXTIPSELL;
    word EXTIPSELH;
    word EXTIRISE;
    word EXTIFALL;
    word IEN;
    word IF;
    word IFS;
    word IFC;
    word ROUTE;
    word INSENSE;
    word LOCK;
    word CTRL;
    word CMD;
    word EM4WUEN;
    word EM4WUPOL;
    word EM4WUCAUSE;
} *GPIO = (struct gpio_t *) GPIO_BASE;

volatile struct systick_t {
    word CTRL;
    word LOAD;
    word VAL;
    word CALIB;
} *SYSTICK = (struct systick_t *) SYSTICK_BASE;

static int state = STATE_SET_SEC;
static struct time_t time = {0};
static char str[8] = "0000000\0";

void int_to_string(char *timestamp, unsigned int offset, int i) {
    if (i > 99) {
        timestamp[offset] = '9';
        timestamp[offset + 1] = '9';
        return;
    }

    while (i > 0) {
        if (i >= 10) {
            i -= 10;
            timestamp[offset]++;
        } else {
            timestamp[offset + 1] = '0' + i;
            i = 0;
        }
    }
}

void time_to_string(char *timestamp, int h, int m, int s) {
    timestamp[0] = '0';
    timestamp[1] = '0';
    timestamp[2] = '0';
    timestamp[3] = '0';
    timestamp[4] = '0';
    timestamp[5] = '0';
    timestamp[6] = '\0';

    int_to_string(timestamp, 0, h);
    int_to_string(timestamp, 2, m);
    int_to_string(timestamp, 4, s);
}

void set_4bit_flag(volatile word *w, int i, word flag) {
    *w &= ~(0b1111 << (i * 4));
    *w |= flag << (i * 4);
}

////////////////////////////// Startup sequence //////////////////////////////
void init_io() {
    set_4bit_flag(&GPIO->ports[LED_PORT].MODEL, LED_PIN, GPIO_MODE_OUTPUT);
    set_4bit_flag(&GPIO->ports[PB0_PORT].MODEH, PB0_PIN - 8, GPIO_MODE_INPUT);
    set_4bit_flag(&GPIO->ports[PB1_PORT].MODEH, PB1_PIN - 8, GPIO_MODE_INPUT);

    set_4bit_flag(&GPIO->EXTIPSELH, PB0_PIN - 8, 0b0001);
    set_4bit_flag(&GPIO->EXTIPSELH, PB1_PIN - 8, 0b0001);

    GPIO->EXTIFALL |= 1 << PB0_PIN;
    GPIO->EXTIFALL |= 1 << PB1_PIN;

    GPIO->IEN |= 1 << PB0_PIN;
    GPIO->IEN |= 1 << PB1_PIN;

    SYSTICK->LOAD = FREQUENCY;
    SYSTICK->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
}

void stop_clock() {
    SYSTICK->CTRL &= ~(SysTick_CTRL_ENABLE_Msk); //NAND
}

void start_clock() {
    SYSTICK->VAL = SYSTICK->LOAD;
    SYSTICK->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

//aktive funksjoner
void hour_inc() {
    ++time.h;
}

void min_inc() {
    ++time.m;
    if (time.m >= 60) {
        time.m = 0;
        hour_inc();
    }
}

void sec_inc() {
    ++time.s;
    if (time.s >= 60) {
        time.s = 0;
        min_inc();
    }
}

void update_time_display() {
    time_to_string(str, time.h, time.m, time.s);
    lcd_write(str);
}

// Knapp 1 | PB0
void GPIO_ODD_IRQHandler() {
    switch (state) {
        case STATE_SET_SEC:
            sec_inc();
            update_time_display();
            break;

        case STATE_SET_MIN:
            min_inc();
            update_time_display();
            break;

        case STATE_SET_HOUR:
            hour_inc();
            update_time_display();
            break;

        default: break;
    }

    GPIO->IFC = 1 << PB0_PIN;
}

// Knapp 2 | PB1
void GPIO_EVEN_IRQHandler() {
    switch (state) {
        case STATE_SET_SEC:
            state = STATE_SET_MIN;
            break;

        case STATE_SET_MIN:
            state = STATE_SET_HOUR;
            break;

        case STATE_SET_HOUR:
            state = STATE_COUNT_DOWN;
            start_clock();
            break;

        case STATE_ALARM:
            state = STATE_SET_SEC;
            GPIO->ports[LED_PORT].DOUTCLR = 1 << LED_PIN;
            break;

		default: break;
    }
    GPIO->IFC = 1 << PB1_PIN;
}

void SysTick_Handler() {
    if (state == STATE_COUNT_DOWN) {
        if (time.s <= 0) {
            if (time.m <= 0) {
                if (time.h <= 0) {
                    state = STATE_ALARM;
                    stop_clock();
                    GPIO->ports[LED_PORT].DOUTSET = 1 << LED_PIN;
                    update_time_display();
                    return;
                }
                --time.h;
                time.m = 60;
            }
            --time.m;
            time.s = 60;
        }
        --time.s;
        update_time_display();
    }
}

////////////////////////////// Main Loop //////////////////////////////

int main() {
    init();
    init_io();
    update_time_display();
}
