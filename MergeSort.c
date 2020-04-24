#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include<time.h>
void merge(int x, int y);
void read_insertNum();
void print_sortedArr();
void * mergesort(void *m);
int size;
int m[512];
typedef struct element {
    int x;
    int y;
} element;
 element m2;
void main()
{
	read_insertNum();
	pthread_t thread;
        m2.x = 0;
        m2.y = size-1;
       	// to create two halves
       int x=pthread_create(&thread, NULL, mergesort, &m2);
	// if return = zero so create is failed
	if(x!=0){
	printf("Error merge thread");
	exit(0);
	}
    
	// to join two halves
        pthread_join(thread, NULL);
	// print size
	printf (" \nsize = %d\n ",size);
	// print sorted array
	print_sortedArr();
       //printf (" \nsize = %d\n ",size);

         pthread_exit(NULL);

}

void merge(int x, int y)
{
      	int newM[y-x+1], countM = 0;

        int m1 = x;

	int middle = (y+x)/2;

        int m2 = middle+1;


        while(m1 <= middle && m2 <= y) {
                if (m[m1] > m[m2]){
                        newM[countM++] = m[m2++];
				}
                else {                   
                        newM[countM++] = m[m1++];
		}
        }

        while(m2 <= y) {
                newM[countM++] = m[m2++];
        }
	
	while(m1 <= middle) {
                newM[countM++] = m[m1++];
        }
	
        for (m1 = 0; m1 < (y-x+1) ; m1++){
                m[x+m1] = newM[m1];
		}

}

void read_insertNum(){
	FILE *f = fopen("input.txt","r");
	int i,j,x,y;
	char *numM1[256];
	char *token1 ;
	char input1[50],input2[512];

	fgets(input1,512,f);
	numM1[0]=strtok(input1," ");
	size=atoi(numM1[0]);
	//printf("size = %d\n",size);
	fgets(input2,512,f);
	token1=strtok(input2," ");
	j=0;
	m[j]=atoi(token1);
		for(j=1;j<size;j++){
		token1=strtok(NULL," ");
		m[j]=atoi(token1);
		//printf("m1 = %d\n",m1[j]);
		}
	
	
	fclose(f);
	

}
void print_sortedArr(){
FILE* fp =fopen("output.txt" , "a");
	fprintf(fp,"Sorted Array :\n");
       for (int i = 0; i < size; i++)
                      fprintf (fp,"%d ", m[i]);
	fprintf(fp,"\n\n");

	fclose(fp);


}



void * mergesort(void *m)
{
	element r, l;
        element *pm = (element *)m;
        pthread_t thread1, thread2;
	int middle = (pm->x+pm->y)/2;
	//left
        l.x = pm->x;
        l.y = middle;
	//right
        r.x = middle+1;
        r.y = pm->y;

        if (pm->x >= pm->y) return 0;
	//create thread for first side (left)
        int x1= pthread_create(&thread1, NULL, mergesort, &l);
	// if return = zero so create is failed
	if(x1!=0){
	printf("Error in left thread");
	exit(0);
	}
    
	// create thread for second side (right)
        int x2= pthread_create(&thread2, NULL, mergesort, &r);
	// if return = zero so create is failed
	if(x2!=0){
	printf("Error in right thread");
	exit(0);
	}
       	// join left
        pthread_join(thread1, NULL);
	//join right
        pthread_join(thread2, NULL);

        merge(pm->x, pm->y);


        pthread_exit(NULL);
}

