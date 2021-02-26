#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
	//function declarations
		void print_data(char** array, int size);
		char** insertion_sort_ptr(char** array1, int size, int given_function(const char* strleft, const char* strright));
		int comp_length(const char *s1, const char* s2);
		int comp_greater(const char *s1, const char* s2);
		int comp_mixt(const char *s1, const char* s2);
		void free_table(char** array2, int size);
	
int main() {

	int num_fileName;			// Getting number of letters in the file then the name
	printf("Enter the number of letters in the file name (including the .txt at the end): ");
		scanf("%d", &num_fileName);		
		if( num_fileName>100){ 
			printf("Error! File name cannot be greater than 100\n");
			exit(0);
		}
	printf("Enter the file name: ");
	char *file_name = malloc(num_fileName*sizeof(char));
	scanf("%s", file_name);

	FILE *in_file;	
	FILE *out_file;
	char *line = NULL; 

	size_t len = 0;  //unsigned integer type of at least 16 bit;
	ssize_t line_length;
	
	in_file = fopen(file_name, "r");
		if (in_file== NULL){
		printf("Error! Could not open file: %s", file_name);
		exit(-1);
}		
							//Reading how many lines are in the file:
		int line_count=1;		//stars at 1 to account for the last name on the list 
		while(!feof(in_file)) {			
			char temp;
			temp = fgetc(in_file);
			if(temp == '\n') {
			line_count++;
			}		

}		
		
						//allocating for the **array of words
		char **words = malloc(line_count*sizeof(char *));  //2d array of all the names in the list
		fclose(in_file);

		int tempnum= 0;
		int tempo= 0;
		in_file = fopen(file_name, "r");		//opening file 2nd time
	
	while((line_length = getline(&line,&len, in_file)) !=-1) {

	
		words[tempnum] = (char *)malloc(line_length);	    //allocating memory for the word length (How many characters it is)
		
		strcpy(words[tempnum], line);	//putting the line from the file into **words	
					 		
		tempnum++;
		tempo+= line_length;
}

	printf("\nData is loaded\n");
	printf("%zu Bytes allocated for characters in the file name.\n%zu Bytes dynamically allocated for the array(%d for chars %zu for pointers).\n%zu Total Bytes.",num_fileName*sizeof(char), (line_count*sizeof(char *)+tempo),tempo, (line_count*sizeof(char *))/8,(num_fileName*sizeof(char)+(line_count*sizeof(char *)+tempo)));
	printf("\nPointer size: 8 Bytes\n\nOriginal data: \n");
	fclose(in_file);
	
	free(line);

	print_data(words, line_count);

	printf("\n - - - - - - - - - - compare by LENGTH only - - - - - - - - - - \n");
	words=insertion_sort_ptr(words, line_count, comp_length);
	print_data(words, line_count);

	printf("\n - - - - - - - - - - compare by strcmp - - - - - - - - - - \n");
	words=insertion_sort_ptr(words, line_count, strcmp);
	print_data(words, line_count);

	printf("\n - - - - - - - - - - compare by GREATER- - - - - - - - - - \n");
	words=insertion_sort_ptr(words, line_count, comp_greater);
	print_data(words, line_count);

	printf("\n - - - - - - - - - - compare by LENGTH and lexicografic - - - - - - - - - - \n");

	free_table(words, line_count);
	
return 0;
}

	void print_data(char** array, int size){
		int i=0;
		while(i<size){
			printf("%s\n", array[i]);
			i++;
		}
}

		//I don't know if my functions work, never got past this segmentation error, it did sort it in a strange way when I returned void instead of char**
	char** insertion_sort_ptr(char** array1, int size, int given_function(const char* strleft, const char* strright)){
			char* temp=NULL;
		for(int i= i; i< size; i++){
			temp=array1[i];	
			int k=i-1;
			while((k>=0) && (given_function(array1[k], temp))) {
				array1[k+1]= array1[k];
				k--;
			}
			array1[k+1]=temp;
			
		}
	return array1;
}
	

	int comp_length(const char *s1, const char* s2){
			if(strlen(s1)>strlen(s2)){
				return 1;
			}
			else return 0;
}

	int comp_greater(const char *s1, const char* s2){
		return -strcmp(s1,s2);
	}


	void free_table(char** array2, int size){
		for(int i=0; i< size; i++){
			free(array2[i]);
		}
}