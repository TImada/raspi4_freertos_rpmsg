#include "interrupt.h"
#include "board.h"

#if defined(__linux__)
#include <stddef.h>
void *gic_base = NULL;
#else /* FreeRTOS */
/* Vector table */
INTERRUPT_VECTOR InterruptHandlerFunctionTable[MAX_NUM_IRQS] = {0};
#endif

static int gic_enable(uint32_t intno, uint32_t pri, uint32_t cpumask)
{
	uint32_t n, reg, shift;
	uint32_t *addr;

	if (intno > 0xFFU) {
		return -1;
	}
	if (pri > 0xFFU) {
		return -2;
	}
	if (cpumask > 0xFFU) {
		return -3;
	}

	/* GICD_ISENABLERn */
	n = intno / 32U;
	addr = (uint32_t *)(GICD_BASE + 0x100U + 4U * n);
	reg = *addr;
	*addr = (reg | (0x1U << (intno % (32U))));
    
	/* GICD_IPRIORITYRn */
   	n = intno / 4U;
	addr = (uint32_t *)(GICD_BASE + 0x400U + 4U * n);
	shift = (intno % 4U) * 8U;
	reg = (*addr) & ~(0xFFU << shift);
	*addr = (reg | pri << shift);
    
	/* GICD_ITARGETSRn (only for SPIs) */
	if (intno >= 32U) {
   	   	n = intno / 4U;
		addr = (uint32_t *)(GICD_BASE + 0x800U + 4U * n);
		shift = (intno % 4U) * 8U;
		reg = (*addr) & ~(0xFFU << shift);
		*addr = (reg | cpumask << shift);
	}
    asm volatile ("isb");

    return 0;
}

#if defined(__linux__)
int gic_register(uint32_t intno, uint32_t pri, uint32_t cpumask, struct metal_io_region *gicio)
{
    int ret;

    gic_base = metal_io_phys_to_virt(gicio, GIC_BASE_PHY);
    if (!gic_base) {
        return -5;
    }

    ret = gic_enable(intno, pri, cpumask);
    if (ret) {
        return ret;
    }

	return 0;
}
#else /* FreeRTOS */
/* Interrupt handler registration */
int isr_register(uint32_t intno, uint32_t pri, uint32_t cpumask, void (*fn)(void))
{
    int ret;

    ret = gic_enable(intno, pri, cpumask);
    if (ret) {
        return ret;
    }

	if (!fn) {
		return -4;
	}

	/* Handler registration */
    InterruptHandlerFunctionTable[intno].fn = fn;
    
	return 0;
}   
/*-----------------------------------------------------------*/
#endif

/* EOI notification */
void eoi_notify(uint32_t val)
{
	uint32_t *addr;

	addr = (uint32_t *)(GICC_BASE + 0x10U);
	*addr = val;
    asm volatile ("isb");

	return;
}   
/*-----------------------------------------------------------*/

#if !defined(__linux__) /* FreeRTOS */
/*
 * wait_gic_init()
 * To check GIC initialization by Linux
 */
void wait_gic_init(void)
{
	volatile uint32_t *addr;

	addr = (uint32_t *)(GICD_BASE + 0x00U);

	while (*addr == 0x1U) { /* Wait until Linux disables GICD to set it up */
		;
	}
	while (*addr == 0x0U) { /* Wait until Linux enables GICD again after completing GICD setting up */
		;
	}

	return;
}
#endif
/*-----------------------------------------------------------*/
