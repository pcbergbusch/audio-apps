/*
  ==============================================================================

    AudioHelpers.h
    Created: 29 Oct 2022 2:36:49pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

const static float smoothingCoeffGeneric = 0.04f;
const static float smoothingCoeffFine = 0.002f;

const static float PI = 3.14159265359f;

const static int maxBufferSize = 88200; // circular buffer must be longer than max delay time * sample rate
