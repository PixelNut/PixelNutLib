// What Effect Does:
//
//    Scales brightness levels individually up and down to create a twinkle effect.
//    Allocates 2 bytes of memory per number of pixels.
//
// Calling trigger():
//
//    Not instantiated.
//
// Calling nextstep():
//
//    Sets some number of pixels to the current color with a calculated amount of
//    brightness, which varies up and down to create a twinkle effect.
//
// Properties Used:
//
//    r,g,b - the current color values.
//
// Properties Affected:
//
//    none
//

class PNP_Twinkle : public PixelNutPlugin
{
public:
  ~PNP_Twinkle() { if (pbytes != NULL) free(pbytes); }

  byte gettype(void) const { return PLUGIN_TYPE_REDRAW; };

  void begin(byte id, uint16_t pixlen)
  {
    pixLength = pixlen;
    pbytes = (int16_t*)malloc(pixLength * sizeof(int16_t));

    maxvalue = 50;
    if (pbytes != NULL) for (uint16_t i = 0; i < pixLength; ++i)
      pbytes[i] = random(0, ((maxvalue * 2) + 50)) - maxvalue;
  }

  void nextstep(PixelNutHandle handle, PixelNutSupport::DrawProps *pdraw)
  {
    if (pbytes == NULL) return;

    for (uint16_t i = 0; i < pixLength; ++i)
    {
      //pixelNutSupport.msgFormat(F("Twinkle: pbytes[%d] = %d"), i, pbytes[i]);

      bool doscale = true;
      float scale = 0.0;

      if (pbytes[i] >= maxvalue)
      {
        if (--(pbytes[i]) >= maxvalue)
          continue; // keep off for now

        pbytes[i] = 1; // draw now, increasing level
      }
      else if (++(pbytes[i]) == 0)
      {
        pbytes[i] = maxvalue + random(10, 60); // go dark for random time
        doscale = false;
      }
      else if (pbytes[i] == maxvalue)
        pbytes[i] = -(maxvalue-1); // start decreasing level

      if (doscale) scale = ((float)abs(pbytes[i])) / maxvalue;

      pixelNutSupport.setPixel(handle, i, pdraw->r, pdraw->g, pdraw->b, scale);
    }
  }

private:
  uint16_t pixLength;
  int16_t *pbytes, maxvalue;
};
