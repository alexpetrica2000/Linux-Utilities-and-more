#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **init_sir(int n){ //initializam vectorul de pointeri la siruri
char **v,*p,s[200];
int i;
v=malloc(n*sizeof(int*)); //alocam linii
for(i=0;i<=n;i++){
	fgets(s,200,stdin); //citim sir
	p=(char*)malloc((strlen(s)+1)*sizeof(char)); //se aloca atata dimensiune cat sirul citit
	strcpy(p,s);
	v[i]=p; //se aloca pe vectorul de pointeri la siruri
}
return v;
}

int test(char *v,int p,int k){ //functie ce testeaza daca un cuvant este format doar din cifre sau nu
int i;
for(i=p;i<k;i++)
	if(v[i]<48 || v[i]>57)
		return 0; //returneaza 0 daca nu contine doar cifre
return 1;	//1 in caz contrar
}

char **codificare(char **v,int n){ //functie de criptare a cuvantului
int k,j,i,r,z,m;
char **s;
for(i=1;i<=n;i++){
	k=strlen(v[i]); //se ia dimensiunea liniei
	r=0;z=0; //r si z s e folosesc pentru pozitia primului si ultimului caracter al unui cuvant
	for(j=1;j<=k;j++){
			if(v[i][j]==' '|| v[i][j]=='\n'){ //in caz de caracterul este spatiu sau '\n'
				z=j;
				if(test(v[i],r,z)==0){ //se testeaza daca cuvantul este format doar din cifre sau nu
					for(m=r+1;m<z;m++)
						v[i][m]=(v[i][m]+v[i][r])%256; //se efectueaza criptarea

				}
			r=z+1; //se retine pozitia 
			}
	}
}
s=v;
return s;
}

int main(){
int n,i;
char **v;
scanf("%d",&n);
v=init_sir(n); //initializare vector de pointeri la siruri	
v=codificare(v,n); //se codifica cuvintele
for(i=1;i<=n;i++)
	printf("%s",v[i]); //se afiseaza
for(i=1;i<=n;i++)
	free(v[i]);
free(v); 
return 0;
}	
