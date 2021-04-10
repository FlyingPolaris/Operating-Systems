# Homework 9

519030910245 余北辰



**9.6 Given six memory partitions of 300 KB, 600 KB, 350 KB, 200 KB, 750 KB, and 125 KB (in order), how would the first-fit, best-fit, and worst-fit algorithms place processes of size 115 KB, 500 KB, 358 KB, 200 KB, and 375 KB (in order)?**



first-fit:

初始时：

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 300KB | 600KB | 350KB | 200KB | 750KB | 125KB |

115KB插入到编号1的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 185KB | 600KB | 350KB | 200KB | 750KB | 125KB |

500KB插入到编号2的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 185KB | 100KB | 350KB | 200KB | 750KB | 125KB |

358KB插入到编号5的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 185KB | 100KB | 350KB | 200KB | 392KB | 125KB |

200KB插入到编号3的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 185KB | 100KB | 150KB | 200KB | 392KB | 125KB |

375KB插入到编号5的位置。

| 编号 | 1     | 2     | 3     | 4     | 5    | 6     |
| ---- | ----- | ----- | ----- | ----- | ---- | ----- |
| 大小 | 185KB | 100KB | 150KB | 200KB | 17KB | 125KB |



best-fit:

初始时：

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 300KB | 600KB | 350KB | 200KB | 750KB | 125KB |

115KB插入到编号6的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6    |
| ---- | ----- | ----- | ----- | ----- | ----- | ---- |
| 大小 | 300KB | 600KB | 350KB | 200KB | 750KB | 10KB |

500KB插入到编号2的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6    |
| ---- | ----- | ----- | ----- | ----- | ----- | ---- |
| 大小 | 300KB | 100KB | 350KB | 200KB | 750KB | 10KB |

358KB插入到编号5的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6    |
| ---- | ----- | ----- | ----- | ----- | ----- | ---- |
| 大小 | 300KB | 100KB | 350KB | 200KB | 392KB | 10KB |

200KB插入到编号4的位置；

| 编号 | 1     | 2     | 3     | 4    | 5     | 6    |
| ---- | ----- | ----- | ----- | ---- | ----- | ---- |
| 大小 | 300KB | 100KB | 350KB | 0KB  | 392KB | 10KB |

375KB插入到编号5的位置。

| 编号 | 1     | 2     | 3     | 4    | 5    | 6    |
| ---- | ----- | ----- | ----- | ---- | ---- | ---- |
| 大小 | 300KB | 100KB | 350KB | 0KB  | 17KB | 10KB |



worst-fit:

初始时：

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 300KB | 600KB | 350KB | 200KB | 750KB | 125KB |

115KB插入到编号5的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 300KB | 600KB | 350KB | 200KB | 635KB | 125KB |

500KB插入到编号5的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 300KB | 600KB | 350KB | 200KB | 135KB | 125KB |

358KB插入到编号2的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 300KB | 242KB | 350KB | 200KB | 135KB | 125KB |

200KB插入到编号3的位置；

| 编号 | 1     | 2     | 3     | 4     | 5     | 6     |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- |
| 大小 | 300KB | 242KB | 150KB | 200KB | 135KB | 125KB |

375KB没有足够的位置。



---

**9.7 Assuming a 1-KB page size, what are the page numbers and offsets for the following address references (provided as decimal numbers):**

**a. 3085**

**b. 42095**

**c. 215201**

**d. 650000**

**e. 2000001**



页的大小为1KB说明offset有10位。

a. $3085 = (110000001101)_2$，故page number为 $(11)_2 = 3$，offset为 $(1101)_2 = 13$。

b. $42095 = (1010010001101111)_2$，故page number为 $(101001)_2 = 41$，offset为 $(1101111)_2 = 111$。

c. $215201 = (110100100010100001)_2$，故 page number为 $(11010010)_2 = 210$，offset为 $(10100001)_2=161$。

d. $650000=(10011110101100010000)_2$，故 page number为 $(1001111010)_2 = 634$，offset为 $(1100010000)_2=784$。

e. $2000001 = (111101000010010000001)_2$，故 page number为 $(11110100001)_2 = 1953$，offset为 $(10000001)_2=129$。



---

**9.9 Consider a logical address space of 256 pages with a 4-KB page size, mapped onto a physical memory of 64 frames.**

**a. How many bits are required in the logical address?**

**b. How many bits are required in the physical address?**



a. 页的大小为4KB说明offset有12位。

逻辑地址空间有256页说明page number有8位。

因此共20位。



b. 页的大小为4KB说明offset有12位。

页帧有64页说明frame number有6位。

因此共18位。



---

**9.10 Consider a computer system with a 32-bit logical address and 4-KB page size. The system supports up to 512 MB of physical memory. How many entries are there in each of the following?**

**a. A conventional, single-level page table**

**b. An inverted page table**



页的大小为4KB说明offset有12位，page number有32-12=20位。

物理内存大小为512MB说明frame number有29-12=17位。

a. 普通单级页表 条目的数量对应的是逻辑地址空间，为 $2^{20}$；

b. 倒置页表  条目的数量对应的是物理地址空间，为 $2^{17}$。