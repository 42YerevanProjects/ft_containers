# 42 ft_containers

*"C++ containers, easy mode"*

In this project you can find the implementations of various container types of the C++ standard 
template library. For each container, there is an appropriately named class files.
The namespace will always be ft and the containers will be utilized by using ft::<container>.
The structure of the reference container is respected.
As a reminder, I coded it in C++98, so any new feature of the containers IS NOT
implemented, but every old feature (even deprecated) is implemented.

>  **Warning**: Don't copy/paste code you don't understand: it's bad for you, and for the school.


## About The Project

ft_containers is a project of the mandatory part of the cursus.
It's only made in C++ and was about recoding some containers from the STL.

In order to succeed, a good comprehension of how **templates**, **iterators**, **containers** and 
**algorithms** work was necessary. Of course, STL is not allowed. That means 
you cannot use \<iterator\> or even \<utility\>. 

Here are the specificities of the containers implemented by me:

- :arrow_right: **Vector:** a dynamic array that allows insertion at the end of the container. Elements can be easily access thanks with the corresponding index, but it's not the most optimal container if a lot of insertion / deletion are needed.
- :arrow_right: **List:** a circular linked list (with a neutral node linking beginning and end of the list). Better than vector for inserting or deleting elements.
- :arrow_right: **Stack:** a container adaptator (LIFO, last in first out).
- :arrow_right: **Queue:** a container adaptator (FIFO, first in first out).
- :arrow_right: **Map:** a sorted container using a Red Black binary tree (auto-equilibrates itself to optimize the time to find a value in the tree), in order to store the data like in a dictionnary (a key associated to its value).
- :arrow_right: **Set:** a sorted container using a Red Black binary tree (auto-equilibrates itself to optimize the time to find a value in the tree), in order to store elements that are unique because the value of the element identifies it.
- :arrow_right: **Multimap:** a sorted container using a Red Black binary tree (auto-equilibrates itself to optimize the time to find a value in the tree), in order to store the data like in a dictionnary (a key associated to its value), where key are not unique.
- :arrow_right: **Multiset:** a sorted container using a Red Black binary tree (auto-equilibrates itself to optimize the time to find a value in the tree), in order to store set elements which are not unique.

All my containers use an allocator to manage properly their memory, iterators to access their datas, and handle the same constructors / methods than the containers from the STL in C++98.


## Testers

The testers available in the repository :

- [mli's containers_test](https://github.com/mli42/containers_test) (very useful, much recommended) Tests not only the vector, stack, map, set but also the older version containers like deque, multimap, multiset and list (you can find them on his repo).

- [ft_containers_unit_tests](https://github.com/divinepet/ft_containers-unit-test) Will show you the speed of your container functions in milliseconds compared to STL.

It will test all the constructors, methods and iterators, by comparating your containers with the STL containers, and making a diff if some errors occured.
Also, you can choose which tests you want to execute, in the case you're checking specific containers / methods.
