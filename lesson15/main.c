#include <stdint.h> /* The most important addition to C99! */
#include "stm32f10x.h"
#include "delay.h"

#define PIN8 (1U << 8)
#define PIN9 (1U << 9)

typedef struct {
    uint8_t y;
    uint16_t x;
} Point;

Point p1 = {
    123U,
    0x1234U
};

Point p2;

typedef struct {
    Point top_left;
    Point bottom_right;
} Window;

typedef struct {
    Point corners[3];
} Triangle;

Window w = {
    { 123U, 0x1234U },
    { 234U, 0x6789U }
};
Window w2;
Triangle t;

int16_t x = -1;
uint32_t y = 0x0000DEADU;

int16_t sqr[8] = {
    1 * 1,
    2 * 2,
    3 * 3,
    4 * 4
};

/******************************************************************************/
void main(void)
/******************************************************************************/
{
    Point * pp;
    Window * wp;

    p1.x = sizeof(Point);
    p1.y = p1.x - 2U;

    w.top_left.x = 1U;
    w.top_left.y = 2U;

    t.corners[0].x = 1U;
    t.corners[2].y = 2U;

    p2 = p1;
    w2 = w;

    pp = &p1;
    wp = &w2;

    (*pp).x = 1U;
    (*wp).top_left = *pp;

    pp->x = 1U;
    wp->top_left = *pp;

    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOF clock.  */
    GPIOC->CRH    = (0x01U << 0) | /* GPIOC8 as PP output. */
                    (0x01U << 4);  /* GPIOC9 as PP output. */

    while (1)
    {
        GPIOC->BSRR = PIN8;
        GPIOC->BRR = PIN9;

        delay(240000);

        GPIOC->BRR = PIN8;
        GPIOC->BSRR = PIN9;

        delay(240000);
    }
}
