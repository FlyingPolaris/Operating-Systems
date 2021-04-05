# Homework 7

余北辰 519030910245



**7.8 The Linux kernel has a policy that a process cannot hold a spinlock while attempting to acquire a semaphore. Explain why this policy is in place.**





---

**7.11 Discuss the tradeoff between fairness and throughput of operations in the readers–writers problem. Propose a method for solving the readers–writers problem without causing starvation.**







---

**7.16 The C program stack-ptr.c (available in the source-code download) contains an implementation of a stack using a linked list. An example of its use is as follows:**

```c
StackNode *top = NULL; 
push(5, &top); 
push(10, &top); 
push(15, &top);
int value = pop(&top); 
value = pop(&top); value = pop(&top);
```

**This program currently has a race condition and is not appropriate for a concurrent environment. Using Pthreads mutex locks (described in Section 7.3.1), fix the race condition.**

