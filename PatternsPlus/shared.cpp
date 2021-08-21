
#include "shared.h"

Shared::Shared() {


}

void Shared::clearBuffer()
{
	int i = BUFFER_LEN - 1;
	bufferPipe[i] = 0;
	while (i >= 0) {
		bufferPipe[i] = 0;
		i -= 1;
	}
	bufferPipe[0] = 0;
	
}
