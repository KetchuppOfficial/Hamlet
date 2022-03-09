#ifndef HAMLET_H_INCLUDED
#define HAMLET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
#define MY_ASSERT(condition, var, description, ...)                                 \
{                                                                                   \
    if (!(condition))                                                               \
    {                                                                               \
        My_Assert (false, __FILE__, __LINE__, __FUNCTION__, (var), (description));  \
        __VA_ARGS__;                                                                \
    }                                                                               \
}
*/
struct Basic_Data
{
    FILE *file_input_ptr;
    const char *file_input_name;
    const char *file_sort_name;
    struct string **str_arr_ptr;
    struct string *str_ar;
    char *buffer;
    long n_symbs;
    int n_strings;
};

struct string
{
    char *beginning;
    char *ending;
};

//---------------------------------
/*
const char PREAMBLE[] = "This is log file of the project \"Hamlet Sorting\".\n"
                        "This file will help you to find and fix all the errors.\n\n";
*/
enum COMPARISON
{
    NOT_EQUAL = -2,
    LESS,
    EQUAL,
    GREATER
};

//---------------------------------

int Run_Hamlet          (struct Basic_Data *structure);

/**
    \brief Prepares buffer for further work

    Checks each element of the buffer.
    If the function finds the sign of the end of the line,
    it increments the number counted of strings and
    starts putting '\0' symbols up to the next letter-symbol.

    \param [out] buffer {pointer on the array with content of file}
    \param [in] n_symbs {the number of elements of the buffer}

*/
int Make_Strings        (char *buffer, const long n_symbs);

/**
    \brief Copies the content of a file into the buffer

    Uses dynamic memory to allocate space for the array of pointers on structures.
    If it is not able to allocate enough memory, calls MY_ASSERT to put warning into log file and returns NULL.
    Then the content of the file copies into this array.
    If the number of symbols in the file is not equal to the number of the symbols that have been copied,
    the function prints  warning on the screen.

    \param [in] file_ptr {pointer on the file}
    \param [in] n_symbs {number of symbols in the file}
    \return buffer {pointer on the array with content of file}

*/
int Make_Arrays         (struct Basic_Data *structure);

/**
    \brief Finds the first and the last letter of each string

    Sets one pointer on the first letter of each string and another one on the last letter.

    \param [out] str_ar {pointer on the array of structures}
    \param [out] buffer {pointer on the array with content of file}
    \param [in] n_symbs {number of symbols in the file}
    \return ERROR/NO_ERRORS {if finds an error, returns ERROR; if there is no error - returns NO_ERRORS}
*/
int Find_String_Borders (struct string *str_ar, char *buffer, const long n_symbs);

/**
    \brief Calls free () for all dynamic arrays in the program

    \param [out] str_ar {pointer on the array of structures}
    \param [out] str_arr_ptr {pointer on the array of pointers on structures}
    \param [out] buffer {pointer on the array with content of file}
*/
int Memory_Free         (struct string *str_ar, struct string **str_arr_ptr, char *buffer);

int Sort_And_Print      (struct string *str_ar, struct string **str_arr_ptr, const int n_strings, const char *file_sort_name);
int Beginning           (FILE *file_sort_ptr, struct string **str_arr_ptr, const int n_strings);
int Ending              (FILE *file_sort_ptr, struct string **str_arr_ptr, const int n_strings);
int Print_Original      (FILE *file_sort_ptr, struct string *str_ar, const int n_strings);
int Check_Order         (struct string **str_arr_ptr, int n_strings, bool mode);
int My_QSort            (void* arr_ptr[], int begin_i, int end_i, int (*cmp_ptr) (const void *, const void *));
int My_Swap             (void *arr_ptr[], int first, int second);
int My_Strcmp_Beginning (const void *struct_1, const void *struct_2);
int My_Strcmp_Ending    (const void *struct_1, const void *struct_2);

//---------------------------------

#endif // HAMLET_H_INCLUDED
