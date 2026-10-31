uint8_t t0_count = 0;     // counts Timer0 compare matches
uint8_t t2_count = 0;     // counts Timer2 overflows
uint8_t busy = 0;         // 1 while the 250 ms debounce is running

void setup() {
  // PB0, PB1, PB2 as outputs
  DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);

  // PD2, PD3 as inputs with pull-up
  DDRD &= ~((1 << PD2) | (1 << PD3));
  PORTD |= (1 << PD2) | (1 << PD3);

  // Timer0: CTC mode
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCCR0A |= (1 << WGM01);                 // CTC mode
  TCCR0B |= (1 << CS02) | (1 << CS00);    // prescaler 1024
  OCR0A = 249;                            // 16 ms per compare match
  TIMSK0 = (1 << OCIE0A);                 // enable compare match A interrupt

  // Timer1: Fast PWM 10-bit
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1A |= (1 << WGM11) | (1 << WGM10);  // fast PWM 10-bit
  TCCR1B |= (1 << WGM12);
  TCCR1A |= (1 << COM1A1);                // non-inverting
  TCCR1B |= (1 << CS11);                  // prescaler 8
  OCR1A = 0;                              // LED off at start

  // Timer2: Normal mode (debounce)
  TCCR2A = 0x00;
  TCCR2B = 0x00;                          // stopped until a button is pressed
  TIMSK2 |= (1 << TOIE2);                 // enable overflow interrupt

  // Buttons: INT0 and INT1 on falling edge
  EICRA |= (1 << ISC01) | (1 << ISC11);
  EIMSK |= (1 << INT0) | (1 << INT1);

  // enable global interrupt
  sei();
}

// Timer0: toggle LED on PB0 every 20 compare matches
ISR(TIMER0_COMPA_vect) {
  t0_count++;
  if (t0_count == 20) {
    t0_count = 0;
    PORTB ^= (1 << PB0);
  }
}

// Button 1: change the blink rate
ISR(INT0_vect) {
  if (busy == 0) {
    OCR0A -= 50;                          // smaller compare value = faster blink
    if (OCR0A < 30) OCR0A = 249;          // back to the slowest rate
    TCNT0 = 0;

    start_debounce();
  }
}

// Button 2: increase the brightness
ISR(INT1_vect) {
  if (busy == 0) {
    OCR1A += 100;                         // duty cycle (0 to 1023)
    if (OCR1A > 1023) OCR1A = 0;          // back to off

    start_debounce();
  }
}

void start_debounce() {
  busy = 1;                             // start 250 ms debounce
  t2_count = 0;
  TCNT2 = 0;
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);   // prescaler 1024
  PORTB |= (1 << PB2);                  // indicator LED on
}

// Timer2: 15 overflows x 16.384 ms = about 250 ms
ISR(TIMER2_OVF_vect) {
  t2_count++;
  if (t2_count == 15) {
    TCCR2B = 0x00;                        // stop Timer2
    busy = 0;
    PORTB &= ~(1 << PB2);                 // indicator LED off
    EIFR |= (1 << INTF0) | (1 << INTF1);  // clear presses that bounced meanwhile
  }
}

void loop() {
}