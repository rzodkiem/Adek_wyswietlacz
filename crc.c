#include <avr/io.h>
//#include "crc.h"

// ############################################## CRC.C :START ################################################

//data to 32bitowe dane, write to flaga mówi¹ca czy dane id¹ do wysy³ania czy przychodz¹ z tranmsmisji
void calculate8bitCRC(uint8_t *output, uint32_t data, uint8_t write){
	uint8_t i=0;
	uint8_t bit_array[22];
	uint8_t num_bits;

	while (i<8){
		output[i] =0;
		i++;
	}
	i=0;
	if(write == 1){
		num_bits = 21;

		while (i<21){
		    bit_array[i] = data & ((unsigned long) 0x00000001 << (31-i)) ? 1 : 0;
			i++;
		}
	}
	else{
		num_bits = 22;

		while (i<22){
		    bit_array[i] = data & ((unsigned long) 0x00000001 << (31-i)) ? 1 : 0;
			i++;
		}
	}

	uint8_t xor_1 = 0;
	uint8_t xor_2 = 0;
	uint8_t xor_3 = 0;
	uint8_t xor_4 = 0;
	uint8_t xor_5 = 0;
	
	i=num_bits;
	while (i>0){
 		xor_5 = output[4] ^ output[7];
		xor_4 = output[2] ^ output[7];
		xor_3 = output[1] ^ output[7];
		xor_2 = output[0] ^ output[7];
		xor_1 = bit_array[num_bits-i] ^ output[7];

		output[7] = output[6];
		output[6] = output[5];
		output[5] = xor_5;
		output[4] = output[3];
		output[3] = xor_4;
		output[2] = xor_3;
		output[1] = xor_2;
		output[0] = xor_1;
		i--;
 	}
}
//uint8_t output[4]; dzielnik 10110
uint8_t calculate4bitCRC(uint32_t data){
	uint8_t polynomial = 0xD8;
	uint32_t remainder = data;
	
	for (uint8_t bit = 20; bit > 0; --bit){
		if (remainder & 0x80){
			remainder ^= polynomial;
		}
		remainder = (remainder <<1);
	}
	return (remainder >> 4);
}

// ############################################## CRC.C :KONIEC ################################################
