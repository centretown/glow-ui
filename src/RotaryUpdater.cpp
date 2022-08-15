// Copyright (c) 2022 Dave Marsh. See LICENSE.
//
// Thanks to: https://garrysblog.com/
// https://garrysblog.com/2021/03/20/
//  reliably-debouncing-rotary-encoders-with-arduino-and-esp32/

#ifdef ARDUINO

#include "RotaryUpdater.h"

namespace glowui
{
  uint32_t RotaryUpdater::Update()
  {
    static const int8_t states[] = {
        0, -1, 1, 0, //
        1, 0, 0, -1, //
        -1, 0, 0, 1, //
        0, 1, -1, 0, //
    };

    encoderIndex <<= 2; // include previous state
    uint8_t b = digitalRead(button);
    if (b != buttonState)
    {
      buttonState = b;
      state++;
    }

    if (digitalRead(encoderA))
      encoderIndex |= 0x02; // Add current state of pin A
    if (digitalRead(encoderB))
      encoderIndex |= 0x01; // Add current state of pin B

    encoderState += states[(encoderIndex & 0x0f)];

    // Update counter if encoder has rotated a full indent, that is at least 4 steps
    if (encoderState > 3)
    {             // Four steps forward
      position++; // Increase counter
      encoderState = 0;
    }
    else if (encoderState < -3)
    {             // Four steps backwards
      position--; // Decrease counter
      encoderState = 0;
    }

    if (position >= bounds.End())
    {
      position = (encoderState > 0) ? bounds.End() - 1 : 0;
    }
    return pack;
  }
}

#endif // ARDUINO