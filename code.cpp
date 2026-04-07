#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_BUF = 1 << 20;
char buf[MAX_BUF], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int read() {
    int x = 0;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == EOF) return -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x;
}

struct Constraint {
    int i, j, e;
};

struct Var {
    int val;
    int* ptr;
    bool operator<(const Var& other) const {
        return val < other.val;
    }
};

const int MAXN = 2000005;
Constraint constraints[MAXN];
Var vars[MAXN * 2];
int parent_node[MAXN * 2];
int size_node[MAXN * 2];

int find_set(int v) {
    if (v == parent_node[v])
        return v;
    return parent_node[v] = find_set(parent_node[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size_node[a] < size_node[b])
            swap(a, b);
        parent_node[b] = a;
        size_node[a] += size_node[b];
    }
}

void solve() {
    int t = read();
    if (t == -1) return;
    while (t--) {
        int n = read();
        int num_vars = 0;
        for (int k = 0; k < n; ++k) {
            constraints[k].i = read();
            constraints[k].j = read();
            constraints[k].e = read();
            vars[num_vars++] = {constraints[k].i, &constraints[k].i};
            vars[num_vars++] = {constraints[k].j, &constraints[k].j};
        }
        
        sort(vars, vars + num_vars);
        
        int unique_count = 0;
        for (int k = 0; k < num_vars; ++k) {
            if (k == 0 || vars[k].val != vars[k-1].val) {
                unique_count++;
            }
            *(vars[k].ptr) = unique_count - 1;
        }
        
        for (int k = 0; k < unique_count; ++k) {
            parent_node[k] = k;
            size_node[k] = 1;
        }
        
        for (int k = 0; k < n; ++k) {
            if (constraints[k].e == 1) {
                union_sets(constraints[k].i, constraints[k].j);
            }
        }
        
        bool possible = true;
        for (int k = 0; k < n; ++k) {
            if (constraints[k].e == 0) {
                if (find_set(constraints[k].i) == find_set(constraints[k].j)) {
                    possible = false;
                    break;
                }
            }
        }
        
        if (possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    solve();
    return 0;
}
