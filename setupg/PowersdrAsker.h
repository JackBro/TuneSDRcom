#pragma once
ref class PowersdrAsker
{
public:
	PowersdrAsker(void);
	System::String^ GetQuestion(void);


	bool UseZZFA;
private:
	array<System::String^,1>^ Messages;
	int iterator;

	
};

