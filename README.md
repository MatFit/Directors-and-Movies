Small project done using hash tables and a skip list. Hash tables to allocate movie nodes. Skip list for probabilistic efficiency in searching for directors.
Hash tables are pretty simple in nature. As least with this implementation, we have a hash function that does something, returns a number that will be an index
to an array defined in the heap. Using modulo helps with getting a number within the array size. And what I used to deal with collisions were implementing linked lists.
So if collision occurs, just have the node that is about to be inserted as the new head of the linked list.

And with skip lists, at first seeing a diagram I thought was wacky. But actually it's nothing more of just layered linked lists. Where insertions works with
comparing values left and right starting at the top of the layer. In this case we're doing alphabetical comparisons with the directors name.
