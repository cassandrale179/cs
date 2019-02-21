# CS380 Documentation 

## Homework 1 
### Problem
Implement algorithm for [Rush	Hour](https://www.thinkfun.com/products/rush-hour/), a	puzzle	game	that	
involves	sliding	“vehicles”	around	a	grid	to	alleviate	gridlock	and	free	your	“car”	from	the	
traffic	jam. Given an input string, returns all possible moves that could be make from that given board.  
```
Input : "  o aa|  o   |xxo   |ppp  q|     q|     q"
Output: board representation of one move  
 ------    
|  o aa|  
|  o   |  
|xxo   |  
|ppp  q|   
|     q|  
|     q|   
 ------ 
``` 

### Approach 
- **def converStringToMatrix(self, strBoard)**: this convert a string representation into a 6 x 6 array. It records all coordinates of a block (i,j) and stores it in a dictionary. It also stores the block in a horizontal / vertical set which identifies which direction a block can move. 
- **def sortBoard()**: this function stores all coordinates (i,j) of each block into a dictionary, and sort the coordinates, so we can identify where the head and tail of each block is. 
- **def findPossibleMoves(self, block):** this returns all (i,j) coordinates of which a block can move to, and the corresponding direction for each of the (i,j) coordinates [left, right, up, down] 
- **def makeBlockMove(self, block, move, loc, direction):** this takes in a block, a move (i,j) which it could move to, the block current location (loc), and the direction of the move, then make the block move to that direction 
- **def clone(self,cloneLoc, block, move, direction):** this returns a copy of the board, but with the new move being made on the board. 
- **def createBoard(strBoard)**: master function, which calls all the above helper functions. The algorithm ran as follow (in pseudocode): 
```python
converStringToMatrix(strBoard)               # convert board to a matrix 
sortBoard()                                  # sort all the coordinates for each block on the board 
for each block:                              # for each block, we find all moves it can move to 
  all_block_moves = findPossibleMoves()   
  for each move in all_block_moves:          # for each move, we create a new board representation with the new move 
    new_location = makeBlockMove()    
    cloneBoard = clone(new_location)           
```

## Homework 2: 
### Problem 
**Part I:** Write	a	method for	your	Board class	that does	a	random	walk	through	next	board	states.	
Specifically, given	a	positive	integer N=10,	the	random	walk	should	do	the	following:
  1. generate	all	the	moves	that	can	be	generated	in	the	board
  2. select	one	at	random
  3. execute	that	move,
  4. Stop	if	we’ve	reached	the	goal	or	we’ve	already	executed	N moves,	otherwise	 repeat.

**Part II:** Write	a	method	for	your	Board class	that does	a	breadth-first	search	from	the	given	
board,	returning	the	first	path	found	that	reaches	the	solution	state.	 

**Part III:** Write	a	method	for	your	Board class that does	an	A*	search	from	the	given	board,	
returning	the	first	path	found	that	reaches	the	solution	state. Note	that	as	part	of	this	
process,	you	will	need	to	choose	and	implement	a	good	heuristic function ℎ(n),	such	that	
A*	can	reasonably	estimate	the minimum	cost	from	a	given	state	to	the	goal	state.


### Approach 
1. **randomWalk(self, matrixBoard, n)**: recursive function 
 - **Base case 0**: if the car already at exit, return; 
 - **Base case 1**: if we ran out of random moves, return the board we currently on
 - **Recursive function**: pick a random board from the list of possible moves generated from Board A
   + Create a new board from that random board
   + Get its children
   + Call the recursive function again with that children 
 - **Conclusion**: this approach might not be effective due to the fact that we might repeat ourselves, since children of board A could be a parent of board A (the case where we walk up and down, up and down...). Due to the fact that we do not have a visited queue, we do not keep track if we have made a previous move or not, therefore, we might revisited a move we already made. 
 
2. **bfs(initialBoard)**: create a Breadth First Search to find the solution 
 - We create two lists, a parent list and a children list
 - BFS can be carry out by a queue, so the logic can be explained like this:
  ```python
  Queue = set(initialBoard) 
  Parent = initialBoard 
   for children of parent:
    queue.add(children) if children not yet in queue
    parent = parent.next     
 ``` 
 
 - We kept repeating the aforementioned algorithm until we find the exit
 - This approach is complete, because:
   + We make the queue a set, so we only append boards that don't exist in the queue yet
   + Queue never contained duplicate boards, meaning, if we have try a move, we won't revisit the move again
   + Each time we add a layer (which is the children), we will eventually find the path by visiting all children of the tree 
   + Parent is increment by 1, so this is how we dequeue. We just move onto the next element of the queue and explored all its children. 
- Boards visited: 77 for string  '  o aa|  o   |xxo   |ppp  q|     q|     q' 
 
3. **astar()**: implement [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) that find the path such that the depth < bfs 
   - f(x) = h(x) + g(x), in which h(x) is the heuristics and g(x) is the cost to make that move
   - h(x) = the heuristics -> in this case, the number of blocks that stands between x and the exit 
   - g(x) = the number of states between a given board A to reach to board B. In an A* algorithm, we want to minimize the number of states, as we want to reach to the end goal as soon as possible 
  
```
 ------     ------      ------     ------    ------    ------     ------      ------     ------    ------
|  o aa|   |  o aa|    |  oaa |   |  oaaq|  |  oaaq|  |   aaq|   |   aaq|    |  oaaq|   |  oaaq|  |  oaa |
|  o   |   |  o  q|    |  o  q|   |  o  q|  |  o  q|  |     q|   |     q|    |  o  q|   |  o  q|  |  o   |
|xxo   |   |xxo  q|    |xxo  q|   |xxo  q|  |xxo  q|  |xx   q|   |   xxq|    |  oxxq|   |  oxxq|  |  oxx |
|ppp  q|   |ppp  q|    |ppp  q|   |ppp   |  |   ppp|  |  oppp|   |  oppp|    |   ppp|   |  ppp |  |  pppq|
|     q|   |      |    |      |   |      |  |      |  |  o   |   |  o   |    |      |   |      |  |     q|
|     q|   |      |    |      |   |      |  |      |  |  o   |   |  o   |    |      |   |      |  |     q|
 ------     ------      ------     ------    ------    ------     ------      ------     ------    ------  
 Total paths explored: 45
 ```
*Example of a board state using A* algorithm* 

- Kept an opened and closed dictionary set, in which the opened set are node we are currently visiting and still have children to explored, while closed include node that had already been visit and we have explored all its possible children 
```python
opened = defaultdict(list)
closed  = {}    
``` 
- **def countObstacles (self, strBoard)**: count the number of obstacles for a given board, so for example, in the first one, we have 1 obstacle that block to the exit
- **def costCalculate (opened)**: given the equation f(x) = h(x) + g(x), returned a dictionary set in which the key is the string f(x), wheres the value is the cost g(x) and the number of blocks that block our car h(x). This set will be sorted based on h(x), so min(cost + heuristics) is always favored. 
```python
 sorted_set = {
 'strA': 5, 
 'strB': 6
 ...
 }
```
- **def getNextStep (self, bestBoard, cost, opened, closed)**: this function will initialize a new board based on a given str bestBoard, add +1 cost to its children, then add its children to the open set. Noted: if a children is a duplicate inside the opened or closed set, it will not add that children, because we have either already finished explored it or will explored it. This is to prevent duplication, so we don't move one block back and forth, while kept increasing the cost. This returned the opened set, which will contain new unique nodes to examine. 
- **def astar(self, initialBoard)**: this function calls all other function 
   1. Initialize opened set = {initialBoard: f(x)} 
   2. While opened set() -> we have nodes to explore:
      - Calculate all the f(x) of its children
      - Add its children to the opened set
      - Delete the parent from open set after we had added all its children, because it meant we never revisit this state again 
      - Add the parent to the close set (so if a children is a duplicate of that parent, we won't add it to open set) 
      - Check if any children has obstacles = 0 (meaning our car can exit since no block between it)
      - If obstacles = 0, break out of the loop
      - Else we repeat the loop and add new nodes to the opened set
   3. In short, we are comparing all possible states (children + parent) inside the opened set, and pick the one with minimum f(x). 
   4. If there are f(x) of similar costs, we randomly pick one. It doens't matter if the order is random because if its children turn out to be a worse path (does not solve the puzzle), we can always traverse back up the path because we store the parent inside the open set 



## Homework 3
### Problem 
**Part I (Random Game) :** [Connect	4](https://shop.hasbro.com/en-us/product/connect-4-game:80FB5BCA-5056-9047-F5F4-5EB5DF88DAF4) is	a 2-player	adversarial	game	in	which	a	player	drops	 pieces	into	a	grid	and	tries	to	get	the	pieces	aligned	to	win	the	game. Augment	the	code	with	a	“random”	command	that	plays	a	random	game	 between	two	players. You should	assume	that	‘X’	plays	first,	and	the	game	terminates when	one	player	has	won	
or	a	tie	has	occurred.	

**Part II (Minimax Algorithm) :** Your	final	and	most	involved	task	is	to	augment	the	code	with	a	“minimax”	command	that	
plays	a	game	between	a random	agent	and	a	minimax	agent. Create	a	game	such	that	player	‘X’	(who	moves	first)	is	a	RandomPlayer,	whereas	 player	‘O’	is	a	MinimaxPlayer.	You	should	see	‘X’	playing	randomly,	but	‘O’	playing	
sensibly,	with	‘O’	winning	all	(or	almost	all)	of	the	games. 

**Part III:(Playing	with	Minimax +	Alpha-Beta	Pruning)** Implement	a	new	player	MinimaxAlphaBetaPlayer that	uses	alpha-beta	pruning	in	 conjunction	with	minimax	to	play	the	game.	You	must	also	augment both	this	player	and	 your	MinimaxPlayer	with	timing	code that	outputs	the	real	time	(in	seconds)	needed	to	 compute	a	next	move.	Then,	you	should	add	a	shell	command	“alphabeta” that	acts	just	 like	the	“minimax” command	except	that	it	replaces	the	minimax	player	with	an	alphabeta
player	(for	‘O’;	‘X’ is	still	a	random	player). 


### Approach
1. **Part I (Random Game)**: this is extremely easy as we already have built-in functions to generate the next moves. Given an array of possible next moves, we have the following algorithm:
 - Choose a random move from the array of possible next moves
 - Set the current state of the game (self.board) to be that next possible move
 - Switch the player and repeat the process 
 ```python 
  while self.board.winner() == None: 
    nextMove = self.player1.move 
    self.gamePlay.append(nextMove)
    self.board = nextMove

    nextMove = self.player2.move()
    self.gamePlay.append(self.board)
    self.board = nextMove 
    .... 
  ``` 
  
  2. **Part II (Minimax)**: ![Minimax algorithm example on Tic-Tac-Toe board](https://cdn-images-1.medium.com/max/1600/1*CIluGSNECrXOoNSskenW4w.jpeg) 
  
  
- Create a class Path that has the following attributes 
```python 
  self.tree = {}              # this is the game tree with multiple paths 
  self.path = []              # an array that store the path to winning state from the root 
  self.root = initialBoard    # the initial given board which will be the root of the tree 
  self.leaf = None            # the final board of the winning state 
```

- The class Path will generate a tree from a given board, and stop generating the tree when we reached a level which we had a winning or tie situation. We can do this by doing a BFS (since we would prefer to stop at the lowest depth and exploring horizontally, not going into a deep end which might contain no winning state for O), and a generic algorithm / pseudocode: 
```python
queue = [root] 
leaf = None 
while not found (winning_board or tie_board) and queue.exist():
 children = queue[0].next()     # get children of the first element in queue 
 children = filter(children not in tree) 
 for child in children:
   if child == winning_board or child == tie_board:
    leaf = winning_board / tie_board
    break; 
   else: 
    queue += children 
 queue.dequeue() 
``` 


   
 
 

