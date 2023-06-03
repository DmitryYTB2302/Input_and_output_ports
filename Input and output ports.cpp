#include <avr/io.h>
#include <avr/interrupt.h>

// установка порта D на выход
void port_set(){
  // устанавливаем 0 - 3 пины
  DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);
}

// установка таймера 0
void timer_set(){
  // устанавливаем предделитель на 1024
  TCCR0B |= (1 << CS02) | (1 << CS00);
  // разрешение прерывания по совпадению
  TIMSK0 |= (1 << OCIE0A);
   // устанавливаем значение сравнения для заданной частоты прерываний
  OCR0A = 100;
}

// установка кнопки на порт B в 0 пин
void button_set(){
  // устанавливаем порт на вход
  DDRB &= ~(1 << PB0);
  // включаем внутренний подтягивающий резистор на входе B0
  PORTB |= (1 << PB0);
}

// состояние кнопки
int button_state(){
  // если кнопка не нажата возвращаем 1
  if (!(PINB & (1 << PB0))) return 1;
  else return 0;
}

// обработка прерывания по совпадению
ISR(TIMER0_COMPA_vect){
  static uint8_t i = 0;
  if (button_state()){
    if (i <= 4){
      PORTD = (1 << i) * 5;
      i++;
    }
    else if (i > 4 && i <= 9){
      PORTD = (1 << (9 - i)) * 5;
      i++;
    }
    else i = 0;
  }
  else PORTD = 0;
}


int main(void){
  port_set();
  timer_set();
  button_set();
  sei(); 
  while (1){
  }
  return 0;
}
