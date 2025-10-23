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

#define SLEEP_MS 1

int main(void) {
 if (0 < BTN_init()){
  return 0;
 }

 if(0 > LED_init()){
  return 0;
 }
  int counter = 0;
  while(1) {
    if (BTN_check_clear_pressed(BTN0)){
      counter++;
      printk("Button 0 pressed!%d\n", counter);
    }
    k_msleep(SLEEP_MS);

    LED_set(LED0, counter & 1);
    LED_set(LED1, (counter / 2) & 1);
    LED_set(LED2, (counter / 4) & 1);
    LED_set(LED3, (counter / 8) & 1);

  }
	return 0;
}
