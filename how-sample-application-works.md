The "Sample" Application
===============================================================

The following refers to the sample application provided with the library. You might first read the file 'library-design.md' to understand the overall architecture of the PixelNut library.

This example illustrates the simplest design possible using the Arduino and Adafruit NeoPixel libraries.

It declares a single effect pattern, and creates instances of the NeoPixel class, and all of the necessary PixelNutEngine classes. The way these libraries work together, the former allocates the memory and handles driving the physical pixel hardware, while the latter is what actually draws the pixel values into that memory, and updates those values during the animation.

So during the 'setup()' phase of program execution, the pixel strand is initialized and displayed using the Neopixel class calls 'begin()' and 'show()' (which clears the pixels to black), and the PixelNutEngine class is called to render the pixel pattern onto a strand of pixels with 'execCmdStr()'.

In the main 'loop()', the PixelNutEngine class continuously calls 'updateEffects()' to update the animation, and if there were any changes to the pixel values the Neopixel 'show()' is called again to display them.

The pattern chosen for this example creates light waves that move down the pixel strip, and which periodically change color at random intervals. You can modify or completely change this pattern by simply editing the 'myPattern' string.

See the file 'how-patterns-work.md' for how to do that.

To make this come to life with actual hardware: 

1) Choose any Arduino compatible processor (such as from Adafruit, or the excellent Teensy LC from PJRC).

2) Wire up a strand of any WS2812B compatible pixels (such as Adafruit's Neopixels) to power, ground, and pin #17 (or modify the DPIN_PIXELS define statement).

3) Modify the PIXEL_COUNT define statement to the number of pixels to be displayed (60 corresponds to 1 meter of the standard 60 pixels/meter pixel strands commonly available).

4) Compile and flash the .INO file using the Arduino IDE (or your own Arduino compatible toolchain) to the processor.

5) Enjoy!
