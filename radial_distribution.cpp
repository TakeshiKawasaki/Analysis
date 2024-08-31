# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <iostream>
# include <fstream>
# include <time.h>
using namespace std;
#define pi 3.141592653589793238462643
int output(double *a){
  int i;
  char filename[128];   
  sprintf(filename,"gr.dat");
  ofstream File;
  File.open(filename);
  File <<"#"<<" "<< "r"<<" "<<"g(r)"<< endl; 
  for(i=0;i<500;i++)
    File << i*0.01 << " " << a[i]<< endl; 
  File.close(); 
  return 0;
}
int gr(double *x,double *y,int Np,double *a,double rho,double ens){
  int i,j;
  double dx,dy,dr;
  double  L = sqrt(double(Np) / 0.8);
  for(i=0;i<Np;i++)
    for(j=0;j<Np;j++){
      if(i!=j){
	dx=x[i]-x[j];
	if(dx>0.5*L)
	  dx-=L;
	if(dx<-0.5*L)
	  dx+=L;
	
	dy=y[i]-y[j];
	if(dy>0.5*L)
	  dy-=L;
	if(dy<-0.5*L)
	  dy+=L;
	
	dr=sqrt(dx*dx+dy*dy);
	a[int(dr/0.01)]+=1./(2.*pi*dr*0.01*rho*Np*double(ens));          
      } 
    }
  return 0;
}
int main(){
  int Np=300;
  double rho=0.8;
  int ens=100;
  double dt=0.01;
  double a[10000],x[Np],y[Np];
  double dummy;
  char filename[128];   
  int i,j;
  for(i=0;i<1000;i++)
    a[i]=0.0;
  
  ifstream file;
  ofstream File;
  for(i=1;i<ens;i++){
    sprintf(filename,"bina2d_%d.dat",i*100);
    file.open(filename);   
    for(j=0;j<Np;j++){
      file >> x[j] >> y[j] >> dummy; 
      cout << x[j]<<endl;
    }
    file.close();
    gr(x,y,Np,a,rho,ens);
  }
  output(a);
  return 0;
}
