// PixelNut Effect Plugin Abstract Interface
// Each plugin must derive from this class.
// Uses the PixelNutSupport Interface.
/*
    Copyright (c) 2015-2017, Greg de Valois
    Software License Agreement (BSD License)
    See license.txt for the terms of this license.
*/

#ifndef PIXELNUT_PLUGIN_H
#define PIXELNUT_PLUGIN_H

// Only the destructor and the gettype functions must be implemented in a derived class
// (although to do anything interesting one of other functions needs to be overriden too).

                                        // these are mutually exclusive:
#define PLUGIN_TYPE_REDRAW        0x01  // creates pixel values from settings    
#define PLUGIN_TYPE_PREDRAW       0x02  // alters effect settings before drawing
#define PLUGIN_TYPE_POSTDRAW      0x04  // alters final output pixel buffer

                                        // any combination of these is valid:
#define PLUGIN_TYPE_TRIGGER       0x10  // triggering changes the effect somehow
#define PLUGIN_TYPE_SENDFORCE     0x20  // will send trigger force to other plugins
#define PLUGIN_TYPE_DIRECTION     0x40  // changing direction will affect animation

class PixelNutPlugin
{
public:
  virtual ~PixelNutPlugin() = 0; // an empty default method is provided

  // Returns capability bits indicating how this plugin affects pixel values.
  // This is the only required method that must be implemented in each plugin.
  virtual byte gettype(void) const = 0; // one or more PLUGIN_TYPE_ values

  // Start this effect, given the number of pixels in the strip to be drawn.
  // If any memory is allocated here make sure it's freed in the class destructor.
  // The "id" value identifies this layer, and is used to trigger other plugins.
  virtual void begin(byte id, uint16_t pixlen) {}

  // Trigger a change to the effect with an amount of "force" to be applied.
  // Guaranteed to be called here first before any calls to nextstep().
  virtual void trigger(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw, short force) {}

  // Perform the next step of an effect by this plugin using the current drawing
  // properties. The rate at which this is called depends on the delay property.
  virtual void nextstep(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw) {}
};

#endif
