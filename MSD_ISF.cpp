#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
int time_ave=100;
int time_int=38;
double rho= 0.8;
//double q=5.5*5.0;
double pi= 3.14159216;
double Np=300.;
char name[]= "";


int main()
{
  static double x[1000][10000],y[1000][10000],z[1000][10000],t[100000],dx,dy,L,dummy;
  int i,j,k;
  double Corr[1000],ISF[1000],ISFt[1000],COSt[3][1000],COS0[3][1000],SINt[3][1000],SIN0[3][1000],MSD[1000];
  char filename[64];
  ifstream file;
  char filename2[64];
  ofstream file2;

  L=pow(Np/rho,0.5);
  double q=2.0*3.141592/1.0;
  printf("%f\n",L);

  ////////////////////////////input
  
  sprintf(filename,"time_coord.dat");
  file.open(filename);
  
  for(j=0;j<time_ave;j++){     
    printf("%d\n",j);
    for(i=0;i<time_int;i++)
      for(k=0;k<Np;k++)
	file >>t[i] >> x[k][time_int*j+i] >> y[k][time_int*j+i];
  }
  file.close();
    
  for(j=0;j<time_ave;j++){     
    for(k=0;k<3;k++){
      for(i=0;i<time_int;i++){
	COSt[k][i]=0.0;
	COS0[k][i]=0.0;
	SINt[k][i]=0.0;
	SIN0[k][i]=0.0;
      }
    }
    for(i=0;i<time_int;i++){
      for(k=0;k<Np;k++){
	dx=x[k][time_int*j+i]-x[k][time_int*j];
	if(dx>L/2.0)
	  dx-=L;
	if(dx<-L/2.0)
	  dx+=L;
	
	dy=y[k][time_int*j+i]-y[k][time_int*j];
	if(dy>L/2.0)
	  dy-=L;
	if(dy<-L/2.0)
	  dy+=L;
	
	
	ISF[i]+=cos(-q*dx)/((double)time_ave)/Np/2.0;
	ISF[i]+=cos(-q*dy)/((double)time_ave)/Np/2.0;

	MSD[i]+=(dx*dx+dy*dy)/((double)time_ave)/Np;
	
	COSt[0][i]+=cos(-q*x[k][time_int*j+i]);
	COS0[0][i]+=cos(-q*x[k][time_int*j]);
	SINt[0][i]+=sin(-q*x[k][time_int*j+i]);
	SIN0[0][i]+=sin(-q*x[k][time_int*j]);
	
	COSt[1][i]+=cos(-q*y[k][time_int*j+i]);
	COS0[1][i]+=cos(-q*y[k][time_int*j]);
	SINt[1][i]+=sin(-q*y[k][time_int*j+i]);
	SIN0[1][i]+=sin(-q*y[k][time_int*j]);
      }
      for(k=0;k<2;k++)
	ISFt[i]+=(COSt[k][i]*COS0[k][i]+SINt[k][i]*SIN0[k][i])/((double)time_ave)/Np/2.0;
    }
  }
  
  /////////////output
  
  sprintf(filename2,"ISFs.dat");
  file2.open(filename2);
  for(i=1;i<time_int;i++)
         file2 << t[i]-t[0] << "   " << ISF[i]  <<endl;
  
  file2.close();  
  
  sprintf(filename2,"ISFt.dat");
  file2.open(filename2);
  for(i=1;i<time_int;i++){
    file2 << t[i]-t[0] << "   " << ISFt[i]/ISFt[0]  <<endl;
  }
  file2.close();  
    
  sprintf(filename2,"MSD.dat");
  file2.open(filename2);
  for(i=1;i<time_int;i++){
    if(i != 0)
      file2 << t[i]-t[0] << "   " << MSD[i]  <<endl;
  }
  file2.close();  
  return 0;
}
