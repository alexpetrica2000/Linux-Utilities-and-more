#include <stdio.h>
#include <stdlib.h>

int **init_matrice(int n){ //initializare matrice
int **v,i,cap=3,j; //se declara capacitate initiala cap=3
v=(int**)malloc(n*sizeof(int*)); //se aloca linii
if( v != NULL )
	for(i=0;i<n;i++)
		v[i]=(int*)calloc(cap,sizeof(int)); //se aloca coloanele ,initial cu valoarea 0
int x; //variabila folosita pentru citire
for(i=0;i<n;i++){ 
	j=0;
	scanf("%d",&x); //se citeste un element 
	cap = 3;
	while(x){ //citirea se efectueaza cat timp elementul citit e diferit de 0
		if(j==(cap-1)){ //in caz de se ajunge j parcurge 3 pozitii, se reinitializeaza dimensiunea liniei
			cap=cap+3;
			v[i]=(int*)realloc(v[i],cap*sizeof(int)); //reinitializare prin incrementare cu +3 a capacitatii
		}
		v[i][j++]=x; //se adauga elementul
		scanf("%d",&x); //se citeste urmatorul element
	}
}
return v;
}

float * medie(int **v,int n){ //vector ce calculeaza mediile
float *z;
int j,nr,i;
z=(float*)malloc(n*sizeof(float));
for(i=0;i<n;i++){
	j=0;
	nr=0;
	while(v[i][j] && v[i][j]<11){ //cat timp elementul este diferit de 0 si este de la 1 la 9
		z[i]+=v[i][j++]; //se adauga in vector
		nr++; //se incrementeaza numarul de elemente corespunzatoare
	}
z[i]=(float)z[i]/nr; //se calculeaza media prin raport suma/numar elemente
}	
return z;
}

void ordonare(float *z,int **v,int n){ //se ordoneaza mediile si liniile cu bubblesort
int i,schimb =1;
float k;
int *p;
while(schimb){
schimb=0;
for(i=0;i<n-1;i++)
	if(z[i]<z[i+1]){ //daca o medie este mai mica decat urmatoarea, se schimba atat liniile cat si mediile
		k=z[i];
		z[i]=z[i+1];
		z[i+1]=k;
		p=v[i];
		v[i]=v[i+1];
		v[i+1]=p;
		schimb=1;
	}
}
}

int main(){
int n,j,i;
int **a;
float *b;
scanf("%d",&n);
a=init_matrice(n);	//initializam matricea
b=medie(a,n); 	//initializam vectorul de mediil
ordonare(b,a,n); //ordonam matricea cat si vectorul
for(i=0;i<n;i++){
	j=0;
	printf("%-9.3f ",b[i]); //printam media 
		while(a[i][j] && a[i][j]<11){ 
		printf("%d ",a[i][j]); //printam valoarile matricei
			j++;
 	}
 	printf("\n");
 }
 for(i=1;i<=n;i++)
	free(a[i]);
free(a); 
return 0;
}
