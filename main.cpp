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
    float x, y;
    string testo;
    sf::RectangleShape shape;
    

};


bool suTasto();

vector<Player> players;

int main() {
    srand(time(NULL));

    //--- LOOP PRINCIPALE ---
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            
        }
    }
}

bool suTasto() {
    if (sf::Mouse::getPosition(window) > ) {
        
    }
}