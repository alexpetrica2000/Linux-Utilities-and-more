#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ** sir_text(int m){ //initializare vector de pointeri la siruri
char s[201],*p,**v;
int i;
v=malloc(m*sizeof(int*)); //initializare linii
for(i=0;i<=m;i++){
	fgets(s,201,stdin); //citire sir
	p=(char*)malloc((strlen(s)+1)); //atribuire dimensiune sir
	strcpy(p,s);
	v[i]=p; //Atribuirea sirului in vectorul de siruri la pointeri
}
return v;
}

char * modificare(char *v,char * sep, char *modif,int *z,int n){ //functie ce extrage sirurile cerute dupa fields si le pune intr-un alt vector
char *p,*a;
int j,nr=0,ok=0; // nr se foloseste pentru numarul de aparitii, ok contorizeaza aparitia primului cuvant, presupunem ca nu exista
a=malloc(200*sizeof(char)); //se atribuie dimensiunea sirului, maxim 200 caractere
p=strtok(v,sep); //se elimina delimitatorii folosind strtok 
nr++; //se incrementeaza nr, in p este un cuvant
for(j=1;j<=n;j++)
	if(z[j]==nr){ //daca nr se identifica cu un element din fields
		strcat(a,p); //se concateneaza 
		j=n+1; //se iese din for
		ok=1; //primul cuvant a fost pus, ok deivne 1
	}
p=strtok(NULL,sep); //se trece la urmatorul cuvant
while(p != NULL){
	nr++;
	for(j=1;j<=n;j++)
		if(z[j]==nr && ok==1){ //se verifica daca exista o asociere intre nr si vectorul fields + daca primul cuvant exista sau nu
			strcat(a,modif);//se concateneaza cu delimitatorul out_del
			strcat(a,p); // se concateneaza cu urmatorul cuvant 
			j=n+1;}
	for(j=1;j<=n;j++)
		if(z[j]==nr && ok==0){ //in caz ca primul cuvant nu exista, ok este 0, deci acesta devine "primul cuvant"
			strcat(a,p);//se concateneaza ca si cum ar fi primul cuvant ( fara delimitator )
			j=n+1;
			ok=1; //primul cuvant exista, deci ok devine 1	
		}
	p=strtok(NULL,sep); 
}
return a;
}

int main(){
char **v,del[10],out_del[10],fields[200],*p;
int m,i,n;
fgets(del,10,stdin); //se citeste del
scanf("%d",&n); 
scanf("%s",fields); //se citeste fields
scanf("%s",out_del); //se citeste out_del
scanf("%d",&m);
int a[n]; //vectorul pentru fields
p=strtok(fields,","); //se foloseste strtok pentru a scapa de " , " si a ramane doar cifrele
i=1; // se initializeaza contorul pentru vector
while(p!=NULL){
	a[i++]=atoi(p); //se converteste char numar la int numar
	p=strtok(NULL,",");
	}
v=sir_text(m); //se formeaza vectorul de pointeri la siruri
for(i=1;i<=m;i++)
	v[i]=modificare(v[i],del,out_del,a,n); //se efectueaza modificarile, "cut-ul"
for(i=1;i<=m;i++)
	printf("%s\n",v[i]); //se afiseaza conform functiei "cut" din Linux, cu delimitatorul specificat(out_del)
for(i=1;i<=n;i++)
	free(v[i]);
free(v); 
return 0;
}
