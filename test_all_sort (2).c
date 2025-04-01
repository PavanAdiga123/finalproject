#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ROW 315
#define COL 9
#define SORTNUMBER 300
#define THRESHOLD 5
#define IS_SORTED 0

void quick(float arr[][COL], int low, int high);
int partition(float arr[][COL], int low, int high);
void copy_array_buf(float first[][COL], float second[][COL], int row_start, int row_end);
float get_difference(float first[][COL], int second);
float get_difference_new(float first[][COL], float new_record[1][COL], int i);
int binary_search(float dataset[][COL], float new_record[1][COL], int left, int right);
int linear_search(float dataset[][COL], float new_record[1][COL], int n);
int is_data_sorted(float dataset[][COL], int n);

void copy_array_buf(float first[][COL], float second[][COL], int row_start, int row_end) {
    for (int i = 0; i < COL; i++) {
        first[row_start][i] = second[row_end][i];
    }
}

int is_data_sorted(float dataset[][COL], int n) {
    for(int i = 0; i < n - 1; i++) {
        if(get_difference(dataset, i) > 0) return 0;
    }
    return 1;
}

float get_difference(float first[][COL], int j) {
    float sum = 0;
    for(int i = 0; i < COL - 1; i++)
        sum += first[j][i] - first[j+1][i];
    return sum;
} 

float get_difference_new(float first[][COL], float new_record[1][COL], int k) {
    float sum = 0;
    for(int i = 0; i < COL - 1; i++)
        sum += first[k][i] - new_record[0][i];
    return sum;
}

int binary_search(float dataset[][COL], float new_record[1][COL], int left, int right) {
    if (left >= right) return right;
    int mid = left + (right - left) / 2;
    if(get_difference_new(dataset, new_record, mid) > 0)
        return binary_search(dataset, new_record, left, mid);
    else
        return binary_search(dataset, new_record, mid + 1, right);
}

int linear_search(float dataset[][COL], float new_record[1][COL], int n) {
    int closest = 0;
    float min_diff = get_difference_new(dataset, new_record, 0);
    for(int i = 1; i < n; i++) {
        float diff = get_difference_new(dataset, new_record, i);
        if(diff < min_diff) {
            min_diff = diff;
            closest = i;
        }
    }
    return closest;
}

int partition(float arr[][COL], int start, int end) {
    float pivot[COL];
    memcpy(pivot, arr[start], COL * sizeof(float));
    int i = start, j = end;
    
    while (i < j) {
        while (i < end && get_difference_new(arr, &pivot, i) < 0) i++;
        while (j > start && get_difference_new(arr, &pivot, j) >= 0) j--;
        if (i < j) {
            float temp[COL];
            memcpy(temp, arr[i], COL * sizeof(float));
            memcpy(arr[i], arr[j], COL * sizeof(float));
            memcpy(arr[j], temp, COL * sizeof(float));
        }
    }
    memcpy(arr[start], arr[j], COL * sizeof(float));
    memcpy(arr[j], pivot, COL * sizeof(float));
    return j;
}

void quick(float arr[][COL], int start, int end) {
    if (start < end) {
        int p = partition(arr, start, end);
        quick(arr, start, p - 1);
        quick(arr, p + 1, end);
    }
}

int main() {
    float dataset[ROW][COL];
    float new_record[1][COL];
    FILE *stream = fopen("updated_rainfall_flood.csv", "r");
    
    if (!stream) {
        printf("Error: File not found!\n");
        return 1;
    }
    
    int row = 0, i = 0;
    char comma;
    while (fgetc(stream) != '\n'); 
    while (row < ROW && fscanf(stream, "%f", &dataset[row][i]) == 1) {
        i++;
        if(i < COL)
            fscanf(stream, "%c", &comma);
        else {
            row++;
            i = 0;
        }
    }
    fclose(stream);
    
    printf("Rows read: %d\n", row);
    quick(dataset, 0, SORTNUMBER - 1);
    
    int search_frequency = 0, error_count = 0;
    int is_sorted = IS_SORTED;
    
    for(int record_index = 300; record_index < 315; record_index++) {
        memcpy(new_record[0], dataset[record_index], COL * sizeof(float));
        printf("Record number %d\n", record_index);
        
        int num = (is_sorted) ? binary_search(dataset, new_record, 0, SORTNUMBER) 
                              : linear_search(dataset, new_record, SORTNUMBER);
        
        search_frequency++;
        if(search_frequency > THRESHOLD) {
            printf("Threshold exceeded, sorting data.\n");
            quick(dataset, 0, SORTNUMBER - 1);
            is_sorted = 1;
            search_frequency = 0;
        }
        
        int closest = (num > 0 && get_difference_new(dataset, new_record, num - 1) < get_difference_new(dataset, new_record, num)) 
                      ? num - 1 
                      : num;
        
        printf("Closest match: %d\n", closest);
        if((int)dataset[record_index][COL-1] != (int)dataset[closest][COL-1])
            error_count++;
    }
    printf("\nError count = %d\n", error_count);
    return 0;
}
