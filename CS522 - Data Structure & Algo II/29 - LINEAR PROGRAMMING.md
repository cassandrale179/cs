## **CHAPTER 29: LINEAR PROGRAMMING**

### 1. FORMULATIONS 

- The constraints can either be inequalities (≤ or ≥) or equalities 

- ≷ 0: Some variables might be unrestricted (they can be positive or negative)

- **Representation**: Maximize or Minimize: $z = c_0 + c_1x_1 + ... c_nx_n$ 
  subject to 
  
- An equality constraint can be converted into 2 inequality constraints as follows:
   3x1 - 4x2 + 5x3 + 8x3 ≤ 56
   3x1 - 4x2 + 5x3 + 8x3 ≥ 56         

- This will result in the following linear equations:

   3x1 - 4x2 + 5x3 + 8x3 + s1 = 56
   3x1 - 4x2 + 5x3 + 8x3 - s2 = 56       

- And we will need to add an artificial variable for −s2:

   3×x1 - 4×x2 + 5×x3 + 8×x3 + s1 = 56
   3×x1 - 4×x2 + 5×x3 + 8×x3 - s2 + a1 = 56         
   
- **Handling unconstrained variables in Simplex:** Replace every unconstrained variable xi by 2 constrained ones as follows:
      $x_i = x_{i1} - x_{i2}$  where $x_{i1}, x_{i2} ≥ 0$ 

### 2. REPRESENTATIONS 

https://www.youtube.com/watch?v=ENEJnPTetBo



### 3. MINIMAX ASSIGNMENT

##### 3.1 TWO PERSON ZERO-SUM GAMES (MAXIMIN)

- **Problem**: a game where player B hides either 1, 2 or 3 coins. Player A then guesses the number of coins hid. If the guess is correct, player A gets four coins; if not, A must pay B the number of coins hidden. 

- **Randomization improves the game**: if A guesses 1,2,3,1,2,3,1,2,3,. . . then B can simply hide 2,3,1,2,3,1,2,3,1,. . . and win every round. By the same argument, it would be equally unwise for B to play in a predictable way.  

- **Let have:** 
  $x_{j}$: represents the probability that A plays move j  
  $\sum_{j=1}^n x_j = 1$ because the probability that 
  $a_{ij}$:  the reward A will get if A plays move j and B plays move $i$  
  Then the expected winnings of A is: 
  $\sum_{j=1}^{n}$ (reward A will get if A plays move j given B plays move i)  * (probability A will play move j)
  $= \sum_{j=1}^{n} a_{ij} x_j$

- **But A doesn’t know what B will play**, hence we need to maximize the minimum expected winning for A  

- **This would require A to solve the following optimization problem**
  Maximize $[ min_{i=1, 2....m} \sum_{j=1^n} a_{ij} x_n]$
  Subject to $\sum_{j=1}^{n} x_j  = 1$
  $x_{ij}  \geq 0$ 

- **We can have** $z = min_{i=1, 2....m} \sum_{j=1^n} a_{ij} x_n$

  - Maximize z 

  - Subject to $z \leq \sum_{j=1}^{n} a_{ij} x_j$ for $i = 1, 2, .... m$
    $z \leq \sum_{j=1}^{n} x_j  = 1$
    $x_j \geq 0$   for $j = 1... m$

  - **Given the board above, we have this linear programming**

     <img src="/Users/cassandrale179/Desktop/Screen Shot 2020-02-22 at 12.58.51 PM.png" style="zoom:50%;" />

    ​	$z \leq 4x_1 - x_2 - x_3$
    ​	$z \leq -2x_1 + 4x_2 - 2x_3$
    ​	$z \leq -3x_1 - 3x_2 + 4x_3$
    ​	$x_1 + x_2 + x_3 = 1$     (probability that A guess 1 coin, 2 coin or 3 coin should add up to 1)

    $x_1 \geq 0, x_2 \geq 0, x_3 \geq 0$

- **Optimal solution** is x1 = 23/107, x2 = 37/107, x3 = 47/107, giving z = 8/107. 
- **Conclusion**:  by randomly guessing one, two or three coins in the ratios 23:37:47, A can accumulate winnings at an average of no worse than 8/107 coins per round, regardless of the strategy (random or otherwise) that B adopts 

##### 3.2 TWO PERSON ZERO-SUM GAMES (MINIMAX)

- **Minimax**: should also tried to minimized his maximum possible loss over all move from A 
- **Let have:** 
  $y_i$: the probability that B plays move $i$
  $\sum_{i=1}^{n} y_i = 1$
  $a_{ij}$: represent the reward A would win, therefore it represent the loss for B 
  Then the expected loss of B is:  
  $\sum_{i=1}^{n} a_{ij}y_i$
- We want to minimize $a_{ij}y_i$ over all possible guess by A 

Source: [http://www.4er.org/CourseNotes/Book%20A/A-III.pdf](http://www.4er.org/CourseNotes/Book A/A-III.pdf) 

### 4. LINEAR PROGRAMMING RELAXATION

- **Pure IP Problem**: A linear programming problem in which all variables are required to be integers 
- **Mixed IP Problem**: some of the variable are required to be integers 
- **0-1 IP**: a IP problem in which variable can only either be 0 or 1 
- **Relaxations:**  

### 5. MINIMUM COST BIPARTE MATCHING

- **Hall's theorem:**  a bipartite graph with |V | ≤ |W| has a perfect matching if and only if for every subset S ⊆ V of the left-hand side, the number |N(S)| of S on the right-hand side is at least |S|. 
- **But a bipartite graph can have many perfect matchings:** therefore we introduce the **minimum cost** perfect matching, where we prefer a matching with the lowest cost
- **Maximum cost biparte matching**: just switch the cost  

