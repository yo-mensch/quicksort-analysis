#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <algorithm> 
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;
int sukeista = 0;
int compared = 0;

void quickSort(int array[], int size, int choice);

int getPivotMiddleEl(int array[], int last) {
    return array[last / 2];
}

int getPivotArrMedian(int array[], int first, int last) {
    vector<int> elements;
    for (int i = first; i <= last; i++) {
        elements.push_back(array[i]);
    }
    sort(elements.begin(), elements.end());
    return elements[elements.size() / 2];
}

int getPivot3ElMedian(int array[], int first, int last) {
    int elements[3] = { array[first], array[last / 2], array[last] };
    sort(elements, elements + 3);
    return elements[1];
}

void quickSort(int array[], int size, int choice) {
    if (size < 2) return;

    int pivot, lower, upper, temp;

    //Set the indexes for the first and last elements                                 
    lower = 0;
    upper = size - 1;

    //Select pivot element                                                   
    if (choice == 1) {
        pivot = getPivotMiddleEl(array, lower);
    }
    else if (choice == 2) {
        pivot = getPivot3ElMedian(array, lower, upper);
    }
    else if(choice==3){
        pivot = getPivotArrMedian(array, lower,upper);
    }

    //veiksmas
    while (lower <= upper) {
        //Lower must be a number > than pivot and upper a number <= pivot               
        while (array[lower] > pivot) {
            lower++;
        }
        while (array[upper] < pivot) {
            upper--;
        }

        //Swap upper and lower                                                          
        if (lower <= upper) {
            temp = array[lower];
            array[lower] = array[upper];
            array[upper] = temp;
            lower++;
            upper--;
            sukeista++;
            compared++;
        }
        else compared++;
    }

    //Repeat the past actions on the two partitions of the array recursively          
    quickSort(array, upper + 1, choice);
    quickSort(&array[lower], size - lower, choice);
}

void displayArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        cout<<setw(3)<< arr[i] << " ";
    }
}

int main() {
    int* arr, kiek;
    srand((unsigned)time(0));

    cout << "Enter the size of an array:";
    cin >> kiek;
    arr = new int[kiek];
    for (int i = 0; i < kiek; i++) {
        arr[i] = (rand() % kiek) + 1;
    }
    //displayArray(arr, kiek);
    cout << endl;

    cout << "Which array item will be a pivot? " << endl;
    cout << "1) Middle element " << endl;
    cout << "2) Median of first, last and middle elements " << endl;
    cout << "3) Median of a full array " << endl;
    int choice;
    cin >> choice;
    cout << endl;

    auto start = high_resolution_clock::now();
    quickSort(arr, kiek, choice);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //displayArray(arr, kiek);
    cout << endl;

    cout << "Swapped " << sukeista << " times" << endl;
    cout << "Values were compared " << compared << " times" << endl;
    cout << "Sorting duration: "<< duration.count() << " microseconds" << endl;
    return 0;
}