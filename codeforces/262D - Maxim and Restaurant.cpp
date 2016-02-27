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
typedef long double ld;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define conj sdkjfhsdkhjf
#define N 60
int n, p;
int caras[N];
ld pd[N][N][N];
int mk[N][N][N], caso;
ld qtd[N];
int topa;

ld memo(int many, int ind, int sum){
	if(many < 0) return 0;
	if(ind == n){
		if(many == 0 && (sum + caras[topa] > p)) return 1;
		return 0;
	}
	int nt = (ind+1 == topa) ? ind+2 : ind+1;
	
	ld& resp = pd[many][ind][sum];
	if(mk[many][ind][sum] == caso) return resp;
	mk[many][ind][sum] = caso;
	resp = 0;
	if(sum + caras[ind] <= p) resp = memo(many-1, nt, sum + caras[ind]);
	resp += memo(many, nt, sum);
	
	return resp;
}

ld fat[N];

int main(){
	ios::sync_with_stdio(false);
	fat[0] = 1;
	fr(i, 1, N) fat[i] = i * fat[i-1];
	
	caso = 1;
	
	cin >> n;	
	int tot = 0;
	rep(i, n) cin >> caras[i], tot += caras[i];
	cin >> p;
	
	if(tot <= p){
		cout << n << endl;
	}else{
		rep(i, n){
			++caso;
			topa = i;
			int st = i ? 0 : 1;
			fr(j, 1, n)
				qtd[j] += fat[j] * memo(j, st, 0)*fat[n-j-1]; 		
		}
		
		ld media = 0;
		fr(i,1,n)
			media += (i * qtd[i])/fat[n];
		
	    cout.precision(10);
	    cout.setf(ios::fixed,ios::floatfield);
		cout << media << endl;
	}
}

