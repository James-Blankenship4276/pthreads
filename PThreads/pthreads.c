//James Blankenship
//pthreads.c
//3/1/2022
//normal thread usage


#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>


struct thread_data{//https://hpc-tutorials.llnl.gov/posix/example_code/hello_arg2.c, https://hpc-tutorials.llnl.gov/posix/passing_args/
  int threadids;
  int runs;


};
int counter = 0;

struct thread_data thread_data_array[4000000];

void *counterfun(void *tid){
  long thread_id;
  int run;
  int i = 0;
  struct thread_data *my_data;
  my_data = (struct thread_data *) tid;
  thread_id = my_data->threadids;
  run = my_data->runs;
  
  
  for(i = 0;i< run;i++) {
    printf("#%d\n",counter);
    counter++;
    
   
     }
  pthread_exit(NULL);


  }


int main(int argc, char *argv[]){
 

  
  long threadamount = 4;
  int run = 10000;
  if(argv[1] != NULL && argv[2] != NULL){
    
  
  threadamount = atoi(argv[1]);

  
  
  
    run = atoi(argv[2]);
  }
  pthread_t threads[threadamount];
   int status;
   long i;

  for(i = 0;i< threadamount; i++){
    thread_data_array[i].threadids = i;
    thread_data_array[i].runs  = run;
    printf("Main here. Creating thread %ld\n",i);
    status = pthread_create(&threads[i],NULL,counterfun,(void*) &thread_data_array[i]);//https://hpc-tutorials.llnl.gov/posix/creating_and_terminating/

    if(status){
      printf("Oops. pthread_create returned error code %d\n", status);
      exit(-1);
    }
  }
 pthread_exit(NULL);
 return 0;
}
