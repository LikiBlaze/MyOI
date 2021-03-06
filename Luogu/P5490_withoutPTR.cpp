#include <bits/stdc++.h>
#define INF 999999999
#define lch (nowX << 1)
#define rch (nowX << 1 | 1)

using namespace std;

inline long long read()
{
	long long x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
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
void write(const long long &x)
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

const long long maxN = 1000090;

struct Line
{
	long long l, r;
	long long h;
	short mark;
} lines[maxN << 1];
bool operator<(Line a, Line b)
{
	return a.h < b.h;
}
struct Node
{
	long long l, r;
	long long sum;
	long long len;
} nodes[maxN << 2];

long long X[maxN << 1];

void build(long long nowX, long long L, long long R)
{
	nodes[nowX].l = L;
	nodes[nowX].r = R;
	nodes[nowX].len = 0;
	nodes[nowX].sum = 0;
	if (L == R)
	{
		return;
	}
	long long Mid = (L + R) >> 1;
	build(lch, L, Mid);
	build(rch, Mid + 1, R);
}
void pushup(long long nowX)
{
	if (nodes[nowX].sum)
	{
		nodes[nowX].len = X[nodes[nowX].r + 1] - X[nodes[nowX].l];
	}
	else
	{
		nodes[nowX].len = nodes[lch].len + nodes[rch].len;
	}
}
void update(long long nowX, long long L, long long R, long long C)
{
	if (X[nodes[nowX].r + 1] <= L || X[nodes[nowX].l] >= R)
	{
		return;
	}
	if ((L <= X[nodes[nowX].l]) && (X[nodes[nowX].r + 1] <= R))
	{
		nodes[nowX].sum += C;
		pushup(nowX);
		return;
	}
	update(lch, L, R, C);
	update(rch, L, R, C);
	pushup(nowX);
}

long long totN;
long long totL;
long long totANS;

int main()
{
	totN = read();
	for (int i = 1, Xa, Ya, Xb, Yb; i <= totN; ++i)
	{
		Xa = read();
		Ya = read();
		Xb = read();
		Yb = read();
		X[2 * i - 1] = Xa;
		X[2 * i] = Xb;
		lines[2 * i - 1] = {Xa, Xb, Ya, 1};
		lines[2 * i] = {Xa, Xb, Yb, -1};
	}
	totN <<= 1;
	sort(lines + 1, lines + totN + 1);
	sort(X + 1, X + totN + 1);
	totL = unique(X + 1, X + totN + 1) - (X + 1);
	build(1, 1, totL - 1);
	for (int i = 1; i < totN; ++i)
	{
		update(1, lines[i].l, lines[i].r, lines[i].mark);
		totANS += nodes[1].len * (lines[i + 1].h - lines[i].h);
	}
	write(totANS);
	return 0;
} //Thomitics Code