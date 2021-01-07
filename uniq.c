#include "types.h"
#include "stat.h"
#include "user.h"

char buffer[5120000];
char* args;

int uniq(int fp, char* filename) {
	int b, n,i,q, lines=0,index=0,final =0,count1 =0,k,p,m=0, count =0;
	char *output[10000];
	char buffer_copy[10000];
	int repeat[10000];
	while((n = read(fp, buffer, sizeof(buffer))) >0) {
		for(b=0; b<n; b++) {
			if(buffer[b] == '\n') {
				lines++;
			}
		}
		for(i=0;buffer[i] != '\n';i++){
			count ++;
			buffer_copy[i] = buffer[i];
		}
//		printf(1, "%s \n", buffer_copy);
		buffer_copy[i] = '\0';
//		printf(1, "%s \n", buffer_copy);
		repeat[0]=1;
		output[0] = (char*) malloc((count+1)*sizeof(char*));
		for(i=0;i<count+1;i++) {
			output[index][i] = buffer_copy[i];
		}
		output[index] = '\0';
		k=i;
		while(final < lines-1) {
			final++;
			count1 = 0;
			for(i=k;buffer[i] != '\n';i++) {
				count1++;
				buffer_copy[m++] = buffer[i];
			}
//			printf(1, "buffer_copy: %s \n", buffer_copy);
			buffer_copy[m] = '\0';
			//printf(1, "Output: %s \n" , output[index]);
			k = k+count1+1;
			m=0;
			if(strcmp(output[index],buffer_copy) != 0) {
				index = index+1;
				output[index] = (char*) malloc((count1+1)*sizeof(char*));
				for(p=0;p<count1;p++) {
					output[index][p]=buffer_copy[p];
				}
				output[index][p] = '\0';
			//	printf(1, "buffer_copy : %s \n", buffer_copy);
			//	printf(1, "Output : %s \n", output[index]);
			//	printf(1,"here\n");
				repeat[index] = 1;
				//index = index+1;
			} else {
			//	printf(1,"here1\n");
				repeat[index] = repeat[index] + 1;
			}
			//printf(1, "Count : %d \n", repeat[index]);
		}
	}
	if(strcmp(args,"-c") == 0) {
//		printf(1,"Here\n");
		for(q=0;q<index+1;q++) {
			printf(1,"%d %s \n",repeat[q],output[q]);
		}
	}
	else if(strcmp(args,"-d") == 0){
//		printf(1,"Here 1\n");
		for(q=0;q<index+1;q++) {
			if(repeat[q] > 1) {
				printf(1, "%s \n", output[q]);
			}
		}
	}
	else {
		//printf(1, "Index: %d \n", index);
		for(q=1;q<index+1;q++) {
			printf(1,"%s \n", output[q]);
		}
	}
	free(output);
	return 0;
}

int main (int argc, char* argv[]) {
	int fp, i;
	if(argc <=1) {
		uniq(0,"");
		exit();
	}
	else if(argc == 2){
		for( i = 1; i< argc; i++) {
			fp = open(argv[i],0);
			if(fp<0) {
				printf(1, "File cannot be opened\n");
			}
			else {
//				printf(1, "File opened successfully\n");
				args = argv[1];
//				printf(1, "%s %s \n", argv[1], argv[0]);
				uniq(fp,argv[i]);
			}
			close(fp);
		} 
	} else {
		for(i=2; i<argc; i++) {
			fp = open(argv[i],0);
			if(fp<0) {
				printf(1, "File cannot be opened\n");
			} else {
				args=argv[1];
//				printf(1,"File opened successfully\n");
//				printf(1, "%s \n", args);
				uniq(fp,argv[i]);
			}
			close(fp);
		}
	}
	exit();
}
