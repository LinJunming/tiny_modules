#include "encoder.h"
#include <unistd.h>

int main()
{
	int i = 10;
	Encoder encoder;
	encoder.Init();

	while (i--){
		int j = 3;
		
		std::cout<< "========>   Group " << i << "   <========" << std::endl;
		while (j--)
			encoder.Sync();
		encoder.Encode();
		std::cout<< std::endl;
	}

	return 0;
}