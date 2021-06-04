---
layout: post
title: Canadian Computing Olympiad 2021
subtitle: Soluciones para el CCO 2021
tags: [CCO2021, competitive programming]
---

<h2 class="color-blue">1. Swap Swap Sort</h2>

<details>
<summary> code </summary>

<code>
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn], qu[maxn * 10];
int p[maxn], sz[maxn];
int fr[maxn];
using ll = long long;
vector<pair<int, ll>> asg[maxn];

int ft[maxn];
void update(int x, int v) {
    while (x < maxn) {
        ft[x] += v;
        x += x&-x;
    }
}

int query(int x) {
    int ans = 0;
    while (x > 0) {
        ans += ft[x];
        x -= x&-x;
    }
    return ans;
}

ll get(int a, int b) {
    int lo = 0, hi = (int)asg[a].size()-1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (asg[a][mid].first <= b) lo = mid;
        else hi = mid-1;
    }
    if (!asg[a].empty() && asg[a][lo].first == b) return asg[a][lo].second;
    return sz[a]*1ll*sz[b] - get(b, a);
}

int main() {
    int n, k, q;
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a+i);
        sz[a[i]] += 1;
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d", qu+i);
    }
    iota(p, p+k+1, 0);
    for (int i = 0; i < q; ++i) {
        int& a = p[qu[i]];
        int& b = p[qu[i] + 1];
        swap(a, b);
        if (sz[a] < sz[b]) asg[a].push_back({b, 0ll});
        else asg[b].push_back({a, 0ll});
    }
    for (int i = 1; i < maxn; ++i) {
        sort(asg[i].begin(), asg[i].end());
        asg[i].resize(unique(asg[i].begin(), asg[i].end()) - asg[i].begin());
    }
    for (int i = 1; i <= n; ++i) {
        for (auto& e : asg[a[i]]) {
            e.second += fr[e.first];
        }       
        fr[a[i]] += 1;
    }
    ll inv = 0;
    for (int i = 1; i <= n; ++i) {
        update(a[i], 1);
        inv += i - query(a[i]);
    }
    iota(p, p+k+1, 0);
    for (int i = 0; i < q; ++i) {
        int& a = p[qu[i]];
        int& b = p[qu[i] + 1];
        inv += 2 * get(b, a) - sz[a]*1ll*sz[b];
        printf("%lld\n", inv);
        swap(a, b);
    }
    return 0;
}
<code>

</details>


### tags:

<details>
<summary>  </summary>
permutations, sqrt-trick, offline, BIT, binary-search
</details>

### hint 1:

<details>
<summary>  </summary>
La respuesta es el número de inversiones. Inicialmente
podemos calcularla $O(n \log k)$ usando BIT.
</details>

### hint 2:

<details>
<summary> </summary>
Si $a$ es una permutación, al hacer un swap solo aumentamos o reducimos
las inversiones en 1. Actualizar este valor es sencillo y solo hará
falta saber cuál de los dos elementos esté a la izquierda del otro en
un inicio.
</details>

### hint 3:

<details>
<summary>  </summary>
Al hacer un swap, si hemos podido mantener la respuesta hasta este momento,
la cantidad de inversiones solo se ve alterada por los elementos con 
igual valor a los intercambiados.
</details>

### hint 4:

<details>
<summary>  </summary>
Si denotamos $f(x, y)$ como la cantidad de inversiones en el array $a$, 
eliminando todos los elementos distintos de $x$ o $y$ y reemplazando
los $x$ por 1 y los $y$ por 2. El cambio en la respuesta es:

$$ N p_i \times N p_{i+1} - 2 f(p_i, p_{i+1})$$

Donde $N x$ indica la cantidad de elementos iguales a $x$ en $a$.

</details>

### hint 5:

<details>
<summary>  </summary>
Notemos que podemos aplicar el <a href="https://youtu.be/VGq6w9TlJBY?t=4408"> sqrt-trick </a> 
para calcular $f$ en los $q$ pares que necesitamos consultar y guardarlos para
ser hallados en $O(\log n)$. Notemos además, que $f(x, y) + f(y, x) = N x \times N y$. 
</details>

### hint 6:

<details>
<summary>  </summary>
Si los calculamos de forma usual y buscamos cuantos elementos estan en menor 
posición en el conjunto grande por cada elemento en el conjunto pequeño, tendremos
un factor logarítmico que nos malogrará la complejidad. Sin embargo, si el cálculo
lo hacemos en un algoritmo offline, recorriendo los índices en orden ascendente,
vemos que no necesitamos hacer una busqueda binaria para calcular dichos valores ya
que podemos guardarlo en array que lleve las cuentas. Nuestra complejidad final
es $O(n \sqrt q + q \log n + n \log k)$.
</details>