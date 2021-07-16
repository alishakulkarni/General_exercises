#include <pthread.h>
#include <stdio.h>



#define NUM_THREADS 2

pthread_mutex_t  mutexBuf;
pthread_cond_t prod_c, cons_c;


//Global buffer

struct Buf{
	char value;
	int status
}buf;

struct Buf buf = {
	.value = 0,
	. status =0
};

void *Client (void *args){
	
	while(1){   //while loop will run indefinately and keep locking and unlocking without doing anything else. So need to pass control to other function.
			//	pthread_cond_wait(&prod_c, &mutexBuf);
	
	
	pthread_mutex_lock(&mutexBuf);
	//Write operation - request for something from the server 
	while(buf.status==0){
		
		    //pthread_cond_wait(&prod_c, &mutexBuf);
			printf ("Press any key to start.......  ");
			buf.value =  getc(stdin)  ;  //non blocking 
			printf("                                                     Client requested %c\n.....",buf.value);
			buf.status = 1;   //buffer is full and no one else can write till emptied
		
	}
	
	      
			pthread_mutex_unlock(&mutexBuf);
			
			 //Signal server that client has filled the buffer and it can wake up 
	         pthread_cond_signal(&cons_c);
	
	

	//pthread_cond_wait(&prod_c, &mutexBuf);
	
	}	
	return NULL;
	
}


void *Server(void *args){
	
	
	
	while(1){
		
		pthread_mutex_lock(&mutexBuf);
		//wait for signal from Client 
	   pthread_cond_wait(&cons_c, &mutexBuf);
	
		
		
		if(buf.status==1){
		//read and take action
		printf("Received request, please wait.....\n");
		
		buf.value = 0;
		buf.status = 0;  //buffer is read and is now empty
		}
		
		sleep(2);
		
		pthread_mutex_unlock(&mutexBuf);
		//pthread_cond_signal(&prod_c);
	}
	
	
	
	
	
	//One sent signal to other, how does other send signal back ?
	
	
	
	

	
	
	return NULL;
}


int main(){
	
	
	pthread_t thread[2];
	int num1 = 1, num2 = 2;
	
	pthread_mutex_init(&mutexBuf,NULL);
	pthread_cond_init(&cons_c, NULL);
	//pthread_prod_init(&prod_c, NULL);
	
	
	pthread_create(&thread[0], NULL, Client, &num1);
	pthread_create(&thread[1], NULL, Server, &num2);
	
	
	
	
	for(int i=0;i<NUM_THREADS;i++)
		pthread_join(thread[i], NULL);
	
	pthread_mutex_destroy(&mutexBuf);
	pthread_cond_destroy(&cons_c);
	
	
	return 0;
	
}