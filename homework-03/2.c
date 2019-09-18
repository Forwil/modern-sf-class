    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #define MAXN 2000000000
    #define ARRAY 40
    #define BLOCK 50
    #define SURROUND 150
    FILE *fin,*fout;
    const long int dx[5]={0,-1,0,1,0};
    const long int dy[5]={0,0,1,0,-1};
	int used[ARRAY][ARRAY], ll, rr;
    void ArgCheck(long int argc, char * argv[],long int count[]);
    void Error(char *s);
    void Input(long int *n,long int *m,long int a[][ARRAY]);
    long int GetInt(char *s,char **end);
    void Work(long int n,long int m,long int a[][ARRAY],long int count[]);
    long int Rectangle(long int n,long int m,long int LimN,long int LimM,long int a[][ARRAY]);
    long int MonoList(long int x[],long int len,long int Lim);
    long int InterConnect(long int n,long int m,long int a[][ARRAY]);
    long int Partition(long int n,long int m,long int a[][ARRAY],long int fixed[][ARRAY],long int part[][ARRAY],long int value[]);
    long int DFS(long int i,long int j,long int num,long int n,long int m,long int a[][ARRAY],long int fixed[][ARRAY],long int part[][ARRAY]);
    void SPFA(long int n,long int m,long int bx,long int by,long int a[][ARRAY],long int fixed[][ARRAY],long int dis[][ARRAY],long int prex[][ARRAY],long int prey[][ARRAY]);
    void GetContour(long int n,long int m,long int fixed[][ARRAY],long int part[][ARRAY],long int conx[][SURROUND],long int cony[][SURROUND],long int ncon[BLOCK]);
    void TestOut(long int a[][ARRAY],long int l1,long int l2);
    long int main(long int argc, char * argv[])
    {
        long int i,j,n,m,a[ARRAY][ARRAY],count[3];
		ArgCheck(argc,argv,count);
		Input(&n,&m,a);
		Work(n,m,a,count);
		return 0;
    }
    void ArgCheck(long int argc, char * argv[],long int count[])
    {
        if(argc>5)
            Error("too many arguments");
        if(argc<2)
            Error("too few arguments");
        long int i;

        count[0]=count[1]=count[2]=0;
        for(i=1;i<argc-1;i++)
        {
            if(argv[i][0]!='-' || (argv[i][1]!='a' && argv[i][1]!='h' && argv[i][1]!='v') || argv[i][2]!='\0')
                Error("invalid argument");
            else if(argv[i][1]=='a')
                count[0]++;
            else if(argv[i][1]=='h')
                count[1]++;
            else if(argv[i][1]=='v')
                count[2]++;
        }

        if(count[0]>1 || count[1]>1 || count[2]>1)
            Error("repeated arguments");

        fin=fopen(argv[argc-1],"r");
        if(fin==NULL)
            Error("no such file");
    }
    void Error(char *s)
    {
        printf("%s\n",s);
        exit(1);
    }
    void Input(long int *n,long int *m,long int a[][ARRAY])
    {
        long int i,j;
        char s[500],*ptr,*endptr;

        fscanf(fin,"%s",s);
        ptr=s;
        *n=GetInt(ptr,&endptr);
        if(endptr[0]!=',' || endptr[1]!='\0')
            Error("invalid characters appears");
        if(*n>32)
            Error("n is too big");
        if(*n<1)
            Error("n must be positive");
        fscanf(fin,"%s",s);
        ptr=s;
        *m=GetInt(ptr,&endptr);
        if(endptr[0]!=',' || endptr[1]!='\0')
            Error("invalid characters appears");
        if(*m>32)
            Error("m is too big");
        if(*m<1)
            Error("m must be positive");
        for(i=1;i<=*n;i++)
        {
            fscanf(fin,"%s",s);
            ptr=s;
            for(j=1;j<=*m;j++)
            {
                endptr=NULL;
                a[i][j]=GetInt(ptr,&endptr);
                if(endptr[0]!=',' && endptr[0]!='\0')
                    Error("invalid characters appears");
                if(a[i][j]>2000000)
                    Error("element is too big");
                if(a[i][j]<-2000000)
                    Error("element is too small");

                ptr=endptr+1;
            }
            if(endptr[0]!='\0')
                Error("invalid end of line");
        }
    }
    long int GetInt(char *s,char **end)
    {
        long int x;
        x=strtol(s,end,10);
        if(*end==s)
            Error("not long integer");
        if(*end[0]!=',' && *end[0]!='\0')
            Error("invalid character appears");
        return x;
    }
    void Work(long int n,long int m,long int a[][ARRAY],long int count[])
    {
        long int ans,i,j;
		for(i=0;i<=n;i++)
            memset(used[i],0,sizeof(used[0][0])*(m+1));

		fout=fopen("data","w");

        if(count[0]==0 && count[1]==0 && count[2]==0)
        {
            ans=Rectangle(n,m,n,m,a);
            fprintf(fout,"%d\n",ans);
        }
        else if(count[0]==0 && count[1]==1 && count[2]==0)
        {
            for(i=1;i<=n;i++)
                memmove(a[i]+m+1,a[i]+1,sizeof(long int)*m);
            ans=Rectangle(n,2*m,n,m,a);
            fprintf(fout,"%d\n",ans);
        }
        else if(count[0]==0 && count[1]==0 && count[2]==1)
        {
            for(i=1;i<=n;i++)
                memmove(a[i+n],a[i],sizeof(long int)*m);
            ans=Rectangle(2*n,m,n,m,a);
            fprintf(fout,"%d\n",ans);
        }
        else if(count[0]==0 && count[1]==1 && count[2]==1)
        {
            for(i=1;i<=n;i++)
            {
                memmove(a[i]+m+1,a[i]+1,sizeof(long int)*m);
                memmove(a[i+n],a[i],sizeof(long int)*m);
                memmove(a[i+n]+m+1,a[i]+1,sizeof(long int)*m);
            }
            ans=Rectangle(2*n,2*m,n,m,a);
            fprintf(fout,"%d\n",ans);

        }
        else if(count[0]==1)
        {
            ans=InterConnect(n,m,a);
            fprintf(fout,"%d\n",ans);
        }

		fprintf(fout, "%d %d\n", n, m);
		for(i = 1; i <= n; i ++)
		{
			for(j = 1; j <= m; j++)fprintf(fout, "%d ", a[i][j]);
			fprintf(fout, "\n");
		}
		for(i = 1; i <= n; i ++)
		{
			for(j = 1; j <= m; j++)fprintf(fout, "%d ", used[i][j]);
			fprintf(fout, "\n");
		}
		fclose(fout);
    }
    long int Rectangle(long int n,long int m,long int LimN,long int LimM,long int a[][ARRAY])
    {
        long int sum[2*ARRAY][2*ARRAY],sum1[2*ARRAY],minN,ans,temp,i,j,k,tl,tr,tu,td,tx,ty;
        for(i=0;i<=n;i++)
            memset(sum[i],0,sizeof(long int)*(m+1));

        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        ans=-MAXN;
        for(i=1;i<=n;i++)
        {
            if(i+LimN-1<n)
                minN=i+LimN-1;
            else
                minN=n;
            
            for(j=i;j<=minN;j++)
            {
                for(k=0;k<=m;k++)
                    sum1[k]=sum[j][k]-sum[i-1][k];

                temp=MonoList(sum1,m,LimM);
                if(temp>ans)
				{
                    ans=temp;
					tl = ll;
					tr = rr;
					tu = i;
					td = j;
				}
            }

        }
		for(i = tu; i<= td; i ++)
		{
			for(j = tl; j<= tr; j ++)
			{
				tx = i;
				ty = j;
				if(tx > LimN)tx -= LimN;
				if(ty > LimM)ty -= LimM;
				used[tx][ty] = 1;
			}
		}
        return ans;
    }
    long int MonoList(long int x[],long int len,long int Lim)
    {
        long int head,tail,ans,temp,i;
        long int list[2*ARRAY];

        list[1]=0;
        head=1;
        tail=1;
        if(x[list[tail]]>=x[1])
            list[tail]=1;
        else
            list[++tail]=1;

        ans=x[1];
        for(i=2;i<=len;i++)
        {
            while(i-list[head]>Lim)head++;
            temp=x[i]-x[list[head]];
            if(temp>ans)
			{
				ans=temp;
				ll = list[head] + 1;
				rr = i;
			}
            while(tail>=head && x[list[tail]]>=x[i])
                tail--;
            list[++tail]=i;
        }
        return ans;
    }
    /*void TestOut(long int a[][ARRAY],long int l1,long int l2)
    {
        long int i,j;
        for(i=1;i<=l1;i++)
        {
            for(j=1;j<=l2;j++)
                printf("%6d ",a[i][j]);
            printf("\n");
        }
        printf("\n");
    }*/
    long int InterConnect(long int n,long int m,long int a[][ARRAY])
    {
        long int i,j,k,num,max,bx,by,ex,ey,k1,k2,d,nowx,nowy,temp,ans,tx,ty,tt;
        long int dis[ARRAY][ARRAY],fixed[ARRAY][ARRAY],part[ARRAY][ARRAY];
        long int value[BLOCK],prex[ARRAY][ARRAY],prey[ARRAY][ARRAY];
        long int conx[BLOCK][SURROUND],cony[BLOCK][SURROUND],ncon[BLOCK];

        for(i=1;i<=n;i++)for(j=1;j<=m;j++)
            if(a[i][j]>=0)
                fixed[i][j]=1;
            else 
                fixed[i][j]=0;

        while(1)
        {
            num=Partition(n,m,a,fixed,part,value);
            GetContour(n,m,fixed,part,conx,cony,ncon);
            max=-MAXN;
            for(i=1;i<=num-1;i++)
                for(k1=1;k1<=ncon[i];k1++)
                {
                    SPFA(n,m,conx[i][k1],cony[i][k1],a,fixed,dis,prex,prey);
                    for(j=i+1;j<=num;j++)
                        for(k2=1;k2<=ncon[j];k2++)
                        {
                            d=dis[conx[j][k2]][cony[j][k2]]-a[conx[j][k2]][cony[j][k2]];
                            if(d>max && value[part[conx[i][k1]][cony[i][k1]]]+d>=0 && value[part[conx[j][k2]][cony[j][k2]]]+d>=0)
                            {
                                max=dis[conx[j][k2]][cony[j][k2]]-a[conx[j][k2]][cony[j][k2]];
                                bx=conx[i][k1];
                                by=cony[i][k1];
                                ex=conx[j][k2];
                                ey=cony[j][k2];
                            }
                        }
                }

            if(max==-MAXN)break;

            SPFA(n,m,bx,by,a,fixed,dis,prex,prey);
            nowx=ex;
            nowy=ey;
            while(nowx!=0 && nowy!=0)
            {
                fixed[nowx][nowy]=1;
                temp=nowx;
                nowx=prex[nowx][nowy];
                nowy=prey[temp][nowy];
            }
        }
        ans=-MAXN;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(a[i][j]>ans)
				{
                    ans=a[i][j];
					tx = i;
					ty = j;
				}
		used[i][j] = 1;
        for(i=1;i<=num;i++)if(value[i]>ans)
		{
			ans=value[i];
			tt = i;
		}
		for(i = 1; i <= n; i ++)
			for(j = 1; j <= m; j++)
				if(part[i][j] == tt)
					used[i][j] = 1;
        return ans;
    }
    void SPFA(long int n,long int m,long int bx,long int by,long int a[][ARRAY],long int fixed[][ARRAY],long int dis[][ARRAY],long int prex[][ARRAY],long int prey[][ARRAY])
    {
        long int i,j,h,t,x,y,tx,ty,sx[100000],sy[10000],in[100][100];
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                dis[i][j]=-MAXN;
                in[i][j]=0;
                prex[i][j]=0;
                prey[i][j]=0;
            }
        sx[1]=bx;
        sy[1]=by;
        dis[bx][by]=0;
        h=t=1;
        in[bx][by]=1;

        while(h<=t)
        {
            x=sx[h];
            y=sy[h];
            for(i=1;i<=4;i++)
            {
                tx=x+dx[i];
                ty=y+dy[i];
                if(tx>=1 && tx<=n && ty>=1 && ty<=m && 
                    ((fixed[x][y]==0 && (tx!=bx || ty!=by)) || (x==bx && y==by && fixed[tx][ty]==0)) &&
                    dis[x][y]+a[tx][ty]>dis[tx][ty])
                {
                    dis[tx][ty]=dis[x][y]+a[tx][ty];
                    prex[tx][ty]=x;
                    prey[tx][ty]=y;
                    if(in[tx][ty]==0)
                    {
                        in[tx][ty]=1;
                        t++;
                        sx[t]=tx;
                        sy[t]=ty;
                    }
                }
            }
            in[x][y]=0;
            h++;
        }
    }
    void GetContour(long int n,long int m,long int fixed[][ARRAY],long int part[][ARRAY],long int conx[100][150],long int cony[100][150],long int ncon[100])
    {
        long int i,j,k,p,num;
        
        for(i=0;i<BLOCK;i++)
        {
            memset(conx[i],0,sizeof(long int)*SURROUND);
            memset(cony[i],0,sizeof(long int)*SURROUND);
        }
        memset(ncon,0,sizeof(long int)*BLOCK);

        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(fixed[i][j]==1)
                {
                    p=part[i][j];
                    for(k=1;k<=4;k++)
                    {
                        if(i+dx[k]>=1 && i+dx[k]<=n && j+dy[k]>=1 && j+dy[k]<=m && fixed[i+dx[k]][j+dy[k]]==0)
                        {
                            ncon[p]++;
                            conx[p][ncon[p]]=i;
                            cony[p][ncon[p]]=j;
                            break;
                        }

                    }
                }
    }
    long int Partition(long int n,long int m,long int a[][ARRAY],long int fixed[][ARRAY],long int part[][ARRAY],long int value[])
    {
        long int i,j,num;
        for(i=1;i<=n;i++)
            memset(part[i],0,sizeof(long int)*(m+1));

        num=0;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(fixed[i][j]==1 && part[i][j]==0)
                {
                    num++;
                    value[num]=DFS(i,j,num,n,m,a,fixed,part);
                }
        return num;
    }
    long int DFS(long int i,long int j,long int num,long int n,long int m,long int a[][ARRAY],long int fixed[][ARRAY],long int part[][ARRAY])
    {
        if(part[i][j]!=0 || fixed[i][j]==0)return 0;
        long int sum=0;
        part[i][j]=num;
        if(i-1>=1)sum+=DFS(i-1,j,num,n,m,a,fixed,part);
        if(i+1<=n)sum+=DFS(i+1,j,num,n,m,a,fixed,part);
        if(j-1>=1)sum+=DFS(i,j-1,num,n,m,a,fixed,part);
        if(j+1<=m)sum+=DFS(i,j+1,num,n,m,a,fixed,part);
        return sum+a[i][j];
    }
