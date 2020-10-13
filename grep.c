#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char **init_sir(int n){ //Initializare vector de pointeri la siruri
char **v,*p,s[200];
int i;
v=malloc(n*sizeof(int*)); //Alocare linii
for(i=0;i<=n;i++){
	fgets(s,200,stdin); //Citire siruri
	p=(char*)malloc((strlen(s)+1)*sizeof(char)); 
	strcpy(p,s);
	v[i]=p; //Alocarea sirurlui in vector
}
return v;
}
	
int *numar_aparitii(char **v,char *sir,int n){ //Vector ce numara aparitiile sirului de modificat pentru fiecare linie
int *nr_aparitii,i;
char *p,*w;
nr_aparitii=malloc(100*sizeof(int)); //Alocarea acestuia (se considera maxim 100 linii)
for(i=1;i<=n;i++){
	w=strdup(v[i]); //Creare copie auxiliara pentru sir;
	p=strstr(w,sir); //Cautarea sirului de modificat
	while(p!= NULL){
		nr_aparitii[i]++; //In caz de aparitie, se incrementeaza vector nr_aparitii
		strcpy(p,p+strlen(sir)); // Se trece peste cuvantul aflat
		p=strstr(p,sir); //Se cauta o eventuala noua aparitie a sirului de modificat 
	}
}
return nr_aparitii;
}

char *my_replace(char *s, char *s1, char *s2){ //Functie de modifcare a sirului (se efectueaza grepul propriu-zis)
char *p;
char *s3=(char*)malloc(200*(sizeof(char))); //Se aloca auxiliar, se mentioneaza dimensiunea maxima a unei linii de 200 caractere 
p=strstr(s,s1); // Se cauta sirul de modificat
char aux[]="\e[0;31m"; //Sir de caractere ce ajuta efectuarea colorarii sirului cerut (culoarea rosie in acest caz)
char aux2[]="\e[m"; //Acest sir de asemenea ajuta la efectuarea colorarii
while(p!= NULL){
	strncat(s3,s,strlen(s)-strlen(p)); //Se concateneaza in s3 caracterele pana in aparitia sirului de modificat
	strcat(s3,aux); // Se concateneaza cu prima parte ce ajuta la colorare
	strcat(s3,s2); //Se concateneaza la loc sirul de modificat
	strcat(s3,aux2); //Se concateneaza a doua parte pentru efectuarea colorarii 
	strcpy(s,p+strlen(s1)); //Cuvantul a fost modificat conform functiei grep, se sare peste el pentru a cauta alte aparitii
	p=strstr(s,s1); //Se cauta alte aparitii
} 	
strcat(s3,s); //se concateneaza cu un posibil "rest" ramas

return s3;
}

int main(){
char sir[31],**v;
int n,i,*numarator;
fgets(sir,31,stdin); //citire sir de modificat 
sir[strlen(sir)-1]='\0'; //se elimina '\n' generat de fgets
scanf("%d",&n);
v=init_sir(n); // initializare vector de pointeri la siruri 
numarator=numar_aparitii(v,sir,n);
for(i=1;i<=n;i++){
	if(numarator[i] != 0){ //In caz de existenta a cuvantului de modificat(pe o linie)
		v[i]=(char*)realloc(v[i],(strlen(v[i])+numarator[i]*10)*sizeof(char)); // Se realoca 
		v[i]=my_replace(v[i],sir,sir); // Se inlocuieste cuvantul cu cuvantul colorat
		printf("%s",v[i]); //Se afiseaza
	}
}
for(i=1;i<=n;i++)
	free(v[i]);
free(v); 
return 0;
}