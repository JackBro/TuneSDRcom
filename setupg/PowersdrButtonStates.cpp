#include "StdAfx.h"
#include "PowersdrButtonStates.h"


PowersdrButtonStates::PowersdrButtonStates(void)
{
	RIT=false;
	XIT=false;
	NR=false;
	ANF=false;
	NB=false;
	NB2=false;
	SR=false;
	BIN=false;
	SPLIT=false;
	m_RX=false;

	AC_step=0;

	MD=0x00;
	PreAMP=0x00;
	BTNs=0x00;

	RitValue=0;
	XitValue=0;

	FrequencyShift=0;
	FrequencyWidth=0;
	FrequencyLeft=0;
	FrequencyRight=0;

	Frequency = -9999999;
}
