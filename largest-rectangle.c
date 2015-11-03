#include <stdio.h>
#define MIN(a,b)	((a>b)?b:a)
#define MAX(a,b)	((a>b)?a:b)
int right(const int *arr, const int s, const int e) {
	int i = s, base = arr[i];
	while (++i <= e) if (arr[i] < base) break;
	return i - s - 1;
}
int left(const int *arr, const int s, const int e) {
	int i = s, base = arr[i];
	while (--i >= e) if (arr[i] < base) break;
	return s - i - 1;
}
int main() {
	int i, n, ans = 0;
	if (scanf("%d", &n) == 1) {
		int arr[n], max[n];
		for (i=0;i<n;i++) if (scanf("%d", &arr[i]) != 1) return -1;
		for (i=0;i<n;i++) {
			max[i] = (left(arr, i, 0) + 1 + right(arr, i, n-1)) * arr[i];
			ans = MAX(ans, max[i]);
		}
		//for (i=0;i<n;i++) printf("%d ", max[i]); puts("");
		printf("%d\n", ans);
	}
    return 0;
}

