objects = main.o algorithm.o AVL.o binNode.o BinTree.o BST.o graph.o\
    list.o listNode.o math.o queue.o RedBlack.o stack.o tools.o vector.o
 
main : $(objects)
    g++ -o main $(object)
AVL.o : BST.hpp
binNode.o : queue.hpp
BinTree.o : queue.hpp binNode.hpp
BST.o : BinTree.hpp
graph.o : vector.h queue.hpp stack.hpp
list.o : listNode.hpp
queue.o : list.hpp
RedBlack.o : BST.hpp
stack.o : vector.h
vector.o : math.h algorithm.hpp
 
.PHONY : clean
clean :
    -rm main $(objects)

