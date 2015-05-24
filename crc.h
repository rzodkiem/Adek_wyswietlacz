#ifndef CRC_H
#define CRC_H

void calculate8bitCRC(uint8_t *output, uint32_t data, uint8_t write);
uint8_t calculate4bitCRC(uint32_t data);

#endif
