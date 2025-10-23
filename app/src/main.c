/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_MS 500


int main(void) {
   if (0 < BTN_init()){
    return 0;
   }

  if(0 > LED_init()){
   return 0;
  }
  
  int password[] = {0, 1, 2, 1, 0};
  int password_length = 5;
  char state = 'l';
  char correct = 1;

  int pass_index = 0;

  printk("Enter your Password\n");

  while(1) {

    if (state == 'l'){
      LED_set(LED0, 1);
      LED_set(LED1, 0);
      LED_set(LED2, 0);
      LED_set(LED3, 0);

      if (BTN_check_clear_pressed(BTN0)){
        if (password[pass_index] != 0)
          correct = 0;
        pass_index++;
      }
      if (BTN_check_clear_pressed(BTN1)){
        if (password[pass_index] != 1)
          correct = 0;
        pass_index++;
      }
      if (BTN_check_clear_pressed(BTN2)){
        if (password[pass_index] != 2)
          correct = 0;
        pass_index++;
      }
      

      // Password Submit -> change state
      if (BTN_check_clear_pressed(BTN3)){
        printk("Password Submitted\n");
        if (correct == 1 && pass_index == password_length){
          printk("CORRECT!\n");
          LED_blink(LED0, 15);
        } else {
          printk("INCORRECT!\n");
          LED_set(LED0, 1);
          LED_set(LED1, 1);
          LED_set(LED2, 1);
          LED_set(LED3, 1);
        }
        printk("Press any button to lock. Waiting for input...\n");
        state = 'w';
      }
    } else if (state == 'w') {
      LED_set(LED0, 0);
      if (BTN_check_clear_pressed(BTN0) || BTN_check_clear_pressed(BTN1) || BTN_check_clear_pressed(BTN2) || BTN_check_clear_pressed(BTN3)){
        printk("Waiting Period Ended... Enter your Password.\n");
        //reset correct flag
        correct = 1;
        pass_index = 0;
        //set state back to locked
        state = 'l';
      }
    }

    k_msleep(SLEEP_MS);
  }
	return 0;
}
