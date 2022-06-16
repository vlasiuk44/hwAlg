#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <iterator>
#include <ctime>
#include "math.h"

template<typename T>
class NDArray{
public:
    //constructors
    NDArray(const std::vector<int>& shape){
        this->shape = shape;
        size = std::accumulate(shape.begin(),shape.end(),1, std::multiplies<int>());
        arr.resize(size);
    }
    NDArray(const std::vector<int>& shape, const T array[]){
        this->shape = shape;
        size = std::accumulate(shape.begin(),shape.end(),1, std::multiplies<int>());
        arr.resize(size);
        arr.assign(array,array+size);
    }

    
    int GetSize() const {return size;}

    T GetItem(int index) const {
        if(index < 0 or index > size){std::cout << "\nerror: wrong index!\n"; return -1;}
        return arr[index];
    }

    //fill NDArray
    void zeroes() {
        for (int i = 0; i < GetSize(); i++) arr[i] = 0;
    }

    void ones() {
        for (int i = 0; i < GetSize(); i++) arr[i] = 1;
    }

    void random() {
        srand(time(NULL));
        for (int i = 0; i < GetSize(); i++) arr[i] = rand();
    }

    
    //operators
    NDArray operator + (const NDArray<T> & other){
        NDArray<T> temp(shape);
        for (int i = 0; i < GetSize(); i++) temp.arr[i] = arr[i] + other.GetItem(i);
        return temp;
    };

    NDArray operator - (const NDArray<T> & other){
        NDArray<T> temp(shape);
        for (int i = 0; i < GetSize(); i++) temp.arr[i] = arr[i] - other.GetItem(i);
        return temp;
    };

    NDArray operator * (const NDArray<T> & other){
        NDArray<T> temp(shape);
        for (int i = 0; i < GetSize(); i++) temp.arr[i] = arr[i] * other.GetItem(i);
        return temp;
    };

    NDArray operator / (const NDArray<T> & other){
        NDArray<T> temp(shape);
        for (int i = 0; i < GetSize(); i++) temp.arr[i] = arr[i] / other.GetItem(i);
        return temp;
    };

    
    void shapePrint() {
        if (shape.size() < 2 or shape.size() > 2) std::cout << "\nerror: wrong size, use standard cout!\n";
        else {
            int buff = 0;
            for (int i = 0; i < shape.at(0); i++){
                for(int j = 0; j < shape.at(1); j ++)
                {
                    std::cout << arr[j+buff] << " ";
                }
                buff += shape.at(1);
                std::cout << std::endl;
            }
        }
    }

    
    //min, max, avg without range

    T min(){
        T min = arr[0];
        for(int i = 1; i < GetSize(); i++){
            if (arr[i] < min) min = arr[i];
        }
        return min;
    }

    T max(){
        T max = arr[0];
        for(int i = 1; i < GetSize(); i++){
            if (arr[i] > max) max = arr[i];
        }
        return max;
    }

    float avg(){
        float sum = 0;
        for(int i = 0; i < GetSize(); i++){
            sum+=arr[i];
        }
        return sum / GetSize();
    }


    //min, max, avg with range
    T* min(int reduction){
        T* array = nullptr;
        int rows = shape.at(0);
        int columns = shape.at(1);
        if (reduction == 0) {
            array = new T[columns];
            for(int i = 0; i < columns; i++){
                T min = arr[i];
                for (int j = 1; j < rows; j++) {
                    if (min > arr[i+columns*j]) min = arr[i+columns*j];
                }
                array[i] = min;
                std::cout << min << " ";
            }
        } else if (reduction == 1) {
            array = new T[rows];
            int temp = 0;
            for(int i = 0; i < rows; i++){
                T min = arr[temp];
                for (int j = 0; j < columns; j++) {
                    if (min > arr[temp+j]) min = arr[temp+j];
                }
                array[i] = min;
                std::cout << min << " ";
                temp += columns;
            }
        }
        std::cout << "\n";
        return array;
    }

    T* max(int reduction){
        T *array = nullptr;
        int rows = shape.at(0);
        int columns = shape.at(1);
        if (reduction == 0) {
            array = new T[columns];
            for(int i = 0; i < columns; i++){
                T min = arr[i];
                for (int j = 1; j < rows; j++) {
                    if (min < arr[i+columns*j]) min = arr[i+columns*j];
                }
                array[i] = min;
                std::cout << min << " ";
            }
        } else if (reduction == 1) {
            array = new T[rows];
            int temp = 0;
            for(int i = 0; i < rows; i++){
                T min = arr[temp];
                for (int j = 0; j < columns; j++) {
                    if (min < arr[temp+j]) min = arr[temp+j];
                }
                array[i] = min;
                std::cout << min << " ";
                temp += columns;
            }
        }
        std::cout << "\n";
        return array;
    }

    float* avg(int reduction){
        float *array = nullptr;
        int rows = shape.at(0);
        int columns = shape.at(1);
        if (reduction == 0) {
            array = new float[columns];
            for(int i = 0; i < columns; i++){
                float sum = arr[i];
                for (int j = 1; j < rows; j++) {
                    sum += arr[i+columns*j];
                }
                array[i] = sum / rows;
                std::cout << array[i] << " ";
            }
        } else if (reduction == 1) {
            array = new float[rows];
            int temp = 0;
            for(int i = 0; i < rows; i++){
                float sum = 0;
                for (int j = 0; j < columns; j++) {
                    sum += arr[temp+j];
                }
                array[i] = sum / columns;
                std::cout << array[i] << " ";
                temp += columns;
            }
        }
        std::cout << "\n";
        return array;
    }


private:
    std::vector<T> arr;
    int size;
    std::vector<int> shape;
};

template<typename T>
std::ostream &operator <<(std::ostream& output, NDArray<T>& arr)
{
    for (int i = 0; i < arr.GetSize(); i ++) {
        output << arr.GetItem(i) << ' ';
    }
    return output;
}


int main() {
    //basic func 
    NDArray<int> arr(std::vector<int>{2,3});
    std::cout << "Size: " << arr.GetSize() << std::endl;
    arr.zeroes();
    std::cout << "Fill array with 0: " << arr << std::endl;
    arr.ones();
    std::cout << "Fill array with 1: " << arr << std::endl;
    arr.random();
    std::cout << "Fill array with random numbers: " << arr << std::endl;

    std::cout << "\n\n";

   
    NDArray<int> arr1(std::vector<int>{2,3});
    arr1.ones();
    NDArray<int> arr2(std::vector<int>{3,3});
    arr2.ones();
     NDArray<int> res(std::vector<int>{3,3});
    std::cout << "First array: " << arr1 << std::endl;
    std::cout << "Second array: " << arr2 << std::endl;
    res = arr1 + arr2;
    std::cout << "arr1 + arr2: " << res << std::endl;
    res = arr1 - arr2;
    std::cout << "arr1 - arr2: " << res << std::endl;
    std::cout << "fill arr1.random() and arr2.zeroes()\n";
    arr1.random(); 
    arr2.zeroes();
    res = arr1 * arr2;
    std::cout << "arr1 * arr2: " << res << std::endl;
    std::cout << "arr2.ones()\n";
    arr2.ones();
    res = arr1 / arr2;
    std::cout << "arr1 / arr2: " << res << std::endl;

    std::cout << "\n\n";

    //min,max,avg with reduction
    int array[9]{0,1,2,3,4,5,6,7,8};
    NDArray<int> drr(std::vector<int>{3,3}, array);
    drr.shapePrint();
    std::cout << "Min arr elems in row: "; drr.min(0);
    std::cout << "Min arr elems in col: "; drr.min(1);
    std::cout << "Max arr elems in row: "; drr.max(0);
    std::cout << "Max arr elems in col: "; drr.max(1);
    std::cout << "Avg arr elems in row: "; drr.avg(0);
    std::cout << "Avg arr elems in col: "; drr.avg(1);




    return 0;
}