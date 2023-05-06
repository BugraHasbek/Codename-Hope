#include <SFML/Graphics.hpp>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");

    // Load the background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Media/Textures/background.png")) {
        return -1; // error loading the texture
    }

    // Create the background sprite
    sf::Sprite background(backgroundTexture);

    // Load the main character texture
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile("Media/Textures/character.png")) {
        return -1; // error loading the texture
    }

    // Create the main character sprite
    sf::Sprite character(characterTexture);

    // Set the character's starting position
    character.setPosition(400, 300);

    // Set the character's movement speed
    float movementSpeed = 200.f;

    // Create a clock to measure elapsed time
    sf::Clock clock;

    // Start the game loop
    while (window.isOpen())
    {
        // Measure elapsed time
        float deltaTime = clock.restart().asSeconds();

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            character.move(0, -movementSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            character.move(0, movementSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            character.move(-movementSpeed * deltaTime, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            character.move(movementSpeed * deltaTime, 0);
        }

        // Draw the background and character sprites
        window.clear();
        window.draw(background);
        window.draw(character);
        window.display();
    }

    return 0;
}
