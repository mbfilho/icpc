#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define oo ll(1e17)
#define N 510
//sliding RMQ. Prestar atenção nos indices durante o pre-process das queries

int r, c, n, M[10], R[N], C[N];
ll pd[N][N];
int ma[N][N];
ll sum[N][N];

void insert(deque<ll>& fila, ll val){
	while(!fila.empty() && val > fila.back()) fila.pop_back();

	fila.push_back(val);
}

void remove(deque<ll>& fila, ll val){
	if(fila.front() == val) fila.pop_front();
}

ll getSum(int i, int j, int fi, int fj){
	ll s = 0;
	int x[] = {i, fi+1}, y[] = {j, fj+1};
	rep(dx, 2) rep(dy, 2){
		s += sum[x[dx]][y[dy]] * ((dx+dy)%2 == 0 ? 1 : -1);
	}

	return s;
}

ll aux[N][N];

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;

	while(t--){
		cin >> r >> c >> n;
		R[0] = r, C[0] = c;
		rep(i, n) cin >> R[i+1];
		rep(i, n) cin >> C[i+1];
		rep(i,1+n) cin >> M[i];

		rep(i, r) rep(j, c) cin >> ma[i][j], pd[i][j] = 0;

		memset(sum, 0, sizeof sum);
		fr(i, 1, 1+ r) fr(j, 1, 1+c)
			sum[i][j] = ma[i-1][j-1] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];

		for(int i = 0; i + R[n] <= r; ++i) for(int j = 0; j + C[n] <= c; ++j) 
			pd[i][j] = getSum(i, j, i + R[n]-1, j+C[n]-1) * (M[n] - M[n-1]);

		for(int k = n-1; k >= 0; --k){
			for(int i = 0; i < r; ++i){
				deque<ll> lista;
				int pipe = C[k] - C[k+1] + 1;
				rep(j, pipe) insert(lista, pd[i][j]);
				for(int j = 0; j + pipe <= c; ++j){
					aux[i][j] = lista.front();
					remove(lista, pd[i][j]);
					insert(lista, pd[i][j+pipe]);
				}
			}

			for(int j = 0; j < c; ++j){
				deque<ll> lista;
				int pipe = R[k] - R[k+1] + 1;
				rep(i, pipe) insert(lista, aux[i][j]);
				for(int i = 0; i + pipe <= r; ++i){
					ll tmp = lista.front();
					remove(lista, aux[i][j]);
					insert(lista, aux[i+pipe][j]);
					aux[i][j] = tmp;
				}
			}

			for(int i = 0; i + R[k] <= r; ++i){
				for(int j = 0; j + C[k] <= c; ++j){
					ll soma = getSum(i, j, i+R[k]-1, j+C[k]-1);
					pd[i][j] = soma * M[k] + aux[i][j] - (k ? M[k-1] * soma : 0);
				}
			}
		}

		cout << pd[0][0] << endl;


	}
}