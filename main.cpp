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

struct Sprite {
    float x, y;
    sf::Texture texture;
    sf::Sprite sprite;
    string path;

    Sprite(float x, float y) {
        this->x = x;
        this->y = y;
    }
    void setSprite(string path, float scale) {
        if (!texture.loadFromFile(path)) {
            std::cout << "Errore nel caricamento dell'immagine: " << path << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    
        // Ottieni la dimensione della texture
        sf::Vector2u textureSize = texture.getSize();
    
        // Imposta l'origine dello sprite al centro
        sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
        sprite.setScale(scale, scale);
    }

    void draw() {
        window.draw(sprite);
    }

};


void input();
void update();
void draw();
void drawMenu();
void drawPartita();
void drawBottoni();
void drawSprites();

bool suBottone();
int tiraDadi(int nDadi,int faccieDado);


vector<Player> players;
vector<Bottone> bottoni;
vector<Sprite> sprites;


bool menu = true;
bool partita = false;


int main() {
    srand(time(NULL));
    // Carica il font per i testi
    font.loadFromFile("data/arial.ttf");

    // Carica le texture e gli sprites
    // Sfondo menu
    sprites.push_back(Sprite(WIDTH/2, HEIGHT/2));
    sprites[0].setSprite("data/menuWP.jpg", 1);
    // Mappa
    sprites.push_back(Sprite(WIDTH/2, HEIGHT/2));

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
    
    sprites[0].draw();
    window.draw(shape);
    window.draw(testo);
    bottoni[0].draw();
}


void drawPartita() {
    sprites[1].draw();
    
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



int tiraDadi(int nDadi,int faccieDado){
    
    int totale = 0;

    //genera e somma i numeri casuali dei dadi
    for(int i = 0; i < nDadi; i++){
        totale += rand() % faccieDado + 1; 
    }

    return totale;
}