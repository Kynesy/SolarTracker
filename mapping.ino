/**
*   @file mapping.ino
*
*   @brief Il file contiene il mapping dei GPIO usati per il progetto.
*
*   @note Il lettore di MicroSD funzionano tramite SPI
*   @note Il modulo LCD ed il sensore BMP280 funzionano tramite I2C
*/

#define CM_CLK_PIN 3 /**< Clock pin del modulo clock */
#define CM_DATA_PIN 4 /**< Data pin del modulo clock */
#define CM_RST_PIN 7 /**< Reset pin del modulo clock */

#define SD_PIN 10 /**< ChipSelect pin del modulo MicroSD */

#define PR_1 A0 /**< Pin analogico del fotoresistore 1 */
#define PR_2 A1 /**< Pin analogico del fotoresistore 2 */
#define PR_3 A2 /**< Pin analogico del fotoresistore 3 */
#define PR_4 A3 /**< Pin analogico del fotoresistore 4 */

#define WATER_SENSOR_PIN_DIGITAL 8 /**< Pin digitale del sensore di pioggia */

#define SERVO_X_PIN 5 /**< Pin del servomotore orizzontale */
#define SERVO_Y_PIN 6 /**< Pin del servomotore verticale */