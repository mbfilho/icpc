#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair

int ev[2];
int d, at;
int m, n;

long double mat[300][300];
long double indep[300];

typedef pair<int,int> pii;
map<pii, int> mapa;

int get(int i, int j){
	return mapa[mp(i,j)];
}

void insert(int i, int j){
	if(mapa.find(mp(i,j)) == mapa.end())
		mapa[mp(i,j)] = n++;
}


void build(){
	mapa.clear();
	
	int soma = ev[0] + ev[1];
	memset(mat, 0, sizeof mat);
	memset(indep, 0, sizeof indep);
	m = n = 0;

	rep(i, soma+1){
		for(int j = 0; j + i <= soma; ++j){
			if(i+j == 0) continue;
			
			insert(i,j);
			
			if(j && i){
				int ni = i + at, nj = max(j-at, 0);
				insert(ni, nj);
				ni = max(0, i - at), nj = j + at;
				insert(ni, nj);
			}
		}
	}
	
	for(map<pii,int>::iterator it = mapa.begin(); it != mapa.end(); ++it){
		mat[m][it -> second] = -1;
		int i = (it -> first).first, j = (it -> first).second;
		
		if(!i || !j){
			mat[m][it -> second] = 1;
			if(i){
				indep[m] = 1;
			}
		}else{
			double ganhar = d / 6.0;
			int ni = i + at, nj = max(j-at, 0);
			mat[m][get(ni,nj)] = ganhar;
			
//			printf("W (%d,%d) -> (%d,%d)\n", i, j, ni, nj);
			double perder = 1 - ganhar;
			ni = max(0, i - at), nj = j + at;
			mat[m][get(ni,nj)] = perder;
//			printf("P (%d,%d) -> (%d,%d)\n", i, j, ni, nj);
		}
		
		++m;
	}
	
//	printf(">>>> %d %d %d\n", n == m, n, m);
}

int cmpEPS(long double a, long double b){
	return fabs(a-b) >= 1e-7;
}

void gaussianElimination(){
	int pivo = 0;
	int linha = 0, npivo;
	long double fator;
	bool achou;
	
	while(pivo < n){
		achou = false;
		for(int i = linha; i < m; i++){
				if(cmpEPS(mat[i][pivo], 0) != 0){
					 achou = true;
					 npivo = i;
					 break;
				}
		}
		if(achou){
				if(npivo != linha){
					for(int i = 0; i < n; i++)
						swap(mat[npivo][i], mat[linha][i]);
					swap(indep[npivo], indep[linha]);
				}
				long double f = mat[linha][pivo];
				rep(i, n) mat[linha][i] /= f;
				indep[linha] /= f;
				
				for(int i = linha+1; i < m; i++){
					if(cmpEPS(mat[i][pivo], 0) != 0){
						fator = mat[i][pivo];
						for(int j = pivo; j < n; j++){
							mat[i][j] = mat[i][j] / fator - mat[linha][j];
						}
						indep[i] = indep[i]/fator - indep[linha];
					}
				}
				linha++;
		}
		pivo++;
	}
		for(int i = linha-1; i >= 0; i--){
			indep[i] = (indep[i]/(mat[i][i]));
			
			for(int j = i -1; j >= 0; j--){
				indep[j] = indep[j] - mat[j][i]*indep[i];
			}
		}
}


int main(){
	while(scanf("%d%d%d%d", ev, ev + 1, &d, &at) == 4 && (ev[0] | ev[1] | at | d)){
		build();
		gaussianElimination();
		
		printf("%.1Lf\n", 100*indep[get(ev[0], ev[1])]);
	}
}



