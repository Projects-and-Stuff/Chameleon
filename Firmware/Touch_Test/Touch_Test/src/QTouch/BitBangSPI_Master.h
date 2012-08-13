#ifndef BITBANGSPI_MASTER_H_INCLUDED
#define BITBANGSPI_MASTER_H_INCLUDED

/*============================ PROTOTYPES ====================================*/
void BitBangSPI_Master_Init (void);
void BitBangSPI_Send_Message(void);

/*============================ MACROS ========================================*/
// Ensure that the port pins mentioned below are not used for SNS/SNSK


#define CPU_SPEED   4	// MHz

#define DELAYUS(DELAY) __builtin_avr_delay_cycles((DELAY)*CPU_SPEED);	



#endif
/* EOF */
