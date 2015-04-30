#include "net.h"

#define STEP 10
#define PATT 50
#define	NEUR 100

int array[PATT][NEUR] = {{0}};


float weight[NEUR][NEUR] = {{0}};

int main(){
	srand(time(NULL));

	float sum[PATT] = {0};
	for(int s = 0; s < STEP; s++){
		
		int stableCounter[PATT] = {0};
		float unstableFrac[PATT] = {0};
		generatePatt();
		
		for(int p = 0; p < PATT; p++){
			stableCounter[p] = 0;
			imprintPatt(p);
			
			stableCounter[p] = testPatt(p);
		
			unstableFrac[p] = 1.0 - float(stableCounter[p])/(p+1);
			sum[p] += unstableFrac[p] / float(STEP);
		}
	}	

	// data of 420
//	printf("p\t\tunstable fraction\t\tstable number\n");
	for(int i = 0; i < PATT; i++){;
		printf("%d\t\t%f\t\t%f\n", i+1, sum[i], (1-sum[i])*(i+1));
	}

	return 0;
}

int generatePatt(){
	for(int i = 0; i < PATT; i++)
		for(int j = 0; j < NEUR; j++){
			array[i][j] = rand()%2 * 2 -1;
		}
	return 0;
}

int imprintPatt(int p){
	for(int i = 0; i < NEUR; i++){
		for(int j = 0; j < NEUR; j++){
			weight[i][j] = 0;
			if(i != j){
				for(int k = 0; k < p + 1; k++){
					weight[i][j] += float(array[k][i]) * float(array[k][j]);
				}
				weight[i][j] = weight[i][j] / float(NEUR);
			}
			else{
				weight[i][j] = 0; //no self-coupling
			}
			
		}
	}
	return 0;
}

int testPatt(int p){

	int stable = 0;
	int temp = 0;

	int arrayNext[NEUR] = {0};

	for(int k = 0; k < p + 1; k++){
		
		for(int i = 0; i < NEUR; i++){
			float h[NEUR] = {0};
			for(int j = 0; j < NEUR; j++){
				h[i] += float(weight[i][j] * array[k][j]);
			}

			if(h[i] != 0)
				arrayNext[i] = (h[i] < 0) ? -1 : 1;
			else
				arrayNext[i] = (rand()%2) * 2 -1; // equally +1 or -1
				//arrayNext[i] = array[p][i]; // keep the same
		
		}
		
		for(int i = 0; i < NEUR; i++){
			if(arrayNext[i] != array[k][i]){
				temp = 0;
				break;
			}
			else
				temp = 1;					
		}

		stable += temp;

	}
	
	return stable;
}

