---
layout: post
title: Doble Conteo
---

Si tenemos dos formas de contar algo, al final podemos tener una nueva expresión que no es tan obvia.

### **nivel 1**. Suma de coeficientes binomiales.

Probar que $\binom{n}{0} + \binom{n}{1} + \dots + \binom{n}{n} = 2^n$.

<details>
<summary>prueba</summary>
- Por el lado izquierdo tenemos la suma de la cantidad de conjuntos de $i$ elementos tomados de un conjunto de $n$ elementos. Por otro lado podemos contar estos conjuntos incrementalmente agregando el elemento $n$, esto agrega la misma cantidad de conjuntos sin contener el elemento $n$ agregando este, al final: $T(n) = 2 T(n-1)$ y $T(0) = 1$.    
</details>

**ejercicio:** probar que $2^0 + 2^1 + \dots + 2^k = 2^{k+1} - 1$.

<details>
<summary> **hint 1:** </summary> contemos conjuntos no vacíos.
</details>

<details>
<summary> **hint 2:** </summary> fijemos un elemento como máximo.
</details>

### **nivel 2**. Contando las aristas de un icosaedro.

Probar que el número de aristas en un icosaedro es 30.

<center>
![](https://respuestas.tips/wp-content/uploads/2014/06/icosaedro.jpg){ width=33% }
</center>

<details>
<summary> prueba </summary>
* Partimos del hecho que un icosaedro tiene 20 caras, cada cara tiene 3 aristas
y cada arista comparte 2 caras, esto nos da un ratio de $\frac{2}{3}$. Para
probar que esto es correcto, procedemos a contar los pares ($E, F$) donde $E$
son las aristas y $F$ las caras. Claramente hay 60 de estos pares, 3 por cada
cara. Si $m$ es el número de aristas, entonces la cantidad equivale a $2 m$, por
tanto la cantidad de aristas es 30.
</details>

### **Bipartite Graph Framework**

El doble conteo se puede ver como una consecuencia de resultados en grafos 
bipartitos. 

$a$. Si G es un grafo bipartito con conjuntos de vertices $X$ e $Y$, entonces 
la suma de los grados de vertices en $X$ es igual a la suma de los grados de los
vertices en $Y$. 

$b$. Si ${avg}_x$ es el promedio de los grados de los vértices en $X$ y ${avg}_y$
es el promedio de los grados de los vértices en $Y$. Entonces 
$\frac{\text{avg}_x}{{avg}_y} = \frac{|Y|}{|X|}$.

### **D-regular Matching**

<center>
![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRa1nFShGwwVSXUG2YBcsZD6Kk-alcN1OnNtg&usqp=CAU){ width=33% }
</center>

Sea $G$ un grafo bipartito con conjuntos de vértices $X$ e $Y$. Supongamos que 
todos los vértices en $X$ tienen grado $d_x > 0$ y los vértices en $Y$ tienen grado 
$d_y > 0$. Sea $U$ cualquier subconjunto de $X$, y sea $V$ el conjunto de todos
los vértices en $Y$ que tienen un arista hacia algún nodo de $U$. Entonces,
**$|V| \ge |U| \frac{d_x}{d_y}$**. 

<details>
<summary>**Prueba**:</summary> Sea H un subgrafo de $G$ con conjunto de vértices $U$ y $V$, con las
aristas inducidas de $G$. Entonces todo vértice en U tiene grado $d_x$ y todo
vertice en $V$ tiene grado a lo más $d_Y$. 

**Afirmación**: Si $|X| = |Y|$, por el **Hall's Theorem**, existe un *perfect 
matching*.
</details>

### **Nivel 3**: Upper Shadows

<center>
![](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/Turan_13-4.svg/1200px-Turan_13-4.svg.png){ width=30% }
</center>

Sea $A$ una colección de subconjuntos de $[n]$, con cada conjunto de tamaño 
$r$. Sea $s > r$ y definimos el upper shadow $\nabla A$ como el conjunto 
de todos los conjuntos de tamaño $s$ tal que contienen al menos un elemento
en $A$. Entonces el tamaño de $\nabla A \ge |A| \frac{\binom{n}{s}}{\binom{n}{r}}$.

<details>
<summary> **prueba**: </summary>

Definamos un grafo bipartito con conjunto de vértices $A$ y $B = \nabla A$, 
los nodos en $a \in A$ estan unidos a los nodos de $b \in B$ si y solo si 
$a \in b$. Cada nodo en $A$ tiene grado $\binom{n-r}{s-r}$, en particular, es
un grado promedio. y cada $b \in \nabla A$ tiene grado a lo más $\binom{s}{r}$,
de tal forma que es una cota superior para el grado promedio in $\nabla A$. Y
por los principios de los grafos bipartitos $\nabla A \ge |A| \frac{\binom{n-r}{s-r}}{\binom{s}{r}}$.

*Afirmación*: $\binom{n-r}{s-r} \binom{n}{r} = \binom{n}{s} \binom{s}{r}$.

La parte derecha es la cantidad de formas de tomar conjuntos de tamaño s, multiplicado
por la cantidad de formas de tomar subconjuntos de tamaño r. Por el otro lado
nosotros podemos escogerlos al reves, primero conjuntos de tamaño r y luego superconjuntos
de tamaño s.

</details>

**nota**: el anterior resultado forma parte de un conjunto más grande de resultados en la teoría extremal de grafos.

### **Phantom Bipartite Graph**

<center>
![](https://www.researchgate.net/profile/Klaus-Heidtmann/publication/270881019/figure/fig2/AS:392161502744578@1470509996119/Abbildung-12-Beispiel-eines-Hypergraphen-Hypergraphen-bieten-mehr.png){width=30%}
</center>

Usualmente nosotros tenemos un conjunto $X$ cuyo tamaño queremos acotar, pero
no tenemos una grafo bipartito obvio. En este caso, nosotros debemos construir
uno. Pensemos en la siguiente forma equivalente: Dado un grafo bipartito con
conjuntos de vertices $X$ e $Y$, cada vértice $y \in Y$ determina una vecindad
en $N_y \subset X$ y por tanto el grafo bipartito en si mismo es determinado por
una colección de subconjuntos de $X$, posiblemente con repeticiones, así 
estrictamente hablando se determina gracias a un multiconjunto de subconjuntos 
de $X$. 

Ahora debemos escoger por cada conjunto una colección de vertices, y así
formar el conjunto $Y$. Sea $B$ una colección de subconjuntos de $X$. Si cada
elemento de $X$ es contenido en al menos $d_x$ conjuntos de $B$ y cada conjunto
en $B$ contiene a lo más $d$ elementos de $X$, entonces $|X| \le |B| \frac{d}{d_x}$.

<details>
<summary>**Prueba**:</summary> Contemos los pares ($x, b$), donde $x \in X$, $b \in B$ y $x \in b$.
</details>

### **Nivel 4:** Burnside Lemma

Supongamos que el grupo finito $G$ actúa sobre el conjunto finito $X$. Es bastante 
natural considerar la relación $R$ sobre $G \times X$ al referirnos a puntos
fijos sobre acciones. Nosotros definimos que $g \in G$ y $x \in X$ están relacionados si $g$ fija
$x$. Simbólicamente:

$$R = \{(g, x) \in G \times X ~\vert ~ g \cdot x = x\}$$
Ahora, de lo anterior, tenemos las projecciones $p: R \rightarrow G$ y $q: R \rightarrow X$. 
Nosotros podemos interpretar $p^{-1}(g)$, para $g \in G$. Como el conjunto de puntos
fijos de $g$ actuando sobre $X$, que denotamos como $X^g$. ¿Qué hay acerca de $q^{-1}(x)$, para
$x \in X$? Este es precisamente el estabilizador de $x$, i.e. El subgrupo de $G$ consistiendo
de puntos cual fijan $x$. Denotado por $G_x$.


Así el doble conteo nos da la identidad:

$$\sum_{g \in G} |X^g| = \sum_{x \in X} |G_x|$$
Nosotros podemos reinterpretar esta formula por recalcar que si $x$ e $y$ están
en la misma orbita de $G$, entonces $G_x$ y $G_y$ son conjugados. Así nosotros
podemos reagrupar la segunda suma en sumas sobre el conjunto de clases
representativas de orbitas $x_1, \dots, x_n$, y así reescribir esto como:

$$\sum_{i=1}^n \sum_{y \in O(x_i)} |G_y| = \sum_{i = 1}^n |O(x_i)||G_{x_i}| = \sum_{i = 1}^n |G| = n |G|$$

Con lo que concluimos:

$$\sum_{g \in G} |X^g| = n|G|$$

Donde $n$ denota el número de orbitas de $G$ actuando sobre $X$. Dividiendo ambos lados
por $|G|$, nosotros encontramos que:

$$\dfrac{1}{|G|}\sum_{g \in G} |X^g| = n$$
O, en otras paralabras:

El número promedio de puntos fijos de un elemento de $G$ actuando sobre $X$ es igual al número de órbitas
de $G$ actuando sobre $X$.


## Referencias:

1. [tricki - Doble Conteo](http://www.tricki.org/article/Double_counting)