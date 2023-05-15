#include "selection_sort.h"

int64_t* selection_sort(int64_t* array, int64_t len){
    int64_t temp, index, max_element;
    for (uint32_t i = 0; i < len; i++){
        index = 0;
        max_element = array[0];
        for (uint32_t j = 1; j < len - i; j++){
            if (max_element < array[j]){
                index = j;
                max_element = array[j];
            }
        }
        temp = array[len - 1 - i];
        array[len - 1 - i] = array[index];
        array[index] = temp;
    }
    return array;
}
