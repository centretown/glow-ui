// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"
#include "wait.h"

#ifdef ARDUINO

#include "RotaryUpdater.h"
#include "StateHandler.h"

using glow::print_line;
using glow::StateHandler;
using glowui::RotaryUpdater;

const uint8_t encoderA = 21;
const uint8_t encoderB = 5;
const uint8_t button = 15;

struct RotaryTarget
{
    uint32_t ticks = 0;
    char buffer[32];
    uint8_t lastState = 0;
    int16_t lastPosition = 0;

    void Update(uint8_t state, int16_t position)
    {
        if (state != lastState)
        {
            lastState = state;
            snprintf(buffer, sizeof(buffer),
                     "b=%u p=%d\n", lastState, lastPosition);
            print_line(buffer);
            ++ticks;
        }

        if (position != 0)
        {
            lastPosition = position;
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
    char buffer[32];
    StateHandler handler;
    RotaryTarget target;

    State state;

    for (uint32_t i = 0; i < count; i++)
    {
        uint32_t p = handler.Handle(rotary, target);
        if (p != state.pack)
        {
            snprintf(buffer, sizeof(buffer),
                     "rs=%x rp=%x\ns=%x p=%x\n",
                     rotary.Status(), rotary.Position(), 
                     state.Status(), state.Position());
            print_line(buffer);
            state.pack = p;
        }
        wait(1);
    }
}

void testRotaryButton()
{
    char buffer[32];
    Range range(0, 100);
    RotaryUpdater rotary(encoderA, encoderB, button, true);

    snprintf(buffer, sizeof(buffer),
             "b=%u p=%d\n", rotary.Status(), rotary.Position());
    print_line(buffer);
    wait(1000);

    testLoop(rotary);

    snprintf(buffer, sizeof(buffer),
             "b=%u p=%d\n", rotary.Status(), rotary.Position());
    print_line(buffer);
}
#endif // ARDUINO

void testRotary()
{
#ifdef ARDUINO
    RUN_TEST(testRotaryButton);
#endif // ARDUINO
}
