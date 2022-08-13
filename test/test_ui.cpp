// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Benchmark.h"

#include "base.h"

void testRotary();

void run()
{
    UNITY_BEGIN();
    testRotary();
    UNITY_END();
}

#ifdef ARDUINO

const uint8_t encoderA = 21;
const uint8_t encoderB = 5;
const uint8_t button = 15;

void setup()
{
    Serial.begin(115200);
    delay(2000);
    glow::Benchmark::Setup();

    // Set encoder pins
    pinMode(encoderA, INPUT_PULLUP);
    pinMode(encoderB, INPUT_PULLUP);
    pinMode(button, INPUT_PULLUP);

    run();
}

void loop()
{
}

#else // NATIVE

int main(int argc, char **argv)
{
    run();
}

#endif // ARDUINO
