//Benjamin Stanelle 1001534907
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
*/


int min(int value1, int value2, int value3){
	if(value1<=value2 && value1<=value3){
		return value1;
	}
	if(value2<=value1 && value2<=value3){
		return value2;
	}
	return value3;
}
void print_Table(char *second_string,char *first_string, int *arr, int m, int n){
	int i, j,d, w;
	int size_first=strlen(first_string);
	int size_second=strlen(second_string);
	printf("   |   |");
	for(i=0; i<size_first; i++){
		printf("  %c|", first_string[i]);
	}
	printf("\n--------");
	for(i=0; i<size_first; i++){
		printf("----");
	}
	printf("\n");
	for(i=0; i<m; i++){
		if(i==0){
			printf("   |");
		}
			for(j=0;j<n;j++){
				printf("%3d|", *((arr+i*n)+j));
			}
		printf("\n--------");
	for(w=0; w<size_first; w++){
		printf("----");
	}
		printf("\n");
		printf("  %c|", second_string[i]);
	}
	
	
}


int edit_distance(char * first_string, char * second_string, int print_table){
	int i, j;
	int edit_DistanceTotal=-1;
	int arr[strlen(first_string)+1][strlen(second_string)+1];
	for(i=0; i<strlen(first_string)+1;i++){
		for(j=0; j<strlen(second_string)+1;j++){
			if(i==0 && j==0){
				arr[i][j]=0;
				}
			else if(i==0){
				arr[i][j]=arr[i][j-1]+1;
			}
			else if(j==0){
				arr[i][j]=arr[i-1][j]+1;
			}
			else{
				if(first_string[i-1]==second_string[j-1]){
					arr[i][j]=arr[i-1][j-1];
				}
				else{
					arr[i][j]=1+min(arr[i][j-1],arr[i-1][j],arr[i-1][j-1]);
				}
			}
		}
	}
		if(print_table==1){
		print_Table(first_string, second_string,(int *)arr, strlen(first_string)+1, strlen(second_string)+1);
		}
return arr[strlen(first_string)][strlen(second_string)];
}
	  
	  
void spellcheck(char * dictname, char * testname){	//file names are passed in	
	int i, j, edit_distValue, max_length, min_edit;
	max_length=100;
	min_edit=max_length;
	char buff_test[max_length];
	char buff_dict[max_length];
	FILE *test_file= fopen(testname,"r");
	FILE *dict_file=fopen(dictname,"r");
	printf("\nLoading the test file: %s\n", testname);
	printf("Loading the dictionary file: %s\n", dictname);
		if(test_file!=NULL || dict_file!=NULL){
			char test_line[max_length];
			char dict_line[max_length];
			int test_wordsCount, dict_wordsCount;
			fscanf(test_file,"%d", &test_wordsCount); 
			fscanf(dict_file,"%d", &dict_wordsCount);
			fgets(buff_test, max_length, test_file);
			fgets(buff_dict, max_length, dict_file);
			int min_Arr[test_wordsCount];
			i=0;
			j=0;

			while(!feof(test_file)){
						fscanf(test_file, "%s", test_line);
						printf("\n\n - - - -  Current test word: %s",test_line);
						min_edit=100;
						rewind(dict_file);
							while(!feof(dict_file)){	
								fscanf(dict_file, "%s", dict_line);
								edit_distValue=(edit_distance(test_line, dict_line, -1));    //edit distance of two words
								if(edit_distValue<min_edit){
									min_edit= edit_distValue;
								}
								
						}
						min_Arr[i]=min_edit;
						printf("\n Minimum distance: %d",min_edit);
						
						rewind(dict_file);
						printf("\nThe words that give the minimum distance: ");
						while(!feof(dict_file)){
							fscanf(dict_file, "%s", dict_line);
							edit_distValue=(edit_distance(test_line, dict_line, -1));
							if(edit_distValue==min_Arr[i]){
								printf("\n%s",dict_line);
							}
						}
						
						i++;
			}
		}
		else{
			printf("File was not opened.");
		}
		printf("\n");
		fclose(test_file);
		fclose(dict_file);
	
}

