/*
  ==============================================================================

    AudioHelpers.h
    Created: 29 Oct 2022 2:36:49pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

const static double smoothingCoeffGeneric = 0.04;
const static double smoothingCoeffFine = 0.002;

const static double PI = 3.14159265359;

static const int maxBufferSize = 88200; // circular buffer must be longer than max delay time * sample rate
