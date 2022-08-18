// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO

#include "Range.h"
#include "State.h"
#include "Updater.h"

using glow::Range;
using glow::range_pack;
using glow::Source;
using glow::State;

namespace glowui
{
    class RotaryUpdater : public Source
    {
    private:
        const uint8_t encoderA;
        const uint8_t encoderB;
        const uint8_t button;

        uint8_t buttonState = HIGH;
        uint8_t encoderIndex = 3; // matrix index
        int8_t encoderState = 0;  // matrix state
        Range bounds;             // position range

        uint16_t status = 0;
        uint16_t position = 0;

    public:
        RotaryUpdater(uint8_t encoderA,
                      uint8_t encoderB,
                      uint8_t button,
                      bool init = false)
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
            bounds(0, 255);
        }

        // Source.Update()
        uint32_t Update();

        inline range_pack Bounds(uint16_t begin, uint16_t end)
        {
            bounds(begin, end);
            return bounds.Pack();
        }
        inline int16_t Status() const { return status; }
        inline int16_t Status(int16_t v) { return status = v; }
        inline int16_t Position() const { return position; }
        inline int16_t Position(int16_t v) { return position = v; }
    };
} // namespace glowui

#endif // ARDUINO