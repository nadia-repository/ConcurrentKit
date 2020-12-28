ConcurrentKit是为C提供的并发工具包：

1.ReentrantLock，为C提供可重入的公平&非公平锁。
* 可重入公平锁&非公平锁的统一实现，屏蔽底层的线程对锁的操作，提供简单的加锁&释放锁方法。
* 提供线程级别的中断状态，线程可自行判断中断状态进行相应处理，而不需要注册进程的中断信号。
* 抽象线程模型，提供对线程简单的操作方法。

2.ThreadPool
* newFixedThreadPool，初始化固定大小线程池
* submit，向线程池中提交任务
* shutdown，结束线程池

3.Atomic
* atomicInt，初始化int类型原子结构
* atomicInt->getAndIncrement，原子操作+1
* atomicInt->getAndDecrement，原子操作-1

4.LinkedBlockingQueue
* initLinkedBlockingQueue，初始化阻塞队列
* LinkedBlockingQueue->add，向阻塞队列中添加数据，超时队列容量时阻塞操作线程。
* LinkedBlockingQueue->take，从阻塞队列中获取数据，阻塞队列为空时阻塞操作线程。