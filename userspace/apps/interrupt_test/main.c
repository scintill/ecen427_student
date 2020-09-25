#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "buttons/buttons.h"
#include "intc/intc.h"
#include "switches/switches.h"
#include "system.h"

#define EXIT_ERROR -1

int main() {
  int32_t err;

  printf("-------------------------------------------------------\n");
  printf("Welcome to the interrupt test.\n");
  printf("When you press or release a button, or move a switch, the program "
         "will print a message.\n");
  printf("The buttons may bounce, so you may sometimes see multiple messages "
         "on a button press.\n");
  printf("-------------------------------------------------------\n");

  // Initialize intc
  err = intc_init(SYSTEM_INTC_UIO_FILE);
  if (err) {
    printf("intc_init failed\n");
    exit(EXIT_ERROR);
  }

  // Enable the buttons and switches interrupt lines to the interrupt controller
  intc_irq_enable(SYSTEM_INTC_IRQ_BUTTONS_IRQ);
  intc_irq_enable(SYSTEM_INTC_IRQ_SWITCHES_IRQ);

  while (1) {
    // Block waiting for an interrupt
    // This will put the program to sleep until an interrupt occurs
    uint32_t int_mask = intc_wait_for_interrupt();
    printf("interrupt ");

    printf("\n");

    // Acknowledge the interrupt with the intc
    intc_ack_interrupt(int_mask);

    // Re-enable interrupts with the UIO
    intc_enable_uio_interrupts();
  }

  intc_exit();

  return 0;
}
