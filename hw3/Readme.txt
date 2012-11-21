Name: Jun Zhou

Usage:
    Just Make, and an excutable 'hw3' will be generated.
    run "./hw3", then done. 
    
    The output.txt will have the optimal steps and result.
    The prun.txt will have all the prunning information.



Structure:

    Problem: Class of the problem. Has the initial state, the actions, the goal state. etc.
        also includes definition of an Action, the game board.

    Search: Class of the MinMax search algorithm. 

    main: Read the input, construct the Search class, then run the doSearch, and output.


Heuristics:
    A basic heuristic function. Just count the scores of the current taken spaces, ignore the 
    empty spaces. This is based on the assumption that in the following steps, both palyers
    will get a same points.

    Default depth limit is 10.

    Another heuristic is defined to choose which action to go the first among valid actions.
    Still simple, just choose the one which has the most same colored neighbours. When there
    are 10 empty spaces, this heuristic roughly double the search speed.


