#include "calculator.h"
#include <string.h>

double convertArea(char* from, char* to, double value) {
    // Conversion factors
    const double m2_to_m2 = 1.0, m2_to_mi2 = 3.861e-7, m2_to_in2 = 1550.003, m2_to_ft2 = 10.7639;
    const double mi2_to_m2 = 2589988.11, in2_to_m2 = 0.00064516, ft2_to_m2 = 0.092903;

    if (strcmp(from, "SQRMT") == 0) {
        if (strcmp(to, "SQRML") == 0) return value * m2_to_mi2;
        if (strcmp(to, "SQRIN") == 0) return value * m2_to_in2;
        if (strcmp(to, "SQRFT") == 0) return value * m2_to_ft2;
    } else if (strcmp(from, "SQRML") == 0) {
        if (strcmp(to, "SQRMT") == 0) return value * mi2_to_m2;
        if (strcmp(to, "SQRIN") == 0) return value * mi2_to_m2 * m2_to_in2;
        if (strcmp(to, "SQRFT") == 0) return value * mi2_to_m2 * m2_to_ft2;
    } else if (strcmp(from, "SQRIN") == 0) {
        if (strcmp(to, "SQRMT") == 0) return value * in2_to_m2;
        if (strcmp(to, "SQRML") == 0) return value * in2_to_m2 * m2_to_mi2; 
        if (strcmp(to, "SQRFT") == 0) return value * in2_to_m2 * m2_to_ft2;
    } else if (strcmp(from, "SQRFT") == 0) {
        if (strcmp(to, "SQRMT") == 0) return value * ft2_to_m2;
        if (strcmp(to, "SQRML") == 0) return value * ft2_to_m2 * m2_to_mi2;
        if (strcmp(to, "SQRIN") == 0) return value * ft2_to_m2 * m2_to_in2;
    }

    return -1; // Invalid conversion
}

double convertVolume(char* from, char* to, double value) {
    // Conversion factors
    const double l_to_l = 1.0, l_to_galnu = 0.264172, l_to_galni = 0.219969, l_to_m3 = 0.001;
    const double galnu_to_l = 3.78541, galni_to_l = 4.54609, m3_to_l = 1000;

    if (strcmp(from, "LTR") == 0) {
        if (strcmp(to, "GALNU") == 0) return value * l_to_galnu;
        if (strcmp(to, "GALNI") == 0) return value * l_to_galni;
        if (strcmp(to, "CUBM") == 0) return value * l_to_m3;
    } else if (strcmp(from, "GALNU") == 0) {
        if (strcmp(to, "LTR") == 0) return value * galnu_to_l;
        if (strcmp(to, "GALNI") == 0) return value * galnu_to_l * l_to_galni;
        if (strcmp(to, "CUBM") == 0) return value * galnu_to_l * l_to_m3;
    } else if (strcmp(from, "GALNI") == 0) {
        if (strcmp(to, "LTR") == 0) return value * galni_to_l;
        if (strcmp(to, "GALNU") == 0) return value * galni_to_l * l_to_galnu;
        if (strcmp(to, "CUBM") == 0) return value * galni_to_l * l_to_m3;
    } else if (strcmp(from, "CUBM") == 0) {
        if (strcmp(to, "LTR") == 0) return value * m3_to_l;
        if (strcmp(to, "GALNU") == 0) return value * m3_to_l * l_to_galnu;
        if (strcmp(to, "GALNI") == 0) return value * m3_to_l * l_to_galni;
    }

    return -1; // Invalid conversion
}

double convertWeight(char* from, char* to, double value) {
    // Conversion factors
    const double kg_to_kg = 1.0, kg_to_pnd = 2.20462, kg_to_cart = 5000;
    const double pnd_to_kg = 0.453592, cart_to_kg = 0.0002;

    if (strcmp(from, "KILO") == 0) {
        if (strcmp(to, "PND") == 0) return value * kg_to_pnd;
        if (strcmp(to, "CART") == 0) return value * kg_to_cart;
    } else if (strcmp(from, "PND") == 0) {
        if (strcmp(to, "KILO") == 0) return value * pnd_to_kg;
        if (strcmp(to, "CART") == 0) return value * pnd_to_kg * kg_to_cart;
    } else if (strcmp(from, "CART") == 0) {
        if (strcmp(to, "KILO") == 0) return value * cart_to_kg;
        if (strcmp(to, "PND") == 0) return value * cart_to_kg * kg_to_pnd;
    }

    return -1; // Invalid conversion
}

double convertTemperature(char* from, char* to, double value) {
    if (strcmp(from, "CELS") == 0) {
        if (strcmp(to, "FAHR") == 0) return (value * 9 / 5) + 32;
        if (strcmp(to, "KELV") == 0) return value + 273.15;
    } else if (strcmp(from, "FAHR") == 0) {
        if (strcmp(to, "CELS") == 0) return (value - 32) * 5 / 9;
        if (strcmp(to, "KELV") == 0) return ((value - 32) * 5 / 9) + 273.15;
    } else if (strcmp(from, "KELV") == 0) {
        if (strcmp(to, "CELS") == 0) return value - 273.15;
        if (strcmp(to, "FAHR") == 0) return ((value - 273.15) * 9 / 5) + 32;
    }

    return -1; // Invalid conversion
}

