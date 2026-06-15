#include <18F4550.h>
#fuses XT, MCLR, NOWDT
#use delay(clock=4MHz)

void main() {

    unsigned int16 P;
    unsigned int16 PR2;
    unsigned int16 DC;
    PR2 = 124;
    P = 50; // 50% de duty cycle ou metade da máxima potência

    setup_timer_2(T2_DIV_BY_16, PR2, 1);
    setup_ccp1(CCP_PWM);

    DC = (unsigned int16)((PR2 + 1) * 4 * (P/100.0));
    set_pwm1_duty(DC);

    while(true) {
    }
}