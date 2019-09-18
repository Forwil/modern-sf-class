
#include<stdio.h>

#define MAXN 1000
#define MAXM 1000
#define MINV (-2147483647)
int n,m,a[2*MAXN+2][2*MAXM+2],dd[2*MAXM+2],id[2*MAXM+2];

void input(char *cin)
{
	int i,j;
	freopen(cin,"r",stdin);
	scanf("%d,",&n);
	scanf("%d,",&m);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			{
			scanf("%d",&a[i][j]);
			getchar();
			}
}
int donocir()
{
	int i,j,k,sum,ans;
	ans=MINV;
	int p[MAXM+2];
	for (i=0;i<n;i++)
		{
		for(k=0;k<m;k++) p[k]=0;
		for (j=i;j<n;j++)
			{
			sum=0;
			for (k=0;k<m;k++)
				{
				p[k]+=a[j][k];
				if (sum<0)sum=0;
				sum+=p[k];
				if (sum>ans)
					ans=sum;
				}
			}
		}
	return ans;
}
int docir(int ish,int isv)
{
	int i,k,j,l,p[2*MAXM+2],nn,mm,ans=MINV,sum,t,w,ai,aj,ak,at;
	nn=n; mm=m;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			{
			if(ish)
			{
				a[i][j+m]=a[i][j];
			}
			if(isv)
			{
				a[i+n][j]=a[i][j];
				a[i+n][j+m]=a[i][j];
			}
			}
	if(isv)nn=2*n; else nn=n;
	if(ish)mm=2*m; else mm=m;
	for(i=0;i<n;i++)
		{
		for(k=0;k<mm;k++) p[k]=0;
		for(j=i;j<nn && j<i+n;j++)
			{
			t=0;
			w=0;
			dd[t]=0;
			id[t]=-1;
			sum=0;
			for(k=0;k<mm;k++)
				{
				p[k]+=a[j][k];
				sum+=p[k];
				while(k-id[t] > m)t++;
				if (sum-dd[t] > ans)
					{
					ans=sum-dd[t];
					ai=i;
					aj=j;
					ak=k;
					at=id[t];
					}
				while(sum<dd[w] && w>=t) w=w-1;
				w=w+1;
				dd[w]=sum;
				id[w]=k;
				}
			}
		}
	//printf("%d\n%d\n%d\n%d\n",ai,aj,at,ak);
	return ans;
}
int main(int argc,char *argv[])
{
	int i,j,ish=0,isv=0;
	if (argc==1)
		{
			printf("no input file!\n");
		}
	if (argc==2)
		{
			input(argv[1]);
			printf("%d\n",donocir());
		}
	else
		{
			input(argv[argc-1]);
			for (i=1;i<argc-1;i++)
				for(j=1;argv[i][j]!='\0';j++)
				{
				if (argv[i][j]=='h') ish=1;
				if (argv[i][j]=='v') isv=1;
				}
			printf("%d\n",docir(ish,isv));
		}
    return 0;
}

