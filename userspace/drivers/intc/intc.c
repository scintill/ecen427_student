#include "intc/intc.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

// Declare a struct for accessing the intc registers
static volatile struct {
	uint32_t isr;
} __attribute__ ((packed)) *reg;
static int fd;

// Based on generic_write()
void ptr_write(char *ptr, uint32_t offset, uint32_t value) {
  *((volatile uint32_t *)(ptr + offset)) = value;
}

int32_t intc_init(char devFilePath[]) {
	fd = open(devFilePath, O_RDWR);
	reg = mmap(NULL, sizeof(*reg), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	// This works
	ptr_write((char*)reg, 0, 1);

	// This should be equivalent, but it causes a bus error
	reg->isr = 1;

	return INTC_SUCCESS;
}

void intc_exit() {
}

uint32_t intc_wait_for_interrupt() {
	return 0;
}

#define unused __attribute__((unused))

void intc_ack_interrupt(uint32_t irq_mask unused) {
}

void intc_enable_uio_interrupts() {
}

void intc_irq_enable(uint32_t irq_mask unused) {
}

void intc_irq_disable(uint32_t irq_mask unused) {
}
