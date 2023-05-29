#include <iostream>
#include <limits.h>
#include <omp.h>

using namespace std;

int main()
{
    int num_elements;
    cout << "Enter the number of elements: ";
    cin >> num_elements;

    int* arr = new int[num_elements];
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    float avg = 0.0, sum = 0.0, sum_val = 0.0;
    int i;

    cout << "Enter " << num_elements << " elements:\n";
    for (i = 0; i < num_elements; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }

    #pragma omp parallel for reduction(min : min_val)
    for (i = 0; i < num_elements; i++)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    cout << "min_val = " << min_val << "\n";

    #pragma omp parallel for reduction(max : max_val)
    for (i = 0; i < num_elements; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    cout << "max_val = " << max_val << "\n";

    #pragma omp parallel for reduction(+: sum_val)
    for (i = 0; i < num_elements; i++)
    {
        sum_val = sum_val + arr[i];
    }
    cout << "sum_val = " << sum_val << "\n";

    #pragma omp parallel for reduction(+: sum)
    for (i = 0; i < num_elements; i++)
    {
        sum = sum + arr[i];
    }
    avg = sum / num_elements;
    cout << "avg_val = " << avg << "\n";

    delete[] arr;
    return 0;
}
