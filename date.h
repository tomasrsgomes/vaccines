/**
 * @file date.h
 * @brief 'Date' structure and function headers for handling date-related 
 *        operations.
 * 
 * This file defines the `Date` structure and provides functions to compare 
 * dates and validate them.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#ifndef _DATE_H_
#define _DATE_H_


/**
 * @struct Date
 * @brief Represents a date in the format dd-mm-yy.
 * 
 * This structure holds the day (`dd`), month (`mm`), and year (`yy`) of a date.
 */
typedef struct {
    int dd;     /**< Day of the month   */
    int mm;     /**< Month of the year  */
    int yy;     /**< Year   */
} Date;


/**
 * @brief Compares two dates.
 * 
 * @param date_1 The first date to compare.
 * @param date_2 The second date to compare.
 * 
 * @return A comparison value: -1 (date_1 > date_2), 0 (date_1 == date_2), 
 *          1 (date_1 < date_2).
 */
int compare_dates(Date date_1, Date date_2);


/**
 * @brief Validates if a given date is valid based on the current date and 
 *          calendar rules.
 * 
 * @param current_date      The current system date.
 * @param date              The date to validate.
 * @param is_before         Flag to specify the type of validation 
 *                          (1 for before, 0 for on/after).
 * 
 * @return 1 if the date is valid, 0 if invalid.
 */
int is_date_valid(Date current_date, Date date, int is_before);

#endif
