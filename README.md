# Data structure class Note

## (1)introduction
### 1.It's the note I took at my class. 
It basically contains all the points of our course and homework.

Feel free to copy or clone it.

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
7. Graph

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

In chapter 6, and after this problem is solved.

We'd define all the functions with return type bool, the returns should be in the parameter.

Let's see an example:

```c
// old defination, in the chapter 3

ELEMENT_TYPE DeQueue_Sq(psqQue sq);

// after change the method, in the chapter 6

bool _tree_que_de(_tQue tar, tNode* container);
```

##### (2) Constructors

#### 3.C Namespace

Finally I'd wrap all the data structure with C namespace.

Actually C doesn't have namespace, but we could use the struct to imitate it.

### 3.Detail info
For each Chapter, I'd write a .md file to illustrate the questions of this chapter.

And in some chapter may have my class note.

What's more it may contain my experiment report(the class required.)

## (3)Acknowledgement
My code may be not that good, but I' m looking to improvement.

And I'm glad to share my understanding of this art and make some friends.

------

This Project already ended.

For me, it's badly  formatted and not work the best on some scene. However I hope this repo could help any starter who like me at that time to quickly grow up. 