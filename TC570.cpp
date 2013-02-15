#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class CentaurCompany {
public:
	double getvalue(vector <int>, vector <int>);
};
const int N = 50;
vector <int> vt[N];
long long dp[N][2 * N + 10][2];
int n;
long long d[2 * N + 10][2];
void dfs(int x, int fa){
     dp[x][50][0] = dp[x][51][1] = 1;
     if(vt[x].size() == 1 && vt[x][0] == fa){
                     return;
     }
     for(int i = 0; i < vt[x].size(); i++){
             int y = vt[x][i];
             if(y == fa)
             continue;
             dfs(y, x);
            for(int j = 0; j < 2 * N; j++)
            for(int k = 0; k < 2; k++){
                d[j][k] = dp[x][j][k];
                dp[x][j][k] = 0;
            }
            for(int c1 = 0; c1 < 2; c1++){
                for(int j = 0; j <= 100; j++)
                    for(int c2 = 0; c2 < 2; c2++)
                        for(int k = 0; k <= 100; k++){
                            if(d[j][c1] && dp[y][k][c2]){
                                if(c1 && c2){
                                    if(j + k >= 52)
                                    dp[x][j + k - 52][c1] += d[j][c1] * dp[y][k][c2];
                                }
                                else
                                    if(j + k >= 50)
                                    dp[x][j + k - 50][c1] += d[j][c1] * dp[y][k][c2];
                            }
                        }
            }
     }
}
double CentaurCompany::getvalue(vector <int> a, vector <int> b) {
	n = a.size() + 1;
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < n; i++)
	vt[i].clear();
    for(int i = 0; i < n - 1; i++){
        a[i]--;
        b[i]--;
        vt[a[i]].push_back(b[i]);
        vt[b[i]].push_back(a[i]);
    }
    dfs(0, -1);
    long long aa = 0, bb = 1LL << n;
    for(int k = 53; k < 101; k++)
        for(int j = 0; j < 2; j++)
        aa += dp[0][k][j] * (k - 52);
    return double(aa) * 2.0 / bb;
}
