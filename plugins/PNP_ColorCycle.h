// What Effect Does:
//
//    Cycles through specific choices of colors (hue and whiteness).
//    The brightness is not affected.
//
// Calling trigger():
//
//    Saves the force value to pass on when the color cycle is complete.
//
// Calling nextstep():
//
//    Changes to next color after 'count' number of steps.
//
// Properties Used:
//
//    pixCount - determines number of steps before color change.
//
// Properties Affected:
//
//    degreeHue, pcentWhite - modified after so many calls to nextstep().
//

class PNP_ColorCycle : public PixelNutPlugin
{
public:
  byte gettype(void) const { return PLUGIN_TYPE_PREDRAW; };

  void begin(byte id, uint16_t pixlen)
  {
      myid = id;
  }

  void trigger(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw, short force)
  {
      forceVal = force;
      count = -1;
      index = 0;
  }

  void nextstep(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw)
  {
    if (count >= pdraw->pixCount)
    {
      pdraw->degreeHue = hues[index];
      pdraw->pcentWhite = whites[index];
      pixelNutSupport.makeColorVals(pdraw);

      count = 1;
      if (++index >= 3)
      {
        index = 0;
        pixelNutSupport.sendForce(handle, myid, forceVal, pdraw);
      }
    }
    else ++count;
  }

private:
    byte myid;
    short forceVal;
    uint16_t count;
    uint16_t index;
    // cycles through Red, White, Blue
    uint16_t hues[3] = { 0, 0, 240 };
    uint16_t whites[3] = { 0, 100, 0 };
};
