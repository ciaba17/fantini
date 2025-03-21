#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

const float WIDTH = 1920;
const float HEIGHT = 1080;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "gioco dei fantini"); // Crea l'oggetto finestra
sf::Event event; // Crea gestore event
sf::Font font; 

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

        
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(colore);
        shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
        shape.setPosition(sf::Vector2f(x, y));
    }

    void draw() {
        window.draw(shape);
    }

};

void draw();
void drawTitolo();

bool suTasto();


vector<Player> players;
vector<Bottone> bottoni;


int main() {
    srand(time(NULL));
    // Carica il font per i testi
    if (!font.loadFromFile("data/arial.ttf")) {
        std::cerr << "Errore: impossibile caricare il font!" << std::endl;
        return -1;
    }


    //--- LOOP PRINCIPALE DEL GIOCO ---
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        

        draw();

    }
}


void draw() {
    window.clear();
    drawTitolo();


    window.display();
}

void drawTitolo() {
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(WIDTH/1.8, HEIGHT/1.8));
    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
    shape.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/2));

    sf::Text testo;
    testo.setFont(font);
    testo.setString("BENVENUTO AL GIOCO \n           DELL'OCA");
    testo.setCharacterSize(80);
    testo.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = testo.getLocalBounds();
    testo.setOrigin(textBounds.width/2, textBounds.height/2);
    testo.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/3));

    window.draw(shape);
    window.draw(testo);
}

bool suTasto() {
    for (auto bottone : bottoni) { // Controlla tutti i bottoni
        if (bottone.area.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) { // Vede se il mouse si trova all'interno di un bottone
            return true;
        }
    }
    return false;
}