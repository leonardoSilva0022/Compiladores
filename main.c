#include <16F628A.h>
#fuses XT
#use delay( clock=4MHz )

void  main () {

    int contador = 0;
    int1 btn1;

    while(TRUE) {
        btn1 = input(PIN_A1 );

        if (btn1 == 0) {
            contador++;
            output_b (contador);
            delay_ms(500);
        }
    }
}