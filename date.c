/**
 * @file date.c
 * @brief Functions for date comparison and validation.
 * 
 * This file provides the implementation of functions for comparing dates and 
 * validating their correctness. 
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#include "date.h"


int compare_dates(Date date_1, Date date_2) {
    int date1, date2;

    // Convert both dates to a comparable integer format (yyyyMMdd)
    date1 = date_1.yy * 10000 + date_1.mm * 100 + date_1.dd;
    date2 = date_2.yy * 10000 + date_2.mm * 100 + date_2.dd;

    // Compare the integer representations
    if (date1 > date2) return -1;

    if (date1 < date2) return 1;

    return 0;
}

int is_date_valid(Date current_date, Date date, int is_before) {
    int dia_lim;

    if (!(1 <= date.mm && date.mm <= 12)) return 0;

    // Determine the maximum number of days based on the month
    if (date.mm == 2) dia_lim = 28;

    else if ((date.mm <= 7 && date.mm % 2 == 1) || 
            (date.mm >= 8 && date.mm % 2 == 0))     
        dia_lim = 31;

    else dia_lim = 30;

    if (!(1 <= date.dd && date.dd <= dia_lim)) return 0;

    // Check if the date is valid - before or after the current date
    if (is_before && compare_dates(date, current_date) == -1) return 0;
    
    if (!is_before && compare_dates(date, current_date) == 1) return 0;

    return 1;    
    }