How PixelNut Software Plugins Work
===============================================================

The following describes how the software plugins work within the PixelNut Library to create various lighting effects. This is an easy to use and open framework, such that you can, with minimal software expertise, add your own effects by writing your own plugin by creating a small and simple C++ class in a '.h' file. 

You also have the choice of how to add your own classes, either by changing the PixelNut Library itself, copying all of the plugins to your application directory, or by sub-classing the PixelNut Factory class to extend the built-in set of plugins.

But first you should read the file 'library-design.md' to understand the overall architecture of the PixelNut library.

Then you want to look at the following source files:

'PixelNutPlugin.h' (in the '/include' subdirectory)
Defines the abstract interface that each plugin conforms to.

'PixelNutSupport.h' (in the '/include' subdirectory)
Defines the support routines available to each plugin.

'PluginFactory.cpp' (in the main directory)
Where the code for the plugins gets included for compilation.


Plugin Interface
---------------------------------------------------------------

There are two types of plugins: ones that actually sets the pixel values in memory using the various property settings (called "drawing"), and ones that can only affect those settings.

These property settings are defined in 'PixelNutSupport.h', and are passed into several of the interface methods ('DrawProps'). They include the pixel range to be drawn, the color hue and percent whiteness, how much delay it has, which direction the effect moves in, and so forth.

The only required method that must be implemented by each plugin 'gettype()', which returns a bitmap describing the properties of the plugin. Note that there is no class constructor.

Each of the other found entry points are optional, but either 'trigger()' or 'nextstep()' needs to be implemented for the plugin to be actually useful.

The overall idea of these entry points is:

begin(): allows the plugin to receive global settings, such as its 'id' value, and how many total pixels there are. This is also where any local variables can be initialized, and where any memory allocation should be done.

trigger(): allows the plugin to perform some action depending on the force value. This is entirely up to the plugin what to do here, and is optional. You can perform initialization here as well, as it will always get called at least once before the first call to 'nextstep()'.

For most of the plugins that have been implemented so far, this is not used by the 'ReDraw' type of plugins that actually draw pixels, but by 'PreDraw' ones that modify drawing properties, to change the way the modification behaves in some manner.

nextstep(): this is most of the work of the plugin gets done, and is called repetitively from the main application loop, the frequency determined by the delay associated with plugin set with the 'D' command.

~PixelNutPlugin(): this is the class destructor, and is needed to free any memory that was allocated in 'begin()'.


When Plugin Methods Get Called
---------------------------------------------------------------

The PixelNut system is synchronous: there are no timer callbacks used to execute any of the above methods, and they are called when the application makes calls into the PixelNut Engine.

When 'execCmdStr()' is called to parse a command string, each plugin effect that is created by an 'E' command immediately causes the gettype() and begin() methods to be called. If there's a 'T' command specified for that effect, then the 'trigger()' method is called.

Whenever the application calls 'triggerForce()', it directly causes a call into each plugin's 'trigger()' method (unless it has been blocked because it has not been enabled by the 'I' command).

During application calls into 'updateEffects()' the 'nextstep()' method is called if the delay time has expired (set with the 'D' command).

Finally if the 'T<val>' style trigger command was specified for the plugin, then before calling 'nextstep()', the 'trigger()' method is called if the random timeout period has expired.


Support Routines
---------------------------------------------------------------

These support functions allow plugins to create pixel values from hue, whiteness, and brightness settings, and to set and manipulate values in the pixel array for the plugin.

Keep in mind that the pixel array drawn into by plugins is not the final output pixels, which are formed by combining the pixels from all the plugin pixel arrays together.

The 'sendForce()' support routine allows plugins to trigger other plugins. This is a powerful means of having plugin interact with each other. 

How this works is if the 'A<id>' command is used in creating a plugin, that 'id' value is the layer number of another plugin, and when that plugin calls 'sendForce()' with its 'id' value, that triggers a call into the 'trigger()' method of the plugin that used the 'A' command. This 'id' value is passed into the 'begin()' method of each plugin.


Plugin Factory
---------------------------------------------------------------

As its name implies, this is where plugins get created. The code for these plugins are included in the file 'PluginFactory.cpp', and assigned a number, which is the value referrenced in the 'E<val>' pattern command.

To add a new plugin, you have three choices:

1) Add it to the existing library of plugins. This is the simplest method, and the effect will be available to any application that uses the PixelNutLib Library.

However, this also means that it will increase the sizes of those applications as well, some of which might already be at their maximum code size (such as some of the PixelNut! Products).

To do this, add your .h file with the plugin code to the '/plugins' subdirectory of the library.

2) Copy and extend the existing library of plugins. This can be useful to have a custom set of plugins for each application. But this means that every application will have to have a copy of all the plugin files as well.

To do this, move the file 'PluginFactory.cpp' and the entire '/plugins' directory from the PixelNutLib Library to your application directory, then add the .h file as above.

3) Perhaps the best method, but a little more complicated, is to derive a new class from the PluginFactory class, and add the new plugins to this new class, remembering to call into the base class by default.

Once one of the above procedures has been accomplished, edit the 'PluginFactory.cpp' file to #include your plugin file, then add another case statement with a value that hasn't yet been used. 

You can now go ahead and use that unique value assigned to your plugin in any of the 'E<Val>' commands in your pattern strings.
