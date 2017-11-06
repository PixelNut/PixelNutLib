PixelNutLib Arduino Library
================================================================

This is a library for creating and manipulating effects using WS2812B LEDs (also referred to as NeoPixels) pixels. After downloading, rename the folder to 'PixelNutLib' and install it into the Arduino Libraries folder.

Note that the sample application that comes with this library requires the standard NeoPixel library 'Adafruit_NeoPixels' to be installed as well, however the PixelNutLib library itself is not dependent any particular Arduino library.

Once these have been installed, restart the Arduino IDE, then open the example sketch found in: File->Sketchbook->Library->PixelNutLib->sample.


What is the PixelNut! System?
================================================================

The PixelNut! System is the combination of an application that creates command strings to define effect patterns which is used by the PixelNutLib Library, along with its collection of Effect Plugins, to create animations on standard LED pixel strands.

This larger application could in turn include the other libraries in the PixelNut family, such as the PixelNutApp, BluefruitStrs, UIDevices, and NeoPixelShow Libraries, to create a complete environment for controlling the creation and use of these effect patterns with both physical controls and/or bluetooth communications.

It is highly extensible and customizable: you simply edit text strings to create new effect patterns, and write very small and simple C++ classes to create your own effect plugins.

For an explanation of how this library has been designed, read 'library-design.md'.

For an explanation of how the example application uses the PixelNutLib Library, read: 'how-sample-application-works.md'.

For an explanation of the command string format and how it's used to create effect patterns, read: 'how-patterns-work.md'.

For an explanation of how software plug-in effects work, and how to extend the library with its collection of built-in plugins by writing your own: read: 'how-plugins-work.md'.
