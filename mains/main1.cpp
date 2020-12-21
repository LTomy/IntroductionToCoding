#include <SFML/Graphics.hpp>

int main()
{
	// Opens a window.
    sf::RenderWindow win(sf::VideoMode(800, 600), "Introduction to coding", sf::Style::Close);

	// Limits the framerate
    win.setVerticalSyncEnabled(true);

	// Holds data about an event.
    sf::Event event;

	// As long as the window is open.
    while(win.isOpen())
    {
    // As long as the window has unretrieved events.
        while(win.pollEvent(event))
        {
        // If the event is the window being asked to be closed.
            if(event.type == sf::Event::Closed)
                win.close(); // We close it.
        }

		// We fill the 'drawing' buffer of the window with black.
        win.clear();

		// We display the 'drawing' buffer on the screen, inside the window.
        win.display();
   	}

    return 0;
}
