#if defined(__linux__)
#define LPRINTF(format, ...) printf(format, ##__VA_ARGS__)
#else /* FreeRTOS */
int my_printf(const char *fmt, ...);
#define LPRINTF(format, ...) my_printf(format, ##__VA_ARGS__)
#endif

#define LPERROR(format, ...) LPRINTF("ERROR: " format, ##__VA_ARGS__)
