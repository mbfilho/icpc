#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 400
#define rep(i,n) for(int i = 0; i < n; ++i)
int mat[N][N];
int n;

int gaussianElimination(){
	int pivo = 0;
	int linha = 0, npivo;
	int fator;
	bool achou;
	
	while(pivo < n){
		achou = false;
		for(int i = linha; i < n; i++){
				if(mat[i][pivo] != 0){
					 achou = true;
					 npivo = i;
					 break;
				}
		}
		if(achou){
				if(npivo != linha){
					for(int i = 0; i < n; i++)
						swap(mat[npivo][i], mat[linha][i]);
				}
				for(int i = linha+1; i < n; i++){
					if(mat[i][pivo] != 0){
						fator = mat[i][pivo];

						for(int j = pivo; j < n; j++)
							mat[i][j] = ((mat[i][j]*mat[linha][pivo] - mat[linha][j])&1);
					}
				}
				linha++;
		}
		pivo++;
	}
	
	int resp = 1;
	rep(i, n) resp = (resp * mat[i][i]) & 1;
	
	return resp;
}

char buf[N];
int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; ++i){
			scanf("%s", buf);
			for(int j = 0; j < n; ++j){
				mat[i][j] = buf[j] - '0';
			}
		}
		
		int resp = gaussianElimination();
		if(resp &1)
			printf("Odd\n");
		else
			printf("Even\n");
	}
}

