#include "../include/Hamlet.h"
#include "My_Lib.h"

int main (int argc, char *argv[])
{
    Open_Log_File ("Hamlet");

    if (argc != 3)
        MY_ASSERT (false, "int argc", UNEXP_VAL, ERROR);

    struct Basic_Data hamlet =
    {
        argv[1],    //source
        argv[2],    //result
        NULL,
        NULL,
        NULL,
        0L,
        0
    };

    if (Run_Hamlet (&hamlet) == ERROR)
        MY_ASSERT (false, "Run_Hamlet ()", FUNC_ERROR, ERROR);

    return 0;
}
