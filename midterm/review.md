# C Functions



## Basic



## I/O

`FILE* fopen(const char* pathname, const char*made)`

* return file pointer (to buffer)
* Mode
  * "r" - read only
  * "w" - write
  * "a" - append

`fclose(FILE* stream)`

`fread`

`fwrite`

`fgetc/fputc`

`fgets/fputs`

`int fseek(FILE *fp, long offset, int whence)`

`long ftell(FILE *fp)`

`void rewind(FILE *fp)`



## Socket

`int socket(int domain, int type, int protocol)`

`int bind(int sockfd, struct sockaddr *my_addr, int addrlen)`

`int listen(int sockfd, int backlog)`

## Threads/Processes



# Psuedocode

# Linux

`strace touch x`: monitor system calls

`>` : redirect stdout to file

`<`: redirect stdin to file

`2>`: redirect stderr to file

`>>`: append stdout to file

`2>&1` redirect fd2 to fd1

`ifconfig lo`