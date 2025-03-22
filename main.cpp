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
vector<Player> players;


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
    
        area = sf::FloatRect(x - width / 2, y - height / 2, width, height);
    
        shape.setSize(sf::Vector2f(width, height));
        shape.setOutlineColor(sf::Color::Black);
        shape.setFillColor(colore);
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
        shape.setPosition(sf::Vector2f(x, y));
    
        testo.setFont(font);
        testo.setString(testoS);
        testo.setCharacterSize(width/3.4);
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
vector<Bottone> bottoni;


struct Sprite {
    sf::Texture texture;
    sf::Sprite sprite;

    Sprite(float x, float y, float scale, const std::string& textureFile) {
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Errore nel caricamento della texture: " << textureFile << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(scale, scale);
        sf::Vector2u textureSize = texture.getSize();
        sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    }

    void draw() {
        window.draw(sprite);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    sf::Vector2f getPosition() {
        return sprite.getPosition();
    }
};
Sprite menuWP(WIDTH / 2, HEIGHT / 2, 1.0f, "data/menuWP.jpg");
Sprite mappa(WIDTH / 2, HEIGHT / 2, 1.0f, "data/mappa.png");


void input();
void update();
void draw();
void drawMenu();
void drawPartita();
void drawBottoni();
void drawSprites();
void turnoPlayer(int nPlayer);
void controlloCasella(int nPlayer);

bool suBottone();
int tiraDadi(int nDadi,int faccieDado);


bool menu = true;
bool staTirandoDado = false;
bool partita = false;


int main() {
    srand(time(NULL));
    // Carica il font per i testi
    font.loadFromFile("data/arial.ttf");
    // Crea i players
    players.push_back(Player("Giocatore", sf::Color::Red));
    players.push_back(Player("CPU 1", sf::Color::Blue));
    players.push_back(Player("CPU 2", sf::Color::Green));
    players.push_back(Player("CPU 3", sf::Color::Yellow));

    // Crea bottone start
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
            partita = true;
            bottoni.erase(bottoni.begin());
        }
    }
}


void update() {
    if (partita) {
        for (int i = 0; i < 4; i++) {
            turnoPlayer(i);
        }
    }
}


void draw() {
    window.clear();

    if (menu) {
        drawMenu();
    }
    else if (partita) {
        drawPartita();
    }
    
    window.display();
}


void drawMenu() {
    // Rettangolo bianco
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(WIDTH/1.8, HEIGHT/1.8));
    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
    shape.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/2));

    // Titolo
    sf::Text testo;
    testo.setFont(font);
    testo.setString(" BENVENUTO AL GIOCO \n           DELL'OCA");
    testo.setCharacterSize(WIDTH/22);
    testo.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = testo.getLocalBounds();
    testo.setOrigin(textBounds.width/2, textBounds.height/2);
    testo.setPosition(sf::Vector2f(WIDTH/2, HEIGHT/3));
    
    menuWP.draw();
    window.draw(shape);
    window.draw(testo);
    bottoni[0].draw();
}


void drawPartita() {
    mappa.draw();
    
}


bool suBottone() {
    for (auto& bottone : bottoni) { // Controlla tutti i bottoni
        // Ottieni la posizione del mouse relativa alla finestra
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosInWindow = window.mapPixelToCoords(mousePos);

        // Verifica se il mouse è sopra il bottone
        if (bottone.area.contains(mousePosInWindow)) { // Vede se il mouse si trova all'interno di un bottone
            return true;
        }
    }
    return false;
}


void turnoPlayer(int nPlayer) {
    int risultatoDado = 0;

    //mettere animazione di cambio turno

    staTirandoDado = true;
    
    while (staTirandoDado) {
        //mettere che appare il dado e aspetta che clicchi lo schermo per tirare
        staTirandoDado = false;
    }

    risultatoDado = tiraDadi(1, 6);

    //mettere l'animazione del tiro del dado possibilmente in funzione

    players[nPlayer].casella += risultatoDado;

    //mettere l'animazione del movimento casella possibilmente in funzione

    controlloCasella(nPlayer);
}


int tiraDadi(int nDadi,int faccieDado) {
    int totale = 0;

    //genera e somma i numeri casuali dei dadi
    for(int i = 0; i < nDadi; i++){
        totale += rand() % faccieDado + 1; 
    }

    return totale;
}


void controlloCasella(int nPlayer) {
    switch (players[nPlayer].casella){
    case 1:
        break;
    default:
        break;
    }
}