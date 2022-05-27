#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
/*
 * 
 */
int B[100][100];
int A[100][100];
pthread_mutex_t lock;
pthread_t tid[100];
pthread_barrier_t barrier;

static int x=0;
static int p=0;


void* populate(void *arg);
int check_neighbours(int i, int j);
void printArray();

int main(int argc, char** argv) {
	FILE* file=NULL;

	file = fopen( argv[1], "r" );
    
    int i=0;
    int y=0;
    
    for (i=0;i<100;i++){
    	for(y=0;y<100;y++){
    		
    		fscanf(file,"%d", &A[i][y]);
    	
    }
}
fclose(file);
while(1){
for (i=0;i<100;i++){
    	for(y=0;y<100;y++){
    		B[i][y]=A[i][y];

    	}
    }
    


 
if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
int k=0,j,err,s;
int *c;
s = pthread_barrier_init(&barrier, NULL, 100);

for(i=0;i<100;i=i+10){
	for(j=0;j<100;j=j+10){
		c=malloc(5* sizeof(*c));
		c[0]=i;
		c[1]=i+9;
		c[2]=j;
		c[3]=j+9;
		c[4]=k;
		err = pthread_create(&(tid[k++]),NULL, &populate, (void *)c);
		if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        //printf("k= %d",k);
		
	}
}


for(i=0;i<100;i++){
	pthread_join(tid[i],NULL);
}

for(i=0;i<100;i++){
	for(j=0;j<100;j++){
		 A[i][j]=B[i][j];
		 if(B[i][j]==0) printf(" ");
		 else printf("*");
		 
		}
	if(j==100) printf("|\n");
		}
	
	


printf("\n");
free(c);
pthread_mutex_destroy(&lock);

pthread_barrier_destroy(&barrier);
}

    return (EXIT_SUCCESS);
}


int check_neighbours(int i, int j){
	int y=0;
	int k=0;
	int count=0;

	 if( i> 0 && j> 0 && A[i-1][j-1]==1) count++;
        if( i> 0         && A[i-1][j  ]==1) count++;
        if( i> 0 && j<99 && A[i-1][j+1]==1) count++;
        if(         j> 0 && A[i  ][j-1]==1) count++;
        if(         j<99 && A[i  ][j+1]==1) count++;
        if( i<99 && j> 0 && A[i+1][j-1]==1) count++;
        if( i<99         && A[i+1][j  ]==1) count++;
        if( i<99 && j<99 && A[i+1][j+1]==1) count++;
        return count;

}
void* populate(void *arg){
	pthread_mutex_lock(&lock);
	int s,k;
	int *val=(int *)arg;
	int i_low=val[0];
	int i_high=val[1];
	int j_low=val[2];
	int j_high=val[3];
	int g=val[4];
	int i=0,j=0,sum=0;
	
	for(i=i_low;i<=i_high;i++){
		for(j=j_low;j<=j_high;j++){
			sum=check_neighbours(i,j);
			if((sum<=1) && (A[i][j]==1)) {
				B[i][j]=0;
				}
			else if(((sum==2) || (sum==3)) && (A[i][j]==1)){
				 B[i][j]=1;
				}
			else if((sum>3) && (A[i][j]==1)){
				 B[i][j]=0;
				}
			else if((sum==3) && (A[i][j]==0)){
				 B[i][j]=1;
				}

		}
	}
	
	
	pthread_mutex_unlock(&lock);

	
	
	
		//s = pthread_barrier_wait(&barrier);
/*
		if(s==PTHREAD_BARRIER_SERIAL_THREAD){
			for(i=0;i<100;i++){
				for(j=0;j<100;j++){
		
		 		if(B[i][j]==0) printf(" ");
		 		else printf("*");
		 usleep(100);
		}
	if(j==100) printf("|\n");
	
}

		}
		*/
		
	

	return NULL;
}

