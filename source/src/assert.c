#include "core.h"
#include "../d_debug.h"

void D_Assert(const Char *msg, const Char *file, Uint line) {
#ifdef D_WEPI
    Wepi_Assert(msg, file, line);
#else
    D_Printk("Debug Assertion Failed! -------------------------------------------------\n\n");
    D_Printk("File: %s\n", file);
    D_Printk("Line: %d\n\n", line);
    D_Printk("%s\n", msg);
    D_Printk("-------------------------------------------------------------------------\n");
#endif
    MC_knlExit(-1);
}
