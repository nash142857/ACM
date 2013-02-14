#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
int n, m, k;
map <string, int> mp;
int a[330][330], ans[330];
char s1[5], s2[5];
int ab(int x){
	return x > 0 ? x : -x;
}
int inv[7] = {0, 1, 4, 5, 2, 3, 6};
int gauss(){
	int k = 0, col = 0;
	for(; k < m && col < n; k++, col++){
		int r = k;
		for(int j = k + 1; j < m ; j++)
		if(ab(a[j][col]) > ab(a[r][col]))
			r = j;
		if(r != k){
			for(int j = 0; j <= n; j++)
				swap(a[r][j], a[k][j]);
		}
		if(a[k][col] == 0){
			k--;
			continue;
		}
		for(int j = k + 1; j < m; j++){
			int ta = a[k][col];
			int tb = a[j][col];
			for(int w = col; w <= n; w++)
			a[j][w] = ((ta * a[j][w] - tb * a[k][w]) % 7 + 7) % 7;
		}
	}
	for(int i = k; i < m; i++)
	if(a[i][n] != 0)
		return -1;
	if(k < n)
		return 1;
	for(int i = n - 1; i >= 0; i--){
		int st = a[i][n];
		for(int j = i + 1; j < n; j++)
		st -= ans[j] * a[i][j];
		st = ((st % 7) + 7)  % 7;
		ans[i] = (inv[(a[i][i] % 7)] * st) % 7;
	}
	return 0;
}
int main(){
	mp["MON"] = 1;
	mp["TUE"] = 2;
	mp["WED"] = 3;
	mp["THU"] = 4;
	mp["FRI"] = 5;
	mp["SAT"] = 6;
	mp["SUN"] = 7;
	while(scanf("%d%d", &n, &m), n || m){
		memset(a, 0, sizeof(a));
		for(int i = 0; i < m; i++){
			scanf("%d", &k);
			scanf("%s%s", s1, s2);
			a[i][n] = (mp[s2] - mp[s1] + 8) % 7;
		for(int j = 0; j < k; j++){
				int c;
				scanf("%d", &c);
				c--;
				a[i][c]++;
			}
		}
		for(int i = 0; i < m; i++)
		for(int j = 0; j < n; i++)
		a[i][j] %= 7;
		int as = gauss();
		if(as == 1){
			printf("Multiple solutions.\n");
		}
		else
		if(as == -1)
		printf("Inconsistent data.\n");
		else{
			for(int i = 0; i < n - 1; i++)
			printf("%d ", ((ans[i] - 3) % 7 + 7) % 7 + 3);
			printf("%d\n", ((ans[n - 1] - 3) % 7 + 7) % 7 + 3);
		}
	}
	return 0;
}
