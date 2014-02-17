#include "StdAfx.h"
#include "PowersdrToPultProvider.h"



PowersdrToPultProvider::PowersdrToPultProvider(void)
{
	PowerAnswer = gcnew array<Byte,1>(4096);
	PowerAnswerIterator = 0;
	LED=0x00;
	SM0=0;

	smMatrix = gcnew array<Byte,1>(261);
	smMatrixActive = false;

	MdPAmpBtnsChanged=true;
}

bool PowersdrToPultProvider::ProvideAnswer(System::String^ answer)
{
	if (answer->Length>0)
	if (answer[0]=='?')
	{
		return false;
	}
	
	if (answer->Length>6)
	if (answer[0]!='Z' || answer[1]!='Z')
	{
		return false;
	}
	
	if (answer->Length>14)
    if (answer[2]=='F' && answer[3]=='A'){
		ZZFA(answer);
// 		if (answer->Length>21)
// 		{
// 			return ProvideAnswer(answer->Remove(0,16));
// 		}
		return true;
	}

	if (answer->Length>14)
	if (answer[2]=='F' && answer[3]=='B'){
		ZZFB(answer);
// 		if (answer->Length>21)
// 		{
// 			return ProvideAnswer(answer->Remove(0,16));
// 		}
		return true;
	}

	if (answer->Length>6) //7?
	if (answer[2]=='S' && answer[3]=='M' && answer[4]=='0'){
		SetSM0(answer);
		SendSmLed();
// 		if (answer->Length>7)
// 		{
// 			return ProvideAnswer(answer->Remove(0,6));
// 		}
		return true;
	}

	if (answer->Length>5)
	{
#pragma region Modulation
		if (answer[2]=='M' && answer[3]=='D'){

			PoBtnSt->MD=answer[4]-0x30;
			PoBtnSt->MD<<=4;
			PoBtnSt->MD+=answer[5]-0x30;

			MdPAmpBtnsChanged=true;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,6));
			}
			return true;
		}
#pragma endregion
	}

	if (answer->Length>4)
	{
#pragma region NR
		if (answer[2]=='N' && answer[3]=='R'){
		
			if (answer[4]=='1')
			{
				PoBtnSt->BTNs=0x10;
				PoBtnSt->NR=true;
			}
			else
			{
				PoBtnSt->BTNs=0x20;
				PoBtnSt->NR=false;
			}

			MdPAmpBtnsChanged=true;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
#pragma region ANF
		if (answer[2]=='N' && answer[3]=='T'){

			if (answer[4]=='1')
			{
				PoBtnSt->BTNs=0x01;
				PoBtnSt->ANF=true;
			}
			else
			{
				PoBtnSt->BTNs=0x02;
				PoBtnSt->ANF=false;
			}

			MdPAmpBtnsChanged=true;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
#pragma region NB
		if (answer[2]=='N' && answer[3]=='A'){

			if (answer[4]=='1')
			{
				PoBtnSt->BTNs=0x30;
				PoBtnSt->NB=true;
			}
			else
			{
				PoBtnSt->BTNs=0x40;
				PoBtnSt->NB=false;
			}

			MdPAmpBtnsChanged=true;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
#pragma region NB2
		if (answer[2]=='N' && answer[3]=='B'){

			if (answer[4]=='1')
			{
				PoBtnSt->BTNs=0x03;
				PoBtnSt->NB2=true;
			}
			else
			{
				PoBtnSt->BTNs=0x04;
				PoBtnSt->NB2=false;
			}

			MdPAmpBtnsChanged=true;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
#pragma region SR
		if (answer[2]=='S' && answer[3]=='R'){

			if (answer[4]=='1')
			{
				PoBtnSt->BTNs=0x50;
				PoBtnSt->SR=true;
			}
			else
			{
				PoBtnSt->BTNs=0x60;
				PoBtnSt->SR=false;
			}

			MdPAmpBtnsChanged=true;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
#pragma region BIN
		if (answer[2]=='B' && answer[3]=='I'){

			if (answer[4]=='1')
			{
				PoBtnSt->BTNs=0x05;
				PoBtnSt->BIN=true;
			}
			else
			{
				PoBtnSt->BTNs=0x06;
				PoBtnSt->BIN=false;
			}

			MdPAmpBtnsChanged=true;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion

#pragma region RIT
		if (answer[2]=='R' && answer[3]=='T'){

			if (answer[4]=='1')
			{
				PoBtnSt->RIT=true;
			}
			else
			{
				PoBtnSt->RIT=false;
			}

			SendRitXitSplit("RT");

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
#pragma region XIT
		if (answer[2]=='X' && answer[3]=='S'){

			if (answer[4]=='1')
			{
				PoBtnSt->XIT=true;
			}
			else
			{
				PoBtnSt->XIT=false;
			}

			SendRitXitSplit("XS");

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
#pragma region SPLIT
		if (answer[2]=='S' && answer[3]=='P'){

			if (answer[4]=='1')
			{
				PoBtnSt->SPLIT=true;
			}
			else
			{
				PoBtnSt->SPLIT=false;
			}

			SendRitXitSplit("SP");

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion

#pragma region PreAMP
		if (answer[2]=='P' && answer[3]=='A'){

			PoBtnSt->PreAMP=answer[4]-0x30;

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion

#pragma region AC_step
		if (answer[2]=='A' && answer[3]=='C'){

			PoBtnSt->AC_step = (answer[4]-0x30)*10+(answer[5]-0x30);

			if (answer->Length>6)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
	}

	if (answer->Length>8)
	{
#pragma region ZZIT Freq Filter Shift 
		if (answer[2]=='I' && answer[3]=='T'){
			int temp_i=0;

			temp_i+=(answer[5]-0x30)*1000;
			temp_i+=(answer[6]-0x30)*100;
			temp_i+=(answer[7]-0x30)*10;
			temp_i+= answer[8]-0x30;

			if (answer[4]=='-')
			{
				temp_i=-temp_i;
			}

			PoBtnSt->FrequencyShift=temp_i;

			if (answer->Length>11)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion

#pragma region ZZIS Freq Filter Width 
		if (answer[2]=='I' && answer[3]=='S'){
			int temp_i=0;

			temp_i+=(answer[4]-0x30)*10000;
			temp_i+=(answer[5]-0x30)*1000;
			temp_i+=(answer[6]-0x30)*100;
			temp_i+=(answer[7]-0x30)*10;
			temp_i+= answer[8]-0x30;

			PoBtnSt->FrequencyWidth=temp_i;

			SendFilterWidth();

			if (answer->Length>11)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion

#pragma region ZZFL Freq Filter Low 
		if (answer[2]=='F' && answer[3]=='L'){
			int temp_i=0;

			temp_i+=(answer[5]-0x30)*1000;
			temp_i+=(answer[6]-0x30)*100;
			temp_i+=(answer[7]-0x30)*10;
			temp_i+= answer[8]-0x30;

			if (answer[4]=='-')
			{
				temp_i=-temp_i;
			}

			PoBtnSt->FrequencyLeft=temp_i;

			SendFilterLow();

			if (answer->Length>11)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion

#pragma region ZZFH Freq Filter High 
		if (answer[2]=='F' && answer[3]=='H'){
			int temp_i=0;

			temp_i+=(answer[5]-0x30)*1000;
			temp_i+=(answer[6]-0x30)*100;
			temp_i+=(answer[7]-0x30)*10;
			temp_i+= answer[8]-0x30;

			if (answer[4]=='-')
			{
				temp_i=-temp_i;
			}

			PoBtnSt->FrequencyRight=temp_i;

			SendFilterHigh();

			if (answer->Length>11)
			{
				return ProvideAnswer(answer->Remove(0,5));
			}
			return true;
		}
#pragma endregion
	}

	return false;
}

void PowersdrToPultProvider::ZZFA(System::String^ answer){
	Byte temp_byte;

	try
	{
		System::String^ freqValue = answer->Substring(4);
		PoBtnSt->Frequency = Convert::ToInt32(freqValue);
	}
	catch (...)
	{}
	
	temp_byte=0xA0;
	temp_byte+=answer[7]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;
	
	temp_byte =answer[8]-0x30;
	temp_byte<<=4;
	temp_byte+=answer[9]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;

	temp_byte =answer[10]-0x30;
	temp_byte<<=4;
	temp_byte+=answer[11]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;

	temp_byte =answer[12]-0x30;
	temp_byte<<=4;
	temp_byte+=answer[13]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;
}

void PowersdrToPultProvider::ZZFB(System::String^ answer){
	Byte temp_byte;

	temp_byte=0xB0;
	temp_byte+=answer[7]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;

	temp_byte =answer[8]-0x30;
	temp_byte<<=4;
	temp_byte+=answer[9]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;

	temp_byte =answer[10]-0x30;
	temp_byte<<=4;
	temp_byte+=answer[11]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;

	temp_byte =answer[12]-0x30;
	temp_byte<<=4;
	temp_byte+=answer[13]-0x30;
	PowerAnswer[PowerAnswerIterator]=temp_byte;
	PowerAnswerIterator++;
}

void PowersdrToPultProvider::SendSmLed(void){
	PowerAnswer[PowerAnswerIterator]=0xC0;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=0x00;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=LED;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=SM0;
	PowerAnswerIterator++;
}

void PowersdrToPultProvider::SendMdPAmpBtns(void){
// 	if (!MdPAmpBtnsChanged)
// 	{
// 		return;
// 	}

	MdPAmpBtnsChanged=false;

	PowerAnswer[PowerAnswerIterator] = 0xC1;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] = PoBtnSt->MD;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] = PoBtnSt->PreAMP;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] = PoBtnSt->BTNs;
	PowerAnswerIterator++;
}

void PowersdrToPultProvider::SendTime(void){
	System::String^ time = DateTime::Now.ToString("HHmmss");

	PowerAnswer[PowerAnswerIterator]=0xC7;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] =time[0]-0x30;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=time[1]-0x30;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] =time[2]-0x30;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=time[3]-0x30;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] =time[4]-0x30;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=time[5]-0x30;
	PowerAnswerIterator++;
}

void PowersdrToPultProvider::SendDate(void){
	System::String^ date = DateTime::Now.ToString("ddMMyy");

	PowerAnswer[PowerAnswerIterator]=0xC8;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] =date[0]-0x30;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=date[1]-0x30;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] =date[2]-0x30;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=date[3]-0x30;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator] =date[4]-0x30;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=date[5]-0x30;
	PowerAnswerIterator++;
}

void PowersdrToPultProvider::SetLED(int mode, int ptt){
	LED = mode;
	LED<<=4;
	LED +=ptt;
}

void PowersdrToPultProvider::SetSM0(System::String^ answer){
	int number = (answer[5]-0x30) * 100 + (answer[6]-0x30) * 10 + (answer[7]-0x30);
	
	if (!smMatrixActive)
	{
		SM0=(number/2-38)/3.375;
	}
	else
	{
		SM0=smMatrix[number];
	}
	
}

void PowersdrToPultProvider::SendRitXitSplit(System::String^ cmdName){
	PowerAnswer[PowerAnswerIterator]=0xC2;
	PowerAnswerIterator++;

	int temp_i;

	if (cmdName=="RT")
	{
		if (PoBtnSt->RIT)
		{
			if (PoBtnSt->RitValue>=0)
			{
				PowerAnswer[PowerAnswerIterator]=0x00;
				temp_i = PoBtnSt->RitValue;
			} 
			else
			{
				PowerAnswer[PowerAnswerIterator]=0x01;
				temp_i = -PoBtnSt->RitValue;
			}
		}
		else
		{
			PowerAnswer[PowerAnswerIterator]=0x02;
			temp_i=0;
		}
		PowerAnswerIterator++;
		
		PowerAnswer[PowerAnswerIterator] =temp_i/10000;
		PowerAnswer[PowerAnswerIterator]<<=4;
		PowerAnswer[PowerAnswerIterator]+=temp_i%10000/1000;
		PowerAnswerIterator++;

		PowerAnswer[PowerAnswerIterator] =temp_i%1000/100;
		PowerAnswer[PowerAnswerIterator]<<=4;
		PowerAnswer[PowerAnswerIterator]+=temp_i%100/10;
		PowerAnswerIterator++;
	}
	else
		if (cmdName=="XS")
		{
			if (PoBtnSt->XIT)
			{
				if (PoBtnSt->XitValue>=0)
				{
					PowerAnswer[PowerAnswerIterator]=0x03;
					temp_i = PoBtnSt->XitValue;
				} 
				else
				{
					PowerAnswer[PowerAnswerIterator]=0x04;
					temp_i = -PoBtnSt->XitValue;
				}
			}
			else
			{
				PowerAnswer[PowerAnswerIterator]=0x05;
			}
			PowerAnswerIterator++;
		
			PowerAnswer[PowerAnswerIterator] =temp_i/10000;
			PowerAnswer[PowerAnswerIterator]<<=4;
			PowerAnswer[PowerAnswerIterator]+=temp_i%10000/1000;
			PowerAnswerIterator++;

			PowerAnswer[PowerAnswerIterator] =temp_i%1000/100;
			PowerAnswer[PowerAnswerIterator]<<=4;
			PowerAnswer[PowerAnswerIterator]+=temp_i%100/10;
			PowerAnswerIterator++;
		}
		else
			if (cmdName=="SP")
			{
				if (PoBtnSt->SPLIT)
				{
					PowerAnswer[PowerAnswerIterator]=0x06;
				}
				else
				{
					PowerAnswer[PowerAnswerIterator]=0x07;
				}
				PowerAnswerIterator++;

				PowerAnswer[PowerAnswerIterator]=0x00;
				PowerAnswerIterator++;

				PowerAnswer[PowerAnswerIterator]=0x00;
				PowerAnswerIterator++;
			}

}

void PowersdrToPultProvider::SendFilterWidth(void)	{
	PowerAnswer[PowerAnswerIterator]=0xC3;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=0x02;
	PowerAnswerIterator++;

	if (PoBtnSt->FrequencyWidth<1000)
	{
		PowerAnswer[PowerAnswerIterator]=PoBtnSt->FrequencyWidth/100;
		PowerAnswerIterator++;

		PowerAnswer[PowerAnswerIterator]=(PoBtnSt->FrequencyWidth%100)/10;
		PowerAnswer[PowerAnswerIterator]<<=4;
		PowerAnswer[PowerAnswerIterator]+=PoBtnSt->FrequencyWidth%10;
		PowerAnswerIterator++;
	} 
	else if (PoBtnSt->FrequencyWidth<10000)
	{
		PowerAnswer[PowerAnswerIterator]=0x10;
		PowerAnswerIterator++;

		PowerAnswer[PowerAnswerIterator]=(PoBtnSt->FrequencyWidth%10000)/1000;
		PowerAnswer[PowerAnswerIterator]<<=4;
		PowerAnswer[PowerAnswerIterator]+=(PoBtnSt->FrequencyWidth%1000)/100;
		PowerAnswerIterator++;
	}
	else if (PoBtnSt->FrequencyWidth<100000)
	{
		PowerAnswer[PowerAnswerIterator]=0x20;
		PowerAnswerIterator++;

		PowerAnswer[PowerAnswerIterator]=(PoBtnSt->FrequencyWidth%100000)/10000;
		PowerAnswer[PowerAnswerIterator]<<=4;
		PowerAnswer[PowerAnswerIterator]+=(PoBtnSt->FrequencyWidth%10000)/1000;
		PowerAnswerIterator++;
	}
}

void PowersdrToPultProvider::SendFilterLow(void){
	PowerAnswer[PowerAnswerIterator]=0xC3;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=0x00;
	PowerAnswerIterator++;

	if (PoBtnSt->FrequencyLeft>=0)
	{
		PowerAnswer[PowerAnswerIterator]=0x00;
	}
	else
	{
		PowerAnswer[PowerAnswerIterator]=0x10;
	}
	PowerAnswer[PowerAnswerIterator]+=Math::Abs(PoBtnSt->FrequencyLeft)/1000;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=(Math::Abs(PoBtnSt->FrequencyLeft)%1000)/100;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=(Math::Abs(PoBtnSt->FrequencyLeft)%100)/10;
	PowerAnswerIterator++;

}

void PowersdrToPultProvider::SendFilterHigh(void){
	PowerAnswer[PowerAnswerIterator]=0xC3;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=0x01;
	PowerAnswerIterator++;

	if (PoBtnSt->FrequencyRight>=0)
	{
		PowerAnswer[PowerAnswerIterator]=0x00;
	}
	else
	{
		PowerAnswer[PowerAnswerIterator]=0x10;
	}
	PowerAnswer[PowerAnswerIterator]+=Math::Abs(PoBtnSt->FrequencyRight)/1000;
	PowerAnswerIterator++;

	PowerAnswer[PowerAnswerIterator]=(Math::Abs(PoBtnSt->FrequencyRight)%1000)/100;
	PowerAnswer[PowerAnswerIterator]<<=4;
	PowerAnswer[PowerAnswerIterator]+=(Math::Abs(PoBtnSt->FrequencyRight)%100)/10;
	PowerAnswerIterator++;

}
