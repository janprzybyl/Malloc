# Malloc

This project is about implementing a dynamic memory allocation mechanism.


# Mechanism
In C, the library function **malloc** is used to allocate a **block of memory** on the **heap**. The program accesses this block of memory via a pointer that malloc returns. When the memory is no longer needed, the pointer is passed to function **free** which deallocates the memory so that it can be used for other purposes.
The last function is called **realloc**. It change size of allocated memory, preserve data and returns a pointer to its block of memory.

# General
Our library contains implementation of functions I mentioned before:
  - `malloc`
  - `free`
  - `realloc`

<br/>:bulb: To better understand this project check *malloc.pdf* file
