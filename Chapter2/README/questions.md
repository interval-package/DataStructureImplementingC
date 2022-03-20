
# questions
## 1) algorithm

### 1.Sort by access frequency
有同学建议，给每个数据元素增加一个访问频度域提高查找的性能.
其思想是每次查找到某个数据元素时，将对应的访问频度加1，
并按访问频度调整其在表中的位置，使得频度大的出现在表的前面。
请你设计算法实现该同学的想法，包括数据结构的设计。
### 2.City management
能够增加、删除、更新、查找不同城市及相关信息
### 3.Josephus problem
In computer science and mathematics, 
the Josephus problem (or Josephus permutation) is a theoretical problem related to a certain counting-out game.


A drawing for the Josephus problem sequence for 500 people and skipping value of 6.
The horizontal axis is the number of the person.
The vertical axis (top to bottom) is time (the number of cycle).
A live person is drawn as green, a dead one is drawn as black.
People are standing in a circle waiting to be executed.
Counting begins at a specified point in the circle and proceeds around the circle in a specified direction. 
After a specified number of people are skipped, the next person is executed. 
The procedure is repeated with the remaining people, starting with the next person, 
going in the same direction and skipping the same number of people, until only one person remains, and is freed.

The problem—given the number of people, starting point, direction, and number to be skipped—is 
to choose the position in the initial circle to avoid execution

#### 解决方案:使用回归算法
对于每一次处决,我们认为都使得总长度-1,然后使得我们的编号重新排序一次.
新编号new,就编号old,则有old = (new+m)%n.

为了补正序号从0开始,old = (new+m-1)%n + 1

f(1,m)=1,到达最后只有一个人的时候,结束.
## 2) functions

### 1.Reverse a single linked list
### 2.Insert X
Insert X into an ordered list, and maintain it as before


in the Sequential list
### 3.Right delete in a circular linked list
Delete an element on the right side of a circular linked list
### 4.First delete of X
delete the first elem of value x in a doubly linked list
