#ifndef UART_H_
#define UART_H_

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void UART_Initialize(void);

void sChar2Str(char *pStr, int value, int charCount);

void moj_sprintf(char *wsk, float liczba, uint8_t d, uint8_t p);

#endif /* UART_H_ */
