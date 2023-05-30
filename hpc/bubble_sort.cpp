#include <omp.h>
#include <iostream>
using namespace std;

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int* a, int n)
{
    double start = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        #pragma omp parallel
        for (int j = 0; j < n-i-1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
    double end = omp_get_wtime();
    double time = end - start;
    cout << "\nTime taken => " << time << endl;
}


int main()
{
    omp_set_num_threads(4);
    int* a;
    int n;

    cout << "\nEnter total number of elements => ";
    cin >> n;

    a = new int[n];
    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    bubble(a, n);

    cout << "\nSorted Array => ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    delete[] a;
    return 0;
}
