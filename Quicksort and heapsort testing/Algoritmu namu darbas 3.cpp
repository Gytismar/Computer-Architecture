#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <chrono>  
#include <string>
#include <iomanip>

using namespace std;

// Counts number of lines in a file
int countLines(string file) {
    ifstream data(file);
    string line;
    int count = 0;
    while (getline(data, line)) {
        count++;
    }

    return count;
}

// Generates random numbers and writes them to file
void generateNumbers(string file, int size) {
    ofstream data(file);
    for (int i = 0; i < size; i++) {
        if (i != 0)
            data << "\n";
        data << (rand() % 1000 + 1) * (rand() % 1000 + 1);
    }
}

class SortTesting {
private:
    int size; // array size
    int *mainarray;
    int *array;
    int *array2;
    string fileName; // file where data will be got
public:
    SortTesting(string file){
        fileName = file;
        size = countLines(file);
        mainarray = new int[size];
        array = new int[size];
        array2 = new int[size];

        getNumbers();
        sort();
    }
    void getNumbers() {
        ifstream data(fileName);
        for (int i = 0; i < size; i++) {
            data >> mainarray[i];
        }
    }

    void placeNumbers() {
        for (int i = 0; i < size; i++) {
            array[i] = mainarray[i];
            array2[i] = mainarray[i];
        }
    }
    void sort() {
        double time; 
        std::ofstream results("Duomenys.csv", std::ios_base::app);

        for (int i = 1; i <= 10; i++) {
            cout << "Testas: " << i << endl;
            results << fileName << "," << size << "," << i << ",";

            placeNumbers();


            auto start = std::chrono::system_clock::now();
            quickSort(0, size - 1);
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            time = elapsed.count();
            time = time / 1000;
            results << time << std::fixed << std::setprecision(2) << ",";

            start = std::chrono::system_clock::now();
            heapSort();
            end = std::chrono::system_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            time = elapsed.count();
            time = time / 1000;
            results << time << std::fixed << std::setprecision(2) << ",";
            
            results << "\n";
        }
        results.close();
    }

    int partition(int start, int end)
    {
        int pivot = array2[start];

        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (array2[i] <= pivot)
                count++;
        }

        // Puts the pivot in place
        int pivotIndex = start + count;
        std::swap(array2[pivotIndex], array2[start]);

        // Sorting left and right parts of the pivot element
        int i = start, j = end;

        while (i < pivotIndex && j > pivotIndex) {

            while (array2[i] <= pivot) {
                i++;
            }

            while (array2[j] > pivot) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                std::swap(array2[i++], array2[j--]);
            }
        }

        return pivotIndex;
    }

    void quickSort(int start, int end)
    {

        // base case
        if (start >= end)
            return;

        // partitioning the array
        int p = partition(start, end);

        // Sorting the left part
        quickSort(start, p - 1);

        // Sorting the right part
        quickSort(p + 1, end);
    }

    void heapify(int n, int i)
    {
        int largest = i; // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && array[l] > array[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < n && array[r] > array[largest])
            largest = r;

        // If largest is not root
        if (largest != i) {
            swap(array[i], array[largest]);

            // Recursively heapify the affected sub-tree
            heapify(n, largest);
        }
    }

    // main function to do heap sort
    void heapSort()
    {
        int n = size;
        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(n, i);

        // One by one extract an element from heap
        for (int i = n - 1; i >= 0; i--) {
            // Move current root to end
            swap(array[0], array[i]);

            // call max heapify on the reduced heap
            heapify(i, 0);
        }
    }

    ~SortTesting() { delete[]array; }

};

int main()
{
    srand(time(0));
    srand(rand()* rand()+ rand());
    /*
    std::ofstream results("Duomenys.csv");
    results << "File name,Size,Test number,quicksort,heapsort,\n";
    results.close();
    */

    bool generate = false;
    if (generate) {
        generateNumbers("4 mil. 1.txt", 4000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("4 mil. 2.txt", 4000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("4 mil. 3.txt", 4000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("4 mil. 4.txt", 4000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("4 mil. 5.txt", 4000000);


        generateNumbers("6 mil. 1.txt", 4000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("6 mil. 2.txt", 6000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("6 mil. 3.txt", 6000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("6 mil. 4.txt", 6000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("6 mil. 5.txt", 6000000);


        generateNumbers("8 mil. 1.txt", 8000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("8 mil. 2.txt", 8000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("8 mil. 3.txt", 8000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("8 mil. 4.txt", 8000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("8 mil. 5.txt", 8000000);


        generateNumbers("9 mil. 1.txt", 9000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("9 mil. 2.txt", 9000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("9 mil. 3.txt", 9000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("9 mil. 4.txt", 9000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("9 mil. 5.txt", 9000000);


        generateNumbers("10 mil. 1.txt", 10000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("10 mil. 2.txt", 10000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("10 mil. 3.txt", 10000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("10 mil. 4.txt", 10000000);
        srand(time(0));
        srand(rand() * rand() + rand());
        generateNumbers("10 mil. 5.txt", 10000000);
    }

    if (true) {
        SortTesting Test4_1("4 mil. 1.txt");
        SortTesting Test4_2("4 mil. 2.txt");/*
        SortTesting Test4_3("4 mil. 3.txt");
        SortTesting Test4_4("4 mil. 4.txt");
        SortTesting Test4_5("4 mil. 5.txt");

        SortTesting Test6_1("6 mil. 1.txt");
        SortTesting Test6_2("6 mil. 2.txt");
        SortTesting Test6_3("6 mil. 3.txt");
        SortTesting Test6_4("6 mil. 4.txt");
        SortTesting Test6_5("6 mil. 5.txt");
        
        SortTesting Test8_1("8 mil. 1.txt");
        SortTesting Test8_2("8 mil. 2.txt");
        SortTesting Test8_3("8 mil. 3.txt");
        SortTesting Test8_4("8 mil. 4.txt");
        SortTesting Test8_5("8 mil. 5.txt");

        SortTesting Test9_1("9 mil. 1.txt");
        SortTesting Test9_2("9 mil. 2.txt");
        SortTesting Test9_3("9 mil. 3.txt");
        SortTesting Test9_4("9 mil. 4.txt");
        SortTesting Test9_5("9 mil. 5.txt");

        SortTesting Test10_1("10 mil. 1.txt");
        SortTesting Test10_2("10 mil. 2.txt");
        SortTesting Test10_3("10 mil. 3.txt");
        SortTesting Test10_4("10 mil. 4.txt");
        SortTesting Test10_5("10 mil. 5.txt");
        */
    }

    /*
    SortTesting test("testdata.txt");
    test.getNumbers();
    test.sort();
    */
    return 0;
}