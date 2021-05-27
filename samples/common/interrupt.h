#include <stdint.h>

/* Functions */
#if defined(__linux__)
#include <metal/io.h>
int gic_register(uint32_t intno, uint32_t pri, uint32_t cpumask, struct metal_io_region *gicio);
#else /* FreeRTOS */
int isr_register(uint32_t intno, uint32_t pri, uint32_t cpumask, void (*fn)(void));
#endif
void eoi_notify(uint32_t val);
void wait_gic_init(void);

/* Interrupt handler table */
typedef void (*INTERRUPT_HANDLER)(void);
typedef struct {
    INTERRUPT_HANDLER fn;
} INTERRUPT_VECTOR;

