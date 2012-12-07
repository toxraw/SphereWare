#include "ADC.h"

/**  Initialise the ADC
  */
void ADC_Init(void)
{
    // Select AVcc as the voltage reference
    //ADMUX |= (1 << REFS0);

    // Select internal 2.56V reference
    ADMUX |= (1 << REFS1) | (1 << REFS0);

    ADC_Set(SINGLE_ENDED, ADC4);

    //// ADC4 - ADC0 X 200 -- 111000
    //ADMUX |= 0b11000;
    //ADCSRB |= (1 << MUX5);

    //// ADC4 - ADC0 X 40 -- 110000
    //ADMUX |= 0b10000;
    //ADCSRB |= (1 << MUX5);

    //ADC_Set(DIFF_0_X200, ADC4);

    //Enable the ADC and set the ADC clock prescale to 128, 16Mhz/128 = 125kHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);

}

/** Set the correct mode and channel on the ADC MUX[5..0]
    */
void ADC_Set(ADC_Mode mode, ADC_Channel chan)
{
//  if (mode != PREVIOUS_MODE) 
//  {
//      if (chan == ADC_PREV)
//          chan = ADMUX & 0b11;
//
        //set the correct MUX[5..0] for this mode and channel
        ADMUX  &= 0b11100000;
        ADCSRB &= 0b11011111;
        ADMUX  |= (mode | chan) & 0b011111;
        ADCSRB |= mode & 0b100000;
//  }
//  else if (chan != ADC_PREV)//just set the channel
//  {
//      ADMUX  &= 0b11111100;
//      ADMUX  |= chan & 0b11;
//  }
    _delay_ms(5);
    //or don't set anything
}

/** Read the ADC optionally setting mode and ADC channel
    */
int16_t ADC_Read(ADC_Mode mode, ADC_Channel chan) 
{
    uint8_t low, high;

    ADC_Set(mode, chan);

    //start the conversion
    ADCSRA |= (1 << ADSC);

    //wait for conversion to finish
    while (bit_is_set(ADCSRA, ADSC));

    //read in this order as both registers are locked when reading ADCL and unlocked
    //when finished reading ADCH
    low     =   ADCL;
    high    =   ADCH;


    if ((mode & 0b110000) && (high >> 1)) //differential mode, negative value
        return -(511 - (low | ((high & 1) << 8)));
    else
        return low | (high << 8);
}
