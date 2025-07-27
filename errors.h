/**
 * @file erros.h
 * @brief Error Messages for the Vaccine Management System
 * 
 * This file contains all the error messages used in the Vaccine Management 
 * System. It includes both English and Portuguese versions for each error 
 * message, ensuring support for different languages in the system.
 * 
 * The error messages cover a range of issues, such as memory errors, invalid 
 * batch numbers, vaccination errors, and user-related errors.
 * 
 * @author ist1114493 (Tomás Gomes)
 * @date 2025
 */

#ifndef _ERRORS_H_
#define _ERRORS_H_

/** Error messages in English **/
#define ENOMEMORY_EN    "No memory."        /**< memory exausted    */
#define E2MANYVAC_EN    "too many vaccines"     /**< too many vaccines  */
#define EDUPBATCH_EN    "duplicate batch number"        /**< duplicate batch*/
#define EINVBATCH_EN    "invalid batch"     /**< invalid batch  */
#define EINVNAME_EN     "invalid name"      /**< invalid name   */
#define EINVDATE_EN     "invalid date"      /**< invalid date   */
#define EINVQUANT_EN    "invalid quantity"      /**< invalid quantity   */
#define ENOVACINE_EN    ": no such vaccine"     /**< inexisting vaccine */
#define ENOSTOCK_EN     "no stock"      /**< no stock   */
#define EDOUBLEVAC_EN   "already vaccinated"        /**< already vaccinated */
#define ENOBATCH_EN     ": no such batch"       /**< inexisting batch   */
#define EINVUSER_EN     ": no such user"        /**< inexisting user    */

/** Error messages in Portuguese **/
#define ENOMEMORY_PT    "sem memória."      /**< memory exausted    */
#define E2MANYVAC_PT    "demasiadas vacinas"        /**< too many vaccines  */
#define EDUPBATCH_PT    "número de lote duplicado"      /**< duplicate batch*/
#define EINVBATCH_PT    "lote inválido"     /**< invalid batch  */
#define EINVNAME_PT     "nome inválido"     /**< invalid name   */
#define EINVDATE_PT     "data inválida"     /**< invalid date   */
#define EINVQUANT_PT    "quantidade inválida"       /**< invalid quantity   */
#define ENOVACINE_PT    ": vacina inexistente"      /**< inexisting vaccine */
#define ENOSTOCK_PT     "esgotado"      /**< no stock   */
#define EDOUBLEVAC_PT   "já vacinado"       /**< already vaccinated */
#define ENOBATCH_PT     ": lote inexistente"        /**< inexisting batch   */
#define EINVUSER_PT     ": utente inexistente"      /**< inexisting user    */

#endif