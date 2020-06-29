// PixelNut! Example Application
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
#include <NeoPixelShow.h>
#include <PixelNutLib.h>
#include "PNP_ColorCycle.h"

#define DPIN_PIXELS   17
#define PIXEL_COUNT   60

byte pixelArray[PIXEL_COUNT*3];
byte *pPixelData = pixelArray;
NeoPixelShow neoPixels = NeoPixelShow(DPIN_PIXELS);

PixelValOrder pixorder = {1,0,2};
PixelNutSupport pixelNutSupport = PixelNutSupport(millis, &pixorder);
PixelNutEngine pixelNutEngine = PixelNutEngine(pPixelData, PIXEL_COUNT);

MyPluginFactory pluginFactory = MyPluginFactory();
PluginFactory *pPluginFactory = &pluginFactory;

class MyPluginFactory : public PluginFactory
{
public:
  PixelNutPlugin *makePlugin(int plugin)
  {
    switch (plugin)
    {
      case 113: return new PNP_ColorCycle; // cycles through specific choices of colors (hue and whiteness)
      
      default:  return PluginFactory::makePlugin(plugin);
    }
  }
};

char myPattern[] = "E0 C50 T E113 T G";

void setup()
{
  pixelNutEngine.execCmdStr(myPattern);
}

void loop()
{
  if (pixelNutEngine.updateEffects())
    neoPixels.show(pPixelData, PIXEL_COUNT*3);
}
