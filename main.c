#include "Hamlet.h"
#include "../My_Lib/My_Lib.h"

int main (int argc, char *argv[])
{
    OPEN_LOG_FILE;

    if (argc < 2)
        MY_ASSERT (false, "int argc", NOT_ENOUGH_ARGS, ERROR);

    struct Basic_Data hamlet =
    {
        NULL,
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
