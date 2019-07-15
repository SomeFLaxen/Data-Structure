#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

int t, n, m, x, y;
int g[110][110], deg[110];

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        memset(g, 0, sizeof(g));
        memset(deg, 0, sizeof(deg));
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d", &x, &y);
            --x; --y;
            g[x][y] = 1;
            ++deg[y];
        }
        
        int topocnt = 0;
        queue<int> q;
        for (int i = 0; i < n; ++i)
        {
            if (!deg[i]) q.push(i);
        }
        
        while (!q.empty())
        {
            ++topocnt;
            int u = q.front();
            q.pop();
            
            for (int i = 0; i < n; ++i)
            {
                if (g[u][i])
                {
                    --deg[i];
                    if (!deg[i]) q.push(i);
                }
            }
        }
        
        if (topocnt == n)
        {
            puts("1");
        }
        else
        {
            puts("0");
        }
    }
    
    return 0;
}
