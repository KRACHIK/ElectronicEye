#include "Application.h"
#include "BaseType.h"

#include <iostream>

int main()
{
	while (true)
	{
		CSetting Setting;

		CApplication  ApplicationBionicEyeVIDIO(Setting);

		ApplicationBionicEyeVIDIO.WhileTrue();
	}

	return 0;
}
