#ifndef USART_BMS_H
#define USART_BMS_H
#include <stdint.h>

#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*2UL)-1)

void initUSART0();
void transmit8bitUSART(uint8_t data);
uint8_t receive8bitUSART();
uint32_t rebuild_frame_from_bms();
uint8_t check_crc(uint32_t frame);
uint8_t check_typ_data(uint32_t frame, uint8_t typ_data);
uint16_t take_data_from_bms(uint8_t typ_data);


void test();

#endif
