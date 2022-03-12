#include "Hamlet.h"
#include "../My_Lib/My_Lib.h"

extern FILE *LOG_FILE;

int Run_Hamlet (struct Basic_Data *structure)
{
    MY_ASSERT (structure, "struct Basic_Data *structure", NULL_PTR, ERROR);

    structure->file_input_ptr = Open_File (structure->file_input_name, "rb");
    if (structure->file_input_ptr == NULL)
        return ERROR;

    structure->n_symbs = Define_File_Size (structure->file_input_ptr);
    if (structure->n_symbs == ERROR)
        return ERROR;

    structure->buffer = Make_Buffer (structure->file_input_ptr, structure->n_symbs);
    if (structure->buffer == NULL)
        return ERROR;

    if (Close_File (structure->file_input_ptr, structure->file_input_name) == ERROR)
        return ERROR;

    structure->n_strings = Make_Strings (structure->buffer, structure->n_symbs);
    if (structure->n_strings == ERROR)
        return ERROR;

    if (Make_Arrays (structure) == ERROR)
        return ERROR;

    if (Find_String_Borders (structure->str_ar, structure->buffer, structure->n_symbs) == ERROR)
        return ERROR;

    if (Sort_And_Print (structure->str_ar, structure->str_arr_ptr, structure->n_strings, structure->file_sort_name) == ERROR)
        return ERROR;

    if (Memory_Free (structure->str_ar, structure->str_arr_ptr, structure->buffer) == ERROR)
        return ERROR;

    return NO_ERRORS;
}

int Make_Strings (char *buffer, const long n_symbs)
{
    MY_ASSERT (buffer,      "char *buffer",       NULL_PTR, ERROR);
    MY_ASSERT (n_symbs > 0, "const long n_symbs", POS_VAL,  ERROR); 

    int  n_strings = 0, symb_i = 0;
    bool is_new_line = false;

    while (symb_i < n_symbs)
    {
        if (buffer[symb_i] == '\n' || buffer[symb_i] == '\r')
        {
            is_new_line = true;

            n_strings++;
            while (isspace (buffer[symb_i]) || buffer[symb_i] == '\0')
            {
                buffer[symb_i] = '\0';
                symb_i++;
                if (symb_i == n_symbs)
                    break;
            }
        }
        else
        {
            symb_i++;
            is_new_line = false;
        }
    }

    if (!is_new_line)
        n_strings++;

    return n_strings;
}

int Make_Arrays (struct Basic_Data *structure)
{
    MY_ASSERT (structure, "struct Basic_Data *structure", NULL_PTR, ERROR);

    structure->str_ar = (struct string *)calloc (structure->n_strings + 1, sizeof (struct string));
    MY_ASSERT (structure->str_ar, "structure->str_ar", NE_MEM, ERROR);

    structure->str_arr_ptr = (struct string **)calloc (structure -> n_strings + 1, sizeof (struct string *));
    MY_ASSERT (structure->str_arr_ptr, "structure -> str_arr_ptr", NE_MEM, ERROR);

    for (int index = 0; index < structure->n_strings; index++)
        (structure->str_arr_ptr)[index] = &(structure->str_ar)[index];

    return NO_ERRORS;
}

int Find_String_Borders (struct string *str_ar, char *buffer, const long n_symbs)
{
    MY_ASSERT (str_ar,      "struct string *str_ar", NULL_PTR, ERROR);
    MY_ASSERT (buffer,      "char *buffer",          NULL_PTR, ERROR);
    MY_ASSERT (n_symbs > 0, "const long n_symbs",    NULL_PTR, ERROR);

    int str_i   = 0;
    long symb_i = 0;
    bool in_str        = true;
    bool str_beginning = true;

    while (symb_i < n_symbs)
    {
        if (buffer[symb_i] == '\0')
        {
            if (in_str)
            {
                in_str = false;

                int end_i = symb_i - 1;
                while (isspace(buffer[end_i]))
                    end_i--;

                str_ar[str_i].ending = &buffer[end_i];
                    str_i++;
            }
            while (symb_i < n_symbs && buffer[symb_i] == '\0')
                symb_i++;
        }
        else
        {
            if (in_str)
            {
                if (str_beginning)
                {
                    while (isspace(buffer[symb_i]) || buffer[symb_i] == '\0')
                        symb_i++;

                    str_ar[str_i].beginning = &buffer[symb_i];
                    str_beginning = false;
                }
                symb_i++;
            }
            else
                in_str = str_beginning = true;
        }
    }

    return NO_ERRORS;
}

int Memory_Free (struct string *str_ar, struct string **str_arr_ptr, char *buffer)
{
    MY_ASSERT (str_ar,      "struct string *str_ar",      NULL_PTR, ERROR);
    MY_ASSERT (str_arr_ptr, "struct string *str_arr_ptr", NULL_PTR, ERROR);

    free (str_ar);
    free (str_arr_ptr);
    free (buffer);

    return NO_ERRORS;
}
