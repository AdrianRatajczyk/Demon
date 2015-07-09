#ifndef UART_H_
#define UART_H_

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void UART_Initialize(void);

void UART_Send_int16(int16_t rx, char* buf, uint8_t d);

void UART_Send_char(char tx);

void UART_Send_LFCR();

void UART_Send_CRLF();

void sChar2Str(char *pStr, int value, int charCount);

void moj_sprintf(char *wsk, float liczba, uint8_t d, uint8_t p);

void sprintf_int(char* ptr, int16_t number, uint8_t d);

void UART_Send_hex(uint8_t byte);

#endif /* UART_H_ */
