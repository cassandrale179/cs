# 34: NP COMPLETENESS

- **The complexity class NP** is the class of languages that <u>can be verified by a polynomial-time algorithm</u> 

- If any NP-complete problem can be solved in polynomial time, then every problem in NP has a polynomial-time solution, that is, **P = NP** 

- The nesting indicates the direction of the reductions used. 

  ```
  Satisfiability 
  ├── 0-1 Integer Programming 
  ├── Clique 
      ├── Vertex Cover 
         ├── Set Cover
         ├── Directed Hamiltonian Circuit 
  ├── 3-SAT  
      ├── Graph coloring problem  
         ├── Clique cover 
         ├── Exact cover  
         		 ├── 3-dimensional matching 
             ├── Knapsack 
                 ├── Max-cut 
  ```

- We want prove some problems are computationally difficult: Problem X is at least as hard as problem Y 

- **Reduction**:  If problem Y can be reduced to problem X, we denote this by Y ≤ pX 

- **Meaning**: Suppose: Y ≤ pX, and  there is an polynomial time algorithm for X 
  then, there is a polynomial time algorithm for Y  

- **Example: **Max Bipartite Matching ≤P Max Network Flow. 

### 34.1 VERTEX COVER 

- Prove that **Indepdent Set** = p **Vertex Cover**
  <img src="/Users/cassandrale179/Desktop/Screen Shot 2020-02-16 at 9.19.36 PM.png" style="zoom:25%;" />

- **{b, c, d, e} i**s a **<u>vertex cover</u>** because all edges adjacent to the vertices of the graph is all the edges in the graph 

- **{a, f}** is an **<u>independent set</u>** because there is no edge between them

- **Proof that independent set is reducible to vertex cover**: If G = (V, E) is a graph, then S is an independent set $\leftrightarrow$ V − S is a vertex cover 

  - **Proof that given an independent set S, then V - S is a vertex cover:** 
    Given an edge **(a, b)**: only $a$ or $b$ is in $S$, not both (since S is an independent set)
    Therefore $a$ must be in $V-S$ and b in $S$ or vice versa
    $V-S$ must be a vertex cover because  at least one of $(a,b)$ is in $V-S$ for every single edge in the graph   

  - **Proof that given V - S is a vertex cover, then S must be an independent set** 

    Let imagine an edge **(u,v)** in S, then (u,v) is not in V-S (Since V-S is a compliment of S)

    If an edge (u,v) is not in V-S, then that means V-S is not a vertex cover (since every edge of the graph must be covered). 

    Therefore either u is in S or v is in S. 
    Therefore S is an independent set bcause no two vertex in there can share the same edge. 

### 34.2 CIRCUIT SATISFIABILITY

- **Problem: **Given a Boolean circuit C, is there an assignment to the variables that causes the circuit to output 1? 
- **Satisfiable :** If the Boolean variables can be assigned values such that the formula turns out to be TRUE, then we say that the formula is satisfiable.
- **Unsatisfiable :** If it is not possible to assign such values, then we say that the formula is unsatisfiable. 
- **Example:** Given F = (A v B) ^ (A v $\neg$ B) ^ ($\neg$A v C) ^ ($\neg$ C v B ), if we have A = 1, B = 1, and C = 1, then F = 1. Therefore the circuit is **satisfied.** 
- **Verifying algorithm**: just replace each value with the assignment, and check if the circuit outputs 1 (polynomial time). 

#### 2 SAT PROBLEM (POLYNOMIAL) 

- **The 2SAT problem:** given a list of clauses where each clauses can at max have two literal per clauses, and it is in **Conjunctive Normal Form**(clauses are ^ together, and no ^ within the clauses), determine if there exist any assignment which satisifes the clause
- **Example:** the clause (A ^ $\bar{A}$) is unsatisfable because whatever value we give to A, it will always return False 

![F = (A_1 \vee  B_1) \wedge (A_2 \vee  B_2) \wedge (A_3 \vee  B_3) \wedge ....... \wedge (A_m \vee  B_m)](https://www.geeksforgeeks.org/wp-content/ql-cache/quicklatex.com-91697b92a59779e7e603c5b0a802a87a_l3.svg)

- **Brute force solution:**  Generate $2^n$ possible combinations, and test each combination and see which one causes F = 1. However, the time complexity of this would be $2^n$

- Okay, I need to look into this later 

#### 3 SAT PROBLEM (NP COMPLETE) TO GRAPH COLORING PROBLEM** 

- **The 3SAT problem:** 

- **Reduce:** 3 SAT < p 3 Coloring. Start with 3-SAT formula φ with n variables x1, . . . , xn and m clauses C1, . . . , Cm. Create graph Gφ such that Gφ is 3-colorable iff φ is satisfiable  

- **Create a graph where there is a base**, and that for each variable $v_1$, we create a complement $\bar{v_1}$ and connect (Base, $v_1, \bar{v_1}$) into a triangle. The triangle must have 3 different color 

  <img src="/Users/cassandrale179/Desktop/Screen Shot 2020-02-17 at 8.48.10 PM.png" style="zoom:50%;" />

  - **A variable can only be True or False:** therefore its complement cannot be the same color as itself 

- **Clause Satisfiability Gadget**: For a clause $C_i$ = (a ∨ b ∨ c), we need to express the OR of its literals using our colours {T, F, B}. <img src="/Users/cassandrale179/Desktop/Screen Shot 2020-02-17 at 8.57.30 PM.png" alt="zoom=" style="zoom:20%;" />

  - If the graph above is three-colorable, then the clause is satisifed.
  - This is because the clause (a v b v c) is connected to **B** and **F**, therefore it must be **T**. 
  - If we trace back and try to make the graph 3 colorable, either **(a, b, c)** must be T. 
  - If all of them are **F**, then the graph is not colorable, and the clause cannot be satisfied

- **Another way of representing the problem:** 
  ![](/Users/cassandrale179/Desktop/Screen Shot 2020-02-18 at 11.23.07 AM.png)





### 34.3 SET COVER  

- **Set cover**:  U be a set of elements (the universe) and S ⊆ ( ℘ U). An exact covering of U is a collection of sets I ⊆ S such that every element of U belongs to exactly one set in I.
- **Example**: Given U = {1,2,3,4,5,6} and S = {{1,2,5}, **{2,5}, {4}, {1,3,6}**, {2,3,4}, {1,5,6}}
- 

### 34.4 CLIQUE PROBLEM 

Given a graph $G = (V,E)$ such that  there there 

![Image result for clique graph](https://i.stack.imgur.com/P8iX1.gif)











----

Sources:

- **Vertex cover - independent set reduction **https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/npcomplete.pdf
- **Stanford's 3Set reduction:** https://web.stanford.edu/class/archive/cs/cs103/cs103.1132/lectures/27/Small27.pdf

- 