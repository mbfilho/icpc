#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define ft first
#define N 3000100
#define MOD 1000000
int n, a, b, c, d;

int cnt[MOD];
//Ver como o pessoal fez!

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	
	while(t--){
		cin >> n >> a >> b >> c >> d;
		memset(cnt, 0, sizeof cnt);
		++cnt[d];
		ll last = d;
		fr(i, 1, n){
			ll s = (a * last * last + b * last + c) % MOD;
			++cnt[s];
			last = s;
		}
		ll sum[] = {0, 0};
		{
			int i = MOD - 1, team = 0;
			while(i > 0){
				if(cnt[i]){
					sum[team] += i;
					team ^= 1;
					--cnt[i];
				}else --i;
			}
		}


		cout << abs(sum[0] - sum[1]) << endl;
	}
}
