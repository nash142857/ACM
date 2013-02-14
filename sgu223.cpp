#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, k, one[1024];
long long dp[11][1 << 10][110];
int mas;
vector <int> vt[1024];
int judge(int sub){
	int f = 0;
	while(sub){
		if(f && (sub & 1))
		return false;
		f = sub & 1;
		sub >>= 1;
	}
	return true;
}
void pre(){
	for(int i = 0; i <= mas; i++){
		int k = (i | (i << 1) | (i >> 1)) & mas;
		k = mas - k;
		for(int sub = k;; sub = (sub - 1) &k){
			if(judge(sub))
				vt[i].push_back(sub);
			if(sub == 0)
			break;
		}
	}
	one[0] = 0;
	for(int i = 1; i < (1 << n); i++){
		one[i] = one[i >> 1] + (i & 1);
	}
}
int main(){
	scanf("%d%d", &n, &k);
	dp[0][0][0] = 1;
	mas = ((1 << n) - 1);
	pre();
	for(int i = 1; i <= n; i++){
		for(int c = 0; c <= k; c++){
			for(int mask = 0; mask <= mas; mask++){
				if(!dp[i - 1][mask][c])
				continue;
				for(int j = 0; j < vt[mask].size(); j++){
					int w = vt[mask][j];
					if(c + one[w] > k)
					continue;
					dp[i][w][c + one[w]] += dp[i - 1][mask][c];
				}
			}
		}
	}
	long long ans = 0;
	for(int i = 0; i <= mas; i++)
	ans += dp[n][i][k];
	printf("%lld\n", ans);
	return 0;
}
