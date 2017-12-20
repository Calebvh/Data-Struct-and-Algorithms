These Three files are the 3 programming assignments from the Data Structures 
and Algorithms course taught by Professor Berman. 

1. MergeSort vs Quicksort using Insertionsort as a threshold sort
	The purpose of this program is to compare the computing times of the two classical sorting
algorithms Mergesort and Quicksort where Insertionsort is used as a threshold sort. Although for
large lists, Insertionsort is, on average, much slower than Mergesort and Quicksort, it is faster than
both for sufficiently small lists. A useful technique to improve the efficiency of a divide-andconquer
sorting algorithm is to employ a sorting algorithm such as Insertionsort when the input size
is smaller than or equal to some threshold t (e.g., a number between 8 and 16 usually works well).
Instead of the bootstrap condition being a list of size <=1 and simply doing nothing other than
return when this condition is satisfied, the bootstrap condition is now a list of size <= t and
Insertionsort is called when this condition is satisfied.


2. Binary Search Trees and Implementing an Electronic Phone Book
	1. Design and implement the class Person, which represents the last name (first
and last) and phone number of a person. You will store instances of this class in
the phone book.
	2. Design and implement the class Book, which represents the phone book. The
class should contain a binary search tree as a data member, where the key is the
person’s name (when comparing keys first compare last names; then if last names
are the same compare first names. You may assume that no two people have the
same first and last names). This tree contains the people in the phone book.
	3.  Output names in alphabetical order (of last names and then first names if last
names are the same). Hint: Use inorder traversal. Display table with names (first
and last) and phone numbers with appropriate title, headers, and formatting.
	4.  Add member functions that use a text file to save and restore tree
 Design and implement the class UserInterface, 
which provides the program’s user interface.

	5. Design your program first without saving and restoring from a text file, i.e., start with an
empty phone book and perform operations in one session/run (worth 90 points). Once
you have this working do the full assignment involving a text file. 

3. Topological Sort and DAGs

	This program involves implementing an ADT Directed Graph and performing a
topological sort, acyclic check, and strong connectivity check for the directed graph. You
are to implement the directed graph using pointer-based adjacency lists. Your class
Digraph should includes constructors and a destructor, operations of edge addition,
edge deletion, etc., as well as the operation of topological sorting and acyclic check. You
are to implement the topological sorting operation using DFT as discussed in class and
Chapter 5 of the textbook. Your program should include the following two parts.