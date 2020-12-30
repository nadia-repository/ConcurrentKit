#include "ConcurrentTools.h"

int compareAndSet(int *this,int expect,int update){
    return __sync_val_compare_and_swap(this,expect,update);
}