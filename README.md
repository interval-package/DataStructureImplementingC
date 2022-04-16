# Data structure class Note

## (1)introduction
### 1.It's the note I took at my class. 
It basically contains all the points of our course and homework.
### 2.Algorithm
It may have some algorithm problems, and I'll share my solution of them.

And some solution of problems on leet code.

Some OS questions.

## (2)tutorial
### 1.Chapters
1. Introduction.
2. Linear List.
3. Stack and Queue.
4. String
5. General List, Arrays and Sparse Matrix
6. Tree

### 2.For Usage

#### 1.Stack and queue

In the chapter3 we define the stack and queue, using the macro `ELEMENT_TYPE` to announce the type of elements in the data struct. 

However in some conditions, this method would cause fatal problems(I actually suffer from this, especially when I'm trying to reuse the struct).

##### (1) When we want to contain two different type element using the struct

Since I'm using only one macro to tell the type, when using two struct of different type, they will overcover each other.

So one method is make the elements all pointer and using a new macro to get element of right type.

Such as:

```c
#ifndef ELEM
#define ELEM
typedef void* ELEMENT_TYPE;
#endif

#define TYPE_MACRO int
```

##### (2) When other method of another data struct is depending on this basic struct and method

When `ELEMENT_TYPE` is defined `void*`, it's possible to reuse it.

However we'd use the new structure to contain new element.

So we make compromise that, we would redefine a existing structure to implement the new one.

#### 2.API wrappers

##### (1) Returns

In the first of some data struct, the is some drawback in it.

For some getter type functions, the returns should be the variables but not the "return". The return should deliver the function is finished or not, with bool type.

In chapter6, and after this problem is solved.

##### (2) Constructors

### 3.Detail info
For each Chapter, I'd write a .md file to illustrate the questions of this chapter.

And in some chapter may have my class note.

What's more it may contain my experiment report(the class required.)

## (3)Acknowledgement
My code may be not that good, but I' m looking to improvement.

And I'm glad to share my understanding of this art and make some friends.