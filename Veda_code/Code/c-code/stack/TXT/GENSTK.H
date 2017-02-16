// Module implementing stack.
// Version : 1.0
// Author : Team -C

// define DATATYPE according to your needs
# define DATATYPE int


# define STACK_SIZE 10
# define ERR_FULL  -1
# define ERR_EMPTY -2

void init_stack(void);
void push (DATATYPE item);
DATATYPE pop();
