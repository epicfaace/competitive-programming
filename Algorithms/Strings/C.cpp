/*
    Codeforces Problem 514C: Watto and Mechanism (http://codeforces.com/problemset/problem/514/C)
    Author: arvindr9
    In this implementation, a hash of a string A_0 A_1 ... A_k is (A_0 * x^k + A_1 * x^{k - 1} + ... + A_k * x^0) mod p
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxk = 1000000; //max value of a string's length
int n, m;
const ll p = 1000000007;
const ll x = 42863052;
const ll x2 = 47825835;
set<ll> set1; //stores hashcodes
map<ll, set<char>> mapc; //stores the characters that are zeroed to generate each hashcode
map<ll, set<int>> mapi; //stores the indexes that are zeroed to generate each hashcode
set<ll> set2;
map<ll, set<char>> mapc2;
map<ll, set<int>> mapi2;
ll h, h2, poww[maxk], poww2[maxk];

void constructPow() {
    ll num = 1;
    ll num2 = 1;
    for(int i = 0; i < maxk; i++) {
        poww[i] = num, poww2[i] = num2;
        num *= x, num2 *= x2;
        num %= p, num2 %= p;
    }
}

void constructHashes(string s) {
    int len = s.size();
    h = h2 = s[0] - '0';
    for(int i = 1; i < len; i++) {
        ll c = s[i] - '0';
        h = (h * x + c) % p;
        h2 = (h2 * x2 + c) % p;
    }
}

void insertHashes(string s) {
    constructHashes(s);
    int len = s.size();
    for(int i = 0; i < len; i++) {
        ll hash = (h - ((s[i] - '0') * poww[len - i - 1]) % p + p) % p; //The hash of the string created by setting the ith character to '0'
        ll hash2 = (h2 - ((s[i] - '0') * poww2[len - i - 1]) % p + p) % p;
        set1.insert(hash);
        mapc[hash].insert(s[i]);
        mapi[hash].insert(i);
        set2.insert(hash2);
        mapc2[hash2].insert(s[i]);
        mapi2[hash2].insert(i);
    }
}

void checkValidity(string s) {
    int len = s.size();
    constructHashes(s);
    for(int i = 0; i < len; i++) {
        ll hash = (h - ((s[i] - '0') * poww[len - i - 1]) % p + p) % p;
        ll hash2 = (h2 - ((s[i] - '0') * poww2[len - i - 1]) % p + p) % p;
        unsigned int req_size = 1 + (mapc[hash].count(s[i]) ? 1 : 0); //the minimum number of distinct characters that should be zeroed to generate the hashcode (this is equal to 2 if there is a memory string that is equal to the query string and 1 otherwise). 
        unsigned int req_size2 = 1 + (mapc2[hash2].count(s[i]) ? 1 : 0);
        if(set1.count(hash) && (mapc[hash].size() >= req_size) && mapi[hash].count(i)
            && set2.count(hash2) && (mapc2[hash2].size() >= req_size2) && mapi2[hash2].count(i)) {
            cout << "YES\n";
            return;
        } 
    }
    cout << "NO\n";
}

int main() {
    //freopen("C.in", "r", stdin);
    //freopen("C.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    constructPow();
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        insertHashes(s);
    }
    for(int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        checkValidity(s);
    }
}
