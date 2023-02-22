## Permutaciones incrementales

Cuantas permutaciones cumplen que
$$\sum_{i=1}^{n-1} [p_i < p_{i+1}] = k$$

_solución:_ construyamos la función  $dp(i, j, k):=$ número de permutaciones usando los números $\{1, 2, \dots, i\}$, terminando en  $j$ y con $k$ posiciones donde $p_t < p_{t+1}$. Vemos que

$$dp(i, j, k) = \sum_{t=1}^{j-1} dp(i-1, t, k-1) + \sum_{t=j}^{i-1} dp(i-1, t, k)$$

evitamos los elementos repetidos haciendo que todos los elementos mayores o iguales a j se le sumen 1.

podemos optimizarlo a $O(n^2 k)$.

- [educational dp - Problem T](https://atcoder.jp/contests/dp/tasks/dp_t)
- [abc282 - Problem G](https://atcoder.jp/contests/abc282/tasks/abc282_g)

## Rangos

Nosotros podemos armar el min-heap de un array en O(n), cada nodo de este min-heap plantea un rango, nosotros podemos iterar sobre el menor de estos para cada nodo y ver la contribución sobre el otro rango en O(nlogn) gracias a la tecnica dsu over trees.

- calcular:

$$\sum_{i=1}^n \sum_{j=i}^n [a_i + a_j = \max(a_i, a_{i+1}, \dots, a_j)]$$

$$\sum_{i=1}^n \sum_{j=i}^n \max(a_i, a_{i+1}, \dots, a_j) [\gcd(i, j) = 1]$$

- [abc282 - Problem H](https://atcoder.jp/contests/abc282/tasks/abc282_h)


## Number theory

calcular a/b los primeros k digitos en base prima ( > 9), donde b divide a.

Idea O(klogp + k^2): 

- si b termina en 0 entonces, a termina en 0. por lo cual podemos eliminarlos.
- en otro caso, el utlimo digito de b por el ultimo digito de la respuesta nos da el ultimmo digito de a, pero existe un unico numero que cumple (ecuacion lineal en base prima).
  
## Greedy

- [XXOpenCup Tokyo - cookies](https://vjudge.net/contest/525899#problem/A)

Solución: 

- Observamos que el valor que queda en el final siempre quedará para los siguientes k.
- Podemos transformar el problema por cada k, de la siguiente manera:
  - supongamos que $c_i$ es el valor que se llevará cada niño, el inicio $c_i = b_i$.
  - Empezamos con un valor $v$, y por cada $i$ si $s_i = S$ y $v > c_i$ intercambiamos $c_i$ con $v$, por otro lado, si $s_i = B$ y $v < c_i$ intercambiamos $c_i$ con $v$.
- Reducción 1: Si hay varias $S$ seguidas, podemos intercambiarlo por una unica cola de prioridades que retorne el minimo, asi solo debemos intercambiar v con ese mínimo. Similarmente para varios $B$.
- Reducción 2: supongamos, sin perdida de generalidad, tenemos colas mínimas y máximas intercaladas, comenzando por una cola mínima. si $X =$ min(min$q_i$) $\ge Y =$ max(max$q_{i+1}$), se cumple:

  - Si $v \ge X$, intercambiamos $v$ con $X$ y no intercambiamos $Y$.
  - Si $v \le Y$, no interactuamos con $X$ e intercambiamos con $Y$.
  - Si $X > v > Y$, no interactuamos con ninguno.

    Por tanto, podemos intercambiar las posiciones de las colas.

- Amortización: agrupemos cada cola mínima con una cola máxima, y llamemos al potencial de ambos como $f(x_i, y_i) = $ elementos en la cola mínima menores al máximo de la cola máxima + elementos en la cola máxima mayores al mínimo de la cola mínima.

  - Similarmente a lo anterior, si $v > Y$, vemos que el potencial se reduce al menos en 2, si $v < X$, se reduce al menos en 1. Si $X \le v \le Y$ se reduce al menos en 1.

- Si en un momento hay L colas, hay al menos $\frac{L}{2}$ pares tal que $|q_i| + |q_{i+1}| \le 2 \frac{M}{L}$.

- Así, luego de $2\frac{M}{L}$ turnos, cada uno de estos se puede mergear, sin embargo, mergear puede alterar a los vecinos, asi que por cada grupo de tres seguidos, se pueden mergear por lo menos 1, haciendo un total de $L/6$ mergeos, quedando con $5/6L$. Por tanto tenemos $log_{\frac{6}{5}} M$ pasos. 

- La complejidad final es: $O(M log^2 M + NlogM)$

### Problema 2.

Tienes un array B de positivos y negativos, debes escoger una subsecuencia con suma maxima tal que dos consecutivos tengan distinto signo, y elimnarlos, hallar la respuesta para k consultas.

