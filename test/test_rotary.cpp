// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"
#include "wait.h"

#ifdef ARDUINO

#include "RotaryUpdater.h"
#include "StateHandler.h"

using glow::print_line;
using glowui::RotaryUpdater;
using glow::StateHandler;

const uint8_t encoderA = 21;
const uint8_t encoderB = 5;
const uint8_t button = 15;

struct RotaryTarget
{
    uint32_t ticks = 0;
    char buffer[32];
    uint8_t lastState = 0;
    int16_t lastPosition = 0;

    void Update(uint8_t state, int16_t delta)
    {
        if (state != lastState)
        {
            lastState = state;
            snprintf(buffer, sizeof(buffer),
                     "b=%u p=%d\n", lastState, lastPosition);
            print_line(buffer);
            ++ticks;
        }

        if (delta != 0)
        {
            lastPosition += delta;
            snprintf(buffer, sizeof(buffer),
                     "b=%u p=%d\n", lastState, lastPosition);
            print_line(buffer);
        }
    }

    uint32_t Ticks() { return ticks; }
};

void testLoop(RotaryUpdater &rotary,
              uint32_t count = 50000, uint32_t ms = 10)
{
    StateHandler handler;
    RotaryTarget target;

    for (uint32_t i = 0; i < count; i++)
    {
        handler.Handle(rotary, target);
        if (handler.Ticks() > 8)
        {
            return;
        }
        wait(1);
    }
}

void testRotaryButton()
{
    char buffer[32];
    Range range(0, 100);
    RotaryUpdater rotary(encoderA, encoderB, button, range.Pack());

    snprintf(buffer, sizeof(buffer),
             "b=%u p=%d\n", rotary.State(), rotary.Position());
    print_line(buffer);
    wait(1000);

    testLoop(rotary);

    snprintf(buffer, sizeof(buffer),
             "b=%u p=%d\n", rotary.State(), rotary.Position());
    print_line(buffer);
}
#endif // ARDUINO

void testRotary()
{
#ifdef ARDUINO
    RUN_TEST(testRotaryButton);
#endif // ARDUINO
}
