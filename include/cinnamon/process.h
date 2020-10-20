/// Copyright (C) strawberryhacker

#ifndef PROCESS_H
#define PROCESS_H

#include <cinnamon/types.h>

struct page* process_mm_init(struct thread* thread, u32 stack_size);

#endif
