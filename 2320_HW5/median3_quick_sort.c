#include <stdio.h>
#include <stdlib.h>
	void print_partition(int A[], int size, int first_element, int last_element){				//prints whats changing in the array as recursive steps are taken
		int i;		
		for(i=0; i<size; i++){
			if(i<=last_element && i>=first_element){
				printf("%4d,", A[i]);                    //partition four spaces apart for each element
			}	
			else {
			printf("    ,"); 			//else print 4 empty spaces
			}
		}
	}

	void swap_arrayInts(int A[], int val1, int val2){           //given array and 2 indexes, swaps the elements in array at those indexes
		int temp= A[val1];
		A[val1]= A[val2];
		A[val2]=temp;
}
	void print_arr(int array[], int size){
		int i;
		for(i =0; i< size; i++){
			printf("%d, ", array[i]);
		}
}
	int Partition(int A[],int start, int end, int size){     //sorts elements using a pivot(which is the median of left right and middle index)
			int  j;
			int mid_Idx= (start+end)/((float)2);   //middle index, rounded down
			int median;		//finding the median value of the left, mid_Idx, and right indexes
			if((A[start]>= A[mid_Idx] && A[start]<= A[end]) || (A[start]<= A[mid_Idx] && A[start]>= A[end])){
				median= start;
			}
			else if((A[mid_Idx]>= A[start] && A[mid_Idx]<= A[end]) || (A[mid_Idx]>= A[end] && A[mid_Idx]<= A[start])){
				median = mid_Idx;
			}
			else if((A[end]>= A[start] && A[end]<= A[mid_Idx]) || (A[end]<= A[start] && A[end]>= A[mid_Idx])){
				median=end;
			}
			printf("\nStart of Partition(A, N, %d, %d)\n",start, end);
			print_partition(A, size, start, end);
			printf("A[%d]=%d, A[%d] = %d, A[%d] = %d\n", start, A[start], median, A[median], end, A[end]);
		
			swap_arrayInts(A, median, end);  //swapping the selected median value so it is the last element in the array (AKA pivot)

			int pivot= A[end];  
			int t= start;
			print_partition(A, size, start, end);
			printf("<- updated pivot: %d", pivot);
			for(j=start; j<=end-1; j++){
				if(A[j] <= pivot){				//compare values with pivot
				swap_arrayInts(A, j, t); 		 //pass in array and 2 indexs you want to swap elements of
				t++;
				}
			}
		swap_arrayInts(A,t, end);		//swapping back the last element so array with be in final order
		printf("\n");
		print_partition(A,size,start,end);
		printf(" <- Partitioned array aorund %d, at the final index %d\n", pivot, mid_Idx);
		printf(" end of partiton (A, N, %d, %d)", start, end);
	return t;
}
		
	void median3_quickSort(int Arr[], int start, int end, int size){		
		if(start >=end) return;
		int pIndex = Partition(Arr, start, end, size);
		median3_quickSort(Arr, start, pIndex-1, size);
		median3_quickSort(Arr, pIndex+1,end, size);
}

int main () {
	FILE *fp;
	int i;
	int n=1;					//set n to random number above 0 to enter the while loop,(n will change)
	int *array;					//instancing a pointer(to what will become dynamically allocated array)
	
	fp= fopen("data1.txt","r");		//opening only file we have
	while(n > 0 && !feof(fp)){			//while the 1st and 3rd line of the file have n(size of array in file)
										//larger than 0, and file not at end of file
	fscanf(fp, "%d", &n);				//get array size you're about to read in from file
	if(n<=0){
		break;
	}
	array = (int*)malloc(n*sizeof(int)); 		 //dynamically allocating new array
		for(i=0;i<n; i++){						//n is size of array specified in data1.txt
			fscanf(fp, "%d", &array[i]);		//array elements from file
		}
		printf("\nLoaded in new array:\nIndexes:\n");

		int k;
		for(k=0;k<n;k++){
			printf("%d ", k);
		}
		printf("\nOriginal array: \n");
		print_arr(array, n);
		
		median3_quickSort(array, 0, n-1,n);		//passing array, left index, right index, and size to quicksort
		

		printf("\nSorted array: \n");
		print_arr(array, n);
		printf("\n\n");

		free(array);
	}

	fclose(fp);	
	return 0;
}
