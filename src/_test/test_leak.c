#include "test.h"

// export MallocStackLogging=1 find leaks after unset MallocStackLogging
// if you want more info about leaks use gcc -g option
// while true; do leaks a.out; sleep 1; done;
void	leak(void)
{
	system("leaks --list miniRT");
}
