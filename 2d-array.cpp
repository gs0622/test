#include <cstdio>
#include <climits>
#include <iostream>
using namespace std;
int main() {
	int i, j, sum, max = INT_MIN, a[6][6] = {};
	for (i=0;i<6;i++)
		for (j=0;j<6;j++) cin >> a[i][j];
#if 0
	for (i=0;i<6;i++) {
		for (j=0;j<6;j++) cout << a[i][j] << " ";
		cout << endl;
	}
#endif
	for (i=0;i<4;i++) {
		for (j=0;j<4;j++) {
			sum = a[i][j]+a[i][j+1]+a[i][j+2]+
					      a[i+1][j+1]+
				  a[i+2][j]+a[i+2][j+1]+a[i+2][j+2];
			max = std::max(max, sum);
			//cout << sum << " ";
		}
		//cout << endl;
	}
	cout << max << endl;
    return 0;
}

