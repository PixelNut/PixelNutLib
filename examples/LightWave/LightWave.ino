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

#define DPIN_PIXELS   17
#define PIXEL_COUNT   60

byte pixelArray[PIXEL_COUNT*3];
byte *pPixelData = pixelArray;
NeoPixelShow neoPixels = NeoPixelShow(DPIN_PIXELS);

PixelValOrder pixorder = {1,0,2};
PixelNutSupport pixelNutSupport = PixelNutSupport(millis, &pixorder);
PixelNutEngine pixelNutEngine(pPixelData, PIXEL_COUNT);

PluginFactory pluginFactory = PluginFactory();
PluginFactory *pPluginFactory = &pluginFactory;

char myPattern[] = "E10 B50 D60 T E101 T E120 F250 T G";   // light waves that change color periodically

void setup()
{
  pixelNutEngine.execCmdStr(myPattern);
}

void loop()
{
  if (pixelNutEngine.updateEffects())
    neoPixels.show(pPixelData, PIXEL_COUNT*3);
}
