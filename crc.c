#include "headers.h"


uint8_t crc_calc(uint8_t const message[], int nBytes)
{
    uint8_t  remainder = 0;	

    for (int byte = 0; byte < nBytes; ++byte)
    {
        remainder ^= (message[byte] << (WIDTH - 8));

        for (uint8_t bit = 8; bit > 0; --bit)
        {
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return (remainder);

} 

unsigned char crc (mensagem_t msg, char opt)
{
	if(opt == 'w')
	{
		unsigned char dividendo[65];
		memset(dividendo, 0, sizeof(dividendo)); 
		strcpy((char*)dividendo, msg.data);
		dividendo[63] = msg.tipo;
		dividendo[64] = msg.tamanho;
		return (unsigned char)crc_calc((const uint8_t *)dividendo, sizeof(dividendo));
	}
	else if(opt == 'r')
	{
		unsigned char dividendo[66];
		memset(dividendo, 0, sizeof(dividendo)); 
		strcpy((char*)dividendo, msg.data);
		dividendo[63] = msg.tipo;
		dividendo[64] = msg.tamanho;
		dividendo[65] = msg.crc;
		return (unsigned char)crc_calc((const uint8_t *)dividendo, sizeof(dividendo));
	}
	return '?';
}
