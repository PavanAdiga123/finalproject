#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#include <assert.h>
#include<math.h>
#include <time.h>

#define ROW 315
#define COL 9
#define SORTNUMBER 300
 void heapSort(float arr[][COL], int N);
 void quick(float arr[][COL],int low, int high);
 int partition(float arr[][COL], int low, int high);
 void heapify(float arr[][COL], int N, int i);
 void merge_sort(float arr[][COL], int l, int r);
 void merge(float arr[][COL], int l, int m, int r);
void sort_selection(int col_size, float large_pix[][COL],int);
void sort_bubble(int col_size, float large_pix[][COL],int);
void insertionsort(float large_pix[][COL], int n);
void copy_array(float first[], float second[][COL], int);
void copy_array_buf(float first[][COL], float second[][COL], int, int);
void copy_array_test(float first[][COL], float second[], int j);

float get_difference(float first[][COL], int second);
float get_difference_new(float first[][COL], float new_record[1][COL], int i);
int binary_search(float floatdataset[][COL],float new_record[1][COL], int i, int j);
 

int main()
{

    float dataset[ROW][COL];
    float new_record[1][COL];
    FILE* stream = fopen("updated_rainfall_flood.csv", "r");
    int record_index;

    char comma;
    float var[COL] ;
    int skip = 1,error_count = 0;
    int row = 0, closest;
    int i=0,j;
    srand(100);
    while(fgetc(stream) != '\n');
    while(1)
    {


        while (fscanf(stream, "%f",&dataset[row][i++]))

        {

        
            if(i<=COL)
                fscanf(stream,"%c",&comma);

      //      printf("%.2f %c \n", dataset[row][i-1], comma);
           if(i == COL)
            {
                 //  printf("Enter next line \n");
                   row++;
                   i = 0;
                   if(row == ROW) break;
            }
        }

        if(stream == NULL || row == ROW) break;
    }
   printf("\n ROws read %d", row);
   quick(dataset,0,SORTNUMBER);
   //heapSort(dataset,SORTNUMBER);
   //merge_sort(dataset,0,SORTNUMBER);
   //sort_selection(COL,dataset,SORTNUMBER);
    //sort_bubble(COL,dataset,SORTNUMBER);
    //insertionsort( dataset,SORTNUMBER);
    for(i=0; i< SORTNUMBER-1; i++){
       assert(get_difference(dataset,i) <= 0);
        for (j=0;j<COL;j++)
        printf(" %f ", dataset[i][j]);
        printf(" \n ");
        }

     
    printf("assert passed");
    for(record_index= 300; record_index < 315; record_index++)
    {
         for (j=0;j<COL;j++)
                new_record[0][j]= dataset[record_index][j];
        
       
        printf("record number %d \n", ((record_index)));
        
        int num;

        printf("Result = %d\n",num = binary_search(dataset,new_record,0,SORTNUMBER));
       
        if (get_difference_new(dataset, new_record,num - 1) < get_difference_new(dataset, new_record,num ))
            closest = num -1;
         else  
            closest = num;
             printf("%d ", closest);
     
       if( (int)dataset[record_index][COL-1] != (int)dataset[closest][COL-1]) error_count++;
        
 }
  printf("\nRecord count = %d", error_count);
 
}

void sort_bubble(int col_size, float large_pix[][COL], int subset)
{

    int i, j;

    float temp[COL]={0};
    

    for(i=0; i< subset; i++)

        for(j=0; j< subset - i -1; j++)
        {
         
            if(get_difference(large_pix, j) >= 0) 
            {
                copy_array(temp, large_pix,j);

                copy_array_buf(large_pix,large_pix,j, j+1);

                copy_array_test(large_pix, temp, j+1);
             
            }
            
    }
         
}

float get_difference(float first[][COL], int j)
{
    int i; 
    float sum = 0;

    for(i=0; i < COL -1; i++)
    {
        sum += first[j][i] - first[j+1][i];
    }
    //printf("%d \n",sum);
    return sum;
} 
 float get_difference_new(float first[][COL],  float new_record[][COL],int k)
{
    int i; 
    float sum = 0;

    for(i=0; i < COL -1; i++)
    {
        sum += first[k][i] -  new_record[0][i];
    };
    //printf("%d \n",sum);
    return sum;
}

 


void copy_array(float first[], float second[][COL], int j)
{
    int i;

    for(i=0; i < COL ; i++)
    {
        first[i] = second[j][i];
    }
}

void copy_array_buf(float first[][COL], float second[][COL], int j, int k)
{
    int i;

    for(i=0; i < COL ; i++)
    {
        first[j][i] = second[k][i];
    }
}

void copy_array_test(float first[][COL], float second[], int j)
{
    int i;

    for(i=0; i < COL ; i++)
    {
        first[j][i] = second[i];
    }
}
int binary_search(float large_pix[][COL],float new_record[1][COL],int i,int n){
    int j;
     if ((n-i) <= 1) return n;
     j= (i+n)/2;
    // printf ("%d ", n-i);
    //printf("diff %f ",get_difference_new(large_pix, new_record,j));


    if(get_difference_new(large_pix, new_record,j) > 0)
        binary_search(large_pix, new_record,i,j);
    else{    
        binary_search(large_pix, new_record,j,n );
}
}



 
void insertionsort(float arr[][COL], int n)
{
    int i, j;
    float key[1][COL];
    for (i = 1; i < n; i++) 
    {
       // key = arr[i];
        copy_array_buf(key,arr, 0,i);

        j = i - 1;

        /* Move elements of arr[0..i-1], 
        that are greater than key, 
        to one position ahead of 
        their current position */
       // while (j >= 0 && arr[j] > key) 
         while (j >= 0 && get_difference_new(arr, key,j) >=0) 
        {
           // arr[j + 1] = arr[j];
            copy_array_buf(arr,arr, j+1,j);

            j = j - 1;
        }
        //arr[j + 1] = key;
        copy_array_buf(arr,key, j+1,0);

    }
}
void sort_selection(int col_size, float large_pix[][COL], int n)
{

     int i, j, min_idx;
     float temp[1][COL];
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++){
             copy_array_buf(temp, large_pix, 0,min_idx);

          if(  get_difference_new(large_pix,temp,j) <= 0)
          //if (arr[j] < arr[min_idx])
            min_idx = j;
    }

        // Swap the found minimum element with the first element
           if(min_idx != i){
            //swap(&arr[min_idx], &arr[i]);
            copy_array_buf(temp, large_pix, 0,i);

            copy_array_buf(large_pix,large_pix, i,min_idx);

            copy_array_buf(large_pix, temp, min_idx,0);
        }
    }
}
void merge(float arr[][COL], int l, int m, int r) 
{
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 

    // Create temp arrays 
    float L[n1][COL],R[n2][COL],new_record[1][COL]; 

    // Copy data to temp arrays 
    // L[] and R[] 
    for (i = 0; i < n1; i++) 
         copy_array_buf(L, arr,i,l+i);
    for (j = 0; j < n2; j++) 
         copy_array_buf(R,arr,j,m+1+j);
    // Merge the temp arrays back 
    // into arr[l..r] 
    // Initial index of first subarray 
    i = 0; 

    // Initial index of second subarray 
    j = 0; 

    // Initial index of merged subarray 
    k = l; 
    while (i < n1 && j < n2) { 
        copy_array_buf(new_record,R,0,j);
        if (get_difference_new(L ,new_record,i)<=0) { 
            //arr[k] = L[i]; 
            //printf (" %d  %d \n ",j,i);
             copy_array_buf(arr, L,k,i);

            i++; 
        } 
        else { 
            //arr[k] = R[j]; 
            copy_array_buf(arr, R,k,j);
            //printf (" %d  %d \n ",j,i);
            j++; 
        } 
        k++;
    }


    // Copy the remaining elements 
    // of L[], if there are any 
    while (i < n1) { 
        //arr[k] = L[i]; 
        copy_array_buf(arr, L,k,i);
        i++; 
        k++; 
    } 

    // Copy the remaining elements of 
    // R[], if there are any 
    while (j < n2) { 
        //arr[k] = R[j]; 
        copy_array_buf(arr,R,k,j);
        j++; 
        k++; 
    } 
    //for(i=0;i<COL;i++)
    //printf("inside merge %f \n",arr[0][i]);
} 


// l is for left index and r is 
// right index of the sub-array 
// of arr to be sorted 
void merge_sort(float arr[][COL], int l, int r) 
{ 
    if (l < r) { 
        // Same as (l+r)/2, but avoids 
        // overflow for large l and r 
        int m = l + (r - l) / 2; 
        //printf(" l= %d mid = %d  r= %d \n",l,m,r);

        // Sort first and second halves 
        merge_sort(arr, l, m); 
        merge_sort(arr, m + 1, r); 

        merge(arr, l, m, r); 
    } 
} 
void heapify(float arr[][COL], int N, int i)
{
    // Find largest among root,
    // left child and right child

    // Initialize largest as root
    int largest = i;
    float temp[1][COL];
    float new_record[1][COL];
    // left = 2*i + 1
    int left = 2 * i + 1;

    // right = 2*i + 2
    int right = 2 * i + 2;

    // If left child is larger than root
    //if (left < N && arr[left] > arr[largest])
    copy_array_buf(new_record,arr,0,largest);
    if (left < N &&  get_difference_new(arr ,new_record,left)>=0)
        largest = left;

    // If right child is larger than largest
    // so far
    //if (right < N && arr[right] > arr[largest])
    copy_array_buf(new_record,arr,0,largest);
        if (right <N && get_difference_new(arr ,new_record,right)>=0)
        largest = right;

    // Swap and continue heapifying
    // if root is not largest
    // If largest is not root
    if (largest != i) {

        //swap(&arr[i], &arr[largest]);
        copy_array_buf(temp, arr, 0,i);

        copy_array_buf(arr,arr,i, largest);

        copy_array_buf(arr, temp, largest,0);
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

// Main function to do heap sort
void heapSort(float arr[][COL], int N)
{
     float temp[1][COL];
    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)

        heapify(arr, N, i);

    // Heap sort
    for (int i = N - 1; i >= 0; i--) {

        //swap(&arr[0], &arr[i]);
            copy_array_buf(temp, arr, 0,0);

            copy_array_buf(arr,arr,0, i);

            copy_array_buf(arr, temp, i,0);
        // Heapify root element
        // to get highest element at
        // root again
        heapify(arr, i, 0);
    }
}
int partition (float arr[][COL], int start, int end)  
{  

    float pivot[1][COL];
    float temp[1][COL];
    int j= end;
    int i = start;
    
    copy_array_buf(pivot,arr,0,i); // pivot element  
    do
    {
        do{
            i++;
          }while(get_difference_new(arr, pivot, i) < 0);

        while((i <= j) && (get_difference_new(arr, pivot, j) >= 0))
            j--;

        if(i < j){
            copy_array_buf(temp, arr,0, i);

            copy_array_buf(arr,arr,i, j);

            copy_array_buf(arr, temp, j,0);
        //printf("i = %d, j = %d \n",i, j);

         }
     }while(i <= j);

    
    
    copy_array_buf(temp, arr,0, j);

    copy_array_buf(arr,arr,j, start);

    copy_array_buf(arr, temp,start,0);

    return j;  
}  

/* function to implement quick sort */  
void quick(float arr[][COL], int start, int end) /* a[] = array to be sorted, start = Starting index, end = Ending index */  
{  
    if (start < end )  
    {  
        int p = partition(arr, start, end); //p is the partitioning index  
        //printf("Pivot =  %d \n",p);
        quick(arr, start, p - 1);  
        quick(arr, p + 1, end);  
    }  
}  