#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define EPS 1e-7
#define N 64
typedef long long ll;
typedef double ld;

ld mat[N][N];
int input[N][N];
ll soma[N][N];
int n = 8;

//void print(ld ma[N][N]){
//	rep(i, N){
//		rep(j, N){
//			printf("%.2Lf ", ma[i][j]);
//		}
//		printf("\n");
//	}
//}

void nomalize(ld ma[N][N]){
	rep(i, N){
		ld soma = 0;
		rep(j, N)
			soma += ma[i][j];
		rep(j, N)
			ma[i][j] /= soma;
	}
}

bool pode(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < n;
}

int get(int i, int j){
	return i * n + j;
}

void build(){
	memset(soma, 0, sizeof soma);
	memset(mat, 0, sizeof mat);
	rep(i, n){
		rep(j, n){
			int at = get(i,j);
			
			fr(dx, -1, 2){
				fr(dy, -1, 2){
					if(!dx && !dy) continue;
					int nx = dx + i, ny = dy + j;
					if(pode(nx, ny))
						soma[i][j] += input[nx][ny];
				}
			}	
		}
	}
	
	rep(i, n){
		rep(j, n){
			int at = get(i,j);
			
			fr(dx, -1, 2){
				fr(dy, -1, 2){
					if(!dx && !dy) continue;
					int nx = dx + i, ny = dy + j;
					if(pode(nx, ny)){
						int nt = get(nx, ny);
						mat[at][nt] = ld(input[nx][ny]) / soma[i][j];
					}
				}
			}
		}
	}

}

void mult(ld a[N][N], ld b[N][N], ld c[N][N]){
	double tmp[N][N];
	
	rep(i, N){
		rep(j, N){
			tmp[i][j] = 0;
			
			rep(k, N)
				tmp[i][j] += a[i][k] * b[k][j];
		}
	}
	
	rep(i, N){
		rep(j, N)
			c[i][j] = tmp[i][j];
	}
}




void expo(int qtd, ld ma[N][N], ld resp[N][N]){
	ld tmp[N][N];
	rep(i, N){
		rep(j, N)
			tmp[i][j] = 0;
		tmp[i][i] = 1;
	}
	
	while(qtd--){
		mult(tmp, ma, tmp);
		mult(ma, ma, ma);
		nomalize(tmp);
		nomalize(ma);
	}
	
	rep(i, N)
		rep(j, N) resp[i][j] = tmp[i][j];
}

bool verify(ld ma[N][N]){
	rep(i, N){
		ld soma = 0;
		
		rep(j, N){
			soma += ma[i][j];
		}
		
		if(abs(soma - 1.0) > EPS){
//			printf("> %d %.12Lf\n", i, soma);
			throw 1;
			return false;
		}
	}
	
	return true;
}

int main(){
	rep(i, n)
		rep(j, n)
			scanf("%d", &input[i][j]);
	build();
	expo(70, mat, mat);

//	verify(mat);

	rep(i, n){
		rep(j, n){
			printf("%.12lf%c", mat[get(i,j)][get(i,j)], j == n - 1 ? '\n' : ' ');
		}
	}
}




