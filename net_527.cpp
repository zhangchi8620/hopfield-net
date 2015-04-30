#include "net.h"

#define STEP 1
#define COUNTER 50
#define NEUR 100
#define PATT 50

int array[PATT][NEUR] = {{0}};

int arrayBasin[NEUR] = {0};
int arrayBasinNext[NEUR] = {0};

float weight[NEUR][NEUR] = {{0}};

float basin[PATT][PATT] = {{0}};

int main(){
	srand(time(NULL));

	for(int s = 0; s < STEP; s++){

		generatePatt();
		
		for(int p = 0; p < PATT; p++){
			imprintPatt(p);
			testPatt(p);
		}
	}	

	// data of 527
	for(int i = 0; i < PATT; i++)
		for(int j = 0; j < PATT; j++)
			if( (i+1)%2 ==0)		
				printf("%d\t\t%d\t\t%f\n", i+1, j+1, basin[i][j]);

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
	for(int j = 0; j < PATT; j++)
		basin[p][j] = 0;

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
				basin[p][k] = 0;		//if unstable
				break;
			}
			else{
				temp = 1;	
			}
				
		}

		stable += temp;
		bool converge = true;
		// if stable
		if(temp){
			for(int step = 0; step < COUNTER; step++){
				int *a = NULL;
				a = genRand(NEUR);

				for(int j = 0; j < PATT; j++){

					// initialize network to current pattern k 
					for(int i = 0; i < NEUR; i++)
						arrayBasin[i] = array[k][i];
					// flip
					for(int f = 0; f <= j; f++)
						arrayBasin[a[f]] *= -1;
	
					// update network
					updateNetwork(10);
				
					
					// check if equal
					for(int i = 0; i < NEUR; i++){
						if (arrayBasin[i] !=  array[k][i]){
							basin[p][j] += 1;
							goto label;
						}
					}
				
				}
				label: converge = false; 

				if (converge)
					basin[p][PATT] += 1;
				free(a);
			}

		}
	}
	
	for(int m = 0; m < PATT; m++)
	    basin[p][m] = basin[p][m] / COUNTER;
	return stable;
}


 //Generate random # from 0 - 899
int *genRand(int number){
	
	int *a = NULL;
	a =(int *)malloc(sizeof(int)*number);

	for(int i = 0; i < number; i++){
		a[i] = i;
	}
	
	for(int i = number - 1; i > 0; i--){
		swap(a[i], a[rand()%i]);
	}

	return a;
}

bool updateNetwork(int iteration){
	int *a = NULL;
	a = genRand(NEUR);
	bool change = true;

	for(int iter = 0; iter < iteration; iter++){
		for(int i = 0; i < NEUR; i++){
			float h = 0;
		
			for(int j = 0; j < NEUR; j++)
				h += arrayBasin[j] * weight[a[i]][j];
		
			if(h<0)
				arrayBasinNext[a[i]] = -1;
			else if(h>0)
				arrayBasinNext[a[i]] = 1;
			else
				arrayBasinNext[a[i]] = rand()%2 * 2 - 1;

		}

		for(int i = 0; i < NEUR; i++){
			if (arrayBasinNext[a[i]] != arrayBasin[a[i]]){
				arrayBasin[a[i]] = arrayBasinNext[a[i]];
				change = false;
			}
			else
				change = true;

		}

		if(change)
			return change;
	}
	
	return change;
}
