// https://www.codechef.com/LTIME61B/problems/TREESORT

#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

void solve();

int main() {
	freopen("input.txt", "r", stdin);

	int t;
	scanf("%d", &t);

	while (t--) {
		solve();
	}

	return 0;
}

#define MAX 100000

int n;
int c[2*MAX], p[MAX], v[MAX], mi[MAX], ma[MAX];

int getmin(int root) {
	if (c[root << 1] == -1) {
		mi[root] = v[root];
		return v[root];
	}

	mi[root] = min(getmin(c[root * 2]), getmin(c[root * 2 + 1]));
	return mi[root];
}

int getmax(int root) {
	if (c[root << 1] == -1) {
		ma[root] = v[root];
		return v[root];
	}

	ma[root] = max(getmax(c[root * 2]), getmax(c[root * 2 + 1]));
	return ma[root];
}

void getminmax(int root) {
	getmin(root);
	getmax(root);
}

int rotations(int root) {
	if (c[root << 1] == -1) {
		return 0;
	}

	int left = (root << 1);
	int right = left + 1;

	int rot = 0, tmp;
	if (mi[c[left]] < mi[c[right]] && ma[c[left]] > mi[c[right]]) {
		return -1;
	}
	else if (mi[c[right]] < mi[c[left]] && mi[c[left]] < ma[c[right]]) {
		return -1;
	}

	if (mi[c[left]] > ma[c[right]]) {
		tmp = c[left];
		c[left] = c[right];
		c[right] = tmp;
		rot = 1;
	}

	left = rotations(c[left]);
	if (left == -1)
		return -1;

	right = rotations(c[right]);
	if (right == -1)
		return -1;

	return rot + left + right;
}

void solve() {
	int i, l, r;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d", &l, &r);
		if (l != -1) {
			c[i<<1] = l - 1;
			c[(i<<1) + 1] = r - 1;
		}
		else {
			c[i << 1] = -1;
			c[(i << 1) + 1] = -1;
			v[i] = r;
		}
	}

	getminmax(0);

	printf("%d\n", rotations(0));
}