#include "UserProgram.h"

void main()
{
    scoped_interpreter guard{}; // Python Interpreter
    UserProgram program;
    program.Run();
}
