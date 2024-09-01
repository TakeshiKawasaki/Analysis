void cell_list(double L,int Np,double *x,double *y,int M,double Rcell,int (*list)[Pm])
{
  int i,j,k;
  int nx,ny;
  int l,m;
  double dx,dy,r2;
  int (*map)[Npm]=new int[M*M][Npm];
  for(i=0;i<M;i++)
    for(j=0;j<M;j++)
      map[i+M*j][0]=0;
  for(i=0;i<Np;i++){
    nx=f((int)(x[i]/Rcell),M);
    ny=f((int)(y[i]/Rcell),M); 
    for(m=ny-1;m<=ny+1;m++){
      for(l=nx-1;l<=nx+1;l++){
	map[f(l,M)+M*f(m,M)][map[f(l,M)+M*f(m,M)][0] +1]=i;
	map[f(l,M)+M*f(m,M)][0]++;
      }
    }
  }
  for(i=0;i<Np;i++){
    list[i][0]=0;
    nx = f((int)(x[i]/Rcell),M);
    ny = f((int)(y[i]/Rcell),M);
    for (k=1; k<=(map[nx+M*ny][0]); k++){
      j = map[nx+M*ny][k];
      if(j>i){
	dx =x[i] - x[j];
	dy =y[i] - y[j];
	if(dx<-L/2.0)
	  dx+=L;
	else if(dx> L/2.0)
	  dx-=L;
	if(dy<-L/2.0)
	  dy+=L;
	else if(dy> L/2.0)
	  dy-=L;
	r2 = dx*dx + dy*dy;	
	if(r2<Rcell*Rcell){
	  list[i][0]++;
	  list[i][list[i][0]]=j;
	}
      }
    }
  }
  delete []map;
}
