#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>
#include<sys/sem.h>

typedef sem_t semaphore;
semaphore mutex;
semaphore db;
int rc=0;
void down(semaphore* s){
    sem_wait(s);
} 
void up(semaphore * s){
    sem_post(s);
}
void *reader(int );
void *wirter(int);
int main (int argc, char* argv[]){
    pthread_t hiloReader;
    pthread_t hiloWriter;


    sem_init(&mutex,0,1);
    sem_init(&db,0,1);

    pthread_create(&hiloWriter,NULL,&writer,NULL);

    pthread_create(&hiloReader,NULL,&reader,NULL);

    pthread_join(hiloReader,NULL);

    pthread_join(hiloWriter,NULL);
    exit(EXIT_SUCCESS);
}

void *reader(int i){
    while (1)
    {
        down(&mutex);
        rc++;
        if (rc==1)
        {
            down(&db);
        }
        up (&mutex);
       // read_data_base();
        down(&mutex);
        rc--;
        if (rc==0)
        {
            up(&mutex);
        }
        up(&mutex);
        //use_data_read();
        
    }
    
    
}
void *writer(int i){
        while (1)
        {
            //thing_up_data();
            down(&db);
            //write_date_base();
            up(&db);

        }
        
    }