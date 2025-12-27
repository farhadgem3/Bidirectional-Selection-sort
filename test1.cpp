// compile: g++ -std=c++11 -O2 simple_selection_array.cpp -o simple_selection_array
#include <iostream>
using namespace std;

// Selection Sort (معمولی)
// innerIterations: مجموع تعداد تکرار حلقهٔ درونی (تعداد اجرای بدنهٔ حلقهٔ j)
void selectionSort(int a[], int n, long long &innerIterations) {
    innerIterations = 0;
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            ++innerIterations;            // یک تکرار درونی
            if (a[j] < a[minIdx]) minIdx = j;
        }
        // سواپ دستی (بدون استفاده از std::swap)
        if (minIdx != i) {
            int tmp = a[i];
            a[i] = a[minIdx];
            a[minIdx] = tmp;
        }
    }
}

// Bidirectional Selection Sort (دوطرفه)
// innerIterations: مجموع تعداد تکرار حلقهٔ درونی (تعداد اجرای بدنهٔ حلقهٔ i)
void bidirectionalSelectionSort(int a[], int n, long long &innerIterations) {
    innerIterations = 0;
    int low = 0, high = n - 1;
    while (low < high) {
        int minIdx = low;
        int maxIdx = low;
        for (int i = low + 1; i <= high; ++i) {
            ++innerIterations;           // یک تکرار درونی
            if (a[i] < a[minIdx]) minIdx = i;
            if (a[i] > a[maxIdx]) maxIdx = i;
        }

        // قرار دادن مینیمم در ابتدای بخش
        if (minIdx != low) {
            int tmp = a[low];
            a[low] = a[minIdx];
            a[minIdx] = tmp;
        }

        // اگر ماکزیمم قبلاً در low بوده، بعد از swap بالا اندیس آن به minIdx منتقل شده
        if (maxIdx == low) maxIdx = minIdx;

        // قرار دادن ماکسیمم در انتهای بخش
        if (maxIdx != high) {
            int tmp = a[high];
            a[high] = a[maxIdx];
            a[maxIdx] = tmp;
        }

        ++low;
        --high;
    }
}

int main() {
    // نمونهٔ آزمایشی
    int arr1[] = {-10, 2, 5, 3, 7, 4, 6, 9, 8, 1, 0, -5, -3, -1, -7, -4, -6, -2, -8, -9};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    // کپی برای هر الگوریتم (تا آرایهٔ اولیه تغییر نکند)
    int a1[100];
    int a2[100];
    for (int i = 0; i < n; ++i) { a1[i] = arr1[i]; a2[i] = arr1[i]; }

    long long innerSel = 0, innerBi = 0;
    selectionSort(a1, n, innerSel);
    bidirectionalSelectionSort(a2, n, innerBi);

    cout << "Selection (normal) result: ";
    for (int i = 0; i < n; ++i) cout << a1[i] << " ";
    cout << "\nInner loop iterations (normal): " << innerSel << "\n\n";

    cout << "Bidirectional selection result: ";
    for (int i = 0; i < n; ++i) cout << a2[i] << " ";
    cout << "\nInner loop iterations (bidirectional): " << innerBi << "\n";

    return 0;
}
