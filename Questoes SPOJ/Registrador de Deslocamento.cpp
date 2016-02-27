#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 35

typedef long long ll;
typedef unsigned int ui;

int n;
void print(int ar[N]){
	rep(i, n)
		printf("%d", ar[n-1-i]);
	printf("\n");
}

ui mult(int v[N], int a[N][N], int resp[N]){
	int tmp[N];
	
	rep(i, n){
		tmp[i] = 0;
		
		rep(j, n)
			tmp[i] += (v[j] * a[j][i]) & 1;
	}
	
	ui res = 0;
	rep(i, n){
		resp[i] = tmp[i] & 1;
		res = res * 2 + (tmp[n-1-i] & 1);
	}
	
	return res;
}

void mult(int a[N][N], int b[N][N], int resp[N][N]){
	int tmp[N][N];
	
	rep(i, n){
		rep(j, n){
			tmp[i][j] = 0;
			
			rep(k, n)
				tmp[i][j] += (a[i][k] * b[k][j]) & 1;
		}
	}
	
	rep(i, n)
		rep(j, n) 
			resp[i][j] = tmp[i][j] & 1;
}


void expo(int ma[N][N], int resp[N][N], int xp){
	int tmp[N][N], X[N][N];
	rep(i, n){
		rep(j, n){
			tmp[i][j] = 0;
			X[i][j] = ma[i][j];
		}
		tmp[i][i] = 1;
	}
	
	while(xp){
		if(xp & 1)
			mult(tmp, X, tmp);
		mult(X, X, X);
		xp >>= 1;
	}
	
	rep(i, n)
		rep(j, n)
			resp[i][j] = tmp[i][j];

}


#define X 1000000
struct no{
	int caso;
	int mk[X];
	vector<pair<ui,int> > nos[X];
	
	no(){	
		caso = 0;
		memset(mk, -1, sizeof mk);
	}
	
	void clear(){
		++caso;
	}
	
	int& operator[](const ui arg){
		int ind = arg % X;
		
		if(mk[ind] == caso){
			rep(i, nos[ind].size()){
				if(nos[ind][i].first == arg)
					return nos[ind][i].second;
			}
		}else{
			mk[ind] = caso;
			nos[ind].clear();
		}
				
//		printf(">>> %d\n", mk[ind]);
		pair<ui,int> tmp = make_pair(arg, -1);
		nos[ind].push_back(tmp);
		return nos[ind][nos[ind].size() - 1].second;
	}
	
}mapa;
#undef X
int inicio[N], fim[N], A[N][N];
int sinks[N], s;
int B;

ll faz(){
	mapa.clear();
	
	memset(A, 0, sizeof A);
	
	rep(i, n-1) A[i+1][i] = 1;
	rep(i, s) A[sinks[i]][n-1] = 1;
	
	int tmp[N];
	rep(i, n) tmp[i] = fim[i];
	rep(i, B + 1){
		ui res = 0;
		rep(j, n)
			res = res * 2 + tmp[n-1-j];

		mapa[res] = i;			
		mult(tmp, A, tmp);
	}
	
	expo(A, A, B);
	rep(i, n) tmp[i] = inicio[i];

	fr(i, 1, B){
		ui result = mult(tmp, A, tmp);		
		
		int x = mapa[result];
		
		if(~x){
			return ll(i) * B - x;
		}
	}
	
	return -1;
}

int main(){
	int caso = 1;
	
	while(scanf("%d%d", &n, &s) == 2 && (n|s)){
		rep(i, s)
			scanf("%d", sinks + i);
		int a, b;
		scanf("%x %x", &a, &b);
		
		
//		if(caso == 81){
//			printf("____________\n");
//			printf("%d %d\n", n, s);
//			rep(i, s)
//				printf("%d ", sinks[i]);
//			printf("\n");
//			printf("%u %u\n", a, b);
//			printf("____________\n");
//			return 0;
//		}
		rep(i, n){
			if(a & (1U<<i))
				inicio[i] = 1;
			else inicio[i] = 0;
			
			if(b & (1U<<i))
				fim[i] = 1;
			else
				fim[i] = 0;
		}
		B = 5 + (int) sqrt(double(1LL << n));	
		ll resp = faz();
		if(~resp)
			printf("%lld\n", resp);
		else
			printf("*\n");
			
		++caso;
	}
}






