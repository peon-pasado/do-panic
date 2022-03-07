#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;

//-1: trash
//0: room
const int B = 1010;
const int maxn = 1e5 + 10;
int bcolor[B];
bool all_eq[B];
int val[maxn];
int n, c, q;
vector<pair<int, int>> s[B];

int get_color(int i) {
    if (val[i] == -1) return -1;
    int bi = i / B; 
    if (all_eq[bi]) return bcolor[bi];
    return val[i];
}

void push(int b) {
    if (all_eq[b]) {
        s[b].clear();
        for (int i = b*B; i < (b+1)*B; ++i) {
            if (val[i] == -1) continue;
            val[i] = bcolor[b];
            s[b].emplace_back(val[i], i); 
        }
        all_eq[b] = 0;
    }
}

void update(int b, int l, int r, int c) {
    vector<pair<int, int>> aux1, aux2;
    for (auto it : s[b]) {
        if (it.second >= l && it.second <= r) continue;
        aux1.emplace_back(it);
    }
    for (int i = l; i <= r; ++i) {
        if (val[i] == -1) continue;
        val[i] = c;
        aux2.emplace_back(c, i);
    }
    merge(all(aux1), all(aux2), s[b].begin());
}

void paint(int l, int r, int c) {
    int bl = l/B; 
    int br = r/B; 
    if (bl == br) {
        push(bl);
        update(bl, l, r, c);
    } else {
        push(bl);
        update(bl, l, (bl+1)*B-1, c);
        for (int i = bl+1; i < br; ++i) {
            all_eq[i] = 1;
            bcolor[i] = c;
        }
        push(br);
        update(br, br*B, r, c);
    }   
} 

void trash(int c) {
    int tb = (n-1)/B;
    for (int i = 0; i <= tb; ++i) {
        if (all_eq[i] && bcolor[i] == c) {
            for (int j = i*B; j < min(n, (i+1)*B); ++j) {
                val[j] = -1;
            }
            bcolor[i] = -1;
            continue;
        }
        auto L = lower_bound(all(s[i]), make_pair(c, -1));
        if (L == s[i].end()) continue;
        auto R = upper_bound(all(s[i]), make_pair(c, n));
        for (auto it = L; it != R; ++it) {
            val[it->second] = -1;
        }
        s[i].erase(L, R);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> c >> q;
    for (int i = 0; i < B; ++i) all_eq[i] = 1;
    for (int i = 0; i < q; ++i) {
        char type;
        cin >> type;
        if (type == 'm') {
            int i, j, k;
            cin>>i>>j>>k;
            i--;
            j--;
            paint(i, j, k);
        } else if (type == 'b') {
            int k;
            cin>>k;
            trash(k);
        } else if (type == 'd') {
            int u;
            cin>>u;
            u--;
            int cu = get_color(u);
            if (cu==-1) cout << "para que quieres saber eso\n";
            else if (cu==0) cout << "si lo encuentro que te hago\n";
            else cout << cu << '\n';
        } else if (type == 's') {
            int u, v;
            cin>>u>>v;
            u--;
            v--;
            int cu = get_color(u);
            int cv = get_color(v);
            if (cu == cv) cout << "si\n";
            else cout << "no\n";            
        }
    }
    return 0;
}