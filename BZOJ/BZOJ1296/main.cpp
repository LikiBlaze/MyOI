#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
	long long x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
void write(const long long& x)
{
	if (!x)
	{
		putchar('0');
		return;
	}
	char f[100];
	long long tmp = x;
	if (tmp < 0)
	{
		tmp = -tmp;
		putchar('-');
	}
	long long s = 0;
	while (tmp > 0)
	{
		f[s++] = tmp % 10 + '0';
		tmp /= 10;
	}
	while (s > 0)
	{
		putchar(f[--s]);
	}
}
inline double dread()
{
	double r;
	double x=0,t=0;
	int s=0,f=1;
	char c=getchar();
	for (;!isdigit(c);c=getchar())
	{
		if (c=='-')
		{
			f=-1;
		}
		if (c=='.')
		{
			goto readt;
		}
	}
	for (;isdigit(c)&&c!='.';c=getchar())
	{
		x=x*10+c-'0';
	}
	readt:
	for (;c=='.';c=getchar());
	for (;isdigit(c);c=getchar())
	{
		t=t*10+c-'0';
		++s;
	}
	r=(x+t/pow(10,s))*f;
	return r;
}

inline void dwrite(long long x)
{
	if (x == 0)
	{
		putchar(48);
		return;
	}
	int bit[20], p = 0, i;
	for (; x; x /= 10)
		bit[++p] = x % 10;
	for (i = p; i > 0; --i)
		putchar(bit[i] + 48);
}
inline void write(double x,int k)
{
	static int n = pow(10, k);
	if (x == 0)
	{
		putchar('0');
		putchar('.');
		for (int i = 1; i <= k; ++i)
			putchar('0');
		return;
	}
	if (x < 0) putchar('-'), x = -x;
	long long y = (long long) (x * n) % n;
	x = (long long) x;
	dwrite(x), putchar('.');
	int bit[10], p = 0, i;
	for (; p < k; y /= 10)
		bit[++p] = y % 10;
	for (i = p; i > 0; i--)
		putchar(bit[i] + 48);
}

int g[52][52][2600],f[52][2600],col[52][52];
char str[60];

void Max(int &a,int b)
{
	if (b > a)
	{
		a = b;
	}
}
int totN, totM, T;
int main()
{
	totN=read();
	totM=read();
	T=read();
	for (int i = 1; i <= totN; ++i)
	{
		scanf("%s", str + 1);
		for (int j = 1; j <= totM; ++j)
		{
			if (str[j] == '0')
				col[i][j] = 0;
			else
				col[i][j] = 1;
			col[i][j] += col[i][j - 1];
		}
	}
	for (int i = 1; i <= totN; ++i)
		for (int k = 1; k <= totM; ++k)
			for (int j = 1; j <= totM; ++j)
				for (int q = k - 1; q < j; ++q)
					Max(g[i][j][k], g[i][q][k - 1] + max(j - q - (col[i][j] - col[i][q]), col[i][j] - col[i][q]));
	for (int i = 1; i <= totN; ++i)
		for (int j = 1; j <= T; ++j)
			for (int k = 0; k <= min(j, totM); ++k) Max(f[i][j], f[i - 1][j - k] + g[i][totM][k]);
	int ans = 0;
	for (int i = 1; i <= T; ++i)
		Max(ans, f[totN][i]);
	printf("%d", ans);
	return 0;
}