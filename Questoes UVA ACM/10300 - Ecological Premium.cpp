#include <cstdio>
using namespace std;

int main(){
	int casos, fazend, area, eco, ani;
	int result;

	scanf( "%d", &casos );

	while( casos-- ){
		result = 0;
		scanf( "%d", &fazend );
		while( fazend-- ){
			scanf( "%d %d %d", &area, &ani, &eco );
			result += ( area * eco );
		}
        printf( "%d\n", result );
	}
}
