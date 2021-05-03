# Homework 11

余北辰 519030910245



**11.13 Suppose that a disk drive has 5,000 cylinders, numbered 0 to 4,999. The drive is currently serving a request at cylinder 2,150, and the previous request was at cylinder 1,805. The queue of pending requests, in FIFO order, is:**

**2,069; 1,212; 2,296; 2,800; 544; 1,618; 356; 1,523; 4,965; 3,681**

**Starting from the current head position, what is the total distance (in cylinders) that the disk arm moves to satisfy all the pending requests for each of the following disk-scheduling algorithms?**

**a. FCFS**

**b. SCAN**

**c. C-SCAN**



a. FCFS：

$2150\rightarrow2069\rightarrow1212\rightarrow2296\rightarrow2800\rightarrow544\rightarrow1618\rightarrow356\rightarrow1523\rightarrow4965\rightarrow3681$

总距离为：

$(2150-2069)+(2069-1212)+(2296-1212)+(2800-2296)+(2800-544)+(1618-544)+(1618-356)\\+(1523-356)+(4965-1523)+(4965-3681)=13011$



b. SCAN：

$2150 \rightarrow 2296 \rightarrow 2800 \rightarrow 3681 \rightarrow 4965 \rightarrow2069\rightarrow1618\rightarrow1523\rightarrow1212\rightarrow544\rightarrow356$

总距离为：

$(4999-2150)+(4999-356) = 7492$



c. C-SCAN

$2150 \rightarrow 2296 \rightarrow 2800 \rightarrow 3681 \rightarrow 4965 \rightarrow 356 \rightarrow 544 \rightarrow 1212 \rightarrow 1523 \rightarrow 1618 \rightarrow2069$

总距离为：

$(4999-2150) + 4999 + 2069 = 9917$

---

**11.20 Consider a RAID level 5 organization comprising five disks, with the parity for sets of four blocks on four disks stored on the fifth disk. How many blocks are accessed in order to perform the following?**

**a. A write of one block of data**

**b. A write of seven continuous blocks of data**



a. 写一个数据块时，需要读写目标块及其对应的奇偶控制块，共访问2个块

b. 写7个连续的数据块时，因为4个块为一组，需要访问这7个块和一个紧挨着的块，以及与之对应的两个奇偶控制块，共10个块

