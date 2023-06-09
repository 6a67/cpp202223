#include <stdio.h>  /* prinf */
#include <string.h> /* strcpy */
#include <stdlib.h> /* atof */

/**
 * calculates the date of easter sunday for a given year
 * @param year the year
 * @return the date of easter in the format mmdd
 */
int easter(int year)
{
    int golden_year;
    int century;
    int skipped_leap_years;
    int moon_correction;
    int solar_correction;
    int epact;
    int day;
    int month;

    golden_year        = (year % 19) + 1;
    century            = (year / 100) + 1;
    skipped_leap_years = ((3 * century) / 4) - 12;
    moon_correction    = (((8 * century) + 5) / 25) - 5;
    solar_correction   = ((5 * year) / 4) - skipped_leap_years - 10;
    epact              = ((11 * golden_year) + 20 + moon_correction - skipped_leap_years) % 30;
    if ((epact == 25 && golden_year > 11) || epact == 24)
    {
        epact++;
    }
    day = 44 - epact;
    if (day < 21)
    {
        day += 30;
    }
    day   = day + 7 - ((solar_correction + day) % 7);
    month = 3;
    if (day > 31)
    {
        month = 4;
        day   = day - 31;
    }

    return month * 100 + day;
}

/**
 * prints the date of easter sunday for a year given through stdin
 * invalid input is interpreted as 0
 */
int main(int argc, char** argv)
{
    int  mmdd;
    int  m;
    int  d;
    char yearStr[100];
    int  year;

    while (scanf("%99s", yearStr) != EOF)
    {
        year = atoi(yearStr);
        mmdd = easter(year);
        m    = mmdd / 100;
        d    = mmdd % 100;

        printf("%d - ", year);
        switch (m)
        {
            case 3:
                printf("March %d\n", d);
                break;
            case 4:
                printf("April %d\n", d);
                break;
        }
    }

    return 0;
}