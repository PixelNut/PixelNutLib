// What Effect Does:
//
//    Moves drawing window back and forth across the entire strip of pixels.
//
// Calling trigger():
//
//    Saves force value to pass on when it reaches either end.
//
// Calling nextstep():
//
//    Moves the drawing window one pixel up/down the strip.
//
// Properties Used:
//
//    pixCount - current value when nextstep() called determines size of the window.
//
// Properties Affected:
//
//    pixStart, pixEnd - starting/ending pixel position of the drawing window.
//

class PNP_WinScanner : public PixelNutPlugin
{
public:
  byte gettype(void) const
  {
    return PLUGIN_TYPE_PREDRAW | PLUGIN_TYPE_SENDFORCE;
  };

  void begin(byte id, uint16_t pixlen)
  {
    pixLength = pixlen;
    myid = id;

    goForward = true; // start going forward
    headPos = 0;
    forceVal = 0;
  }

  void trigger(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw, short force)
  {
    forceVal = force; // can be negative
  }

  void nextstep(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw)
  {
    // must leave at least one pixel free
    uint16_t pixcount = pdraw->pixCount;
    if (pixcount >= pixLength) pixcount--;

    uint16_t tailpos = headPos + pixcount-1;
    if (tailpos > (pixLength-1)) tailpos = (pixLength-1);

    pdraw->pixStart = headPos;
    pdraw->pixEnd   = tailpos;

    if (goForward)
    {
      if (tailpos >= (pixLength-1))
      {
        goForward = false;
        pixelNutSupport.sendForce(handle, myid, forceVal, pdraw);
      }
    }
    else
    {
      if (headPos <= 0)
      {
        goForward = true;
        pixelNutSupport.sendForce(handle, myid, forceVal, pdraw);
      }
    }

    if (goForward) ++headPos;
    else          --headPos;
  }

private:
  byte myid;
  short forceVal;
  bool goForward;
  uint16_t pixLength, headPos;
};
