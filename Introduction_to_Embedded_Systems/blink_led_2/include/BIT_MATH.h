
#define SET_BIT(Var,Bit_No)       Var |=(1<<Bit_No)
#define CLR_BIT(Var,Bit_No)       Var &=~(1<<Bit_No)
#define TOGGLE_BIT(Var,Bit_No)    Var ^=(1<<Bit_No)
#define GET_BIT(Var,Bit_No)      ((Var >>Bit_No)&1)