/*
 * file:        part-1.c
 * description: Part 1, CS5600 Project 1, 2025 SP
 */

/* THE ONLY INCLUDE FILE */
#include "sysdefs.h"

/* write these functions */

int read(int fd, void *ptr, int len) {
	return (int)syscall(__NR_read, fd, ptr, len, 0, 0, 0);
}

int write(int fd, void *ptr, int len) {
	return (int)syscall(__NR_write, fd, ptr, len, 0, 0, 0);
}

void exit(int err) {
	syscall(__NR_exit, err, 0, 0, 0, 0, 0);
}

/* ---------- */

/* Factor, factor! Don't put all your code in main()! 
*/
void clear_buffer(char *buffer, int size) {
    for (int i = 0; i < size; i++) {
        if(buffer[i] == '\0')
			return;
		buffer[i] = '\0';
    }
}
/* clear buffer before taking any ne input*/

/* read one line from stdin (file descriptor 0) into a buffer: */
void readline(char *buffer, int len)
{	
	clear_buffer(buffer, len);
	char *ptr = buffer;  // Pointer to traverse the buffer
    while (ptr < buffer + len - 1) {  // Ensure space for null terminator
        int bytes_read = read(0, ptr, 1);  // Read 1 byte from stdin
        if (bytes_read <= 0) {  // Stop on EOF or error
            break;
        }
        if (*ptr == '\n') {  // Stop on newline (Enter key)
            ptr++;
			break;
        }
        ptr++;  // Move to the next position in the buffer
    }
    *ptr = '\0'; 
} 

/* print a string to stdout (file descriptor 1) */
void print(char *buffer) {
    write(1, (void *)buffer, 200);
}

int check_quit(char *buffer) {
    return buffer[0] == 'q' && buffer[1] == 'u' && buffer[2] == 'i' && buffer[3] == 't';
}
/* ---------- */

void main(void)
{
	/* your code here */
	char buffer[200];
    while(1) {
        readline(buffer, 200);
        if (check_quit(buffer)) {
            exit(0);
        }
        print(buffer);
    }
}
