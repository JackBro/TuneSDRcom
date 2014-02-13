#pragma once

#include "PowersdrToPultProvider.h"
#include "PowersdrButtonStates.h"

using namespace System::Text;

ref class PultToPowersdrProvider
{
public:
	bool BigValCodeAB;
	bool Acceleration;
	
public:
	int modeBtn;
	int pttBtn;

	PowersdrToPultProvider^ PoPuPro;
	PowersdrButtonStates^ PoBtnSt;

	System::Windows::Forms::TrackBar^  Acc0;
	System::Windows::Forms::TrackBar^  Acc1;
	System::Windows::Forms::TrackBar^  Acc2;
	System::Windows::Forms::TrackBar^  Acc3;
	System::Windows::Forms::TrackBar^  Acc4;
	System::Windows::Forms::TrackBar^  Acc5;

	System::Windows::Forms::NumericUpDown^  NumFilt;
	System::Windows::Forms::NumericUpDown^  NumRitXit;

	System::Windows::Forms::TextBox^  tbFFirst;
	System::Windows::Forms::TextBox^  tbFSecond;

public:
	PultToPowersdrProvider(void);

	StringBuilder^ PowersdrCmds;

	bool ProvideCmd(int Command);

	void IncrementFrequency(int step, bool AB);
	void DecrementFrequency(int step, bool AB);
	
	void ClearRIT(void);
	void ClearXIT(void);

	void ChangeRitXit(bool cmdName, bool direction);

	void TurnRitXit(System::String^ cmdName, bool% btnState);
	void TurnBtnState(System::String^ cmdName, bool% btnState, Byte ON, Byte OFF);

	void SetMD(System::String^ md);
	void SetVS(System::String^ vs);
	
	void SendPreAMP(Byte amp);

	void ChangeBand(System::String^ direction);

	void WheelUp(int cmd);
	void WheelDwn(int cmd);

	void FreqShift(bool UpDwn);
	void FreqWidth(bool UpDwn);
	void FreqLeft(bool UpDwn);
	void FreqRight(bool UpDwn);

	void AccButton(void);

	void FBtn(void);
	bool FPair;
	
	bool AccMode;
	bool ForOldAccStep;
};

