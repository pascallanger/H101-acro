
#include "binary.h"
#include "drv_spi.h"

#include "gd32f1x0.h"
#include "xn297.h"


void xn_writereg( int reg , int val)
{
	reg = reg&0x0000003F;
	reg = reg|0x00000020;
	spi_cson();
	spi_sendbyte( reg);
	spi_sendbyte( val);
	spi_csoff();
}

int xn_readreg( int reg)
{
	reg = reg&0x1F;
	spi_cson();
	spi_sendrecvbyte( reg);
	reg =spi_sendrecvbyte( 0);
	spi_csoff();
	return reg;
}

int xn_command( int command)
{
	spi_cson();
	int status = spi_sendrecvbyte(command);
	spi_csoff();
	return status;
}


void _spi_write_address( int reg, int val)
{
	spi_cson();
	spi_sendbyte( reg);
	spi_sendbyte( val);
	spi_csoff();
}


void xn_readpayload( int *data , int size )
{
	int index = 0;
	spi_cson();
	spi_sendbyte( B01100001 ); // read rx payload
	while(index<size)
	{
	data[index]=	spi_sendzerorecvbyte(  );
	index++;
	}
	spi_csoff();
}



void xn_writerxaddress(  int *addr )	
{
 int index = 0;
spi_cson();
spi_sendbyte(0x2a);
	while(index<5)
	{
	spi_sendbyte( addr[index] );
	index++;
	}

spi_csoff();
}















