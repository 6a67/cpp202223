#include <stdio.h>      /* printf */
#include <stdlib.h>     /* atof */

int main(int argc, char** argv) {
    if(argc != 4) {
        printf("ERROR\nUsage: ./milage distance_km total_fuel_consumption_L fuel_price\n");
        return 1;
    }

    float avg_fuel_consumption = (atof(argv[2]) / atof(argv[1])) * 100;
    float avg_fuel_price = (atof(argv[2]) / atof(argv[1])) * atof(argv[3]);

    printf("Average price per 100km: %f c/100km\nPrice per Kilometer: %f c/L\n", avg_fuel_consumption, avg_fuel_price);
    return 0;
}