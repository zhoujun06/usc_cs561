Name: Jun Zhou

Usage:
    Just Make, and an excutable 'hw2' will be generated.
    run ./hw2 , then done.

MACROS definition:
    there are four MACROS available. To use, just add into the Makefile.
    then make clean; make.

    EUC_INTEGER: using integer to represent a Euclidean distance, other wise
        a double value will be used.
    BIG_GX: choose the one with a bigger g(x) when two nodes have the same 
        f(x). other wise, it dependes on the implementation of std::priority
        queue, and it tends to be choosing the one that first into the queue
    HW2_DEBUG: for debug
    WITH_GREEDY_MAN: also run the greedy manhattan test.


Structure:

MapNode: Class of the node. The node A and B are handled together as one MapNode.
    And the actions of A and B are also seen as one action. Each node has a method
    to generate a Key, for the use of checking whether it exists in the queue or not.

Problem: Class of the problem. Has the initial state, the actions, the goal state. etc.

Queue.h: Template class of a queue, just encaptulation of the std::priority_queue.

Search: Class of the search algorithm. Each algorithm has it's own queue. And the difference
    is mainly which node is at the top of the queue. Defferent queues use different methods
    to determine which node has the most priority. 
    Different algorithms are finally implemented by the comparason class of the Queue.
    Different comparason class will use different values of the nodes to get the relative
    priority.

main: Read the input, construct the Search class, then run the doSearch, and output.


