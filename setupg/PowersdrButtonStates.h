#pragma once

using namespace System;

ref class PowersdrButtonStates
{
public:
	PowersdrButtonStates(void);

	bool RIT;
	bool XIT;
	bool NR;
	bool ANF;
	bool NB;
	bool NB2;
	bool SR;
	bool BIN;
	bool SPLIT;
	bool m_RX;

	int AC_step;

	Byte MD;
	Byte PreAMP;
	Byte BTNs;

	int XitValue;
	int RitValue;

	int FrequencyShift;
	int FrequencyWidth;
	int FrequencyLeft;
	int FrequencyRight;

	int Frequency;
};

