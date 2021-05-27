#include <stdarg.h>
#include <stdio.h>
#include "uart.h"

#define BUF_SIZE    (256)

int my_printf(const char *fmt, ...) {
    char buf[BUF_SIZE];
    va_list args;
    int ret;

    va_start(args, fmt);
    ret = vsprintf(buf, fmt, args);
    uart_puts(buf);
    va_end(args);

    return ret;
}
