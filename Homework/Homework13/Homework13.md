# Homework 13

余北辰 519030910245



**13.7 Consider a system that supports 5,000 users. Suppose that you want to allow 4,990 of these users to be able to access one file.**

**a. How would you specify this protection scheme in UNIX?**

**b. Can you suggest another protection scheme that can be used more effectively for this purpose than the scheme provided by UNIX?**



a. 创建一个访问列表，保存这4990个用户的ID。设置该列表为可访问的。当用户提出访问请求时，在列表中查询，若ID在列表中则允许访问。

b. 创建一个列表用以保存10个被禁止访问的用户的ID，当用户提出访问请求时，在列表中查询，若ID在列表中未被找到则允许访问。