#if defined(ARDUINO)
#include "includes/PixelNutSupport.h"   // engine support interface and standard types
#include "includes/PixelNutPlugin.h"    // template for all plugins (abstract class)
#include "includes/PixelNutEngine.h"    // main header file for pixelnut engine
#elif defined(SPARK)
#include "PixelNutSupport.h"
#include "PixelNutPlugin.h"
#include "PixelNutEngine.h"
#endif
