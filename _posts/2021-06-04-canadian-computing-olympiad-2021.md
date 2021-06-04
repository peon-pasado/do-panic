---
layout: post
title: Canadian Computing Olympiad 2021
subtitle: Soluciones para el CCO 2021
tags: [CCO2021, competitive programming]
---

<h2 class="color-blue">1. Swap Swap Sort</h2>


<details>
<summary> <h3>hint 0:</h3></summary>
permutations, sqrt-trick, offline, BIT, binary-search
</details>

<details>
<summary> <h3>hint 1:</h3></summary>
La respuesta es el número de inversiones. Inicialmente
podemos calcularla $O(n \log k)$ usando BIT.
</details>

<details>
<summary> <h3>hint 2:</h3></summary>
Si $a$ es una permutación, al hacer un swap solo aumentamos o reducimos
las inversiones en 1. Actualizar este valor es sencillo y solo hará
falta saber cuál de los dos elementos esté a la izquierda del otro en
un inicio.
</details>

<details>
<summary> <h3>hint 3:</h3></summary>
Al hacer un swap, si hemos podido mantener la respuesta hasta este momento,
la cantidad de inversiones solo se ve alterada por los elementos con 
igual valor a los intercambiados.
</details>

<details>
<summary> <h3>hint 4:</h3></summary>
Si denotamos $f(x, y)$ como la cantidad de inversiones en el array $a$, 
eliminando todos los elementos distintos de $x$ o $y$ y reemplazando
los $x$ por 1 y los $y$ por 2. El cambio en la respuesta es 
$ N p_i \times N p_{i+1} - 2 f(p_i, p_{i+1})$.
</details>

<details>
<summary> <h3>hint 5:</h3></summary>
Notemos que podemos aplicar el [sqrt-trick](https://youtu.be/VGq6w9TlJBY?t=4408) 
para calcular $f$ en los $q$ pares que necesitamos consultar y guardarlos para
ser hallados en $O(\log n)$. Notemos además, que $f(x, y) + f(y, x) = N x \times N y$.
</details>

<details>
<summary> <h3>hint 6:</h3></summary>
Si los calculamos de forma usual y buscamos cuantos elementos estan en menor 
posición en el conjunto grande por cada elemento en el conjunto pequeño tendremos
un factor logaritmico que nos malogrará la complejidad. Sin embargo, si el cálculo
lo hacemos en un algoritmo offline, recorriendo los índices en orden ascendente
vemos que no necesitamos hacer una busqueda binaria para calcular dichos valores ya
que podemos guardarlo en array que lleve las cuentas. Nuestra complejidad final
es $O(n \sqrt q + q \log n + n \log k)$.
</details>