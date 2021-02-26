//Benjamin Stanelle 1001534907
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[100];
}str;

typedef struct{
    int vertex_Num;
    int ** matrix_array;
}graph;

graph *new_Matrix(int vertices);
int indexof(char *name, str *arr, int size);
void delete_Matrix(graph *temp);
void DFS(graph *g, str *names,int *edge);
void DFS_visit(graph *g, int curr_index,str *names,str* color, int *pred, int *edge, int groupNum);
int max(int *arr,int size);
void print_matrix(graph *temp, int size);
void MST_Prim_Matrix(graph *g, graph* weights,int sVertex ,int N);
void printMST(int pred[], int distance[], int N);
int minDistance(int distance[], str *color, int N);

int main()
{
    int N,i,j, Weighted, sVertex,m, n; //where N is number of vertices

    printf("Weighted: ");
    scanf("%d",&Weighted);
    printf("%d", Weighted);
    printf("\nStart Vertex: ");
    scanf("%d",&sVertex); 
    printf("%d\n", sVertex);
    printf("Number of vertices (N): ");
    scanf("%d",&N);
    printf("%d\n",N);

    str names[N];     		//array of structures
    graph *g = new_Matrix(N);		//setting a pointer to a dynamically allocated a 2d array with N vertices
    graph *weights=new_Matrix(N);
    weights->vertex_Num=N;
    g->vertex_Num=N;
    for(i = 0; i < N; i++)  //gets names from file or command window
    {
        printf("Enter name %d: ",i+1);
        scanf("%s",names[i].name);   //stores names in structure array names[0]= first  name, names[1]second name;

    }

    while(1)		//building the adjacency matrix
    {
        str edge1;
        str edge2;
	int weight;
        printf("Enter Edge1 Edge2: ");
        scanf("%s%s",edge1.name,edge2.name);
	if(Weighted==1){
	printf("\nEnter edge weight: ");
	scanf("%d", &weight);
	}
	printf("\n");
		//if(strcmp(strcat(edge1.name,edge2.name), "-1-1")==0){  can't do this because of null terminator, or new line??
       if(strcmp(edge1.name,"-1") == 0 || strcmp(edge2.name,"-1") == 0){
            break;	
	}

        m  = indexof(edge1.name,names,N);
        n = indexof(edge2.name,names,N);		 //returns -1 or index of edgename in vertices array
        if(m != -1 || n != -1)				//as long as m and n are indexs in vertices array, then make adjacency matrix
        {
            g->matrix_array[m][n] = 1;		                 //creates adjacency  matrix
            g->matrix_array[n][m] = 1;				 //puts 1 at indexes specified by m and n, into the all 0 g matrix
            weights->matrix_array[n][m]= weight;
	    weights->matrix_array[m][n]= weight;
	}

  }//end while loop

    for(i = 0; i < N; i++)  
    {
        printf("%d - %s\n",i,names[i].name);
    }
    printf("\nEdges 2D matrix: \n");

    print_matrix(g, N);
    printf("\n\nWeights 2D matrix:\n");
    print_matrix(weights,N);
    int edge[g->vertex_Num];
    for(i = 0; i < g->vertex_Num; i++)		//0 list, size of vertice number
    {
        edge[i] = 0;
    }
    DFS(g,names,edge);
    int groups = max(edge,g->vertex_Num);
    printf("\nRunning DFS...\nFinished DFS\n");
    printf("\nNumber of groups: %d\n",groups);

    for(i = 1; i <= groups; i++)		//printing group number and names
    {
        printf("\nGroup: %d\n", i);
        for(j = 0; j < g->vertex_Num; j++)
        {
            if(i == edge[j])
            {
                printf("%s\n",names[j].name);
            }
        }

    }		//end printing

    if ( Weighted == 1){
		MST_Prim_Matrix(g, weights,sVertex,g->vertex_Num);
	}

    else {
		printf("This is not a weighted graph. We will not run MST_Prim for it.\n");
	}

    delete_Matrix(g);
    delete_Matrix(weights);
    return 0;
}

void DFS(graph *g, str *names, int *edge)
{
   str color[g->vertex_Num];		//structure array of strings to see if visited
   int pred[g->vertex_Num];
   int i;
   for(i = 0; i < g->vertex_Num; i++)	//color all vertices white and make pred -1
   {
       strcpy(color[i].name,"WHITE");	
       pred[i] = -1;

   }

    int group_Num = 0;				
       for(i = 0; i < g->vertex_Num; i++)
        {
            if(strcmp(color[i].name,"WHITE") == 0)			//if not visited
            {
                DFS_visit(g,i,names,color,pred,edge,group_Num+1);		//visit that vertex

                group_Num++;
            }

        }

}


void DFS_visit(graph *g, int curr_index,str *names,str *color, int *pred,int *edge, int groupNum)
{
    int i;
    strcpy(color[curr_index].name,"GRAY");		//make it grey or visited
    edge[curr_index] = groupNum;
    for(i = 0; i < g->vertex_Num; i++)
    {	
		//if its connected to another vertice and that vertice is not visited (grey or black)		
		//doesn't  matter if rows or columns because its a mirrored along diagonal, so the transpose for adjcency matrix is the same
		//also the edges are doublely connected
        if((g->matrix_array[curr_index][i] == 1)&& (strcmp(color[i].name,"WHITE") == 0))
        {
                pred[i] = curr_index;
                DFS_visit(g,i,names,color,pred,edge,groupNum);   //visit the vertice that it is connected to
        }
    }
    strcpy(color[curr_index].name,"BLACK");   //color it black
    return;
}


graph *new_Matrix(int vertices_Num)
{
    int i,j;
    graph *temp = malloc(sizeof(graph));  	//dynamically allocating a new graph structure 

    temp->vertex_Num = vertices_Num;
    temp->matrix_array = (int**)calloc(vertices_Num,sizeof(int*));	//allocating the matrix setting all spaces to 0

    for(i = 0; i < vertices_Num; i++)
    {
        temp->matrix_array[i] = calloc(vertices_Num,sizeof(int));   //dynamically allocating and initiallizing columns of each row with 0s
    }

    return temp;  //returning a 2d 0 matrix
}


int indexof(char *name, str *arr, int size)	 //compares vertices name to edges name and returns index 
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(strcmp(name,arr[i].name) == 0)		//compare edgename to each item in vertices struct array
            return i;									//returns index of edgename compared to vertices array of names

    }
    return -1;									//stopping condition 
}


void delete_Matrix(graph *temp)  //freeing the structure and its 2d array
{
    int i;
    for(i = 0; i < temp->vertex_Num; i++)
    {
        free(temp->matrix_array[i]);
    }
    free(temp->matrix_array);
    free(temp);
}

int max(int *arr,int size)
{
    int max = arr[0];
    int i;
    for(i = 1; i < size; i++)
    {
        if(max < arr[i])
            max = arr[i];
    }
    return max;
}


void print_matrix(graph *temp, int size){		//prints a 2d matrix 
	int j, i;
	printf("   | ");
	for(i=0; i<size; i++){
		printf("%-3d ", i);
	}
	printf("\n\n");
	for(i = 0; i < size; i++){
		printf("%-3d| ",i);
     	   for(j = 0; j < size; j++){
            printf("%-3d ",temp->matrix_array[i][j]);
           }
       printf("\n");
       }
	return;
}

void MST_Prim_Matrix(graph *g, graph* weights,int sVertex ,int N){
	int i, j,v, p,minVertex, minVal, totalmst=0;
	int distance[N];
	int pred[N];
	str color[N];
	for(p=0;p<N;p++){		//initialize all vertices to unseen color(white), parents to -1, distance to infinity(999)
		distance[p]=999; 
		strcpy(color[p].name,"WHITE");	
		
	} //end p loop

	distance[sVertex]=0;					
	pred[sVertex]=-1;

	for(i=1;i<N;i++){		
		minVal= minDistance(distance, color, N);
		strcpy(color[minVal].name,"GREY");
		for(j=0;j<N;j++){			
			if((g->matrix_array[minVal][j]==1) && (strcmp(color[j].name, "WHITE")==0) && (weights->matrix_array[minVal][j]<distance[j])){    //if that vertice hasn't been looked colored and the distance in smaller than minval
				pred[j]=minVal;
				distance[j]= weights->matrix_array[minVal][j];
				
			}
		} //end j loop
		
		int temp1=0;
		if(strcmp(color[minVal].name,"GREY")==0 && weights->matrix_array[minVal][i]<distance[i]){
		}
	} //end i for loop
	

	printMST(pred, distance, N); 
	return;
}

int minDistance(int distance[], str *color, int N){
	int min= 999;
	int min_index, i;
	for(i=0; i<N; i++){
		if(strcmp(color[i].name, "WHITE")==0 && distance[i]<min){
			min=distance[i];
			min_index=i;
		}
	}
	return min_index;
}

void printMST(int pred[], int distance[], int N){
	 int t, totalmst=0;
	printf("\nRunning MST_prim...\nMST tree edges:\n");
   	for ( t = 0; t < N; t++){
		if(distance[t]!=999){
      		printf("(%3d,%3d,%3d)\n", pred[t], t, distance[t]); 
   		}
		totalmst+=distance[t];
 	}
	printf("total MST cost: %d\n\nFinished MST_prim.\n",totalmst); 
	return;
}

