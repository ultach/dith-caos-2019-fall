#include <stdint.h>
#include <stdio.h>

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01, // S=1, E=0, M=0
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

uint64_t get_sign(uint64_t value)
{
    return (value >> 63) & 1;
}
uint64_t get_exp(uint64_t value)
{
    return 0x7ff & (value >> 52);
}
uint64_t get_mantissa(uint64_t value)
{
    return value & 0xfffffffffffff;
}

float_class_t classify(double *value_ptr) 
{
    // Теряем информацию о типе, приведением его к типу void*
    void* a_ptr_as_void = value_ptr;

    // Указатель void* в языке Си можно присваивать любому указателю
    uint64_t* a_ptr_as_uint = a_ptr_as_void;

    // Ну а дальше просто разыменовываем указатель
    uint64_t value = *a_ptr_as_uint;

    uint64_t mantissa = get_mantissa(value);
    uint64_t exp = get_exp(value);
    uint64_t sign = get_sign(value);
    
    if (sign == 0 && exp == 0 && mantissa == 0)
    {
        printf("PlusZero\n");
        return PlusZero;
    }
    else if (sign == 1 && exp == 0 && mantissa == 0)
    {
        printf("MinusZero\n");
        return MinusZero;
    }
    else if (sign == 0 && exp == 0x7ff && mantissa == 0)
    {
        printf("PlusInf\n");
        return PlusInf;
    }
    else if (sign == 1 && exp == 0x7ff && mantissa == 0)
    {
        printf("MinusInf\n");
        return MinusInf;
    }
    else if (sign == 0 && exp == 0x7ff && mantissa == 0x4000000000000)
    {
        printf("SignalNAn\n");
        return SignalingNaN;
    }
    else if (sign == 0 && exp == 0x7ff && mantissa == 0x8000000000000)
    {
        printf("QuietNan\n");
        return QuietNaN;
    }
    else if (sign == 1 && exp == 0 && mantissa != 0)
    {
        printf("MinusDenormal\n");
        return MinusDenormal;
    }
    else if (sign == 0 && exp == 0 && mantissa != 0)
    {
        printf("PlusDenormal\n");
        return PlusDenormal;
    }
    else if (sign == 1)
    {
        
        printf("MinusRegular;\n");
        return MinusRegular;
    }
    else if (sign == 0)
    {
        printf("PlusRegular;\n");
        return PlusRegular;
    }
}


// Используем тип union
typedef union {
    double     real_value;
    uint64_t   uint_value;
} real_or_uint;

int main () {
    real_or_uint u;
    real_or_uint minus_inf;
    minus_inf.uint_value = 0b1111111111110000000000000000000000000000000000000000000000000000;

    real_or_uint minus_zero;
    minus_zero.uint_value = 0b1000000000000000000000000000000000000000000000000000000000000000;

    real_or_uint sNaN;
    sNaN.uint_value = 0b0111111111110100000000000000000000000000000000000000000000000000;

    real_or_uint qNaN;
    qNaN.uint_value = 0b0111111111111000000000000000000000000000000000000000000000000000;

    real_or_uint plus_zero;
    plus_zero.uint_value = 0b0000000000000000000000000000000000000000000000000000000000000000;

    real_or_uint plus_inf;
    plus_inf.uint_value = 0b0111111111110000000000000000000000000000000000000000000000000000;

    real_or_uint plus_demornal;
    plus_demornal.uint_value = 0b0000000000000111111111111111111111111111111111111111111111111111;

    real_or_uint minus_demornal;
    minus_demornal.uint_value = 0b1000000000000111111111111111111111111111111111111111111111111111;

    double c1 = 20., c2 = -20.;

    printf("%lf=", plus_inf.real_value);
    double* prt_a = &plus_inf.real_value;
    classify(prt_a);

    printf("%lf=", minus_inf.real_value);
    prt_a = &minus_inf.real_value;
    classify(prt_a);

    printf("%lf=", sNaN.real_value);
    prt_a = &sNaN.real_value;
    classify(prt_a);

    printf("%lf=", qNaN.real_value);
    prt_a = &qNaN.real_value;
    classify(prt_a);

    printf("%lf=", plus_zero.real_value);
    prt_a = &plus_zero.real_value;
    classify(prt_a);

    printf("%lf=", minus_zero.real_value);
    prt_a = &minus_zero.real_value;
    classify(prt_a);

    printf("%e=", plus_demornal.real_value);
    prt_a = &plus_demornal.real_value;
    classify(prt_a);

    printf("%e=", minus_demornal.real_value);
    prt_a = &minus_demornal.real_value;
    classify(prt_a);

    printf("%lf=", c1);
    prt_a = &c1;
    classify(prt_a);

    printf("%lf=", c2);
    prt_a = &c2;
    classify(prt_a);



    
    return 0;
}
