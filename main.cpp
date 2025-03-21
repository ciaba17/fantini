#include <time.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "gioco dei fantini"); // Crea l'oggetto finestra
sf::Event event; // Crea gestore event

struct Player {
    string nome;
    float x, y;
    int casella = 0;
    sf::Color colore;
    
    Player(string nome, sf::Color colore) {
        this -> nome = nome;
        this -> colore = colore;
    }
};


struct Bottone {
    bool premuto = false;
    float x, y;
    float width, height;
    string testo;
    sf::Color colore;
    sf::RectangleShape shape;
    sf::FloatRect area;
    
    Bottone(float x, float y, float width, float height, string testo, sf::Color colore) {
        this -> x = x;
        this -> y = y;
        this -> testo = testo;
        this -> width = width;
        this -> height = height;
        area = sf::FloatRect(x, y, width, height);

        
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(colore);
    }

    void drawBottone() {
        window.draw(shape);
    }

};


bool suTasto();


vector<Player> players;
vector<Bottone> bottoni;


int main() {
    srand(time(NULL));

    //--- LOOP PRINCIPALE ---
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            
        }
    }
}

bool suTasto() {
    for (auto bottone : bottoni) { // Controlla tutti i bottoni
        if (bottone.area.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) { // Vede se il mouse si trova all'interno di un bottone
            return true;
        }
    }
}