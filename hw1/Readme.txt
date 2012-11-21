Name: Jun Zhou

Usage:
Just Make, and an excutable 'hw1' will be generated.
run ./hw1 , then done.

Structure:

MapNode: Class of the node. The node A and B are handled together as one MapNode.
And the actions of A and B are also seen as one action. Each node has a method
to generate a Key, for the use of checking whether it exists in the queue or not.

Problem: Class of the problem. Has the initial state, the actions, the goal state. etc.

Queue.h: Template class of a queue, just encaptulation of the std::queue and std::priority_queue.

Search: Class of the search algorithm. Each algorithm has it's own queue. And the difference
is mainly which node is at the top of the queue. Defferent queues use different methods
to determine which node has the most priority. 
Different algorithms are finally implemented by the comparason class of the Queue.
Different comparason class will use different values of the nodes to get the relative
priority.

main: Read the input, construct the Search class, then run the doSearch, and output.
