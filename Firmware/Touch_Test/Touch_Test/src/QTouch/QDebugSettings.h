//---------- Do not edit --------------------
// Project Constants
// Values from 0xF000->0xFFFF are reserved for Atmel Kits
// values from 0x0000->0xEFFF are available for other projects
#define   QM04    0x0004
#define   QM08    0x0008
#define   QM16    0x0010
#define   QM32    0x0020
#define   QM56    0x0038
#define   QM64    0x0040


// Interface constans
#define 	TWI				1
#define 	SPI1W				2
#define 	SPI2W				3
#define 	UART				4
#define         BitBangSPI     5

//---------- Edit Project Info -------------


#if defined(QDEBUG_SPI)
#define		INTERFACE           SPI2W
#elif defined(QDEBUG_TWI)
#define		INTERFACE           TWI
#elif defined(QDEBUG_SPI_BB)
#define     INTERFACE           BitBangSPI
#endif


