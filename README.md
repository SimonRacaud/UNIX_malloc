# UNIX_malloc
Rewriting of unix memory allocation functions

Using only __brk__ and __sbrk__, rewrite the 5 following C library functions: malloc, calloc, realloc, reallocarray and free.

```
  void *malloc(size_t size);
  
  void  free(void *ptr);
  
  void *calloc(size_t nmemb, size_t size);
  
  void *realloc(void *ptr, size_t size);
  
  void *reallocarray(void *ptr, size_t nmemb, size_t size);
 ```
 
 # Allocation Strategy
 
 - Align your memory on a power of 2.
 - The break is always aligned on a multiple of 2 pages.
 - Implement the best fit algorithm.
