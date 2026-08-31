#ifndef EXTI_PRIVATE
#define EXTI_PRIVATE

/*MCUCR*/
#define Bit_ISC00    0
#define Bit_ISC01    1
#define Bit_ISC10    2
#define Bit_ISC11    3
/*MCUCSR*/
#define Bit_ISC2     6
/*GICR*/
#define Bit_INT1   7
#define Bit_INT0   6
#define Bit_INT2   5
/*GIFR*/
#define Bit_INTF1   7
#define Bit_INTF0   6
#define Bit_INTF2   5


/*SensControl Option */

#define EXTI_LowLevel   0 
#define EXTI_AnyLogic   1 
#define EXTI_Falling    2 
#define EXTI_Rising     3 



#define EXTI0     0
#define EXTI1     1
#define EXTI2     2
#endif /* EXTI_PRIVATE */
