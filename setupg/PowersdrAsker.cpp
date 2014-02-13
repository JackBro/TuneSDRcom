#include "StdAfx.h"
#include "PowersdrAsker.h"


PowersdrAsker::PowersdrAsker(void)
{
	iterator=-1;
	Messages = gcnew array<System::String^,1>(17);
	Messages[0]="ZZMD;";
	Messages[1]="ZZNR;";
	Messages[2]="ZZNT;";
	Messages[3]="ZZRT;";
	Messages[4]="ZZNA;";
	Messages[5]="ZZXS;";
	Messages[6]="ZZNB;";
	Messages[7]="ZZSR;";
	Messages[8]="ZZSP;";
	Messages[9]="ZZBI;";
	Messages[10]="ZZMU;";
	Messages[11]="ZZPA;";
	Messages[12]="ZZIT;";
	Messages[13]="ZZIS;";
	Messages[14]="ZZFL;";
	Messages[15]="ZZFH;";
	Messages[16]="ZZAC;";
}

System::String^ PowersdrAsker::GetQuestion(void){
	iterator++;
	if (iterator == Messages.Length) iterator=0;
	return Messages[iterator];
}