#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int n, i;
	scanf("%d", &n);
	int arr[n];
	for (i=0;i<n;i++) scanf("%d", &arr[i]);
	for (i=n;i>0;i--) printf("%d ", arr[i-1]);
	puts("");
    return 0;
}

