#include "conf.h"
#ifdef ONEWIRE_ENABLED
#include "onewire.h"
#endif
#ifdef I2CUTILS_ENABLED
#include "i2ctools.h"
#endif
#ifdef DS18b20_ENABLED
#include "ds18b20.h"
#endif
#ifdef WHXXXX_ENABLED
#include "WHxxxx.h"
#endif
#ifdef MAX6675_ENABLED
#include "max6675.h"
#endif