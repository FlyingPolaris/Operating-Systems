# Homework 14

余北辰 519030910245



**14.1 Consider a file currently consisting of 100 blocks. Assume that the file-control block (and the index block, in the case of indexed allocation) is already in memory. Calculate how many disk I/O operations are required for contiguous, linked, and indexed (single-level) allocation strategies, if, for one block, the following conditions hold. In the contiguous-allocation case, assume that there is no room to grow at the beginning but there is room to grow at the end. Also assume that the block information to be added is stored in memory.**

**a. The block is added at the beginning.**

**b. The block is added in the middle.**

**c. The block is added at the end.**

**d. The block is removed from the beginning.**

**e. The block is removed from the middle.**

**f. The block is removed from the end.**



​			     Contiguous                                            Linked                                                 Indexed

a.       201(100读写+1新写)       1（1新写）                1（1新写）

b. 101(50读写+1新写)        52（50读+第50块写+1新写）   1（1新写）

c. 1（1新写）              3（第100块读写+1新写）      1（1新写）

d. 198（99读写）           1（读第1块）               0

e. 98（后49块读写）         52（51读+第50块写）         0

f. 0                     100（99读+1写）            0