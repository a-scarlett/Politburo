#include <iostream>
#include <cmath>
#include <set>
#include <vector>

using namespace std;

bool check (unsigned int n, unsigned int i)
{
    if (((n&(1<<i))>>i)==1)
        return 1;
    else
        return 0;
}

int main ()
{
    short n, d, e;
    unsigned long long x, c, b;
    cin>>n;
    x=pow(2, n);
    set <unsigned int> m [x];
    vector <unsigned int> a (n);
    for(int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    for (short i=0; i<n; i++)
    {
        c=pow(2, i);
        m[c].insert(c);
        for (short j=i+1; j<n; j++)
        {
            b=pow(2,j);
            m[b+c].insert(b);
        }
    }

    short v=0;
    short w=0;

    for (short k= 3; k < n+1; k++)
    {
        v=0;
        for (short i=0; i<k; i++)
        {
            v+=pow(2,i);
        }
        while(v<=x)
        {
            vector <vector<vector<unsigned int>>> p (k+1, vector<vector<unsigned int>>(k, vector<unsigned int> (5)));

            unsigned int s[k];
            d=0;
            for (short i=0; i<n; i++)
            {
                if (check(v, i))
                {
                    s[d]=i;
                    d++;
                }
            }

            bool alive=1;
            short maxel =k;
            short minpos =0;

            for (short j=0; j<k; j++)
            {
                p[0][j][0]=1;
                p[0][j][1]=k;
                p[0][j][2]=k-j-1;
                p[0][j][3]=0;
                p[0][j][4]=0;
            }

            for(short i=0; i<k; i++)
            {
                for (short j=0; j<k; j++)
                {
                    unsigned long long z=v-pow(2,s[i]);

                    maxel=0;
                    minpos=k;
                    alive=1;

                    for (auto it = m[z].begin();
                            it != m[z].end();
                            it++)
                    {
                        if (!check(*it, s[j]))
                        {
                            alive=0;
                        }
                        d=__builtin_popcount(*it);

                        if(d>maxel)
                        {
                            maxel=d;
                        }

                        e=*it>>(s[j]+1);
                        e=__builtin_popcount(e);
                        if (e<minpos)
                        {
                            minpos=e;
                        }
                    }

                    if(alive==1)
                    {
                        p[i+1][j][0]=1;
                        p[i+1][j][1]=maxel;
                        p[i+1][j][2]=minpos;
                        p[i+1][j][4]=i+1;
                    }
                    else
                    {
                        p[i+1][j][0]=0;
                        p[i+1][j][1]=k;
                        p[i+1][j][2]=k-1;
                        p[i+1][j][4]=i+1;
                    }
                }
            }
            for(short i=0; i<p.size(); i++)
            {
                d=0;
                e=0;
                for(short j=0; j<k; j++)
                {
                    if(p[i][j][0]==1)
                    {
                        d+=a[s[j]];
                    }
                    else
                        e+=a[s[j]];
                }
                if(e>=d)
                {
                    p.erase(p.begin()+i);
                    i--;
                }
            }
            for(short i=0; i<p.size(); i++)
            {
                for(short j=0; j<p[i].size(); j++)
                {

                    bool r=1;
                    if(p[i][j][0]==1)
                    {
                        for(short l=0; l<p.size(); l++)
                        {
                            if(p[i][j][1] > p[l][j][1])
                                r=0;
                            if(p[i][j][1] == p[l][j][1] && p[i][j][2]> p[l][j][2])
                                r=0;
                        }
                    }
                    else
                        r=0;
                    if (r)
                        p[i][j][3]=1;
                    else
                        p[i][j][3]=0;
                }
            }

            for(short i=0; i<p.size(); i++)
            {
                d=0;
                e=0;
                for(short j=0; j<p[i].size(); j++)
                {
                    if (p[i][j][3]==1)
                        d+=a[s[j]];
                    else
                        e+=a[s[j]];
                }

                if (d>e)
                {
                    if (p[i][0][4]==0)
                    {
                        m[v].insert(v);
                    }
                    else
                    {
                        unsigned long long z=v-pow(2,s[p[i][0][4]-1]);
                        for(auto it= m[z].begin(); it!=m[z].end(); it++)
                        {
                            m[v].insert(*it);
                        }
                    }
                }
            }

            short t = (v | (v - 1)) + 1;
            w = t | ((((t & -t) / (v & -v)) >> 1) - 1);
            v=w;

        }
    }

    for(auto it = m[x-1].begin(); it != m[x-1].end(); it++)
    {
        cout<<"Answer: { ";
        for (short i=0; i<n; i++)
        {
            if(check(*it, i))
                cout<< a[i]<<" ";
        }
        cout<<" }"<<endl;
    }
}
