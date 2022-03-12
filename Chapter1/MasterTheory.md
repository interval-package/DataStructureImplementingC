# 递归算法的时间复杂度分析方法
## 1.递推方法
---
就是基本的数学的推导方法，就像我们以前写的那样

## 2.主方法求解递归式，Master定理

## 3.递归树求解

## 4.代入法
比如我们求解，递归式 T(n) = 2T(n/2)+n 我们猜测解是O(nlgn),我们要寻找到一个常数c,使得T(n)<=cnlgn 即T(n) <= 2c(n/2)lg(n/2)+n <= cnlgn-cnlg2+n = cnlgn-cn+n 
只要c>=1,T(n)<=cnlgn,所以我们的猜测是正确的。
***
代入法全凭经验，通常用递归树来确定上界，然后用代入法再证明。