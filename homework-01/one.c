#include<stdio.h>
#define MAXN 100000
#define MINV (-(1<< 31 -1))
int maxsum(int p[],int size)
{
	int i,sum,ans;
	ans=MINV;
	sum=0;
	for (i=0;i<size;i++)
	{
		if (sum<0)
			sum=0;
		sum+=p[i];
		if (sum>ans)
			ans=sum	;	
	}
	return ans;
}
int main()
{
    int i,n,p[MAXN];
    freopen("input1.txt","r",stdin);
    freopen("output1.txt","w",stdout);
    scanf("%d,",&n);
    for(i=0;i<n;i++)
                    scanf("%d,",&p[i]);
    printf("%d\n",maxsum(p,n));
    return 0;
}
