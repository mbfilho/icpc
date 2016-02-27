#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef long long ll;
typedef pair<int,ll> pii;
#define N 1000000
int val[500], tam;
char linha[N], input[N];
bool ap[500];

int main(){
	while(gets(linha)){
		memset(ap, false, sizeof ap);
		
		tam = 0;
		for(int i = 0; linha[i]; ++i){
			if(linha[i] == ' ') continue;
			input[tam++] = linha[i];
		}
		input[tam] = 0;
		
		fr(i, 'a', 1 + 'z') val[i] = i - 'a' + 1;
		
		int prt = 0;
		int soma = 0;
		int op = 1;
		while(prt < tam){
			if(input[prt] == '+' && input[prt+1] == '+'){
				int var = input[prt+2];
				++val[var];
				soma += op * val[var];
				prt += 3;
				ap[var] = true;
			}else if(input[prt] == '-' && input[prt+1] == '-'){
				int var = input[prt+2];
				--val[var];
				soma += op * val[var];
				prt += 3;
				ap[var] = true;
			}else if(input[prt] == '+' || input[prt] == '-') op = input[prt] == '+' ? 1 : -1, ++prt;
			else if(input[prt] >= 'a' && input[prt] <= 'z'){
				ap[input[prt]] = true;
				
				soma += op * val[input[prt]];
				
				if(input[prt+1] == '+' && input[prt+2] == '+') ++val[input[prt]], prt += 3;
				else if(input[prt+1] == '-' && input[prt+2] == '-') --val[input[prt]], prt += 3;
				else ++prt;
			}
		}
		
		printf("Expression: %s\n", linha);
		printf("    value = %d\n", soma);
		fr(i, 'a', 1+'z'){
			if(ap[i]) printf("    %c = %d\n", char(i), val[i]);
		}
	}
}
