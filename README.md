Implementation of the popular [Wa-Tor simulation](https://en.wikipedia.org/wiki/Wa-Tor) on C++ and Qt (cute).
My dev box was SuSE Linux tubleweed, however due to Qt's cross-platform design, the code can be recompiled in other platforms such as Windows and MacOS.

Main technical specs of this project:
- C++/Qt
- Type: Game/simulation
- Cross-platform
- Contains suite of automated tests using Qt Tests
- CI build pipeline using github actions using YAML

This simulation takes place in a n x m grid of cells (the “world”), where sharks and fish (“creatures”) coexist by moving, breeding and acting as predators/preys.  The point of the simulation is to watch how the world evolves based on how you tweak the starting parameters, such as size, starting number of sharks and fish, and breeding, lifetime intervals.

Below is a screenshot of the main window:
![image](https://github.com/user-attachments/assets/c5ee8d17-1947-472b-9d62-66e263c0861c)

In the original definition of the game, the world takes a toroid shape, where the top and bottom edges are connected, and also the left and right edges.  

I found that for the end-user that is watching the simulation, these rules are not very intuitive, so I chose to treat the world as a box enclosure where the edges are barriers.  That being said, in my implementation it is easy enough to fall back to the original definition.
While the game seems straightforward enough to code, it presents interesting design challenges if the implementation is to adhere to principles of single responsibility, encapsulation, extensibility, code reuse and others, making this an excellent exercise from a programming perspective.  On a C++ implementation, one must also take care of defining and utilizing constructors & destructors for the various classes and deciding where to use static objects, references and pointers to model when creatures move, breed, are eaten or die.
From the start, it becomes apparent that shark and fish have behaviors in common, but also rules that make them behave differently.  This can be modelled using a base abstract class “Creature” from which “Shark” and “Fish” classes inherit.  Moreover, it is entirely possible to extend the game with other fun creatures such as “Octopus”,  “Squids” or others with additional derived classes.  This adheres with the “Open for extension, closed for modification” SOLID design principle.
Each creature overrides the virtual “tick” method, that defines the next move the creature will make within the world (move, breed, etc) adhering to the rules of the research paper or your own fun variations of it.
Another element that must be modelled is the “World”.  

The world is the container where creatures live, move and die in the grid of cells.  As such, the world is modelled in its own class, that orchestrates each “tick” in the game, having knowledge of the layout of creatures within.  The world is further refined into a grid of “Cells”, where each cell represents an element in the grid.  Cells have knowledge of the existence or absence of creatures within.
As with other projects I have authored, I followed a strict rule of decoupling of the “Core” classes from the “Presentation” layer, which in this case is a Qt widget application (but can easily be a console or web application).  After each “tick” of the game, the Qt application renders the scene, by querying each cell of the world.  The core classes have no dependency with Qt.
For the Qt widget app, I used a QtGridLayout.  Each position in the grid matches a Cell in the world.  To render the cell, I used a QtLabel widget, where I loaded a JPG image into a Pixmap.

As I spent time on this project, I recalled some realtime strategy games I played years ago, such as “StarCraft” and “Warcraft”. While these games are obviously much more complex, with multiplayer, 3D worlds, fog of war, map traversal using A*, etc, many of the basic building blocks should be applicable.  Likewise, my 2D presentation layer with widgets could also be re-written using a more capable engine such as Unity, OpenGL or Direct X, but that was beyond the scope I had in mind for my project.
I was very pleased with the outcome I achieved, both from my learnings of Qt and Qt creator, but also making good use of C++ features such as algorithms, references, pointers, object oriented programming, etc.  I was able to make some enhancements to my implementation of the simulation, such as assigning distinct images to the various individual creatures, making it easier to track each individual in the grid, as opposed to using the same image for all.

In this project, I also utilized AI-assisted code generation in a few places:
- Auto-generation of doxygen comments for all header files.
- Test case creation for various classes.
- Addition of a new feature "sharks use 1 energy unit in each cycle".
- Optimization to build core CPP files to a static library (libGameOfLifeCore.a), so that I can statically link this library in the QT application and each of the Test projects, avoiding multiple rebuilds of the same source files.

For these AI assisted changes, I used GitHub Copilot, and I was very pleased with the outcome, being able to quickly accomplish these tasks.  In the case of code comments, the output from the AI assistant required little to no change.  In the case of test case generation, the output was also very impressive, but I consider that it is still necessary for the developer to review the code paths and types of test cases being generated and fill out any gaps. 
The energy unit expense feature was mostly correct, but it did require some intervention as the AI code did not correctly capture some nuances of how the logic is orchestrated by the world class. I was able to fix this easily. The refactor to a static library was also successful in the first try, allowing me to cut build times both locally and in my github CI workflow.
