#ifndef _timeout_h_
#define _timeout_h_

#include <drivers.h>

_Bool _tim_timeout_blocking(uint16_t seconds, char scaler);

void (*timeout_callback)();
_Bool _tim_timeout_nonblocking_with_callback(uint16_t seconds, char scaler, void (*callback)());


#endif
