
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>


#define LED_PIN     PB0
#define BUTTON_PIN  PD2
#define BAUD        9600
#define UBRR_VAL    (F_CPU / 16 / BAUD - 1)


volatile uint8_t botao_pressionado = 0;


void uart_init(void) {
    UBRR0H = (uint8_t)(UBRR_VAL >> 8);
    UBRR0L = (uint8_t)(UBRR_VAL);

    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send_char(char c) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_send_char(*str++);
    }
}


void gpio_init(void) {
    /* LED como saida */
    DDRB |= (1 << LED_PIN);

    DDRD  &= ~(1 << BUTTON_PIN);
    PORTD |=  (1 << BUTTON_PIN);
}

void led_on(void) {
    PORTB |= (1 << LED_PIN);
}

void led_off(void) {
    PORTB &= ~(1 << LED_PIN);
}

void led_toggle(void) {
    PORTB ^= (1 << LED_PIN);
}

void interrupcao_init(void) {
    /* Dispara na borda de descida do pino INT0 */
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    /* Habilita INT0 */
    EIMSK |= (1 << INT0);
    sei();
}

ISR(INT0_vect) {
    botao_pressionado = 1;
}

int main(void) {
    gpio_init();
    uart_init();
    interrupcao_init();

    uart_send_string("Sistema iniciado\r\n");

    while (1) {
        /* Pisca o LED a cada 500 ms */
        led_toggle();
        _delay_ms(500);

        if (botao_pressionado) {
            botao_pressionado = 0;
            uart_send_string("Botao pressionado!\r\n");
            led_on();
            _delay_ms(1000);
            led_off();
        }
    }

    return 0;
}