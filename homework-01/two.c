#include<stdio.h>
#define MAXN 1000
#define MAXM 1000
#define MINV (-(1<< 31 -1))
int n,m,a[MAXN][MAXM];
int maxsum(int N,int M)
{
	int i,j,k,sum,ans;
	int p[M];
	for (i=0;i<M;i++) p[i]=0;
	ans=MINV;
	sum=0;
	for (i=0;i<N;i++)
		{
		for(j=i;j<N;j++)
			{
			sum=0;
			for (k=0;k<M;k++)
				{
				p[k]+=a[j][k];
				if (sum<0)
					sum=0;
				sum+=p[k];
				if (sum>ans)
					ans=sum;
				}
			}
		for (k=0;k<M;k++)p[k]=0;
		}
	return ans;
}
int main()
{
    int i,j;
    freopen("input2.txt","r",stdin);
    freopen("output2.txt","w",stdout);
    scanf("%d,",&n);
    scanf("%d,",&m);
    for(i=0;i<n;i++)
    for(j=0;j<m;j++)
                    {
                    scanf("%d,",&a[i][j]);
                    //printf("%d ",a[i][j]);
                    }
    printf("%d\n",maxsum(n,m));
    return 0;
}
