// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO

#include "Range.h"

using glow::Range;
using glow::range_pack;

namespace glowui
{
    class RotaryUpdater
    {
    private:
        const uint8_t encoderA;
        const uint8_t encoderB;
        const uint8_t button;

        int16_t position = 0;
        uint8_t buttonState = HIGH;

        uint8_t encoderIndex = 3; // matrix index
        int8_t encoderState = 0;  // matrix state

    public:
        RotaryUpdater(uint8_t encoderA,
                      uint8_t encoderB,
                      uint8_t button, bool init = false)
            : encoderA(encoderA),
              encoderB(encoderB),
              button(button)
        {
            if (init)
            {
                pinMode(encoderA, INPUT_PULLUP);
                pinMode(encoderB, INPUT_PULLUP);
                pinMode(button, INPUT_PULLUP);
            }
        }

        uint16_t Update();

        inline uint8_t ButtonState() const
        {
            return buttonState;
        }

        inline int16_t Position() const
        {
            return position;
        }

    };
} // namespace glowui

#endif // ARDUINO