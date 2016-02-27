#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define pb push_back
#define mp make_pair
#define N 500000

vector<int> resp;
int n, k;
ll a[N];

int main(){
	scanf("%d%d", &n, &k);
	
	rep(i, n){
		int tmp;
		scanf("%d", &tmp);
		a[i] = tmp;
	}
	
	ll soma = 0, j = 1, nn = n;
	rep(i, n){
		ll d = soma - a[i] * ((j-1) * nn - (j-1) * j);
		if(d < k) resp.pb(i+1), --nn;
		else{
			soma += a[i] * ll(j - 1);
			++j;
		}
	}			
	rep(i, resp.size())
		printf("%d\n", resp[i]);
}


