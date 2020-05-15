#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int add_two(void *);

int add_two(void * parameters)
{
  int result = (int) *parameters + 2;
  printf("adding two to %d = %d\n", (int) *parameters, result);

  pthread_exit(NULL);
}

int main()
{
  // create placeholder for threads
  pthread_t first_thread, second_thread;

  // create placeholder for parameters
  int first_num = 5, second_num = 3;

  // start thread
  pthread_create(&first_thread, NULL, add_two, (void *) &first_num);
  pthread_create(&second_thread, NULL, add_two, (void *) &second_num);

  // wait for threads to finish
  pthread_join(first_thread, NULL);
  pthread_join(second_thread, NULL);

  // done
  return 0;
}
