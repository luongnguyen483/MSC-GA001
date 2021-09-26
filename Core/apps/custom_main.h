/************************************************************************************
*                                                                                   *
*   File Name   : custom_main_h.h                                                   *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

#ifndef custom_main_h
	#define custom_main_h
/* Define bit assignments. */
#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9	0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000

#define BIT16	0x00010000
#define BIT17	0x00020000
#define BIT18	0x00040000
#define BIT19	0x00080000
#define BIT20	0x00100000
#define BIT21	0x00200000
#define BIT22	0x00400000
#define BIT23	0x00800000
#define BIT24	0x01000000
#define BIT25	0x02000000
#define BIT26	0x04000000
#define BIT27	0x08000000
#define BIT28	0x10000000
#define BIT29	0x20000000
#define BIT30	0x40000000
#define BIT31	((unsigned long) 0x80000000)

/* Number of Bits */
#define BITS_1   ((1 << 1)  - 1) //1
#define BITS_2   ((1 << 2)  - 1) //3
#define BITS_3   ((1 << 3)  - 1) //7
#define BITS_4   ((1 << 4)  - 1) //f
#define BITS_5   ((1 << 5)  - 1) //1f
#define BITS_6   ((1 << 6)  - 1) //3f
#define BITS_7   ((1 << 7)  - 1) //7f
#define BITS_8   ((1 << 8)  - 1) //ff
#define BITS_9   ((1 << 9)  - 1) //1ff
#define BITS_10  ((1 << 10) - 1) //3ff
#define BITS_11  ((1 << 11) - 1) //7ff
#define BITS_12  ((1 << 12) - 1) //fff
#define BITS_13  ((1 << 13) - 1) //1fff
#define BITS_14  ((1 << 14) - 1) //3fff
#define BITS_15  ((1 << 15) - 1) //7fff
#define BITS_16  0xffff


/* Define boolean variables. */
typedef unsigned char	BOOL;
#define FALSE	0x00
#define TRUE	((unsigned char) 0xFF)
/*	Define the boolean flag return type for functions.  Note that this
	type should be used for function return types only, and for nothing
	else.  The compiler does not know the difference with this type, but
	this type controls the code optimiser, resulting in code size
	reduction where the return type is not a value as such but is a
	TRUE/FALSE status return only (for the ST9, this is the ZFLG where
	ZFLG=1 for TRUE and ZFLG=0 for FALSE).
*/
typedef unsigned char	BOOL_FLAG;

/*	Define what is the default character type most suitable for the
	compiler.
*/
typedef unsigned char	DEFAULT_CHAR;

/*	Define what is the default integer type most suitable for the
	compiler.
*/
typedef unsigned int	DEFAULT_INT;
/* Define the union for translating between integer and 2 characters. */
union ShortCharUnion {
	unsigned short	i;
	struct {
		unsigned char	low,high;
	} bytes;
};
/* Define the union for translating between integer and 2 2xcharacters. */
union IntShortUnion {
	unsigned int ivalue;
	struct {
		unsigned short	low,high;
	} bytes;
};
/* Define a null pointer. */
#define NULL_POINTER	0


/* Define the macro for reading a ROM character. */
#define GetConstByte(c)		(*((signed char*) c))
#define GetConstUCHAR(c)	((unsigned char) GetConstByte(c))
#define GetConstCHAR(c)		GetConstByte(c)

#define GetConstShort(c)		(*((signed short*) c))
#define GetConstUShort(c)		((unsigned short) GetConstShort(c))

/* Define the macro for reading a ROM integer. */
#define GetConstWord(c)		(*((signed int*) c))
#define GetConstUINT(c)		((unsigned int) GetConstWord(c))
#define GetConstINT(c)		GetConstWord(c)

#define Time_2mS		((unsigned char) ((2*((long) TicksPerSecond)+500)/1000))
#define Time_3mS		((unsigned char) ((3*((long) TicksPerSecond)+500)/1000))
#define Time_4mS		((unsigned char) ((4*((long) TicksPerSecond)+500)/1000))
#define Time_5mS		((unsigned char) ((5*((long) TicksPerSecond)+500)/1000))
#define Time_6mS		((unsigned char) ((6*((long) TicksPerSecond)+500)/1000))
#define Time_7mS		((unsigned char) ((7*((long) TicksPerSecond)+500)/1000))
#define Time_8mS		((unsigned char) ((8*((long) TicksPerSecond)+500)/1000))
#define Time_9mS		((unsigned char) ((9*((long) TicksPerSecond)+500)/1000))
#define Time_10mS		((unsigned char) ((10*((long) TicksPerSecond)+500)/1000))
#define Time_13mS		((unsigned int) ((13*((long) TicksPerSecond)+500)/1000))
#define Time_15mS		((unsigned int) ((15*((long) TicksPerSecond)+500)/1000))
#define Time_20mS		((unsigned int) ((20*((long) TicksPerSecond)+500)/1000))
#define Time_22mS		((unsigned int) ((22*((long) TicksPerSecond)+500)/1000))
#define Time_30mS		((unsigned int) ((30*((long) TicksPerSecond)+500)/1000))
#define Time_40mS		((unsigned int) ((40*((long) TicksPerSecond)+500)/1000))
#define Time_50mS		((unsigned int) ((50*((long) TicksPerSecond)+500)/1000))
#define Time_60mS		((unsigned int) ((60*((long) TicksPerSecond)+500)/1000))
#define Time_100mS	((unsigned int) ((100*((long) TicksPerSecond)+500)/1000))
#define Time_103mS	((unsigned int) ((103*((long) TicksPerSecond)+500)/1000))
#define Time_125mS	((unsigned int) ((125*((long) TicksPerSecond)+500)/1000))
#define Time_150mS	((unsigned int) ((150*((long) TicksPerSecond)+500)/1000))
#define Time_180mS	((unsigned int) ((180*((long) TicksPerSecond)+500)/1000))
#define Time_200mS	((unsigned int) ((200*((long) TicksPerSecond)+500)/1000))
#define Time_203mS	((unsigned int) ((203*((long) TicksPerSecond)+500)/1000))
#define Time_250mS	((unsigned int) ((250*((long) TicksPerSecond)+500)/1000))
#define Time_300mS	((unsigned int) ((300*((long) TicksPerSecond)+500)/1000))
#define Time_375mS	((unsigned int) ((375*((long) TicksPerSecond)+500)/1000))
#define Time_400mS	((unsigned int) ((400*((long) TicksPerSecond)+500)/1000))
#define Time_500mS	((unsigned int) ((500*((long) TicksPerSecond)+500)/1000))
#define Time_625mS	((unsigned int) ((625*((long) TicksPerSecond)+500)/1000))
#define Time_750mS	((unsigned int) ((750*((long) TicksPerSecond)+500)/1000))
#define Time_800mS	((unsigned int) ((800*((long) TicksPerSecond)+500)/1000))
#define Time_875mS	((unsigned int) ((875*((long) TicksPerSecond)+500)/1000))
#define Time_1S		TicksPerSecond
#define Time_2S		(2*TicksPerSecond)
#define Time_3S		(3*TicksPerSecond)
#define Time_5S		(5*TicksPerSecond)
#define Time_6S		(6*TicksPerSecond)
#define Time_7S		(7*TicksPerSecond)
#define Time_10S		(10*TicksPerSecond)
#define Time_20S		(20*TicksPerSecond)

#define SecondsInHour	(60*60)
#define SecondsIn3min	(3*60)
#define SecondsIn4min	(4*60)


/******************************************************************************
Function Prototypes
******************************************************************************/

#endif /*end main_h*/
