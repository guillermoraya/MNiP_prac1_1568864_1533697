#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "integracio.h"

// N és la funció a integrar (funció de densitat de probabilitat de la 
// distribució Gaussiana).
double N(double* arguments,double x)

{
	double mu=arguments[0];
	double sigma=arguments[1];
	double exponent = -pow(x-mu,2)/(2*sigma*sigma);
	return exp(exponent)/(sigma*sqrt(2*M_PI));
}

double f_1(double x)
{
	return x*x/exp(x);
}

int main(int argc, char **argv)
{
	int n;
	if((argc!=4)&&(argc!=5))
	{
		fprintf(stderr, "ERROR a main: La funció necessita al menys tres arguments; sigma (std), mitjana (mu) i x (valor del qual calculem la probabilitat acumulada). Opcionalment pot rebre'n quatre, on el quart argument seria el nombre d'intervals per als mètodes composts de Simpson i del trapezi.\n\n");
		return -1;
	}
	else if(argc==5)
	{
		n = (int) atof(argv[4]);
	}
	else
	{
		n = 1000000;
	}
  
	double mu = atof(argv[1]);
	double sigma = atof(argv[2]);
	double x = atof(argv[3]);
	
	//We create the arguments array, called "args", in order to call our integration functions later.
	double args[4]={mu,sigma};
	
	printf("PARÀMETRES:\n");
	printf("	Mitjana:             %.8f\n",mu);
	printf("	Desviació estàndard: %.8f\n",sigma);
	printf("	Valor d'x:           %.8f\n",x);
	printf("	Nº d'intervals:      %d\n\n",n);

	printf("Càlcul de la probabilitat acumulada de x=%.8f:\n",x);
	// We'll print the results of calling our integration functions.
	// The arguments passed to each integration function are:
		// N   : the gaussian probability density function, as implemented above our main in this file.
		// args: array of double which contains the arguments we want to pass to "N".
				// In this case, args contains:
					// mu   : desired mean of the gaussian distribution.
					// sigma: desired standard deviation of the gaussian distribution.
		// mu  : first (leftmost) point of the interval over which we want to integrate.
		// x   : the last (rightmost) of the interval over which we want to integrate.
		// n   : the number of intervals to use for the integration method.
		
	// Note that we print 0.5+ the results of the integration.
	// That is because we are calculating the cumulative probability of x for x>mu.
	// Since the cumulative probability of the mean is 0.5, the cumulative probabilty of x>mu
	// Would be 0.5+Integral(probabilityDensityFunction(x)[from mu to x]).
	// (see this assignment's documentation for more details).
	printf("	-Mètode trapezi compost (n=%d): %.8f \n",n,0.5+integrar_trapezi_compost(N,args,mu,x,n));
	printf("	-Mètode Simpson compost (n=%d): %.8f \n",n,0.5+integrar_simpson_compost(N,args,mu,x,n));
	return 0;
}
