#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 1100
typedef pair<int,int> pii;

//#define T 7000000
//int caso;
//int esta[T];
//vector<int> values[T];

//void clear(){
//	++caso;
//}

//void insert(int val){
//	int ind = val % T;
//	if(esta[ind] != caso) values[ind].clear(), esta[ind] = caso;
//	
//	values[ind].push_back(val);
//}

//bool find(int val){
//	int ind = val % T;
//	if(esta[ind] != caso) return false;
//	
//	rep(i, values[ind].size()){
//		if(values[ind][i] == val) return true;
//	}
//	return false;
//}

int x[N], y[N];
int values[N*N];

int main(){
	int t;
	scanf("%d", &t);
	
	fr(cas, 1, t+1){
		int n;
		scanf("%d", &n);
		
		rep(i, n) scanf("%d%d", x + i, y + i);
		
		int cont = 0, prt = 0;
		rep(i, n){
			fr(j, i, n){
				int dx = x[i] - x[j], dy = y[i] - y[j];
				values[prt++] = dx * dx + dy * dy;
			}
		}
		
		sort(values, values + prt);
		int last = -1;
		rep(i, prt){
			if(values[i] != last) ++cont;
			last = values[i];
		}
		
		printf("Case %d: %d\n", cas, cont);
	}	
}






