
#include "SimpleScheduler.h"

SimpleScheduler::SimpleScheduler(int tolerance){
  dt = tolerance;
  lastMicros = micros();
}

void SimpleScheduler::watch(){
  unsigned long timePassed = micros()-lastMicros;
  lastMicros = micros();
  if(timePassed<1+dt)
    doEachMicroSec();
  else if(timePassed>1e1-dt && timePassed<1e1+dt)
    doEach10MicroSec();
  else if(timePassed>1e2-dt && timePassed<1e2+dt)
    doEach100MicroSec();
  else if(timePassed>1e3-dt && timePassed<1e3+dt)
    doEachMilliSec();
  else if(timePassed>1e4-dt && timePassed<1e4+dt)
    doEach10MilliSec();
  else if(timePassed>1e5-dt && timePassed<1e5+dt)
    doEach100MilliSec();
  else if(timePassed>1e6-dt && timePassed<1e6+dt)
    doEachSec();
}
