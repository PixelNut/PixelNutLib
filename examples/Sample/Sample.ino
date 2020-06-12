// PixelNut! Sample Application
//
// Copyright(c) 2017, Greg de Valois, www.devicenut.com
//
/*---------------------------------------------------------------------------------------------
 This is free software: you can redistribute it and/or modify it under the terms of the GNU
 Lesser General Public License as published by the Free Software Foundation, version 3 or later.
 http://www.gnu.org/licenses/

 This is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
---------------------------------------------------------------------------------------------*/

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <PixelNutLib.h>

#define DPIN_PIXELS             17          // neopixels data pin
#define PIXEL_COUNT             60          // number of pixels
#define NUM_PLUGIN_LAYERS       4           // total number of plugins
#define NUM_PLUGIN_TRACKS       3           // number of drawing plugins

// create single statically allocated object instance
Adafruit_NeoPixel neoPixels = Adafruit_NeoPixel(PIXEL_COUNT, DPIN_PIXELS, NEO_GRB + NEO_KHZ800);

PixelValOrder pixorder = {1,0,2};

// create single static object instance and a pointer to it
PixelNutSupport pixelNutSupport = PixelNutSupport(millis, &pixorder);

// create single static object instance and a pointer to it
PixelNutEngine pixelNutEngine(neoPixels.getPixels(), neoPixels.numPixels(), 0, NUM_PLUGIN_LAYERS, NUM_PLUGIN_TRACKS);
PixelNutEngine *pPixelNutEngine = &pixelNutEngine;

// create single static object instance and a pointer to it
PluginFactory pluginFactory = PluginFactory();
PluginFactory *pPluginFactory = &pluginFactory;

char myPattern[] = "P E10 B50 D60 T E101 T E120 F250 T G";   // light waves that change color periodically

void setup()
{
  neoPixels.begin();
  neoPixels.show(); // clears the display to black

  pixelNutEngine.execCmdStr(myPattern);
}

void loop()
{
  if (pixelNutEngine.updateEffects())
    neoPixels.show(); // display new pixel values
}