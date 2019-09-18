#问题重述
这次作业略繁琐。需要在一个程序内支持传递运行参数，支持横向相通，纵向相通，扩展子区域(随意联通)。
##问题分析
需要重新构造程序，支持传入参数，有-v-h-a三种，如果是c语言的话，在`main()`函数内加`int argc,char *argv[]`就可以引用传入的参数，其中文件名在`argv[argc-1]`里，程序名在`argv[0]`里，剩下的就是支持的选项。
###只有-v和-h怎么做
-v是上下联通，-h是左右联通。对于环形问题很容易想到的方法就是复制一份接在矩形后边，比如如果需要支持左右联通-h，那么如果原来的矩形是：
>5 6 -3 8 -9 2

则可以往右边复制一份自己接上，变成
>5 6 -3 8 -9 2 | 5 6 -3 8 -9 2

这样就能够包含所有环形结构，不过有个问题，这样求出来会包含长度大于m的结果，而这是不符合题意的。

为了避免这样的问题，从[之前的解法](http://www.cnblogs.com/Forwil/p/3329933.html)很难再改进。

另外-v只需要限制上下区间的距离就能避免不合题意的情况，所以不用特殊处理。
###另一种思路
换一种思路去考虑这个问题就比较容易了，令`sum[i]`表示`sigma{a[j],1<=j<=i}`(其中`sum[0]=0`)，我们的目的是最大化`sum[a]-sum[b]`，即：

>ans=Max{sum[a]-sum[b],0<=b<=a<=m}

从左向右循环，记录最小的`sum[min]`，对于每个`i`，以`a[i]`结尾的最大和的子串就是`sum[i]-sum[min]`，所以只需要不断更新`sum[min]`并计算最大的`sum[i]-sum[min]`就行了。时间复杂度也是`O(N)`。

为了限制长度`i-min<=m`，可以维护一个队列`dd[]`，其中队头是`t`,队尾是`w`。其中`dd[i].value`是其`sum`值，而`dd[i].id`是该`sum`值对应的`i`。

维护队列t-w按`dd[].value`从小到大排序，每次取出`dd[t]`便为需要的`sum[min]`。而每次计算完一个`sum`值需要插入到队尾。

若`dd[t].id`距离当前i大于m，也就是取得了不符合规定的区间，那么该`dd[t]`就不能被使用，显然该值同样不能被大于i的sum使用，所以应该让其出队。

新加入的`sum[i]`到`dd[w]`中需要做一次插入排序，而显然所有大于`sum[i]`的队列里的元素都应该被去除。

所以在一次循环中，每个点只会进入单调队列一次,而且再被插入的时候就会被淘汰。所以维护单调队列不会带来复杂度的增加，仅会带来常数的增加。所以时间复杂度依然为O(n^2\*m)
###扩展子区域 -a如何实现
大概想了一下可以用状态压缩动态规划来做，这样可以得到最优解。

最朴素的想法是用1表示选定格子，0表示不选定格子，一行一行进行递推，只有上面的状态和下面的状态有联通才能转移。

具体一点说，用Dp[i][status]来表示第i行，状态为status的方格，其取到的最优子区域和是多少。用Canappend(status1,status2)来表示两个状态是否能转移。则动态规划方程为:
>Dp[i][status]=Max{Dp[i-1][status_i],status_i in status_all}+cost[i][status]

其中cost[i][status]为取第i行中status的状态所带来的和。

这种想法很简单，不过可惜是错的。

很明显，状态数是不够的，因为单单有0和1表示的信息不够，它只能表示纵向联通的信息，而不能表示横向联通，这样最直接的结果就是终状态的合理性无法判断，所以要正确进行Dp，还需要额外的信息量。

用0-k表示格子的选取情况，其中0表示不取，1-k表示其处于某种联通状态。比如说

>0 1 1 2 0 2 1

表示其中{2,3,7}为一个联通块(不管它到底怎么连的，反正在它上边就是连上了),{4,6}是另一个联通块。这样表示的信息就足够了。

但信息变多带来的是转移的复杂性，一行一行转移所需要处理的状态有点略多。

据说可以用插头Dp来实现简单转移，我看了下[一篇论文](http://wenku.baidu.com/view/a6dce6c76137ee06eff918d1.html)，发现实现起来还是有点微难的。其复杂度上界大概是O((m/2)^m\*n)，在n，m<=32的情况下的运行时间依然是天文数字。所以任务很艰难，在下能力有限，还是没能写出正解来。

另外有一种想法是先把所有联通的正值点抽象成一个点，然后再在这些新的"大点"上作最小生成树，不过这显然没法得到最优解。


###程序
程序只实现了-h -v两种参数。
``` c


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
	printf("%d\n%d\n%d\n%d\n",ai,aj,at,ak);
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

```
###执行方法
运行`./maxsum [options] <filename>`

支持 -h -v -hv 和 -h -v

