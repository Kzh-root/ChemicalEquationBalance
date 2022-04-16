/*
Chemical Equation Balancer
HiJ1m 2017.10.6
*/
#include<bits/stdc++.h>
using namespace std;
inline int gcd(int x,int y){
    return x%y==0?y:gcd(y,x%y);
}
inline int lcm(int x,int y){
    return x*y/gcd(x,y);
}
struct frac{                            //������ 
    int a,b;
    void reduce(){
        int x=gcd(a,b);
        a/=x,b/=x;
    };
    frac operator = (int x){
        a=x,b=1;
        return *this;
    };
    frac operator = (const frac x){
        a=x.a,b=x.b;
        reduce();
        return *this;
    };
    frac operator + (const frac x){
        return (frac){b*x.a+a*x.b,b*x.b};
    };
    frac operator - (const frac x){
        return (frac){a*x.b-b*x.a,b*x.b};
    };
    frac operator * (const frac x){
        return (frac){a*x.a,b*x.b};
    };
    frac operator / (const frac x){
        return (frac){a*x.b,b*x.a};
    };
    bool operator < (const frac x){
        return a*x.b<b*x.a;
    };
    bool operator == (const frac x){
        return a*x.b==b*x.a;
    };
    void print(){
        if(b==1)printf("%d\n",a);
        else printf("%d/%d\n",a,b);
    };
};        
inline frac Abs(frac x){
    int p=x.a>0?x.a:-x.a,q=x.b>0?x.b:-x.b;
    return (frac){p,q};
}                                            
char s[55];
int fun[55][55];
int Map[27][27];                        //�ֶ�MAP 
frac M[55][55];                            //������
frac ans[55];                            //�� 
int Ans[55];                            //������ 
int cnt,c1,c2,flag=1,N,K;                //cnt��Ԫ�أ�c1����Ӧ�c2���� ��δ֪���������� 
char mat[55][55];                        //�洢���ʵ����� 
void print(){
    printf("%d %d\n",N,K);
    for(int i=1;i<=K;i++){
        for(int j=1;j<=N+1;j++)
            printf("%d ",M[i][j].a);
        printf("\n");
    }
    printf("\n");
}
inline int getint(int pos){                //���� 
    pos++;
    if(s[pos]>='a'&&s[pos]<='z')pos++;
    if(s[pos]<'0'||s[pos]>'9')return 1;                                //û������1 
    else {
        int x=0;
        while(s[pos]>='0'&&s[pos]<='9')x=x*10+s[pos]-'0',pos++;        //��Ԫ�غ�������� 
        return x;
    }
}
inline void scan(int l,int r){             //��������    
    c2++;
    for(int i=0;i<=r-l;i++)mat[c2][i]=s[l+i];        //����Ԫ�ص�����
    if(flag==1)c1++;                                //ͳ��һ�·�Ӧ������
    int tmp=1;                                        //tmp��С���ű��� 
    for(int i=l;i<=r;i++){
        if(s[i]==')')tmp=1;                                                        
        if(s[i]=='('){
            int j=i+1;while(s[j]!=')')j++;            //��������ŵķ�Χ 
            tmp=getint(j);                            //��")"�ұߵ����� 
        }
        if(s[i]>='A'&&s[i]<='Z'){                    //����Ԫ�� 
            int x=s[i]-'A'+1,y=0;
            if(s[i+1]>='a'&&s[i]<='z')                //��һ����һ����ĸ�Ļ��������� 
                y=s[i+1]-'a'+1;
            if(!Map[x][y])Map[x][y]=++cnt;            //����
            fun[Map[x][y]][c2]+=flag*getint(i)*tmp;    //����������������Ԫ�������Ž���������꣨map[x][y]��c2�� 
        }
    } 
}

void printF()
{
	for(int i=1;i<=cnt;i++)
    {
    	for(int j=1;j<=c2+1;j++)
    		cout<<M[i][j].a<<"/"<<M[i][j].b<<" ";
    	cout<<endl;
	}  
	cout<<endl;
}

inline bool Solve(){
/*for(int i=1;i<=cnt;i++)
    {
    	for(int j=1;j<=c2+1;j++)
    		cout<<fun[i][j]<<" ";
    	cout<<endl;
	}     */               //�ⷽ��  ������ ��cnt����c2+1,c2+1�г���ȫ0�� 
    ans[c2]=1;                                    //�����һ����Ϊ1
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=c2;j++)
            M[i][j]=fun[i][j];
    }
    for(int i=1;i<=cnt;i++)
        M[i][c2].a=-M[i][c2].a;            //�Ƶ����� 
   /* for(int i=1;i<=cnt;i++)
    {
    	for(int j=1;j<=c2+1;j++)
    		cout<<M[i][j].a<<"/"<<M[i][j].b<<" ";
    	cout<<endl;
	}  */
    //��˹��Ԫ���� 
    N=c2-1,K=cnt;
    cout<<N<<endl;
    for(int k=1;k<=N;k++){
    	
        frac maxm=(frac){-1,1};int maxi;
        for(int i=k;i<=K;i++)
            if(maxm<Abs(M[i][k]))
                maxm=Abs(M[i][k]),maxi=i,cout<<maxm.a<<"/"<<maxm.b<<endl;
        if(maxm==(frac){0,1})
            return false;
        if(maxi!=k)
            for(int j=1;j<=N+1;j++){
                swap(M[k][j],M[maxi][j]);
            }
        frac tmp=M[k][k];
        for(int j=1;j<=N+1;j++)
            M[k][j]=M[k][j]/tmp;
        for(int i=k-1?1:2;i<=K;i++){
            if(i==k)continue;
            frac tmp=M[i][k];
            for(int j=1;j<=N+1;j++)
                M[i][j]=M[i][j]-tmp*M[k][j];
        }
        printF();
    }
    return true;
}
int main()
{
	freopen("in.txt","r",stdin);
//    printf("Chemical Equation Balancer\n");
//    printf("\nEnter the chemical equation:\n");
    scanf("%s",s);
    int lst=0;
    for(int i=1;i<strlen(s);i++){
        if(i==strlen(s)-1)scan(lst,i);                    
        if(s[i]=='+'||s[i]=='=')scan(lst,i-1),lst=i+1;     
        if(s[i]=='=')flag=-1;                            //�Ⱥź����ϵ���为 
    }
    
    if(Solve())
        for(int i=1;i<=c2-1;i++)
            ans[i]=M[i][N+1];
    else printf("No Solution");
    //printF();
   /* for(int i=1;i<=cnt;i++)
    {
    	for(int j=1;j<=c2;j++)
    		cout<<M[i][j].a<<"/"<<M[i][j].b<<" ";
    	cout<<endl;
	}  */
    /*for(int i=1;i<=c2-1;i++)
    	cout<<ans[i].a<<"/"<<ans[i].b<<endl;*/
    int tmp=lcm(ans[1].b,ans[2].b);
    for(int i=3;i<=c2;i++)tmp=lcm(tmp,ans[i].b);
    for(int i=1;i<=c2;i++)Ans[i]=ans[i].a*tmp/ans[i].b;    //ȡ��ĸLcm���ѷ��������� 
    for(int i=1;i<=c2;i++)
    {
        if(Ans[i]>1)printf("%d",Ans[i]);
        for(int j=0;j<strlen(mat[i]);j++)
            printf("%c",mat[i][j]);
        if(i==c2)return 0;
        else if(i==c1)printf("=");
        else printf("+");
    }
}
