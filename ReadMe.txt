DECA GAMES ASSIGNMENT DOC:

The project is built on VS2019 V142
-----The executable is in the solution directory itself so the executable is able to find where the resources are. SDL is linked statically so no dll needs to be installed when the executable is running-----


To achieve the targets I made a small engine which can handle different types of states in the game. Eg. GameOver, InGameState etc
With this we can deallocate the memory which isn't required and keep things in modular way. Things get easy to be extendible in future. 

I used std::vector for managing the grid because it gives the flexibility to handle objects with more freedom