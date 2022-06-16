#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <map>

int main() {
    std::map<int, int> myMap;

    int start_time = clock();
    int p=4;//степень


    std::ofstream out("Map_statistics_time.txt");
    for (int i = 1; i <= pow(10,p); i++)
    {
        int end_time = clock();
        myMap.insert(std::pair<int, int>(i, i)); //наполнение map
        int search_time = end_time - start_time; //подсчет времени для составления графика
        out << "Elements: " << i << "\t";
        out << "Time: " << search_time << std::endl;
    }

    std::map<int, int> myMap2;
    std::ofstream out2("Map_statistics_memory.txt");
    for (int i = 1; i <= pow(10,p); i++)
    {
        myMap2.insert(std::pair<int, int>(i, i));
        out2 << "Elements: " << i << "\t";
        out2 << "Size in memory: " << sizeof(myMap) + sizeof(int) * 2 * i << std::endl; //подсчет памяти при добавлении каждого элемента
    }

    return 0;
}