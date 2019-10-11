I am taking classes in the excellent Modern Embedded Systems Programming Course.

Go check it out here: https://www.state-machine.com/quickstart/

This repository contains source code and project files that I develop as I
advance through the course.

I don't simply copy and paste what is presented in the lectures, but I rather
(re)write it using my own hardware, which in this case happens to be two hands
and a keyboard.

You'll notice that there are some differences between the code presented in
the course and the one you 'll find in the repo. There are two reasons for that:

* I'm not simply copying and pasting (as explained above), so I have
  the freedom to follow my own coding rules,
* I'm using different evaluation board.

The second reason is kinda interesting. The amazing lecturer, Miro Samek,
is using EK-TM4C123GXL evaluation board (aka LaunchPad Evaluation Kit)
from Texas Instruments for his lectures. It has a TM4C123GH6PM microcontroller,
that has Arm's Cortex-M4F core. When it comes to me, well, that's a different
story :-) I didn't have any TI's evaluation board lying around,
but as a long-term STM32 developer I surely had some ST's evals. And honestly,
I was too impatient to get onto the course's bandwagon, so waiting for TI's
board to arrive was not an option. I ended up using STM32VLDISCOVERY evaluation
board (aka STM32 Discovery Kit), that sports an STM32F100RBT6B microcontroller,
that's built on top of Arm's Cortex-M3 core. Not as beefy as M4F, but meh,
good enough for Australia (vide EEVBlog).

If you haven't yet had the chance to feel the vibe for embedded systems
programming, I strongly encourage you to undertake Miro Samek's Modern Embedded
Systems Programming Course. You'll learn the microcontrollers thoroughly,
while Miro's manner of lecturing and explaining intricacies of embedded systems
will make you feel like having an extraordinary journey.

You can use the code from this repo for your own inspiration,
should you need to run the lectures on a different hardware.

Go grab it and have fun!

I'm using the following IDEs and/or toolchains throughout the course:

* lesson 1 - 18: IAR Embedded Workbench for ARM 7.80.
