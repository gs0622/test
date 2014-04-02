#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // Generate the first n numbers
    const int n = 20;

    std::vector<int> v(n);
    v[0] = 1;

    int i2 = 0; // Index for 2
    int i5 = 0; // Index for 5

    // Next two candidates
    int x2 = 2 * v[i2];
    int x5 = 5 * v[i5];

    for (int i = 1; i != n; ++i)
    {
        int m = std::min(x2, x5);

        std::cout << m << " ";

        v[i] = m;

        if (x2 == m)
        {
            ++i2;
            x2 = 2 * v[i2];
        }
        if (x5 == m)
        {
            ++i5;
            x5 = 5 * v[i5];
        }
    }
    std::cout << std::endl;
    return 0;
}
