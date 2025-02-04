#include <stdio.h> 
#include "pico/stdlib.h"
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.


#define led_red 11
#define led_yellow 12
#define led_green 13 

int estado = 0;

bool repeating_timer_callback(struct repeating_timer *t) {

    gpio_put(led_red, 0);
    gpio_put(led_yellow, 0);
    gpio_put(led_green, 0);

    if (estado == 0) 
    {
      gpio_put(led_yellow, 0);
      gpio_put(led_green, 0);
      gpio_put(led_red, 1);
      estado = 1;
    } else if (estado == 1) 
    {
      gpio_put(led_red, 0);
      gpio_put(led_green, 0);
      gpio_put(led_yellow, 1);
      estado = 2;
    } else if (estado == 2)
    {
      gpio_put(led_yellow, 0);
      gpio_put(led_red, 0);
      gpio_put(led_green, 1);
      estado = 0;
    }

    // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador para.
    return true;
}



int main()
{

 stdio_init_all();

  gpio_init(led_red);
  gpio_set_dir(led_red, GPIO_OUT);
  gpio_put(led_red, 0);

  gpio_init(led_yellow);
  gpio_set_dir(led_yellow, GPIO_OUT);
  gpio_put(led_yellow, 0);

  gpio_init(led_green);
  gpio_set_dir(led_green, GPIO_OUT);
  gpio_put(led_green, 0);

 struct repeating_timer timer;

// Configura o temporizador para chamar a função de callback a cada 1 segundo.
 add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

  while (true)
  {
  sleep_ms(3000);
  printf("Funcionando...");
  }

  return 0;
}