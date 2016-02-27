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

ui mult(ui v, ui a[N]){
	ui resp = 0;
	
	for(int i = n-1; i >= 0; --i){
		ui tmp = v & a[i];
		int c =0;
		while(tmp){
			++c;
			tmp -= tmp & (-tmp);
		}
		resp = resp * 2 + (c&1);
	}

	return resp;
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

ui inicio, fim;
int A[N][N];
int sinks[N], s;
int B;

void trans(int ma[N][N], ui resp[N]){
	rep(j, n){
		resp[j] = 0;
		
		rep(i, n)
			resp[j] = resp[j] * 2 + ma[n-1-i][j];
	}
}

ll faz(){
	mapa.clear();
	
	memset(A, 0, sizeof A);
	
	rep(i, n-1) A[i+1][i] = 1;
	rep(i, s) A[sinks[i]][n-1] = 1;
	
	ui tmp = fim;
	ui ma[N];
	trans(A, ma);

	rep(i, B + 1){
		mapa[tmp] = i;			
		tmp = mult(tmp, ma);
	}
	
	expo(A, A, B);
	tmp = inicio;
	
	trans(A, ma);
	
	ll ret = -1;
	fr(i, 1, B){
		tmp = mult(tmp, ma);		
		
		int x = mapa[tmp];
		
		if(~x){
			return ll(i) * B - x;
		}
	}
	
	return ret;
}

int main(){
	while(scanf("%d%d", &n, &s) == 2 && (n|s)){
		rep(i, s)
			scanf("%d", sinks + i);
		scanf("%x %x", &inicio, &fim);
		
		B = 5 + (int) sqrt(double(1LL << n));
		
		ll resp = faz();
		if(~resp)
			printf("%lld\n", resp);
		else
			printf("*\n");
	}
}






