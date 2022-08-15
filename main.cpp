#include <iostream>
#include <algorithm>
#include <cmath>

//size of part of array to switch to insertion sort
size_t switchSize = 16;

//swap values
template<typename T>
void swapVal(T* a, T* b){
    T* temp = a;
    a = b;
    b = temp;
}

// insertion sort for lesser than switchSize parts of array
template<typename Type>
void insertionSort(Type arr[], Type* _begin, Type* _end){

    // indexes of subarrays to sort
    int left = _begin - arr;
    int right = _end - arr;


    for(int i = left+1; i <= right; ++i){
        Type key = arr[i];
        int j = i - 1;

        //move elements that >key to one pos right
        while(j >= left && arr[j] > key){
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

//function to get array partition point
template <typename Type>
Type* arrayPartition(Type arr[], size_t low, size_t high){

    //get pivot point value and smaller elem index
    size_t pivotPointValue = arr[high];
    size_t i = low - 1;

    for(size_t j = low; j <=high; ++j){
        if(arr[j] <= pivotPointValue){
             //if element <= pivotPointVal increase smaller element index and swap
             // element after smaller with current
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i+1], arr[high]);
    //return point of partition
    return arr + i + 1;
}

//function to find middle value of 3 values and get pointer to this val
template <typename Type>
Type* medianOfThree(Type* a, Type* b, Type* c){
    if (*a < *b && *b < *c)
        return (b);

    if (*a < *c && *c <= *b)
        return (c);

    if (*b <= *a && *a < *c)
        return (a);

    if (*b < *c && *c <= *a)
        return (c);

    if (*c <= *a && *a < *b)
        return (a);

    if (*c <= *b && *b <= *a)
        return (b);
}


// utility function to perform introsort
template<typename Type>
void introSortUtil(Type arr[], Type* _begin, Type* _end, uint8_t depthLimit){
    //get size
    size_t _size = _end - _begin;

    //if size is lower than switchSize do insertionSort
    if(_size < switchSize){
        insertionSort(arr, _begin, _end);
        return;
    }

    //use heapsort if depthLimit == 0
    if(depthLimit == 0){
        std::make_heap(_begin, _end+1);
        std::sort_heap(_begin, _end+1);
        return;
    }

    //if size > switchSize and depthLimit is not zero
    // get pivot point
    Type* pivotPoint = medianOfThree(_begin, _begin + _size/2, _end);

    //swap end value and pivot value
    swapVal(pivotPoint, _end);

    // get partitionPoint
    Type* partitionPoint = arrayPartition(arr, _begin - arr, _end - arr);

    // repeat algorithm for parts of array
    introSortUtil(arr, _begin, partitionPoint -1, depthLimit - 1);
    introSortUtil(arr, partitionPoint + 1, _end, depthLimit - 1);

}

//introsort itself
template <typename Type>
void introsort(Type arr[], Type* _begin, Type* _end){
    //calculate depth limit
    uint8_t depthLimit = 2 * std::log(_end - _begin);

    //perform recursive introsort
    introSortUtil(arr, _begin, _end, depthLimit);

}


//function for test
template <typename Type>
void printArray(Type arr[], size_t _size){
    for(size_t i = 0; i < _size; ++i){
        std::cout << arr[i] << "\n";
    }
    std::cout << std::endl;
}


int main()
{
    int arrsize = 145547;

    float arr[arrsize];

    for(int i = 0; i < arrsize; ++i){
        arr[i] = (rand()%100) * 0.618;
    }



    introsort(arr, &arr[0], &arr[arrsize-1]);

    printArray(arr, arrsize);


    return 0;
}
