#include "thread.h"

THREAD *currentThread(void){

}

void *runThread(THREAD *thread){
    if(thread->is_self == 0){
        //执行run方法时不为当前线程本身，则执行
        
    }
}