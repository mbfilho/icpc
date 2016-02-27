#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
typedef unsigned long long hash;
typedef pair<hash,int> Ponto;
#define B 1097

string words[11000];
int n;
char input[2000];
int size[11000];
hash ha[11000], hb[2000];
hash pot[30];
int pd[2000], pred[2000];
int tam;

void faz(){
	tam = strlen(input);
	memset(pd, 0, sizeof pd);
	
	for(int i = 0; i < tam; ++i){
		for(int k = 0; k < n; ++k){
			if(i + 1 < size[k]) continue;
			
			hash aux = 0;
			if(i-size[k] >= 0) aux = hb[i-size[k]];
			hash seq = hb[i] - aux;

			if(seq == ha[k] && words[k][0] == input[i-size[k]+1] && words[k][size[k]-1] == input[i]){
				
				int ac = i-size[k] >= 0 ? pd[i-size[k]] : 1;
				pd[i] += ac;
				if(ac)
					pred[i] = k;
				if(pd[i] > 1) pd[i] = 2;
			}
		}
	}
}

void print(int i, vector<int>& resp){
	if(i < 0) return;
	print(i - size[pred[i]], resp);
	
	resp.push_back(pred[i]);
}

char linha[2000];
int main(){
	int casos;
	scanf("%d", &casos);
	pot[0] = 1;
	for(int i = 1; i < 30; ++i) pot[i] = B * pot[i-1];
	
	while(casos--){
		scanf("%s%d", input, &n);

		hb[0] = pot[input[0]-'a'+1];
		for(int i = 1; input[i]; ++i)
			hb[i] = hb[i-1] + pot[input[i]-'a'+1];

		for(int i = 0; i < n; ++i){
			scanf("%s", linha);
			words[i] = linha;
			ha[i] = 0;
			
			for(size[i] = 0; linha[size[i]]; ++size[i])
				ha[i] += pot[linha[size[i]] - 'a'+1];
		}
		
		faz();
		if(!pd[tam-1]){
			printf( "impossible\n");
		}else if(pd[tam-1] > 1){
			printf( "ambiguous\n");
		}else{
			vector<int> resp;
			print(tam-1, resp);
			printf( "%s", words[resp[0]].c_str());
			for(int i = 1; i < resp.size(); ++i){
				printf( " %s", words[resp[i]].c_str());
			}
			printf( "\n");
		}
	}
}

