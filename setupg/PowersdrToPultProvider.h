#pragma once

#include "PowersdrButtonStates.h"

using namespace System;
using namespace System::Collections::Generic;

ref class PowersdrToPultProvider
{
public:
	PowersdrToPultProvider(void);
	bool ProvideAnswer(System::String^ answer);

	void ZZFA(System::String^ answer);
	void ZZFB(System::String^ answer);

	void SendSmLed(void);
	void SetLED(int mode, int ptt);
	void SetSM0(System::String^ answer);

	void SendTime(void);
	void SendDate(void);

	array<Byte,1>^ PowerAnswer;
	array<Byte,1>^ smMatrix;
	bool smMatrixActive;
	int PowerAnswerIterator;

	int LED;
	int SM0;

	void SendMdPAmpBtns(void);
	bool MdPAmpBtnsChanged;

	void SendRitXitSplit(System::String^ cmdName);

	void SendFilterWidth(void);
	void SendFilterLow(void);
	void SendFilterHigh(void);

	PowersdrButtonStates^ PoBtnSt;

};

