#include "delay.h"

/******************************************************************************/
void delay(int volatile iter)
/******************************************************************************/
{
    //int volatile counter = 0;

    while (iter > 0)
    {
        --iter;
    }
}