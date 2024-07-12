#include <SFML/Graphics.hpp>

class AnimatedSprite {
public:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;
    int frameCount;
    sf::Time animationSpeed;
    sf::Vector2i frameSize;

    AnimatedSprite(const std::string& texturePath, sf::Vector2i frameSize, int frameCount, float animationSpeedSec)
        : position(0.0f, 0.0f), speed(100.0f), frameCount(frameCount),
        animationSpeed(sf::seconds(animationSpeedSec)), frameSize(frameSize) {
        if (!texture.loadFromFile(texturePath)) {
            // Handle error
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    }

    void update(sf::Time deltaTime, const sf::Vector2f& direction) {
        static sf::Time timeSinceLastUpdate = sf::Time::Zero;
        static int currentFrame = 0;

        position += direction * speed * deltaTime.asSeconds();
        sprite.setPosition(position);

        if (direction != sf::Vector2f(0, 0)) {
            timeSinceLastUpdate += deltaTime;
            if (timeSinceLastUpdate >= animationSpeed) {
                currentFrame = (currentFrame + 1) % frameCount;
                sprite.setTextureRect(sf::IntRect(frameSize.x * currentFrame, frameSize.y * int(direction.y + 1 + direction.x + direction.x), frameSize.x, frameSize.y));
                timeSinceLastUpdate = sf::Time::Zero;
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Application");
    sf::Clock clock;

    AnimatedSprite character("../../assets/Spritesheet.png", sf::Vector2i(32, 32), 16, 0.15f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x = 1;

        sf::Time deltaTime = clock.restart();
        character.update(deltaTime, movement);

        window.clear();
        character.draw(window);
        window.display();
    }

    return 0;
}