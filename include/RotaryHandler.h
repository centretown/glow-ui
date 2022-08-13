// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "RotaryUpdater.h"

namespace glowui
{
    class RotaryHandler
    {
    private:
        uint32_t ticks = 0;
        uint8_t lastState = 0x7f;
        int16_t lastPosition = 0x7fff;

    public:
        template <typename TARGET>
        void Handle(RotaryUpdater &rotary, TARGET &target)
        {
            rotary.Update();

            uint8_t state = rotary.ButtonState();
            int16_t position = rotary.Position();

            if (state == lastState && position == lastPosition)
            {
                return;
            }

            target.Update(state, position);
            lastState = state;
            lastPosition = position;
        }

        inline uint32_t Ticks() { return ticks; }
    };

} // namespace glowui
