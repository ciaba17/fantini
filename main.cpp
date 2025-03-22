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
sf::Texture menuWPT;
sf::Sprite menuWP;


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
    sf::Color colore;
    sf::RectangleShape shape;
    sf::Text testo;
    sf::FloatRect area;
    
    
    Bottone(float x, float y, float width, float height, string testoS, sf::Color colore) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    
        area = sf::FloatRect(x, y, width, height);
    
        shape.setSize(sf::Vector2f(width, height));
        shape.setOutlineColor(sf::Color::Black);
        shape.setFillColor(colore);
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
        shape.setPosition(sf::Vector2f(x, y));
    
        testo.setFont(font);
        testo.setString(testoS);
        testo.setCharacterSize(WIDTH / 18);
        testo.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = testo.getLocalBounds();
        testo.setOrigin(textBounds.width / 2, textBounds.height / 2);
        testo.setPosition(sf::Vector2f(x, y));  // Posiziona il testo al centro
    }
    

    void draw() {
        window.draw(shape);
        window.draw(testo);
    }
};

void input();
void update();
void draw();
void drawMenu();
void drawBottoni();

bool suBottone();
int tiraDadi(int nDadi,int faccieDado);


vector<Player> players;
vector<Bottone> bottoni;


bool menu = true;


int main() {
    srand(time(NULL));
    // Carica il font per i testi
    font.loadFromFile("data/arial.ttf");
    menuWPT.loadFromFile("data/menuWP.jpg");
    menuWP.setTexture(menuWPT);
    menuWP.setPosition(0,0);
    sf::Vector2u textureSize = menuWPT.getSize();
    menuWP.setScale(WIDTH / textureSize.x, HEIGHT / textureSize.y);

    bottoni.push_back(Bottone(WIDTH/2, HEIGHT/1.5, WIDTH*0.2, HEIGHT*0.2, "START", sf::Color::Red));


    //--- LOOP PRINCIPALE DEL GIOCO ---
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            input();
        }
        
        update();

        draw();

    }
}


void input() {
    if (event.type == sf::Event::KeyPressed) {
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && suBottone()) {
        if (menu) {
            menu = false;
            bottoni.erase(bottoni.begin());
        }
    }

}


void update() {
    cerr << sf::Mouse::getPosition(window).x << "\t";
}


void draw() {
    window.clear();
    if (menu) {
        drawMenu();
    }

    drawBottoni();


    window.display();
}


void drawMenu() {
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(WIDTH/1.8, HEIGHT/1.8));
    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
    shape.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/2));

    sf::Text testo;
    testo.setFont(font);
    testo.setString(" BENVENUTO AL GIOCO \n           DELL'OCA");
    testo.setCharacterSize(WIDTH/22);
    testo.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = testo.getLocalBounds();
    testo.setOrigin(textBounds.width/2, textBounds.height/2);
    testo.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/3));

    window.draw(menuWP);
    window.draw(shape);
    window.draw(testo);
}


void drawBottoni() {
    for (auto bottone : bottoni) {
        bottone.draw();
    }
}


bool suBottone() {
    for (auto &bottone : bottoni) { // Controlla tutti i bottoni
        if (sf::Mouse::getPosition(window).x > bottone.x &&
            sf::Mouse::getPosition(window).x < bottone.x + bottone.width &&
            sf::Mouse::getPosition(window).y > bottone.y &&
            sf::Mouse::getPosition(window).y < bottone.y + bottone.height) { // Vede se il mouse si trova all'interno di un bottone
            return true;
        }
    }

    return false;
}


int tiraDadi(int nDadi,int faccieDado){
    
    int totale = 0;

    //genera e somma i numeri casuali dei dadi
    for(int i=0;i<nDadi;i++){
        totale += rand() % faccieDado + 1; 
    }

    return totale;
}