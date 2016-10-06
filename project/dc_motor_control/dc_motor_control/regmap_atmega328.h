#ifndef REGMAP_ATMEGA328_H_
#define REGMAP_ATMEGA328_H_

#define PORTB       PORTB_BASE
#define PORTC       PORTC_BASE
#define PORTD       PORTD_BASE

/** ALL GPIO pins*/
#define BIT_0       0x01
#define BIT_1       0x02
#define BIT_2       0x04
#define BIT_3       0x08
#define BIT_4       0x10
#define BIT_5       0x20
#define BIT_6       0x40
#define BIT_7       0x80

#define PERIPH_PORTB		((GPIO_typedef *) PORTB_BASE)
#define PERIPH_PORTC		((GPIO_typedef *) PORTC_BASE)
#define PERIPH_PORTD		((GPIO_typedef *) PORTD_BASE)


#define PERIPH_UART0        ((UART_typedef *) UART0_BASE )
#define PERIPH_SPI          ((SPI_typedef *) SPI_BASE )

#define PERIPH_TIMER0       ((TIMER_8bit_typedef *) TIMER0_BASE )
#define PERIPH_TIMER1       ((TIMER_16bit_typedef *) TIMER1_BASE )
#define PERIPH_TIMER2       ((TIMER_8bit_typedef *) TIMER2_BASE )
#define TIMSK_INT           ((TIMER_interrupt_typedef *) TIMER_INT_BASE )

#define PERIPH_TWI          ((TWI_typedef *) TWI_BASE )
#define PERIPH_ADC          ((ADC_typedef *) ADC_BASE )
#define PERIPH_EEPROM       ((EEPROM_typedef *) EEPROM_BASE )
#define PERIPH_WDT          ((WDT_typedef *) WDT_BASE )

#define PERIPH_EXTINT       ((EXTINT_typedef *) EXTINT_BASE )
#define PERIPH_EIMSK        ((EIMSK_typedef *) EIMSK_BASE )
#define PERIPH_PCINT        ((PCINT_typedef *) PCINT_BASE )

#define INT_FLAG            ((IntrFlag_typedef *) INT_FLAG_BASE )

#define _RW volatile
#define _R volatile const

/** \brief GPIO_typedef Struct */
typedef struct
{
    _RW uint8_t PIN;
    _RW uint8_t DDR;
    _RW uint8_t PORT;
}GPIO_typedef;

/** \brief UART_typedef Struct */
typedef struct
{
    _RW uint8_t UCSRA;
    _RW uint8_t UCSRB;
    _RW uint8_t UCSRC;
    _R uint8_t reserved;
    union
    {
        _RW uint16_t UBRR;
        struct
        {
            _RW uint8_t UBRRL;
            _RW uint8_t UBRRH;   
        };
    };
    _RW uint8_t UDR;
}UART_typedef;

/** \brief SPI_typedef Struct */
typedef struct
{
    _RW uint8_t SPCR;
    _RW uint8_t SPSR;
    _RW uint8_t SPDR;
}SPI_typedef;

/** \brief TIMER_8bit_typedef Struct */
typedef struct
{
    _RW uint8_t TCCRA;
    _RW uint8_t TCCRB;
    _RW uint8_t TCNT;
    _RW uint8_t OCRA;
    _RW uint8_t OCRB;
}TIMER_8bit_typedef;

/** \brief TIMER_interrupt_typedef Struct */
typedef struct
{
    _RW uint8_t TIMER0;
    _RW uint8_t TIMER1;
    _RW uint8_t TIMER2;
}TIMER_interrupt_typedef;

/** \brief TIMER_16bit_typedef Struct */
typedef struct
{
    _RW uint8_t TCCRA;
    _RW uint8_t TCCRB;
    _RW uint8_t TCCRC;
    _R  uint8_t reserved;
    union
    {
        _RW uint16_t TCNT;
        struct
        {
            _RW uint8_t TCNTL;
            _RW uint8_t TCNTH;
        };
    };
    union
    {
        _RW uint16_t ICR;
        struct
        {
            _RW uint8_t ICRL;
            _RW uint8_t ICRH;
        };
    };
    union
    {
        _RW uint16_t OCRA;
        struct
        {
            _RW uint8_t OCRAL;
            _RW uint8_t OCRAH;
        };
    };
    union
    {
        _RW uint16_t OCRB;
        struct
        {
            _RW uint8_t OCRBL;
            _RW uint8_t OCRBH;
        };
    };                        
    
}TIMER_16bit_typedef;

/** \brief TWI_typedef Struct */
typedef struct
{
    _RW uint8_t TWBR;
    _RW uint8_t TWSR;
    _RW uint8_t TWAR;
    _RW uint8_t TWDR;
    _RW uint8_t TWCR;
    _RW uint8_t TWAMR;
}TWI_typedef;

/** \brief ADC_typedef Struct */
typedef struct
{
    _RW uint8_t ADCL;
    _RW uint8_t ADCH;
    _RW uint8_t ADCSRA;
    _RW uint8_t ADCSRB;
    _RW uint8_t ADMUX;
}ADC_typedef;

/** \brief EEPROM_typedef Struct */
typedef struct
{
    _RW uint8_t EECR;
    _RW uint8_t EEDR;
    _RW uint8_t EEARL;
    _RW uint8_t EEARH;   
}EEPROM_typedef;

/** \brief EXTINT_typedef Struct */
typedef struct
{
    _RW uint8_t EICRA;  
}EXTINT_typedef;

/** \brief EIMSK_typedef Struct */
typedef struct
{
    _RW uint8_t EIMSK;
}EIMSK_typedef;

/** \brief PCINT_typedef Struct */
typedef struct
{
    _RW uint8_t PCICR;
    _R uint8_t reserved[2];
    _RW uint8_t PCMSK0;
    _RW uint8_t PCMSK1;
    _RW uint8_t PCMSK2;
}PCINT_typedef;

/** \brief WDT_typedef Struct */
typedef struct
{
    _RW uint8_t MCUSR;
    _R  uint8_t reserved[11];
    _RW uint8_t WDTCSR;
}WDT_typedef;

/** \brief IntrFlag_typedef Struct */
typedef struct
{
    _RW uint8_t TIMER0;
    _RW uint8_t TIMER1;
    _RW uint8_t TIMER2;
    _RW uint8_t PCINT;
    _RW uint8_t EXINT;
}IntrFlag_typedef;

/** All vectors */

#define     RESET           0
#define     EINT0           1
#define     EINT1           2
#define     PCINTR0         3
#define     PCINTR1         4
#define     PCINTR2         5
#define     WDT_VECT        6
#define     TIMER2_COMPA    7
#define     TIMER2_COMPB    8
#define     TIMER2_OVF      9
#define     TIMER1_CAPT     10
#define     TIMER1_COMPA    11
#define     TIMER1_COMPB    12
#define     TIMER1_OVF      13
#define     TIMER0_COMPA    14
#define     TIMER0_COMPB    15
#define     TIMER0_OVF      16
#define     SPI_VECT        17
#define     USART0_RX       18
#define     USART0_UDRE     19
#define     USART0_TX       20
#define     ADC_VECT        21
#define     EEPROM_VECT     22
#define     ANALOG_COMP     23
#define     I2C_VECT        24
#define     SPROGMEM        25

/** ALL GPIO port*/
#define PORTB_BASE          0x23
#define PORTC_BASE          0x26
#define PORTD_BASE          0x29

/** UART */

#define UART0_BASE          0xC0

/** SPI*/
#define SPI_BASE            0x4C

/** TIMER 8bit*/
#define TIMER0_BASE         0x44
#define TIMER2_BASE         0xB0

/** TIMER 16bit */
#define TIMER1_BASE         0x80

#define TIMER_INT_BASE      0x6E

/** INTERRUPT FLAG */
#define INT_FLAG_BASE       0x35

/** TWI (I2c)*/
#define TWI_BASE            0xB8

/** EXTINT */
#define EXTINT_BASE         0x69

/** EXTINT */
#define EIMSK_BASE          0x3D

/** PCINT */
#define PCINT_BASE          0x68

/** ADC */
#define ADC_BASE            0x78

/** EEPROM */
#define EEPROM_BASE         0x3F

/** WDT */
#define WDT_BASE            0x54

/** Status flag Register */
//#define SREG              _SFR_IO8(0X5F)

void __vector_0(void)  __attribute__ ((signal,used));
void __vector_1(void)  __attribute__ ((signal,used));
void __vector_2(void)  __attribute__ ((signal,used));
void __vector_3(void)  __attribute__ ((signal,used));
void __vector_4(void)  __attribute__ ((signal,used));
void __vector_5(void)  __attribute__ ((signal,used));
void __vector_6(void)  __attribute__ ((signal,used));
void __vector_7(void)  __attribute__ ((signal,used));
void __vector_8(void)  __attribute__ ((signal,used));
void __vector_9(void)  __attribute__ ((signal,used));
void __vector_10(void)  __attribute__ ((signal,used));
void __vector_11(void)  __attribute__ ((signal,used));
void __vector_12(void)  __attribute__ ((signal,used));
void __vector_13(void)  __attribute__ ((signal,used));
void __vector_14(void)  __attribute__ ((signal,used));
void __vector_15(void)  __attribute__ ((signal,used));
void __vector_16(void)  __attribute__ ((signal,used));
void __vector_17(void)  __attribute__ ((signal,used));
void __vector_18(void)  __attribute__ ((signal,used));
void __vector_19(void)  __attribute__ ((signal,used));
void __vector_20(void)  __attribute__ ((signal,used));
void __vector_21(void)  __attribute__ ((signal,used));
void __vector_22(void)  __attribute__ ((signal,used));
void __vector_23(void)  __attribute__ ((signal,used));
void __vector_24(void)  __attribute__ ((signal,used));
void __vector_25(void)  __attribute__ ((signal,used));
void __vector_26(void)  __attribute__ ((signal,used));

#endif /* REGMAP_ATMEGA328_H_ */

/**@}*/

