The PixelNut Library Design Architecture
================================================================

The purpose of this library is to provide an overall framework, and a lot of the building blocks, for the creation of your own custom smart lighting effects applications.

The library provides methods for translating command strings into bit patterns in memory representing RGB pixel values, and for manipulating those values to create fun and visually pleasing light animations using either WS2812B or APA102 LED pixels.

It stands independent of any other software libraries (except for the standard Arduino support files), and any specific hardware devices, and so should be compatible with any microcontroller supported by the Arduino community.

It only provides support for the creation of these lighting effects, and must be combined with external application code to display these effects on physical hardware. See the sample application in the \examples subdirectory, which uses the standard NeoPixels library to display these pixels on WS2812B LEDs.

What makes this unique among other such libraries:

1. You can create your own animation patterns using simple to manipulate command strings, that layer simple effects together to create more complex and entertaining visual effects.

2. You can create your own effect plugins by writing very small snippets of C++ code, which can interact with other plugins in various ways.

3. You can modify the resultant animations with controls that are easily set from simple hardware input devices, such as buttons and pots (potentiometers), and/or with phone applications that provides virtual visual controls instead.


Software Architecture
================================================================

To visualize how all this works together, view the image: 'PixelNutLib-Design.jpg', which will help in the following explanation.

The application must include 'PixelNutLib.h' (which includes the other .h files shown in the drawing), and instantiate instances of the PixelNutSupport and PixelNutEngine classes defined in them, to get access to its constants and data types, and to call its methods.

The PixelNutEngine class is the heart of the library. Its methods are called by applications to interpret the command strings that create an animation, modify the pixel bits in memory during an animation, and to update the animation periodically (on every call to loop() for example), It also manages the effect plugins.

The PixelNutSupport class methods are used by applications to set global delay and brightness values, and are used by the effect plugins to create and manipulate actual pixel values. It also provides global constants and centralizes methods for getting time information and for printing debug messages.

The PluginFactory class only has a single method that, when called with a plugin number, returns the instantiation of the software class implementing the plugin effect. The definition for each of these plugins is in the 'PixelNutPlugin.h' file.

These plugins in turn provide all the code to create pixels, using common PixelNutSupport routines to actually set, clear, and copy the pixel values in memory.

There are two types of plugins: one that actually create pixels values (“drawing”), and ones that just manipulate the drawing properties for these drawing plugins. These include properties such as the color hue, whiteness and brightness, how much delay there between redraws, and others.

The result of all of this is an array of memory with pixel values that the application then displays to physical arrays (strips or strands) of pixels. 

(Note that the only code that knows the actual format of the physical pixels is localized in the PixelNutSupport routines, and all of it is independent of the actual physical hardware.)

See the file 'how-plugins-work.md' for further explanation.


Tracks, Layers, Pixel Drawing, and Command Strings
================================================================

Complete patterns are created from one or more effect "layers", each corresponding to an effect plugin. The plugins that draw pixels, do so onto a "track". (Layers and tracks are represented by their own data structures defined in PixelNutEngine.h.)

Each track has its own pixel data array. To create the final output array of pixels, the data from all the tracks are combined together, either by OR'ing the values together, or by overwriting subsequent tracks non-zero values over previous ones, depending on an option when the track was specified.

To create any given animation, command strings are written that specify a stack of effect layers and tracks. The commands in this string are just letters ('A', 'G', etc.), most of which also require numeric values to be specified as well ('D10', 'T5', etc.).

The 'E<val>' command chooses which effect plugin to use, where <val> is the numeric value assigned to the plugin in the file 'PluginFactory.cpp'.

For more details on pattern commands work see both the files 'how-patterns-work.md' and 'pattern-command-reference.md'.


Triggering with Force
================================================================

Every software plugin, corresponding to an effect layer, can optionally utilize an effect trigger, along with its associated trigger force value. There is an optional entry point for each plugin called 'trigger()', which takes this force value as an argument.

There are several ways this entry point gets called:

1. Use the 'T' command in the specification for the layer. This causes 'trigger()' to be called once as the entire pattern string is being parsed.

2. Using this command with a value, as in 'T<val2>', with or without the 'O<val1>' command, to causes the entry point to be called randomly every val1-val2 number of seconds. The number of times this happens is determined by the 'N' command.

In both of these cases the force that is passed into 'trigger()' is determined by the 'F' command for that layer, which is either an explicit value assigned to the command ('F100'), or if left blank then a random value is assigned each time it is triggered.

3. The application calls the 'triggerForce()' PixelNutEngine method with a force value. What event triggers this call, and how the force value is determined, is entirely up to the application, and can be from pushing a button, or from some other hardware input device.


Applications
================================================================

Finally, an application must be written that creates command strings, sends them to the engine, and displays the pixels.

See the file 'how-sample-application-works.md' for an example of one of these applications.

See also the PixelNutApp Library for an application framework that uses this library to create more complex applications.
