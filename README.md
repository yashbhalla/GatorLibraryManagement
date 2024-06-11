# Gator Library Management

The project's objective is to create the fictional library called GatorLibrary, utilizing a Red-
Black Tree to organize books based on their book-ids. GatorLibrary is designed to offer
functionalities such as adding and deleting books, as well as enabling patrons to borrow, return,
and reserve books.

## How to run the program?

The program is made using C++, and thus requires a makefile to create the executable. The
makefile makes the executable file ‘gatorLibrary’ which can be executed using terminal.

To run the executable, type:
.\ gatorLibrary <input_filename>

Replace the <input_filename> with the file name, for example, the input file is ‘input1.txt’
the command should look like:
.\ gatorLibrary input1.txt

## What is a Makefile?

The makefile serves the purpose of generating a target executable file. Its primary function is
to articulate a series of tasks essential for the execution of a program. Essentially, the makefile
establishes a connection between the source code and the final executable by specifying the
steps and dependencies involved in the build process. This enables efficient compilation and
linking of source code, ensuring that the executable is created in a systematic and reproducible
manner.

<img width="634" alt="image" src="https://github.com/yashbhalla/GatorLibraryManagement/assets/53651804/4255d6aa-ee73-465c-96df-d58d12600331">


## Concepts Utilized

A Red-Black Tree is a self-balancing binary search tree in computer science. In this tree
structure, each node has an additional attribute called color, which can be either red or black,
and plays a crucial role in maintaining balance.

The rotations executed in the program deviate from those illustrated in the lecture slides.
Instead, they align with rotations observed in an online tree simulator. This approach enhances
the visualization of the tree at each step, aiding in the identification of potential mistakes and
ensuring a more accurate implementation.

A Min Heap is a binary tree variant where the value of each parent node is less than or equal
to the values of its children. This characteristic holds true throughout the entire tree.
Consequently, the root node invariably holds the smallest (minimum) value in the heap.


