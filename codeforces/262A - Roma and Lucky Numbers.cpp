#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 60

int n, k;
char num[20];

int main(){
	ios::sync_with_stdio(false);
	scanf("%d%d", &n, &k);
	
	int c = 0;
	rep(i, n){
		scanf("%s", num);
		int tmp = 0;
		for(int j = 0; num[j]; ++j){
			if(num[j] == '4' || num[j] == '7') ++tmp;
		}
		if(tmp <= k) ++c;
	}
	printf("%d\n", c);
}


