#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define N 200000
#define pb push_back

char word[N];
vector<int> letras[300];

int main(){
	scanf("%s", word);
	for(int i = 0; i < 300; ++i) letras[i].clear();
	
	for(int i = 0; word[i]; ++i){
		letras[word[i]].pb(i);
	}
	
	int last = -1;
	
	for(int i = 300; ~i; --i){
		int prt = 0;
		while(prt < letras[i].size() && letras[i][prt] < last) ++prt;
		
		while(prt < letras[i].size()){
			last = letras[i][prt];
			printf( "%c", char(i));
			++prt;
		}
	}
	printf("\n");
}


