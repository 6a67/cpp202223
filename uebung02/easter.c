// TODO
// correct usage with 'easter < infile > outfile'
// io operations
// makefile
// better names for variables?

#include <stdio.h>  /* prinf */
#include <string.h> /* strcpy */
#include <stdlib.h> /* atof */

void easter(int year);

int main(int argc, char** argv)
{
    int year = atof(argv[1]);
    easter(year);
}

void easter(int year)
{
    int golden_year        = (year % 19) + 1;
    int century            = (year / 100) + 1;
    int skipped_leap_years = ((3 * century) / 4) - 12;
    int moon_correction    = (((8 * century) + 5) / 25) - 5;
    int d                  = ((5 * year) / 4) - skipped_leap_years - 10;
    int epact              = ((11 * golden_year) + 20 + moon_correction - skipped_leap_years) % 30;
    if ((epact == 25 && golden_year > 11) || epact == 24)
    {
        epact++;
    }
    int day = 44 - epact;
    if (day < 21)
    {
        day += 30;
    }
    day       = day + 7 - ((d + day) % 7);
    int month = 3;
    if (day > 31)
    {
        month = 4;
        day   = day - 31;
    }
    char month_name[10];
    switch (month)
    {
        case 3:
            strcpy(month_name, "March");
            break;
        case 4:
            strcpy(month_name, "April");
            break;
    }
    printf("%d - %s %d\n", year, month_name, day);
}