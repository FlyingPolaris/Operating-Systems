# Homework 10

余北辰 519030910245

**10.5 Consider the page table for a system with 12-bit virtual and physical addresses and 256-byte pages.**

| Page | Page Frame |
| :--: | :--------: |
|  0   |     -      |
|  1   |     2      |
|  2   |     C      |
|  3   |     A      |
|  4   |     -      |
|  5   |     4      |
|  6   |     3      |
|  7   |     -      |
|  8   |     B      |
|  9   |     0      |

**The list of free page frames is D, E, F (that is, D is at the head of the list, E is second, and F is last). A dash for a page frame indicates that the page is not in memory.**

**Convert the following virtual addresses to their equivalent physical addresses in hexadecimal. All numbers are given in hexadecimal.**

**• 9EF**

**• 111**

**• 700**

**• 0FF**



- $9EF \rightarrow 0EF$
- $111 \rightarrow 211$
- 7没有对应的页框，故使用第一个空闲页框D。 $700 \rightarrow D00$
- 0没有对应的页框，故使用第二个空闲页框E。  $0FF \rightarrow EFF$





---

**10.7 Consider the two-dimensional array A:**

```c
int A[][] = new int[100][100];
```

**where `A[0][0]` is at location 200 in a paged memory system with pages of size 200. A small process that manipulates the matrix resides in page 0 (locations 0 to 199). Thus, every instruction fetch will be from page 0.**

**For three page frames, how many page faults are generated by the following array-initialization loops? Use LRU replacement, and assume that page frame 1 contains the process and the other two are initially empty.**

**a.**

```c
for (int j = 0; j < 100; j++)
for (int i = 0; i < 100; i++)
A[i][j] = 0;
```

**b.** 

```c
for (int i = 0; i < 100; i++)
for (int j = 0; j < 100; j++)
A[i][j] = 0;
```



a.

页的大小为200，不同的i之间是非连续的。因此无论j的值如何，每当i为偶数时++，会出现缺页错误。每当i为奇数，则能够命中。因此一共会出现50*100=5000次缺页错误。

b.

不同的j之间是连续的。因此只有当j为0且i为偶数时++，才会出现缺页错误。因此一共会出现50次缺页错误。



---

**10.8 Consider the following page reference string:**

**1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6.**

**How many page faults would occur for the following replacement algorithms, assuming one, two, three, four, five, six, and seven frames? Remember that all frames are initially empty, so your first unique pages will cost one fault each.**

**• LRU replacement**

**• FIFO replacement**

**• Optimal replacement**



1个页框：

LRU，FIFO 和 Optimal均为20次缺页错误。



2个页框：

LRU：命中2次，18次缺页错误。

1	2	3	4	2	1	5	6	2	1	**2**	3	7	6	3	**2**	1	2	3	6



1	1	3	3	2	2	5	5	2	2	**2**	3	3	6	6	**2**	2	2	3	3

 	 2	2	4	4	1	1	6	6	1	**1**	1	7	7	3	**3**	1	1	1	6



FIFO：命中2次，18次缺页错误。

1	2	3	4	2	1	5	6	2	1	**2**	3	7	6	3	**2**	1	2	3	6



1	1	3	3	2	2	5	5	2	2	**2**	3	3	6	6	**2**	2	2	3	3

 	 2	2	4	4	1	1	6	6	1	**1**	1	7	7	3	**3**	1	1	1	6



Optimal：命中5次，15次缺页错误。

1	2	3	4	**2**	1	5	6	**2**	1	**2**	3	7	6	**3**	2	1	**2**	3	6



1	1	3	4	**4**	1	5	6	**6**	1	**1**	3	3	3	**3**	3	1	**1**	1	6	

 	 2	2	2	**2**	2	2	2	**2**	2	**2**	2	7	6	**6**	2	2	**2**	3	3



3个页框：

LRU：命中5次，15次缺页错误。

1	2	3	4	**2**	1	5	6	2	1	**2**	3	7	6	**3**	2	1	**2**	3	6



1	1	1	4	**4**	4	5	5	5	1	**1**	1	7	7	**7**	2	2	**2**	**2**	2

​	  2	2	2	**2**	2	2	6	6	6	**6**	3	3	3	**3**	3	3	**3**	**3**	3

​			3	3	**3**	1	1	1	2	2	**2**	2	2	6	**6**	6	1	**1**	**1**	6



FIFO：命中4次，16次缺页错误。

1	2	3	4	**2**	1	5	6	2	1	**2**	3	7	6	**3**	2	1	**2**	3	6

1	1	1	4	**4**	4	4	6	6	6	**6**	3	3	3	**3**	2	2	**2**	2	6	

​	  2	2	2	**2**	1	1	1	2	2	**2**	2	7	7	**7**	7	1	**1**	1	1

​			3	3	**3**	3	5	5	5	1	**1**	1	1	6	**6**	6	6	**6**	3	3



Optimal：命中9次，11次缺页错误。

1	2	3	4	**2	1**	5	6	**2	1	2**	3	7	**6	3**	2	1	**2	3**	6

1	1	1	1	**1	1**	1	1	**1	1	1**	3	3	**3	3**	3	3	**3	3**	6

​	  2	2	2	**2	2**	2	2	**2	2	2**	2	7	**7	7**	2	2	**2	2**	2

​			3	4	**4	4**	5	6	**6	6	6**	6	6	**6	6**	6	1	**1	1**	3

​	

4个页框：

LRU：命中10次，10次缺页错误。

1	2	3	4	**2	1**	5	6	**2**	**1	2**	3	7	6	**3	2**	1	**2	3	6**

1	1	1	1	**1	1**	5	5	**5**	**5	5**	3	3	3	**3	3**	3	**3	3	3**

​	  2	2	2	**2	2**	2	2	**2**	**2	2**	2	2	2	**2	2**	2	**2	2	2**

​			3	3	**3	3**	3	6	**6**	**6	6**	6	7	7	**7	7**	1	**1	1	1**

​				  4	**4	4**	4	4	**4**	**1	1**	1	1	6	**6	6**	6	**6	6	6**

​	

FIFO：命中6次，14次缺页错误。

1	2	3	4	**2	1**	5	6	2	1	**2**	3	7	6	**3**	2	1	**2**	3	**6**

1	1	1	1	**1	1**	5	5	5	5	**5**	3	3	3	**3**	3	1	**1**	1	**1**

​	  2	2	2	**2	2**	2	6	6	6	**6**	6	7	7	**7**	7	7	**7**	3	**3**

​			3	3	**3	3**	3	3	2	2	**2**	2	2	6	**6**	6	6	**6**	6	**6**

​			 	 4	**4	4**	4	4	4	1	**1**	1	1	1	**1**	2	2	**2**	2	**2**



Optimal：命中12次，8次缺页错误。

1	2	3	4	**2	1**	5	6	**2	1	2	3**	7	**6	3	2**	1	**2	3	6**

1	1	1	1	**1	1**	1	1	**1	1	1	1**	7	**7	7	7**	1	**1	1	1**

​	  2	2	2	**2	2**	2	2	**2	2	2	2**	2	**2	2	2**	2	**2	2	2**

​			3	3	**3	3**	3	3	**3	3	3	3**	3	**3	3	3**	3	**3	3	3**

​				  4	**4	4**	5	6	**6	6	6	6**	6	**6	6	6**	6	**6	6	6**



5个页框：

LRU：命中12次，8次缺页错误。

1	2	3	4	**2	1**	5	6	**2	1	2**	3	7	**6**	**3	2	1	2	3	6**

1	1	1	1	**1	1**	1	1	**1	1	1**	1	1	**1	1	1	1	1	1	1**

​	  2	2	2	**2	2**	2	2	**2	2	2**	2	2	**2	2	2	2	2	2	2**

​			3	3	**3	3**	3	6	**6	6	6**	6	6	**6	6	6	6	6	6	6**

​				  4	**4	4**	4	4	**4	4	4**	3	3	**3	3	3	3	3	3	3**

​									 5	5	**5	5	5**	5	7	**7	7	7	7	7	7	7**



FIFO：命中10次，10次缺页错误。

1	2	3	4	**2	1**	5	6	**2**	1	2	3	**7	6	3	2	1	2	3	6**

1	1	1	1	**1	1**	1	6	**6**	6	6	6	**6	6	6	6	6	6	6	6**

​	  2	2	2	**2	2**	2	2	**2**	1	1	1	**1	1	1	1	1	1	1	1**

​			3	3	**3	3**	3	3	**3**	3	2	2	**2	2	2	2	2	2	2	2**

​				  4	**4	4**	4	4	**4**	4	4	3	**3	3	3	3	3	3	3	3**

​									5	5	**5**	5	5	5	**7	7	7	7	7	7	7	7**



Optimal：命中13次，7次缺页错误。

1	2	3	4	**2	1**	5	6	**2	1	2	3**	7	**6	3	2	1	2	3	6**

1	1	1	1	**1	1**	1	1	**1	1	1	1**	1	**1	1	1	1	1	1	1**

​	  2	2	2	**2	2**	2	2	**2	2	2	2**	2	**2	2	2	2	2	2	2**

​			3	3	**3	3**	3	3	**3	3	3	3**	3	**3	3	3	3	3	3	3**

​				  4	**4	4**	4	6	**6	6	6	6**	6	**6	6	6	6	6	6	6**

​									 5	5	**5	5	5	5**	7	**7	7	7	7	7	7	7**	



6个页框：

LRU：命中13次，7次缺页错误。

1	2	3	4	**2	1**	5	6	**2	1	2	3**	7	**6	3	2	1	2	3	6**

1	1	1	1	**1	1**	1	1	**1	1	1	1**	1	**1	1	1	1	1	1	1**

​	  2	2	2	**2	2**	2	2	**2	2	2	2**	2	**2	2	2	2	2	2	2**

​			3	3	**3	3**	3	3	**3	3	3	3**	3	**3	3	3	3	3	3	3**

​				  4	**4	4**	4	4	**4	4	4	4**	4	**4	4	4	4	4	4	4**	

​								 	5	5	**5	5	5	5**	7	**7	7	7	7	7	7	7**

​										   6	**6	6	6	6**	6	**6	6	6	6	6	6	6**



FIFO：命中10次，10次缺页错误。

1	2	3	4	**2	1**	5	6	**2	1	2	3**	7	**6	3	2**	1	2	3	**6**

1	1	1	1	**1	1**	1	**1	1	1	1**	1	7	**7	7	7**	7	7	7	**7**

​	  2	2	2	**2	2**	2	**2	2	2	2**	2	2	**2	2	2**	1	1	1	**1**

​			3	3	**3	3**	3	**3	3	3	3**	3	3	**3	3	3**	3	2	2	**2**

​				  4	**4	4**	4	**4	4	4	4**	4	4	**4	4	4**	4	4	3	**3**

​									 5	**5	5	5	5**	5	5	**5	5	5**	5	5	5	**5**

​										   **6	6	6	6**	6	6	**6	6	6**	6	6	6	**6**



Optimal：因为序列中一共有7个数字，因此至少会发生7次缺页错误。5个页框时，已经命中13次，7次缺页错误。故此时一定发生7次缺页错误。



7个页框：

因为序列中一共有7个数字，且有7个页框，故LRU，FIFO 和 Optimal均为7次缺页错误。

---

**10.9 Consider the following page reference string:**

**7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1.**

**Assuming demand paging with three frames, how many page faults would occur for the following replacement algorithms?**

**• LRU replacement**

**• FIFO replacement**

**• Optimal replacement**



7	2	3	1	2	5	3	4	6	7	7	1	0	5	4	6	2	3	0	1



LRU：共命中2次，18次缺页错误

7	2	3	1	**2**	5	3	4	6	7	**7**	1	0	5	4	6	2	3	0	1



7	7	7	1	**1**	1	3	3	3	7	**7**	7	7	5	5	5	2	2	2	1		

​	  2	2	2	**2**	2	2	4	4	4	**4**	1	1	1	4	4	4	3	3	3

​			3	3	**3**	5	5	5	6	6	**6**	6	0	0	0	6	6	6	0	0



FIFO：共命中3次，17次缺页错误

7	2	3	1	**2**	5	**3**	4	6	7	**7**	1	0	5	4	6	2	3	0	1



7	7	7	1	**1**	1	**1**	1	6	6	**6**	6	0	0	0	6	6	6	0	0

​	  2	2	2	**2**	5	**5**	5	5	7	**7**	7	7	5	5	5	2	2	2	1

​			3	3	**3**	3	**3**	4	4	4	**4**	1	1	1	4	4	4	3	3	3



Optimal：共命中7次，13次缺页错误

7	2	3	1	2	5	3	4	6	7	7	1	0	5	4	6	2	3	0	1



7	7	7	1	**1**	1	**1**	1	1	1	**1	1**	1	**1**	1	1	1	1	**1	1**	

​	  2	2	2	**2**	5	**5**	5	5	5	**5	5**	5	**5**	4	6	2	3	**3	3**

​			3	3	**3**	3	**3**	4	6	7	**7	7**	0	**0**	0	0	0	0	**0	0**