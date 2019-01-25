#include <SoftwareSerial.h>
#include <string.h>
#include "bt_utils.hpp"

int write_stream(SoftwareSerial device, char *s)
{
  uint32_t len = strlen(s);

  for(unsigned i = 0; i < len; ++i)
  {
    if(device.write(*(s+i)) < 0)
      return -1;
  }

  return len;
}
