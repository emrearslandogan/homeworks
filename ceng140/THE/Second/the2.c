#include <stdio.h>
#include <stdlib.h>

int transform_name(const char *name)
{
    int i = 0;
    int sum = 0;

    for (; name[i] != '\0'; i++)    sum += (i+1)*(i+1)*name[i];

    return sum;
}

int** initialize_storage(int IA_size, int DA_size, int** DA_sizes)
{
    int **index_array;
    int i, j, place_holder = 0;

    index_array = (int **) malloc (sizeof(int*)*IA_size);

    for (i = 0; i < IA_size; i++){
        index_array[i] = (int *) malloc (sizeof(int) * DA_size);
        for (j = 0; j < DA_size; j++)
            index_array[i][j] = place_holder;
    }

    *DA_sizes = (int*) malloc (sizeof(int) * IA_size);
    for (i = 0; i < IA_size; i++)
        (*DA_sizes)[i] = DA_size;

    return index_array;
}

void print_storage(int** storage, int IA_size, int* DA_sizes)
{
    int i, j;

    for (i = 0; i < IA_size; i++){
        printf("%d ->", i);
        for (j = 0; j < DA_sizes[i]; j++)
            printf(" %d", storage[i][j]);
        printf("\n");
    }   
}

void insert(int** storage, int IA_size, const char* name, int* DA_sizes)
{
    int name_code = transform_name(name);
    int index = name_code % IA_size;
    int i;

    if (storage[index][DA_sizes[index] -1] != 0){
        storage[index] = (int *) realloc (storage[index], sizeof(int)*DA_sizes[index]*2);

        for (i = DA_sizes[index]; i < DA_sizes[index]*2; i++)
            storage[index][i] = 0;
        
        DA_sizes[index] *= 2;
    }   
    
    for (i = 0; i < DA_sizes[index]; i++)
        if (storage[index][i] == 0){
            storage[index][i] = name_code;
            break;
        }

}

void insert2(int** storage, int IA_size, int name_code, int* DA_sizes)
{
    int index = name_code % IA_size;
    int i;

    /* controlling whether if it is full */
    if (storage[index][DA_sizes[index] -1] != 0){
        storage[index] = (int *) realloc (storage[index], sizeof(int)*DA_sizes[index]*2);

        for (i = DA_sizes[index]; i < DA_sizes[index]*2; i++)
            storage[index][i] = 0;
        
        DA_sizes[index] *= 2;
    }   
    
    for (i = 0; i < DA_sizes[index]; i++)
        if (storage[index][i] == 0){
            storage[index][i] = name_code;
            break;
        }
}

void fill_new_storage(int** storage, int IA_size, int** new_storage, int *DA_sizes, int** new_DA_sizes)
{
    int i, j;
    int data;

    for (i = 0; i < IA_size/2; i++)
        for (j = 0; j < DA_sizes[i]; j++){
            data = storage[i][j];
            if (data != 0)
                insert2(new_storage, IA_size, data, *new_DA_sizes);
        }
}

void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes)
{
    int sum_da_sizes = 0;
    int i, j;
    int **temp_index_array;
    int *temp_DA_sizes;

    for (i = 0; i < *IA_size; i++)
        sum_da_sizes += (*DA_sizes)[i];

    if (sum_da_sizes >= *IA_size*DA_size*1.5){
        *IA_size *= 2;
        
        temp_index_array = (int **) malloc (sizeof(int*)*(*IA_size)/2);

        for (i = 0; i < (*IA_size)/2; i++){ 
            temp_index_array[i] = (int*) malloc (sizeof(int)*((*DA_sizes)[i]));
            for (j = 0; j < (*DA_sizes)[i]; j++)
                temp_index_array[i][j] = (*storage)[i][j];
            }

        temp_DA_sizes = (int *) malloc (sizeof(int)*(*IA_size)/2);
        
        for (i = 0; i < (*IA_size)/2; i++)  
            temp_DA_sizes[i] = (*DA_sizes)[i];
        

        /* fighting memory leak */
        for (i = 0; i < (*IA_size)/2; i++)
            free((*storage)[i]);
        free(*storage);
        free(*DA_sizes);

        *storage = initialize_storage(*IA_size, DA_size, DA_sizes);
        fill_new_storage(temp_index_array, *IA_size, *storage, temp_DA_sizes, DA_sizes);

        free(temp_DA_sizes);

        for (i = 0; i < (*IA_size)/2; i++)
            free(temp_index_array[i]);
        free(temp_index_array);
    }
}