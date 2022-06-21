#ifndef HAMLET_H_INCLUDED
#define HAMLET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Basic_Data
{
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

enum COMPARISON
{
    NOT_EQUAL = -2,
    LESS,
    EQUAL,
    GREATER
};

//---------------------------------

int Run_Hamlet          (struct Basic_Data *structure);
int Make_Strings        (char *buffer, const long n_symbs);
int Make_Arrays         (struct Basic_Data *structure);
int Find_String_Borders (struct string *str_ar, char *buffer, const long n_symbs);
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

#endif
