#ifndef __SDCONTROL
  #include"SD_control.h"
#endif

#include"config.h"

#include <RtcDS3231.h>
#include<Wire.h>

RtcDS3231<TwoWire> Rtc(Wire);




