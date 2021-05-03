# Homework 12

余北辰 519030910245



**12.5 How does DMA increase system concurrency? How does it complicate hardware design?**

启动DMA传输时，主机将DMA命令块写入内存。CPU将该命令块写入DMA控制器后继续其他工作，而DMA控制器通过直接操作内存总线的方式，在没有CPU的帮助下进行传输。这样CPU可以在数据传输的同时进行其它的工作，因此提高了并行性。



DMA控制器通过一对称为DMA请求和DMA确认的线路实现DMA控制器与设备控制器之间的握手。有数据需要传输时，设备控制器通过发送信号使得DMA控制器占用内存总线。完成整个传输时，DMA中断CPU。