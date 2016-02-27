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
#define sd second
#define N 100

int falha[N];
int pd[N][N][N];
int nt[N][N][N];
#define MA 0
#define AA 1
#define BB 2

string A, B, virus;

void fail(){
	int k = falha[0] = -1;

	fr(i, 1, virus.size()){
		while(k != -1 && virus[k+1] != virus[i]) k = falha[k];
		if(virus[k+1] == virus[i]) ++k;
		falha[i] = k;
	}
}

int match(int pre, char ch){
	while(pre != -1 && virus[pre+1] != ch) pre = falha[pre];
	if(virus[pre+1] == ch) ++pre;
	return pre;
}

int memo(int a, int b, int v){
	if(v == virus.size()-1) return -800;
	if(a == A.size()) return 0;
	if(b == B.size()) return 0;

	int &rec = pd[a][b][v+1];
	if(~rec) return rec;

	rec = 0;
	if(A[a] == B[b]) rec = 1 + memo(a+1,b+1,match(v, A[a])), nt[a][b][v+1] = MA;
	if(rec < memo(a+1, b, v)) rec = memo(a+1, b, v), nt[a][b][v+1] = AA;
	if(rec < memo(a, b+1, v)) rec = memo(a, b+1, v), nt[a][b][v+1] = BB;
	
	return rec;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> A >> B >> virus;
	memset(pd, -1, sizeof pd);
	fail();
	int qtd = memo(0,0,-1);
	string ans = "";
	int a = 0, b = 0, v = 0;

	while(qtd){
		if(nt[a][b][v] == MA) ans += A[a], v = 1+match(v-1, A[a]), a++, b++, --qtd;
		else if(nt[a][b][v] == AA) ++a;
		else ++b;
	}

	if(ans == "") cout << 0 << endl;
	else cout << ans << endl;
	
}