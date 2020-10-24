/// Copyright (C) strawberryhacker 

#include <cinnamon/types.h>
#include <cinnamon/sprint.h>
#include <cinnamon/apic.h>
#include <cinnamon/print.h>
#include <cinnamon/buddy_alloc.h>
#include <cinnamon/cache.h>
#include <cinnamon/mm.h>
#include <cinnamon/benchmark.h>
#include <cinnamon/thread.h>
#include <cinnamon/sched.h>
#include <cinnamon/page_alloc.h>
#include <cinnamon/pt_entry.h>
#include <cinnamon/syscall.h>
#include <cinnamon/interrupt.h>
#include <cinnamon/atomic.h>
#include <cinnamon/kmalloc.h>
#include <cinnamon/loader.h>
#include <cinnamon/panic.h>
#include <cinnamon/elf.h>
#include <cinnamon/gpio.h>
#include <cinnamon/mmc.h>
#include <cinnamon/task_manager.h>
#include <cinnamon/disk.h>

#include <regmap.h>
#include <stdarg.h>
#include <stdalign.h>

/// Early initialization for the kernel
void early_init(void)
{
    apic_init();

    // The loader is in control of the kernel download serial line and 
    // should be initialized first in order to access the bootloader. 
    loader_init();

    // Enable interrupt now to support reboot
    irq_disable();
    async_abort_enable();

    // Enable the L1 cache
    icache_enable();
    dcache_enable();
}

/// Initializes the kernel 
void kernel_init(void)
{
    mm_init();
    sched_init();
    disk_init();
}

/// This will handle driver initialization
void driver_init(void)
{
    mmc_init();
}

/// Entry point for the kernel after the assembly entry
void main(void)
{
    print(BLUE "Cinnamon starting...\n" NORMAL);
    
    // Initializes the system
    early_init();
    kernel_init();
    driver_init();

    // Add all the kernel processes here
    print("Adding kernel processes\n");
    //task_manager_init();

    // This will start the scheduler. After this point the main does not exist
    // anymore
    print("Start the scheduler\n");
    sched_start();

    while (1);
}
