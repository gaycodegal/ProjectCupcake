# ProjectCupcake

You can find SDL2, SDL-image, and SDL-ttf under SDL_iOS. 
This may work for whatever operating system you're writing for, 
so you may want to search around for the includes for whatever your
operating system is.

Put your main project files in the main folder, classes in the class
folder other code under the misc_code folder, and tests under the test
folder.

Initialize whatever needs initializing in global_init.cpp, keep what you
can out of main.cpp. Major Singletons should be an instance of component.
See classes/EventDispatcher or test/RandomSquares for a sample.
