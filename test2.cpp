// compile: g++ -std=c++11 -O2 timed_selection_array.cpp -o timed_selection_array
#include <iostream>
#include <chrono>
#include <cstdlib> // rand, srand
#include <ctime>   // time
using namespace std;
using namespace std::chrono;

// همان توابع ولی این بار قابل استفاده در برنامهٔ زمان‌گیری
void selectionSort(int a[], int n, long long &innerIterations) {
    innerIterations = 0;
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            ++innerIterations;
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int tmp = a[i]; a[i] = a[minIdx]; a[minIdx] = tmp;
        }
    }
}

void bidirectionalSelectionSort(int a[], int n, long long &innerIterations) {
    innerIterations = 0;
    int low = 0, high = n - 1;
    while (low < high) {
        int minIdx = low;
        int maxIdx = low;
        for (int i = low + 1; i <= high; ++i) {
            ++innerIterations;
            if (a[i] < a[minIdx]) minIdx = i;
            if (a[i] > a[maxIdx]) maxIdx = i;
        }
        if (minIdx != low) {
            int tmp = a[low]; a[low] = a[minIdx]; a[minIdx] = tmp;
        }
        if (maxIdx == low) maxIdx = minIdx;
        if (maxIdx != high) {
            int tmp = a[high]; a[high] = a[maxIdx]; a[maxIdx] = tmp;
        }
        ++low; --high;
    }
}

int main() {
    srand((unsigned)time(nullptr));

    // اندازه‌های مختلف برای تست
    int sizes[] = {1000, 2000, 5000}; // می‌تونی این لیست رو تغییر بدی
    for (int sidx = 0; sidx < (int)(sizeof(sizes)/sizeof(sizes[0])); ++sidx) {
        int n = sizes[sidx];
        // ایجاد آرایهٔ دادهٔ اصلی
        int *data = new int[n];
        for (int i = 0; i < n; ++i) data[i] = rand(); // مقدار تصادفی

        int *a = new int[n];
        int *b = new int[n];

        for (int i = 0; i < n; ++i) { a[i] = data[i]; b[i] = data[i]; }

        long long innerSel = 0, innerBi = 0;

        auto t1 = high_resolution_clock::now();
        selectionSort(a, n, innerSel);
        auto t2 = high_resolution_clock::now();
        auto durSel = duration_cast<microseconds>(t2 - t1).count();

        auto t3 = high_resolution_clock::now();
        bidirectionalSelectionSort(b, n, innerBi);
        auto t4 = high_resolution_clock::now();
        auto durBi = duration_cast<microseconds>(t4 - t3).count();

        cout << "n=" << n
             << " | Selection: " << durSel << " us"
             << " | inner iters: " << innerSel
             << " || Bidirectional: " << durBi << " us"
             << " | inner iters: " << innerBi << "\n";

        delete[] data;
        delete[] a;
        delete[] b;
    }

    return 0;
}
