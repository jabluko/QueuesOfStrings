#ifndef _STRQUEUE_H_
#define _STRQUEUE_H_

#ifndef __cplusplus
#include <stddef.h>
#else
#include <cstddef>
extern "C" {
    namespace cxx {
#endif

unsigned long strqueue_new();
void strqueue_delete(unsigned long id);
size_t strqueue_size(unsigned long id);
void strqueue_remove_at(unsigned long id, size_t position);
const char* strqueue_get_at(unsigned long id, size_t position);
void strqueue_clear(unsigned long id);
int strqueue_comp(unsigned long id1, unsigned long id2);

#ifdef __cplusplus
    }
}
#endif

#endif