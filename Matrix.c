#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include<time.h>
int v=0,l=0,k=0,z=0,s=0,qm=0,rc=0,rc1=0,m=0,ww=0,ww1=0,ff=0,ff1=0,ff2=0,ff3=1,af=0;
int qw=0,rrr,sizeM1,sizeM2,lenM1,lenM2,elements;
void* elements_func (void*arg1);
void* elements_func2 (void*arg2);
void read_insertMat();
//void print_matRow();
//void print_matElement();
	
int  m1[512][512] ,m2[512][512],m3[512][512] ,m4[512][512],elements_data[512][512];
void main(){
	int y;
	read_insertMat();
	pthread_t *thread1;
	pthread_t *thread2;
	thread1=(pthread_t*)malloc(elements*sizeof(pthread_t));
	thread2=(pthread_t*)malloc(elements*sizeof(pthread_t));
	int thread1_count =1;
	 y=1;
	while(y<=elements){
		for(;v<sizeM1;v++){
			for(l=0;l<lenM1;l++){
				elements_data[v][l]=m1[v][l];
					}
			v++;
			if(1)
			break;
			}
				s=l;
				if(v <= sizeM1){
						for(k=0;k<lenM2;k++){
							for(z=0;z<sizeM2;z++){
								elements_data[v-1][z+s]=m2[z][k];

									}
							s=s+l;
							}
}
		

	pthread_create(&thread1[thread1_count],NULL,elements_func,(void*)(elements_data));
	pthread_create(&thread2[thread1_count],NULL,elements_func2,(void*)(elements_data));
	thread1_count++;
	y++;
	
	//if(thread1_count>sizeM1)
	//break;
	 // or v++ for making threads for rows (sizeM1)  -- v=0 for elements threads

	}
	clock_t td1;
	td1=clock();
	int d;
	//printf("Matrix of first procedure (ROW METHOD) : \n");
	for(d=1;d<=sizeM1;d++){//sizeM1 for rows .. elements for elements

	pthread_join(thread1[d],NULL);

	}
	FILE* fp1 =fopen("output.txt" , "a");
	fprintf(fp1,"Matrix of first procedure (ROW METHOD) : \n");
	for(int p1=0;p1<sizeM1;p1++){
		for(int p2=0;p2<lenM2;p2++)
			fprintf(fp1," %d  ",m3[p1][p2]);
		fprintf(fp1,"\n");
		}
	
	td1=clock()-td1;
	double time_taken1=((double)td1/CLOCKS_PER_SEC);
	fprintf(fp1,"time for first procedure is %f seconds\n",time_taken1);
	fclose(fp1);



	clock_t td2;
	td2=clock();
	int d2;
	//printf("Matrix of second procedure (ELEMENT METHOD) : \n");
	for(d2=1;d2<=elements;d2++){//sizeM1 for rows .. elements for elements

	pthread_join(thread2[d2],NULL);

	}
	FILE* fp =fopen("output.txt" , "a");
	fprintf(fp,"Matrix of second procedure (ELEMENT METHOD) : \n");
	for(int p3=0;p3<sizeM1;p3++){
		for(int p4=0;p4<lenM2;p4++)
			fprintf(fp," %d  ",m4[p3][p4]);
		fprintf(fp,"\n");
		}
	td2=clock()-td2;
	double time_taken2=((double)td2/CLOCKS_PER_SEC);
	fprintf(fp,"time for second procedure is %f seconds\n",time_taken2);
	fclose(fp);



	


}

 void *elements_func ( void *arg1){
		
/*for(int mm=0;mm<sizeM2*lenM2+lenM1;mm++){
		printf("Dataaa = %d\n",elements_data[ww][mm]);
		}
		printf("****\n");
*/	int a1 ,b1;
	for(a1=0;a1<lenM2;a1++){
		for(b1=0;b1<sizeM2;b1++)
		//printf("element 1 = %d , elemnt 2 = %d \n",elements_data[ww][b1],elements_data[ww][b1+lenM1+ww1]);
		m3[ww][a1]+=elements_data[ww][b1]*elements_data[ww][b1+lenM1+ww1];
		ww1=ww1+sizeM2;
	}
	ww1=0;
	//printf("*******\n");
	//printf("w = %d \n",ww);
	//printf("M3 = %d \n ",m3[ww][3]);
	ww++;
}


void *elements_func2 ( void *arg2){
	//sleep(2);
		
/*for(int mm=0;mm<sizeM2*lenM2+lenM1;mm++){
		//printf("Dataaa = %d\n",elements_data[ff][mm]);
		}
	*/

	//printf("*******\n");
	for(int b1=0;b1<sizeM2;b1++){
		//printf("element 1 = %d , elemnt 2 = %d \n",elements_data[ff][b1],elements_data[ff][b1+lenM1+ff1]);
		m4[ff][af]+=elements_data[ff][b1]*elements_data[ff][b1+lenM1+ff1];	
		}
		ff1=ff1+sizeM2;
	//printf("ff = %d af= %d \n",ff,af);
	af++;
	//printf("M4 = %d \n ",m4[0][3]);
	if(ff2-sizeM1==0){
	ff1=0;
	ff++;
	ff2=-1;
	af=0;
	//af++;
	//if(af%lenM2==0)
	//af--;
	}
	ff2++;
	if(ff%sizeM1==0){
	ff=ff%sizeM1;
	}
	
	


	
}
void read_insertMat(){
FILE *f = fopen("input.txt","r");
	int i,j,x,y;
	char *numM1[256] ,*numM2[256];
	char *token1 ,*token2;
	char input1[50],input2[512],input3[50],input4[512];

	fgets(input1,512,f);
	numM1[0]=strtok(input1," ");
	numM1[1]=strtok(NULL," ");
	lenM1=atoi(numM1[1]);
	sizeM1=atoi(numM1[0]);
	printf("matrix one size = %d , %d\n",sizeM1,lenM1);
	while(i<sizeM1){
	fgets(input2,512,f);
	token1=strtok(input2," ");
	j=0;
	m1[i][j]=atoi(token1);
		for(j=1;j<lenM1;j++){
		token1=strtok(NULL," ");
		m1[i][j]=atoi(token1);
		}
	i++;
	}
	fgets(input3,512,f);
	numM2[0]=strtok(input3," ");
	numM2[1]=strtok(NULL," ");
	lenM2=atoi(numM2[1]);
	sizeM2=atoi(numM2[0]);
	printf("matrix two size = %d , %d \n",sizeM2,lenM2);
	while(x<sizeM2){
	fgets(input4,512,f);
	token2=strtok(input4," ");
	y=0;
	m2[x][y]=atoi(token2);
		for(y=1;y<lenM2;y++){
		token2=strtok(NULL," ");
		m2[x][y]=atoi(token2);
		}
	x++;
	}
	fclose(f);
	if(lenM1!=sizeM2){
	printf("\n\n\tError ! matrixes size is incorrect !\n\n");
	exit(0);
	}
	elements=sizeM1*lenM2;
	printf("number of elements = %d \n",elements);


}


	




