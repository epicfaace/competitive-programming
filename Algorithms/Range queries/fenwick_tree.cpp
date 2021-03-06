#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6;

int bit[maxn];

int get(int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= i & -1) {
        ret += bit[i];
    }
}

int upd(int pos, int delta) {
    for (int i = pos; i < maxn; i += i & -i) {
        bit[i] += delta;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}
