# El problema del máximo flujo

<center>
<img src="/images/flow1.PNG">
</center>

La figura anterior nos muestra un grafo con pesos, semánticamente distinto a los que estamos acostumbrados. Los pesos indican _capacidades_, el monto máximo de _algo_ que puede fluir por la arista. El objetivo es idear como trasladar la mayor cantidad de _algo_ (flujo) desde $s$ hacia $t$.

Como vemos en el ejemplo, ya no es posible trasladar más flujo desde $s$ hacia $t$, una simple inspección nos hace ver que las aristas desde $s$ ya no tienen más  capacidad disponible. Posteriormente generalizaremos esta idea, por ahora podemos concluir que el flujo es máximo.

## Instancia ideal

Se puede plantear el problema de flujos para cualquier grafo en general, veremos por simplicidad como debe ser una instancia ideal, de tal forma que todos los grafos pueden ser pensados de forma ideal bajo algunas transformaciones que no alteren el flujo máximo.

Una instancia del flujo máximo se puede representar por la siguiente tupla:

$$(G, s, t, u(x))$$

donde:

1. $G$ es un grafo dirigido, con vértices $V$ y aristas dirigidas $E$;

2. Un vértice _fuente_ $s \in V$;

3. Un vértice _sumidero_ $t \in V$;

4. Una función $u : E \rightarrow Z^+_0$, que asigna una capacidad para toda arista.

Como el objetivo es en trasladar flujo desde $s$ hacia $t$, podemos asumir sin pérdida de generalidad que $s$ no tiene aristas entrantes y $t$ no tiene aristas salientes.

Dado una instancia como entrada, las soluciones asequibles son los flujos en la red (la instancia). Cuando nos referimos al flujo usualmente podemos hablar de los caminos que constituyen el mismo, bajo una visión algoritmica, es más sencillo hablar de la cantidad de flujo en cada arista.

Formalmente, un flujo es un vector no negativo $\{f(e_1), f(e_2), \ldots, f(e_{\vert E\vert})\}$, que satisface las siguientes restricciones:

- __restricción de capacidad:__ $f(e) \le u(e), \forall e \in E$;
- __restricción de conservación__: $\forall v \in V\setminus\{s, t\} $,

$$\text{cantidad de flujo entrando por } v = \text{cantidad de flujo saliendo por } v$$

$$\sum\limits_{(u, v) \in E} f((u, v)) = \sum\limits_{(v, w) \in E} f((v, w))$$

El objetivo consiste en encontrar el __máximo flujo__ saliendo por $s$, o similarmente entrando por $t$.

### ¿Algoritmo _Greedy_?

Hasta el momento no tenemos ninguna certeza que exista una solución __polinómica__ al problema del máximo flujo. Inspeccionaremos un enfoque _greedy_, recordemos que un enfoque _greedy_ toma decisiones locales irrevocables, con la esperanza que todo trabaje bien al terminar.

El enfoque _greedy_ más simple para el problema del máximo flujo es empezar con flujo $0$ y avariciosamente producir flujos con mayor valor cada vez. La manera natural es enviar flujo consecutivamente sobre caminos desde $s$ hacia $t$.

```py
def algoritmo_greedy(G, s, t, u):
    f = dict([(e, 0) for e in E])
    while buscar un camino P(s, t) con f[e] < u(e), para todo e en P:
        delta = min([u(e) - f[e] for e in P])
        for e in P: 
            f[e] += delta
    return f
```

Vemos que verificar un camino con la restricción $f[e] < u(e)$ se puede realizar en $O(\vert V\vert + \vert E\vert)$ con algún algoritmo de búsqueda como __DFS__ o __BFS__. En efecto, pueden haber muchos caminos entre $s$ y $t$; por ahora, permitimos que el algoritmo escoja arbitrariamente alguno de ellos. El algoritmo entonces envía cuanto flujo posible por este camino, sujeto a la restricción de capacidad.

__¿El algoritmo _greedy_ funciona?__ que es, al terminar con un flujo, __¿Es necesario que este flujo sea máximo?__ Lastimosamente si el primer camino que encontramos en nuestro grafo inicial es el camino $(s, v, w, t)$, no permitiendo cualquier otro camino futuro y terminando nuestro algoritmo con un flujo de $3$, que al ser menor al encontrado anteriormente con $5$, no pude ser máximo.

<center>
<img src="/images/flow2.PNG">
</center>

### Grafos residuales

La segunda idea consiste en extender el algoritmo greedy permitiendo una operacion de "rectificación". Por ejemplo, cuando el algoritmo se detiene como se ve en la imagen 2, nosotros quisieramos enviar dos unidades más de flujo por la arista $\left(s, w\right)$, luego estas unidades en contra de la arista $\left(v, w\right)$, rectificando dos de las tres unidades enviadas en la anterior iteración, y finalmente a lo largo de la arista $\left(v, t\right)$. Así, logrando el máximo flujo vito en la figura 1(b).

Formalmente necesitamos especificar como permitir la operación de "rectificación". Así, esto motiva las siguientes definiciones.

#### Red Residual

Dado un grafo $G$ y un flujo $f$ sobre esta, nosotros formamos una nueva red de flujo $G_f$ que tiene el mismo conjunto de vértices de $G$ y que tiene dos aristas por cada arista de $G$. una arista $e = (v, w)$ de $G$ que mantiene un flujo $f_e$ y tiene capacidad $u(e)$ como en la figura 3(a) se convierte en una arista hacia adelante $(u, v)$ de $G_f$ con capacidad $u(e) - f_e$ (el flujo remanente) y una arista en contra $(w, v)$ de $G_f$ con capacidad $f_e$ (el mondo de flujo anteriormente enviado que puede ser rectificado). Ver figura 3(b). Observemos que los caminos $s-t$ con $f_e < u_e$ para todas sus aristas, como los que se buscan por el algoritmo _greedy_, corresponden a un caso especial caso de caminos $s-t$ de $G_f$ que comprende solo aristas hacia adelante. Por ejemplo, con el $G$ de nuestro ejemplo y f de la figura 2, la red residual correspondiente $G_f$ luce como en la figura 4. Las cuatro aristas con capacidad cero en $G_f$ son omitidas.


<center>
<img src="/images/residual edge.PNG">
</center>

<center>
<img src="/images/residual.PNG">
</center

### El algoritmo de Ford-Fulkerson

Felizmente, si nosotros ejecutamos el algoritmo greedy natural en la actual red residual, nosotros obtendremos un algoritmo correcto, el algoritmo de _Ford-Fulkerson_.

```py
def ford_fulkerson():
    f = dict([(e, 0) for e in E])
    //sobre el grafo residual
    while buscar un camino P(s, t) con f[e] < u(e), para todo e en P:
        delta = min([u(e) - f[e] for e in P])
        for e in P:
            f[e] += delta
            f[rev(e)] -= delta
    return f
```

Por ejemplo, iniciando desde la red residual de la figura 4, el algoritmo ford-fulkerson deberia aumentar el flujo por dos unidades a traves del camino $s \rightarrow w \rightarrow v \rightarrow t$. Este proceso de aumento produce el máximo flujo de figura 1(b).

### terminación del algoritmo

#### Invariante 1. Al termino de cada paso el algoritmo mantiene un flujo factible.

Antes del bucle es claramente cierto. El parametro _delta_ es definido de tal forma que el valor del flujo nunca toma un valor negativo o excede su capacidad $u(e)$. Respecto a las restricciones de conservación, considera un vértice $v$. Si $v$ no esta sobre el camino de aumento $P$ en $G_f$, entonces el flujo que pasa por $v$ permanece igual. 
Si $v$ esta sobre $P$, con aristas $(x, v)$ y $(v, w)$ pertenecientes a $P$, entonces hay cuatro casos, dependiente si son aristas hacia adelante o de retroceso. Por ejemplo, si ambos son aristas de avance, entonces el flujo de aumento incrementa tanto como de entrada como de salida, similarmente para cada caso, tal que la restriccion de conservacion se preserva.

#### Invariante 2. Dada una red con capacidades enteras, el algoritmo cumple que el flujo final es entero.

Inductivamente, todas las capacidades residuales son enteras, así el parametro _delta_ es entero, tal que el flujo se mantiene entero.

#### Invariante 3. En cada interación el algoritmo de Ford-Fulkerson incrementa la cantidad de flujo por _delta_.

La segunda invariante implica que _delta_ $\ge 1$ en cada interación. 

#### Invariante 4. El algoritmo siempre termina.

Note que cada vez que una arista saliendo de $s$ es usada completamente, la arista reversa nunca será usada en un camino simple, por tanto el flujo eventualmente llegará a terminar.

### Problemas con capacidad unitaria

menger theorem: 

Theorem (Menger’s Theorem – Edge Version) Let x and y be
distinct vertices in a connected graph G. Then the maximum
number of edge disjoint paths from x to y is equal to the
minimum number of edges whose removal from G leaves x and
y in different components.
Theorem (Menger’s Theorem – Vertex Version) Let x and y
be distinct non-adjacent vertices in a connected graph G. Then
the maximum number of vertex disjoint paths from x to y is
equal to the minimum number of vertices whose removal from G
leaves x and y in different components.

### Maximum Bipartite Matching

__Augmenting Paths__

### Defecto de G: 

Sea $G = (X, Y, E)$ un grafo bipartito, por cada subconjunto $S$ de $X$, sea $N(S)$ el conjunto de todos los elementos $y$ adjacentes a algún elemento de $x \in X$. El defecto de $G$, denotado por $d(G)$, es:

$$d(G) = \max \lbrace \vert S\vert - N(S): S \subseteq X\rbrace$$ 

__Teorema de Hall__ Sea $G = (x, Y, E)$ un grafo bipartito. Entonces el máximo tamaño de un emparejamiento en $G$ es  $\vert X\vert - d(G)$.

__corolario__ un grafo regular tiene un emparejamiento de tamaño $\vert X\vert$

__corolario__ un grafo $r$ regular puede ser particionado en $r$ empareamientos de tamaño $\vert X\vert$

### Flujos como un problema de optimización matemática (opcional)

$$
\begin{equation*}
\begin{aligned}
& \underset{f}{\text{maximize}}
& \sum\limits_{(s, u) \in E} & f((u, s)) \\
& \text{subject to}
& f(e_i) &\leq u(e_i), &\; e \in E;\\
& & \sum\limits_{(u, v) \in E} f((u, v)) &= \sum\limits_{(v, w) \in E} f((v, w)), & v \in V.
\end{aligned}
\end{equation*}
$$