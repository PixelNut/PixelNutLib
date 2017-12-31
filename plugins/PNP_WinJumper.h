// What Effect Does:
//
//    Randomly changes the location of the drawing window.
//
// Calling nextstep():
//
//    Changes the location of the drawing window randomly.
//
// Properties Used:
//
//    pixCount - current value when nextstep() called determines window size.
//
// Properties Affected:
//
//    pixStart, pixEnd - starting/ending pixel position of the drawing window.
//

class PNP_WinJumper : public PixelNutPlugin
{
public:
  byte gettype(void) const
  {
    return PLUGIN_TYPE_PREDRAW;
  };

  void begin(byte id, uint16_t pixlen)
  {
    pixLength = pixlen;
  }

  void nextstep(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw)
  {
    short head = random(0, pixLength-1);
    short tail = head + pdraw->pixCount;
    pdraw->pixStart = head;
    pdraw->pixEnd = (tail >= pixLength) ? pixLength-1 : tail;
  }

private:
  uint16_t pixLength;
};
