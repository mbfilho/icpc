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
#define N 20100
#define M 20

int n, m;
int cards[N];
int forb[M];
int pd[1<<M];

int rec(int can){
	int& ans = pd[can];
	if(~ans) return ans;
	ans = 0;

	rep(i, m) if((1 << i) & can){
		ans = max(1 + rec(can & ~forb[i]), ans);
	}

	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	memset(cards, 0, sizeof cards);
	memset(forb, 0, sizeof forb);
	memset(pd, -1, sizeof pd);

	cin >> n >> m;
	rep(i, m){
		int k;
		cin >> k;

		while(k--){
			int c;
			cin >> c;
			cards[c] |= 1 << i;
		}
	}

	fr(i, 1, n+1){
		rep(j, m) if(cards[i] & (1 << j)){
			forb[j] |= cards[i];
		}
	}

	cout << rec((1<<m)-1) << endl;
		
}
