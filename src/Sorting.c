#include "../include/Hamlet.h"
#include "My_Lib.h"

int Sort_And_Print (struct string *str_ar, struct string **str_arr_ptr,
                    const int n_strings, const char *file_sort_name)
{
    MY_ASSERT (str_ar,         "struct string *str_ar",       NULL_PTR, ERROR);
    MY_ASSERT (str_arr_ptr,    "struct string **str_arr_ptr", NULL_PTR, ERROR);
    MY_ASSERT (n_strings > 0,  "const int n_strings",         POS_VAL,  ERROR);
    MY_ASSERT (file_sort_name, "const char *file_sort_name",  NULL_PTR, ERROR);

    FILE *file_sort_ptr = Open_File (file_sort_name, "wb");
    if (file_sort_ptr == NULL)
        return ERROR;

    if (Beginning      (file_sort_ptr, str_arr_ptr, n_strings) == ERROR ||
        Ending         (file_sort_ptr, str_arr_ptr, n_strings) == ERROR ||
        Print_Original (file_sort_ptr, str_ar,      n_strings) == ERROR)
        return ERROR;

    if (Close_File (file_sort_ptr, file_sort_name) == ERROR)
        return ERROR;

    return NO_ERRORS;
}

int Beginning (FILE *file_sort_ptr, struct string **str_arr_ptr, const int n_strings)
{
    MY_ASSERT (file_sort_ptr, "FILE *file_sort_ptr",         NULL_PTR, ERROR);
    MY_ASSERT (str_arr_ptr,   "struct string **str_arr_ptr", NULL_PTR, ERROR);
    MY_ASSERT (n_strings > 0, "const int n_strings",         POS_VAL,  ERROR);

    if (My_QSort ((void **)str_arr_ptr, 0, n_strings - 1, My_Strcmp_Beginning) == ERROR)
        return ERROR;

    fprintf(file_sort_ptr, "HERE COMES BEGINNING SORTING\n\n");

    for (int str_i = 0; str_i < n_strings; str_i++)
        fprintf (file_sort_ptr, "%s\n", str_arr_ptr[str_i]->beginning);

    Check_Order (str_arr_ptr, n_strings, true);

    return NO_ERRORS;
}

int Ending (FILE *file_sort_ptr, struct string **str_arr_ptr, const int n_strings)
{
    MY_ASSERT (file_sort_ptr, "FILE *file_sort_ptr",         NULL_PTR, ERROR);
    MY_ASSERT (str_arr_ptr,   "struct string **str_arr_ptr", NULL_PTR, ERROR);
    MY_ASSERT (n_strings > 0, "const int n_strings",         POS_VAL,  ERROR);

    if (My_QSort ((void **)str_arr_ptr, 0, n_strings - 1, My_Strcmp_Ending) == ERROR)
        return ERROR;

    fprintf (file_sort_ptr, "\n\nHERE COMES END SORTING\n\n");
    for (int str_i = 0; str_i < n_strings; str_i++)
        fprintf (file_sort_ptr, "%70s\n", str_arr_ptr[str_i]->beginning);

    Check_Order (str_arr_ptr, n_strings, false);

    return NO_ERRORS;
}

int Check_Order (struct string **str_arr_ptr, int n_strings, bool mode)
{
    MY_ASSERT (str_arr_ptr,   "struct string **str_arr_ptr", NULL_PTR, ERROR);
    MY_ASSERT (n_strings > 0, "const int n_strings",         POS_VAL, ERROR);

    for (int str_i = 0; str_i < n_strings - 1; str_i++)
    {
        int result = 0;

        if (mode)
            result = My_Strcmp_Beginning (str_arr_ptr + str_i, str_arr_ptr + str_i + 1);
        else
            result = My_Strcmp_Ending (str_arr_ptr + str_i, str_arr_ptr + str_i + 1);

        if (result == GREATER)
            fprintf (stderr, "Sorting fail.\nString %d: %s\nString %d: %s\n\n",
                    str_i, str_arr_ptr[str_i]->beginning, str_i + 1, str_arr_ptr[str_i + 1]->beginning);
    }

    return NO_ERRORS;
}

int Print_Original (FILE *file_sort_ptr, struct string *str_ar, const int n_strings)
{
    MY_ASSERT (file_sort_ptr, "FILE *file_sort_ptr",   NULL_PTR, ERROR);
    MY_ASSERT (str_ar,        "struct string *str_ar", NULL_PTR, ERROR);
    MY_ASSERT (n_strings > 0, "const int n_strings",   POS_VAL,  ERROR);

    fprintf (file_sort_ptr, "\n\nHERE COME THE STRINGS IN ORIGINAL ORDER\n\n");
    for (int str_i = 0; str_i < n_strings; str_i++)
        fprintf (file_sort_ptr, "%s\n", str_ar[str_i].beginning);

    return NO_ERRORS;
}

int My_QSort (void* arr_ptr[], int begin_i, int end_i, int (*cmp_ptr) (const void *, const void *))
{
    int left  = begin_i;
    int right = end_i;

    void *pivot = arr_ptr[(left + right) / 2];

    while (left <= right)
    {
        while ((*cmp_ptr) (arr_ptr + left, &pivot) == LESS)
            ++left;

        while ((*cmp_ptr) (arr_ptr + right, &pivot) == GREATER)
            --right;

        if (left <= right)
            My_Swap (arr_ptr, left++, right--);
    }

    if (begin_i < right)
            My_QSort (arr_ptr, begin_i, right, cmp_ptr);
    if (end_i > left)
            My_QSort (arr_ptr, left, end_i, cmp_ptr);

    return NO_ERRORS;
}

int My_Swap (void *arr_ptr[], int first, int second)
{
    MY_ASSERT (arr_ptr,     "void *arr_ptr", NULL_PTR, ERROR);
    MY_ASSERT (first >= 0,  "int first",     POS_VAL,  ERROR);
    MY_ASSERT (second >= 0, "int second",    POS_VAL,  ERROR);

    void *temp = arr_ptr[first];
    arr_ptr[first] = arr_ptr[second];
    arr_ptr[second] = temp;

    return NO_ERRORS;
}

int My_Strcmp_Beginning (const void *element_1, const void *element_2)
{
    MY_ASSERT (element_1, "const void *element_1", NULL_PTR, ERROR);
    MY_ASSERT (element_2, "const void *element_2", NULL_PTR, ERROR);

    const char *string_1 = ((struct string **)element_1)[0]->beginning;
    const char *string_2 = ((struct string **)element_2)[0]->beginning;

    while (*string_1 != '\0' && *string_2 != '\0')
    {
        if (toupper (*string_1) == toupper (*string_2))
        {
            string_1++;
            string_2++;
        }
        else
        {
            if (isalpha (*string_1) && isalpha (*string_2))
                break;
            if (!isalpha (*string_1) && *string_1 != '\0')
                string_1++;
            if (!isalpha (*string_2) && *string_2 != '\0')
                string_2++;
        }
    }

    if (toupper (*string_1) > toupper (*string_2))
        return GREATER;

    if (toupper (*string_1) < toupper (*string_2))
        return LESS;

    return EQUAL;
}

int My_Strcmp_Ending (const void *element_1, const void *element_2)
{
    MY_ASSERT (element_1, "const void *element_1", NULL_PTR,  ERROR);
    MY_ASSERT (element_2, "const void *element_2", NULL_PTR, ERROR);

    const char *string_1 = ((struct string **)element_1)[0]->ending;
    const char *string_2 = ((struct string **)element_2)[0]->ending;

    while (*string_1 != '\0' && *string_2 != '\0')
    {

        if (toupper (*string_1) == toupper (*string_2))
        {
            string_1--;
            string_2--;
        }
        else
        {
            if (isalpha (*string_1) && isalpha (*string_2))
                break;
            if (!isalpha (*string_1) && *string_1 != '\0')
                string_1--;
            if (!isalpha (*string_2)  && *string_2 != '\0')
                string_2--;
        }
    }

    if (toupper (*string_1) > toupper (*string_2))
        return GREATER;
    if (toupper (*string_1) < toupper (*string_2))
        return LESS;

    return EQUAL;
}
