/* GIC-400 registers */
#if defined(__linux__)
#define GIC_BASE_PHY    (0x40041000UL)
#define GIC_BASE        (gic_base)
#else /* FreeRTOS */
#define GIC_BASE        (0xFF840000UL)
#endif
#define GICD_BASE       (GIC_BASE + 0x00001000UL)
#define GICC_BASE       (GIC_BASE + 0x00002000UL)

/* The number of IRQs on BCM2711 */
#define MAX_NUM_IRQS    (224U)

/* IRQ number */
#if defined(__linux__)
#define IRQ_MBOX        (32U)
#else /* FreeRTOS */
#define IRQ_MBOX        (44U)
#define IRQ_VTIMER      (27U)
#define IRQ_VC_UART     (153U)
#endif
