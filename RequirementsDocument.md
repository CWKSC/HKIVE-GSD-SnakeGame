# Requirements Document



This assignment is to implement a game using Object-Oriented Programming and Data Structure Techniques.  In this game, the player controls a snake moving around the board, with food appearing randomly from time to time.  The snake can eat the food to grow and get marks.  The food is represented on the board as brackets and quote symbols.  The snake can only digest the food when it matches the one on top of its stomach stack.  Extra marks will be awarded to the player when the food is paired up and digested.

 

**The Game Board and the Initial Position of Snake**

The game board can be presented in either way below:

![1564218558087](RequirementsDocument_Image\1564218558087.png)

It is a 10 x 10 game board and “o” is used to represent the snake body and “O” is used to represent the head of snake.  The initial position is shown as above.

 

 

**The food and the way to generate food**

There are 8 kinds of food, as listed below:

[ ] { } ( ) " '

Food is randomly generated, and the frequency is shown as below:

1st – 10th food:     appear every 3 moves (starting right after the first move)

11th – 20th food:   appear every 2 moves

the food after:        appear every 1 move

 

Food is randomly placed in any free space on the board (i.e. not occupied by the snake and any food).  When there is no more space on the board, it will stop generating the food until there is free space on the board again.

 

**The snake**

As shown in the Game Board section, the snake size is initially three.  It can move around by using WASD, where W is up, A is left, S is down and D is right. The movement controls the head’s next position and the body follow, i.e. the tail position will be updated to the second last position.  The following is an example of moving down: 

 ![1564218613861](RequirementsDocument_Image\1564218613861.png)


The above example also shows how a food is generated. If the snake keeps going down and eat the food, 

![1564218631355](RequirementsDocument_Image\1564218631355.png)

The length of the snake will increase:

![1564218675109](RequirementsDocument_Image\1564218675109.png)

And in this case, the position of tail remains unchanged and the length of the snake is increased by 1.

The stomach of the snake is a stack of size 5.  The food just eaten by the snake is pushed to the top of the stack and kept there.  Only the foods at the top of the stack can be digested, and this is done by eating a food which matched with the top element.  Following is the matching table

| **Top of the stack** | **Matching food** |
| -------------------- | ----------------- |
| [                    | ]                 |
| ]                    | n/a               |
| {                    | }                 |
| }                    | n/a               |
| (                    | )                 |
| )                    | n/a               |
| "                    | "                 |
| '                    | '                 |

Therefore, the snake should avoid eating close bracket like ] } ) before open bracket like [ { (.

When a pair matched foods is eaten, the food just eaten will not be added to the stomach and the food at the top of the stomach will be removed (popped).  In other words, the space in the stomach increases by 1.

Every single move of the snake has 1 mark, every eaten food will add extra 3 marks, every pair of quotes digested has 5 extra marks and every pair of brackets digested has 8 extra marks.

 

**Game over**

Like every living thing, the snake ends up being dead.  The following scenarios will lead to the snake’s dead:

1. The snake eats a food when its stomach stack is full;
2. The snake hits on the wall (the edge of the game board); and 
3. The snake hits on itself, i.e. hit on any part of its body.

 

**Sample User Interface**

![1564218694353](RequirementsDocument_Image\1564218694353.png)