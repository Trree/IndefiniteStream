# Indefinite Stream 

[中文说明](doc/description.md)

## About

When I read scip, I am so interesting in indefinite stream.So I implement it using cpp.

### v1.0

I want to make it simple enough, and only supports value types.

I think it like a deque, there are constantly data inserted from the back end. And we get data from top.

### v2.0

Using iterator(ForwardIterator), and inherit it. 



## Stream , scale and filter 

```
               /--------+        |++++++++++++++++          /--------+
              /         |        |               |         /         |
 stream  -> <    scale  | -----> |   filter      | ----> <    scale  | -----> 
              \         |        |               |         \         |
               \--------+        |++++++++++++++++          \--------+

```


