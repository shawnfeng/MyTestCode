#include <unistd.h>
#include "hello.h"

void main_hello()
{
  for (;;) {
    hello();
    sleep(1);
  }
}

int main()
{
  
  main_hello();
  return 0;
}
