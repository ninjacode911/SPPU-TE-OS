//1
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int main()
{
	int fd1,fd2;
	char * fifo1="fifo1";
	char * fifo2="fifo2";

	mkfifo(fifo1, 0666);
	

	char arr[40];
	int i;
	for( i = 0; i < sizeof(arr); i +=2 ){
	scanf("%c%c",&arr[i],&arr[i+1]);
	if( arr[i] == '\n' && arr[i+1] == '\n' )
	    break;
	}
        arr[i]='$';
	        
	int buffer1[100], buffer2[100];
	//while (1)
	{
		//Pipe from file 1 to file 2
		fd1 = open(fifo1, O_WRONLY);

		write(fd1, arr, strlen(arr)+1);
		
		close(fd1);
		
		sleep(2);
		
		//Pipe from file 2 to file 1
		fd2 = open(fifo2, O_RDONLY);
		
		read(fd2, buffer1, 100);
 
		printf("User1: \n\nWords :%d\nLines:%d\nCharacters:%d\n", buffer1[0],buffer1[1],buffer1[2]);
		
		close(fd2);
	}
	
	return 0;
}	

//2
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd1,fd2;
	char * fifo1="fifo1";
	char * fifo2="fifo2";

	
	

	char buffer1[100], buffer2[100];
	
	//while (1)
	{
		sleep(1);
		//Pipe from file 1 to file 2
		int wc=0,lc=0,cc=0;
		fd1 = open(fifo1, O_RDONLY);
		
		read(fd1, buffer2, 100);
		
 		int i=0;
 		while(buffer2[i]!='$')
 		{
 			if(buffer2[i]==' ' || buffer2[i]=='\n')
 			{
 				wc++;
 			}
 			if(buffer2[i]=='\n')
 			{
 				lc++;
 			}
 			else
 			{
 				cc++;
 			}
 			i++;
 			
 		}
 		wc++;
 		lc++;
 		
 		//writing into the file
 		FILE* fptr1;
 		fptr1 = fopen("demo.txt", "w");
 		putw(wc, fptr1);
 		putw(lc, fptr1);
 		putw(cc, fptr1);
 		fclose(fptr1);
 						
		printf("User2: %s\n\n", buffer2);
		printf("Words :%d\nLines:%d\nCharacters:%d\n",wc,lc,cc);
		
		close(fd1);
		
		
		//Pipe from file 2 to file 1
		mkfifo(fifo2, 0666);
		
		//reading from the file
		int arr1[3];
		FILE* fptr2;
 		int ch,num;
 		fptr2 = fopen("demo.txt", "r");
 		fclose(fptr2);
 		arr1[0]=wc;
 		arr1[1]=lc;
 		arr1[2]=cc;
 		
		fd2 = open(fifo2, O_WRONLY);

		write(fd2, arr1,4);
		
		close(fd2);
		
		
	}
	
	return 0;
}		
