#include "StdAfx.h"
#include "PultToPowersdrProvider.h"

using namespace System::Text;

PultToPowersdrProvider::PultToPowersdrProvider(void)
{
	PowersdrCmds=gcnew StringBuilder();
	BigValCodeAB=false;
	modeBtn=0;
	pttBtn=2;
	Acceleration=true;
	FPair=true;
	AccMode = false;
	ForOldAccStep = true;
}

void PultToPowersdrProvider::IncrementFrequency(int step, bool AB){
		if (AccMode)
		{
			PowersdrCmds->Append("ZZ");

			if (AB)
			{
				PowersdrCmds->Append("BP");
			} 
			else
			{
				PowersdrCmds->Append("AU");
			}

			if (!Acceleration)
			{
				step=PoBtnSt->AC_step;
			}

			if (step<10) { PowersdrCmds->Append("0"); }
			PowersdrCmds->Append(step);
			PowersdrCmds->Append(";");
		}
		else
		{
			PowersdrCmds->Append("ZZ");

			if (AB)
			{
				PowersdrCmds->Append("SH");
			} 
			else
			{
				PowersdrCmds->Append("SB");
			}

			PowersdrCmds->Append(";");
		}
}

void PultToPowersdrProvider::DecrementFrequency(int step, bool AB){
		if (AccMode)
		{	
			PowersdrCmds->Append("ZZ");

			if (AB)
			{
				PowersdrCmds->Append("BM");
			} 
			else
			{
				PowersdrCmds->Append("AD");
			}

			if (!Acceleration)
			{
				step=PoBtnSt->AC_step;
			}

			if (step<10) { PowersdrCmds->Append("0"); }
			PowersdrCmds->Append(step);
			PowersdrCmds->Append(";");
		}
		else
		{
			PowersdrCmds->Append("ZZ");

			if (AB)
			{
				PowersdrCmds->Append("SG");
			} 
			else
			{
				PowersdrCmds->Append("SA");
			}

			PowersdrCmds->Append(";");
		}
}

void PultToPowersdrProvider::ChangeRitXit(bool RitXit, bool direction){
	int value_i;
	
	if (RitXit)
	{
		if (direction)
		{
			PoBtnSt->RitValue = PoBtnSt->RitValue + Convert::ToInt32(NumRitXit->Value);
		}
		else
		{
			PoBtnSt->RitValue = PoBtnSt->RitValue - Convert::ToInt32(NumRitXit->Value);
		}
		
		PowersdrCmds->Append("ZZRF");
		if (PoBtnSt->RitValue>=0)	{ PowersdrCmds->Append("+"); } 
							else	{ PowersdrCmds->Append("-"); } 

		if (Math::Abs(PoBtnSt->RitValue)<10)   { PowersdrCmds->Append("0"); }
		if (Math::Abs(PoBtnSt->RitValue)<100)  { PowersdrCmds->Append("0"); }
		if (Math::Abs(PoBtnSt->RitValue)<1000) { PowersdrCmds->Append("0"); }

		PowersdrCmds->Append(Math::Abs(PoBtnSt->RitValue));
		PowersdrCmds->Append(";");

 		PoPuPro->SendRitXitSplit("RT");
	}
	else
	{
		if (direction)
		{
			PoBtnSt->XitValue = PoBtnSt->XitValue + Convert::ToInt32(NumRitXit->Value);
		}
		else
		{
			PoBtnSt->XitValue = PoBtnSt->XitValue - Convert::ToInt32(NumRitXit->Value);
		}

		PowersdrCmds->Append("ZZXF");
		if (PoBtnSt->XitValue>=0)	{ PowersdrCmds->Append("+"); } 
		else	{ PowersdrCmds->Append("-"); } 

		if (Math::Abs(PoBtnSt->XitValue)<10)   { PowersdrCmds->Append("0"); }
		if (Math::Abs(PoBtnSt->XitValue)<100)  { PowersdrCmds->Append("0"); }
		if (Math::Abs(PoBtnSt->XitValue)<1000) { PowersdrCmds->Append("0"); }

		PowersdrCmds->Append(Math::Abs(PoBtnSt->XitValue));
		PowersdrCmds->Append(";");

		PoPuPro->SendRitXitSplit("XS");
	}


}

void PultToPowersdrProvider::ClearRIT(void){
	PowersdrCmds->Append("ZZRC;");
	PoBtnSt->RitValue=0;
}

void PultToPowersdrProvider::ClearXIT(void){
	PowersdrCmds->Append("ZZXC;");
	PoBtnSt->XitValue=0;
}

void PultToPowersdrProvider::SetMD(System::String^ md){
	PowersdrCmds->Append("ZZMD");
	PowersdrCmds->Append(md);
	PowersdrCmds->Append(";");

	if (PoPuPro!=nullptr)
	{
		PoBtnSt->MD =md[0]-0x30;
		PoBtnSt->MD<<=4;
		PoBtnSt->MD+=md[1]-0x30;
		PoPuPro->SendMdPAmpBtns();
	}
}

void PultToPowersdrProvider::SetVS(System::String^ vs){
	PowersdrCmds->Append("ZZVS");
	PowersdrCmds->Append(vs);
	PowersdrCmds->Append(";");
}

void PultToPowersdrProvider::SendPreAMP(Byte amp){
	PowersdrCmds->Append("ZZPA");
	PowersdrCmds->Append(amp);
	PowersdrCmds->Append(";");
}

void PultToPowersdrProvider::TurnRitXit(System::String^ cmdName, bool% btnState){
	btnState=!btnState;

	Byte btnbt;

	PowersdrCmds->Append("ZZ");
	PowersdrCmds->Append(cmdName);
	if (btnState)
	{
		PowersdrCmds->Append("1");
	}
	else
	{
		PowersdrCmds->Append("0");
	}
	PowersdrCmds->Append(";");
	
	PoPuPro->SendRitXitSplit(cmdName);
}

void PultToPowersdrProvider::TurnBtnState(System::String^ cmdName, bool% btnState, Byte ON, Byte OFF){
	btnState=!btnState;

	Byte btnbt;

	PowersdrCmds->Append("ZZ");
	PowersdrCmds->Append(cmdName);
	if (btnState)
	{
		PowersdrCmds->Append("1");
		btnbt=ON;
	}
	else
	{
		PowersdrCmds->Append("0");
		btnbt=OFF;
	}
	PowersdrCmds->Append(";");
	
	if (PoPuPro!=nullptr)
	{
		PoBtnSt->BTNs=btnbt;
		PoPuPro->SendMdPAmpBtns();
	}
}

void PultToPowersdrProvider::ChangeBand(System::String^ direction){
	PowersdrCmds->Append("ZZ");
	PowersdrCmds->Append(direction);
	PowersdrCmds->Append(";");
}

void PultToPowersdrProvider::WheelUp(int cmd){
	int temp_i=0;

	if (cmd-64<7)
	{
		temp_i=0;
	}
	else if (cmd-64>57)
	{
		temp_i=100;
	}
	else
	{
		temp_i=(cmd-64-7)*2;
	}
	PowersdrCmds->Append("ZZAG");
	if (temp_i<100)
	{
		PowersdrCmds->Append("0");
	}
	if (temp_i<10)
	{
		PowersdrCmds->Append("0");
	}
	PowersdrCmds->Append(temp_i);
	PowersdrCmds->Append(";");
}

void PultToPowersdrProvider::WheelDwn(int cmd){
	int temp_i=0;

	if (cmd<7)
	{
		temp_i=-20;
	}
	else if (cmd>57)
	{
		temp_i=120;
	}
	else
	{
		temp_i=(cmd-7)*2.8-20;
	}
	PowersdrCmds->Append("ZZAR");
	if (temp_i<0)
	{
		PowersdrCmds->Append("-0");
		if (temp_i>-10)	{ PowersdrCmds->Append("0"); }
	} 
	else
	{
		PowersdrCmds->Append("+");
		if (temp_i<100) { PowersdrCmds->Append("0"); }
		if (temp_i<10)	{ PowersdrCmds->Append("0"); }
	}

	
	PowersdrCmds->Append(Math::Abs(temp_i));
	PowersdrCmds->Append(";");
}

void PultToPowersdrProvider::FreqShift(bool UpDwn){
	if (UpDwn)
	{
		PoBtnSt->FrequencyShift	= PoBtnSt->FrequencyShift + Convert::ToInt32(NumFilt->Value);
	} 
	else
	{
		PoBtnSt->FrequencyShift	= PoBtnSt->FrequencyShift - Convert::ToInt32(NumFilt->Value);
	}
	PowersdrCmds->Append("ZZIT");
	
	if (PoBtnSt->FrequencyShift>=0) { PowersdrCmds->Append("+"); } 
							   else { PowersdrCmds->Append("-"); }

	if (Math::Abs(PoBtnSt->FrequencyShift)<10)	{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyShift)<100)	{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyShift)<1000)	{ PowersdrCmds->Append("0"); }

	PowersdrCmds->Append(Math::Abs(PoBtnSt->FrequencyShift));
	PowersdrCmds->Append(";");
}

void PultToPowersdrProvider::FreqWidth(bool UpDwn){
	if (UpDwn)
	{
		PoBtnSt->FrequencyWidth	= PoBtnSt->FrequencyWidth + Convert::ToInt32(NumFilt->Value);
	} 
	else
	{
		PoBtnSt->FrequencyWidth	= PoBtnSt->FrequencyWidth - Convert::ToInt32(NumFilt->Value);
	}
	PowersdrCmds->Append("ZZIS");

	if (Math::Abs(PoBtnSt->FrequencyWidth)<10)		{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyWidth)<100)		{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyWidth)<1000)	{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyWidth)<10000)	{ PowersdrCmds->Append("0"); }

	PowersdrCmds->Append(PoBtnSt->FrequencyWidth);
	PowersdrCmds->Append(";");

	PoPuPro->SendFilterWidth();
}

void PultToPowersdrProvider::FreqLeft(bool UpDwn){
	if (UpDwn)
	{
		PoBtnSt->FrequencyLeft	= PoBtnSt->FrequencyLeft + Convert::ToInt32(NumFilt->Value);
	} 
	else
	{
		PoBtnSt->FrequencyLeft	= PoBtnSt->FrequencyLeft - Convert::ToInt32(NumFilt->Value);
	}
	PowersdrCmds->Append("ZZFL");

	if (PoBtnSt->FrequencyLeft>=0) { PowersdrCmds->Append("+"); } 
	else { PowersdrCmds->Append("-"); }

	if (Math::Abs(PoBtnSt->FrequencyLeft)<10)	{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyLeft)<100)	{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyLeft)<1000)	{ PowersdrCmds->Append("0"); }

	PowersdrCmds->Append(Math::Abs(PoBtnSt->FrequencyLeft));
	PowersdrCmds->Append(";");

	PoPuPro->SendFilterLow();
}

void PultToPowersdrProvider::FreqRight(bool UpDwn){
	if (UpDwn)
	{
		PoBtnSt->FrequencyRight	= PoBtnSt->FrequencyRight + Convert::ToInt32(NumFilt->Value);
	} 
	else
	{
		PoBtnSt->FrequencyRight	= PoBtnSt->FrequencyRight - Convert::ToInt32(NumFilt->Value);
	}
	PowersdrCmds->Append("ZZFH");

	if (PoBtnSt->FrequencyRight>=0) { PowersdrCmds->Append("+"); } 
	else { PowersdrCmds->Append("-"); }

	if (Math::Abs(PoBtnSt->FrequencyRight)<10)	{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyRight)<100)	{ PowersdrCmds->Append("0"); }
	if (Math::Abs(PoBtnSt->FrequencyRight)<1000)	{ PowersdrCmds->Append("0"); }

	PowersdrCmds->Append(Math::Abs(PoBtnSt->FrequencyRight));
	PowersdrCmds->Append(";");

	PoPuPro->SendFilterHigh();
}

void PultToPowersdrProvider::FBtn(void){
	FPair =! FPair;
	
	if (!FPair)
	{
		PowersdrCmds->Append(tbFFirst->Text);
	}
	else
	{
		PowersdrCmds->Append(tbFSecond->Text);
	}
}

void PultToPowersdrProvider::AccButton(void)
{
	if (AccMode)
	{
		Acceleration=!Acceleration;
	}
	else
	{
		PowersdrCmds->Append("ZZ");

		if (ForOldAccStep)
		{
			PowersdrCmds->Append("SU");
		}
		else
		{
			PowersdrCmds->Append("SD");
		}

		PowersdrCmds->Append(";");
		ForOldAccStep=!ForOldAccStep;
	}
}

bool PultToPowersdrProvider::ProvideCmd(int cmd){
	switch (cmd)
	{
	//Великий валкод
	case 209: IncrementFrequency(0,				BigValCodeAB); return true;
	case 210: IncrementFrequency(Acc1->Value,	BigValCodeAB); return true;
	case 211: IncrementFrequency(Acc2->Value,	BigValCodeAB); return true;
	case 212: IncrementFrequency(Acc3->Value,	BigValCodeAB); return true;
	case 213: IncrementFrequency(Acc4->Value,	BigValCodeAB); return true;
	case 214: IncrementFrequency(Acc5->Value,	BigValCodeAB); return true;

	case 193: DecrementFrequency(0,				BigValCodeAB); return true;
	case 194: DecrementFrequency(Acc1->Value,	BigValCodeAB); return true;
	case 195: DecrementFrequency(Acc2->Value,	BigValCodeAB); return true;
	case 196: DecrementFrequency(Acc3->Value,	BigValCodeAB); return true;
	case 197: DecrementFrequency(Acc4->Value,	BigValCodeAB); return true;
	case 198: DecrementFrequency(Acc5->Value,	BigValCodeAB); return true;

	//правий малий валкод, 00
	case 248: IncrementFrequency(1, true); return true;
	case 240: DecrementFrequency(1, true); return true;

	//правий малий валкод, 10
	case 249: ChangeRitXit(false, true);  return true;
	case 241: ChangeRitXit(false, false); return true;

	//правий малий валкод, 01
	case 250: ChangeRitXit(true, true);  return true;
	case 242: ChangeRitXit(true, false); return true;

	//лівий малий валкод, 00
	case 232: FreqShift(true);  return true;
	case 224: FreqShift(false); return true;

	//лівий малий валкод, 10
	case 233: FreqLeft(true);  return true;
	case 225: FreqLeft(false); return true;

	//лівий малий валкод, 01
	case 234: FreqRight(true);  return true;
	case 226: FreqRight(false); return true;

	//лівий малий валкод, 11
	case 235: FreqWidth(true);  return true;
	case 227: FreqWidth(false); return true;

	//кнопки режиму і передачі
	case 185: modeBtn+=2; modeBtn%=3; return true;
	case 183: pttBtn=1; return true;

	//кнопка A|B
	case 174: BigValCodeAB=!BigValCodeAB; return true;

	//кнопка F
	case 178: FBtn(); return true;

	//кнопка викл прискорення
	case 168: AccButton();  return true;

	//кнопки, нумерація зліва
	//1 верхня
	case 165: switch (modeBtn)
			  {
				case 0: ClearRIT(); break;
				case 2: TurnBtnState("NR", PoBtnSt->NR, 0x10, 0x20); break;
				case 1: SetMD("04"); break;
			  }
			  modeBtn=0;
	return true;

	//1 нижня
	case 175: switch (modeBtn)
			  {
				case 0: ClearXIT(); break;
				case 2: TurnBtnState("NT", PoBtnSt->ANF, 0x01, 0x02); break;
				case 1: SetMD("03"); break;
			  }
			  modeBtn=0;
	return true;

	//2 верхня
	case 162: switch (modeBtn)
			  {
				case 0: TurnRitXit("RT", PoBtnSt->RIT); break;
				case 2: TurnBtnState("NA", PoBtnSt->NB, 0x30, 0x40); break;
				case 1: SetMD("01"); break;
			  }
			  modeBtn=0;
	return true;

	//2 нижня
	case 172: switch (modeBtn)
			  {
				case 0: TurnRitXit("XS", PoBtnSt->XIT); break;
				case 2: TurnBtnState("NB", PoBtnSt->NB2, 0x03, 0x04); break;
				case 1: SetMD("00"); break;
			  }
			  modeBtn=0;
	return true;
	
	//3 верхня
	case 161: switch (modeBtn)
			  {
				case 0: SetVS("0"); break;
				case 2: TurnBtnState("SR", PoBtnSt->SR, 0x50, 0x60); break;
				case 1: SetMD("06"); break;
			  }
			  modeBtn=0;
	return true;

	//3 нижня
	case 171: switch (modeBtn)
			  {
				case 0: TurnRitXit("SP", PoBtnSt->SPLIT); break;
				case 2: TurnBtnState("BI", PoBtnSt->BIN, 0x05, 0x06); break;
				case 1: SetMD("05"); break;
			  }
			  modeBtn=0;
	return true;
	
	//4 верхня
	case 166: switch (modeBtn)
			  {
				case 0: SetVS("1"); break;
				case 2: TurnRitXit("MU", PoBtnSt->m_RX); break;
				default: return false;
			  }
			  modeBtn=0;
	return true;

    //4 нижня
	case 176: switch (modeBtn)
			  {
				case 0: SetVS("2"); break;
				default: return false;
			  }
			  modeBtn=0;
	return true;

	//5 верхня
	case 167: switch (modeBtn)
			  {
 				case 0: ChangeBand("BU"); break;
				case 2: if (PoBtnSt->PreAMP<3)
						{
							PoBtnSt->PreAMP++;
						}
						SendPreAMP(PoBtnSt->PreAMP); break;
				default: return false;
			  }
			  modeBtn=0;
	return true;

	//5 нижня
	case 177: switch (modeBtn)
			  {
				case 0: ChangeBand("BD"); break;
				case 2: if (PoBtnSt->PreAMP>0)
						{
							PoBtnSt->PreAMP--;
						}
						SendPreAMP(PoBtnSt->PreAMP); break;
				default: return false;
			  }
			  modeBtn=0;
	return true;

	//відповідь на перевірку версії
	case 129: return true;

	default: if (cmd<64)
			 {
				 WheelDwn(cmd);
				 return true;
			 } 
			 else if (cmd<128)
			 {
				 WheelUp(cmd);
				 return true;
			 }
			 else return false;
	}

	return false;
}

