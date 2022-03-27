#include "Program.h"

void main()
{
    scoped_interpreter guard{}; // Python Interpreter
    Program program;
    program.Run();
}
