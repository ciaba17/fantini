#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const float WIDTH = 1920;
const float HEIGHT = 1080;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "gioco dell'oca"); // Crea l'oggetto finestra
sf::Event event; // Crea gestore eventi
sf::Font font;


struct Player {
    int numero;
    string nome;
    float x, y;
    float initX, initY;
    int casella = 0;
    bool staGiocando = false;
    sf::Color colore;
    sf::CircleShape shape; // Rappresenta il giocatore con un cerchio

    Player(string nome, sf::Color colore, int numero, int x, int y) {
        this->x = initX = x;
        this->y = initY = y;
        this->numero = numero;
        this->nome = nome;
        this->colore = colore;
        shape.setRadius(WIDTH*0.008); // Imposta il raggio della "pietra" che rappresenta il giocatore
        shape.setFillColor(colore);
        setPosition(x, y);
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    void draw() {
        window.draw(shape);
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
        testo.setCharacterSize(width / 3.4);
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
// Crea gli sprites
Sprite menuWP(WIDTH / 2, HEIGHT / 2, 1, "data/menuWP.jpg");
Sprite mappa(WIDTH * 2.65 / 4, HEIGHT * 1.48 / 4, 0.8, "data/mappa.png");
Sprite d1(0, 0, 0.4, "data/d1.png");
Sprite d2(0, 0, 0.4, "data/d2.png");
Sprite d3(0, 0, 0.4, "data/d3.png");
Sprite d4(0, 0, 0.4, "data/d4.png");
Sprite d5(0, 0, 0.4, "data/d5.png");
Sprite d6(0, 0, 0.4, "data/d6.png");


bool suBottone();
int tiraDadi(int nDadi);
void creazioneMenu(sf::RectangleShape& shape, sf::Text& testo);
void creazionePausa();
void drawMenu(sf::RectangleShape shape, sf::Text testo);
void drawPausa(sf::RectangleShape shape);
void drawDado();
void input();
void update();
void turnoPlayer(Player& player);
void controlloCasella(Player& player);
void sleep(int ms);

bool menu = true;
bool partita = false;
bool pausa = false; 
int totaleDadi;
vector<int> facciaDadi;


int main() {
    srand(time(NULL));
    mappa.sprite.setScale(0.8, 0.85); // Risetta la scala della mappa
    font.loadFromFile("data/arial.ttf"); // Carica il font
    // Crea i player
    players.push_back(Player("Giocatore", sf::Color::Red, 1, WIDTH*0.2745, HEIGHT*2.6669/4));
    players.push_back(Player("CPU 1", sf::Color::Blue, 2, WIDTH*0.2995, HEIGHT*2.6669/4));
    players.push_back(Player("CPU 2", sf::Color::Green, 3, WIDTH*0.2745, HEIGHT*2.796/4));
    players.push_back(Player("CPU 3", sf::Color::Yellow, 4, WIDTH*0.2995, HEIGHT*2.796/4));
    // Crea il menu
    sf::RectangleShape shape;
    sf::Text testo;
    creazioneMenu(shape, testo);
    // Crea il menu pausa
    creazionePausa();


    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            input();
        }

        update();

        window.clear(sf::Color::Cyan);
        if (menu) {
            drawMenu(shape, testo);
        }
        else if (partita) {
            mappa.draw();
            drawDado(); // Chiamata per il dado
            for (auto& player : players) {
                player.draw();
            }
        }
        else if (pausa) {
            drawPausa(shape);
        }
        window.display();
    }
}

void input() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && suBottone()) {
        if (menu) { // Se si è nel menu
            menu = false;
            partita = true;
            bottoni.erase(bottoni.begin());
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && partita) { // Input per lanciare i
        players[0].staGiocando = true; // Il giocatore 1 inizia il turno
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && partita) {
        partita = false;
        pausa = true;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && pausa) {
        partita = true;
        pausa = false;
    }
}


void update() {
    if (partita) {
        // Controlla se e di chi è il turno
        for (auto& player : players) {
            if (player.staGiocando) {
                turnoPlayer(player);
            }
        }
    
        for (auto& player : players) {
            if (player.staGiocando) {
                sleep(1000);
                player.staGiocando = false;

                if (player.numero % 4 != 0) {
                    players[(player.numero) % 4].staGiocando = true;
                    break;
                }
            }
        }
    }

    cerr << players[0].casella << '\t';
    cerr << players[1].casella << '\t';
    cerr << players[2].casella << '\t';
    cerr << players[3].casella << '\t';
    cerr << endl;
}


void creazioneMenu(sf::RectangleShape& shape, sf::Text& testo) {
    // Rettangolo bianco
    shape.setSize(sf::Vector2f(WIDTH / 1.8, HEIGHT / 1.8));
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
    // Testo
    testo.setFont(font);
    testo.setString(" BENVENUTO AL GIOCO \n           DELL'OCA");
    testo.setCharacterSize(WIDTH / 22);
    testo.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = testo.getLocalBounds();
    testo.setOrigin(textBounds.width / 2, textBounds.height / 2);
    testo.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 3));
    // Bottone start
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT / 1.5, WIDTH * 0.2, HEIGHT * 0.2, "START", sf::Color::Red));
}

void creazionePausa() {
    // Bottone RIPRENDI
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT / 1.5, WIDTH * 0.2, HEIGHT * 0.2, "RIPRENDI", sf::Color::Red));
    // Bottone TORNA AL MENU
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT / 2, WIDTH * 0.2, HEIGHT * 0.2, "TORNA AL MENU", sf::Color::Red));
    // Bottone ESCI DAL GIOCO
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT / 2.5, WIDTH * 0.2, HEIGHT * 0.2, "ESCI DAL GIOCO", sf::Color::Red));
}

void drawMenu(sf::RectangleShape shape, sf::Text testo) {
    menuWP.draw(); // Disegna il background del menu
    window.draw(shape); // Disegna il rettangolo
    window.draw(testo); // Disegna il testo
    bottoni[0].draw(); // Disegna il bottone START
}

void drawPausa(sf::RectangleShape shape) {
    window.draw(shape); //disegna il rettangolo
    bottoni[1].draw();  // Disegna il bottone RIPRENDI  
    bottoni[2].draw();  // Disegna il bottone TORNA AL MENU
    bottoni[3].draw();  // Disegna il bottone ESCI DAL GIOCO
}

void drawDado() {
    int x, y;

    // Itera per ogni dado
    for (int i = 0; i < facciaDadi.size(); i++) {
    // Imposta la posizione del dado in base al numero del dado
        switch (i) {
            case 0:
                x = y = WIDTH * 0.35 / 4;
                break;
            case 1:
                x = WIDTH * 1 / 4;
                y = WIDTH * 0.35 / 4;
                break;
            case 2:
                x = WIDTH * 0.35 / 4;
                y = HEIGHT * 1.6 / 4;
                break;
            case 3:
                x = WIDTH * 1 / 4;
                y = HEIGHT * 1.6 / 4;
                break;
            default:
                break;
        }

        // Disegna la faccia del dado
        if (!players[0].staGiocando || players[1].staGiocando || players[2].staGiocando || players[3].staGiocando) { // Se è il turno di un giocatore
            switch (facciaDadi[i]) {
                case 1:
                    d1.setPosition(x, y);
                    d1.draw();
                    break;
                case 2:
                    d2.setPosition(x, y);
                    d2.draw();
                    break;
                case 3:
                    d3.setPosition(x, y);
                    d3.draw();
                    break;
                case 4:
                    d4.setPosition(x, y);
                    d4.draw();
                    break;
                case 5:
                    d5.setPosition(x, y);
                    d5.draw();
                    break;
                case 6:
                    d6.setPosition(x, y);
                    d6.draw();
                    break;
                default:
                    break;
            }
        }
    }
}


int tiraDadi(int nDadi) {
    totaleDadi = 0;

    for (int i = 0; i < nDadi; i++) {
        facciaDadi.push_back(rand() % 6 + 1); // Aggiunge il risultato del dado all'array
        totaleDadi += facciaDadi[i];
    }

    
    return 1; // PER ORA NON USATO
}


void turnoPlayer(Player& player) {
    cerr << endl << "sta giocando" << player.nome << endl;

    // Tira i dadi
    facciaDadi.clear(); // Elimina i risultati dei dadi precedenti
    tiraDadi(2); // Tira i dadi in base al numero di dadi 

    player.casella += totaleDadi; // Aggiorna la casella del giocatore

    controlloCasella(player);
}


void controlloCasella(Player& player) {
    // Gestisci il comportamento quando un giocatore finisce su una casella


    switch(player.casella) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
    default:
        break;
    }


    const float casellaX = WIDTH*0.073;
    const float casellaY = HEIGHT*0.06534;

    if (player.casella <= 9) { // Gestione caselle da 1 a 9
        player.x = player.initX;
        player.x += player.casella * casellaX;
    }
    else if (player.casella <= 19) { // Gestione caselle da 10 a 19
        player.x = player.initX + 9 * casellaX;
        player.y = player.initY;
        player.y -= (player.casella - 9) * casellaY;
    }
    else if (player.casella <= 27) { // Gestione caselle da 20 a 27
        player.x = player.initX + 9 * casellaX;
        player.y = player.initY - 10 * casellaY;
        player.x -= (player.casella - 19) * casellaX;
    }
    else if (player.casella <= 35) { // Gestione caselle da 28 a 35
        player.x = player.initX + casellaX;
        player.y = player.initY - 10 * casellaY;
        player.y += (player.casella - 27) * casellaY;
    }
    else if (player.casella <= 41) { // Gestione caselle da 36 a 41
        player.x = player.initX + casellaX;
        player.y = player.initY - 2 * casellaY;
        player.x += (player.casella - 35) * casellaX;
    }
    else if (player.casella <= 47) { // Gestione caselle da 42 a 47
        player.x = player.initX + 7 * casellaX;
        player.y = player.initY - 2 * casellaY;
        player.y -= (player.casella - 41) * casellaY;
    }
    else if (player.casella <= 51) { // Gestione caselle da 48 a 51
        player.x = player.initX + 7 * casellaX;
        player.y = player.initY - 8 * casellaY;
        player.x -= (player.casella - 47) * casellaX;
    }
    else if (player.casella <= 55) { // Gestione caselle da 52 a 55
        player.x = player.initX + 3 *casellaX;
        player.y = player.initY - 4 * casellaY;
        player.y -= (player.casella - 51) * casellaY;
    }
    else if (player.casella == 56) // Gestione casella 56
    {
        player.x = player.initX + 4 * casellaX;
        player.y = player.initY - 4 * casellaY;
    }
    else if (player.casella > 56) { // Gestione vittoria
        player.x = player.initX + 5 * casellaX;
        player.y = player.initY - 6 * casellaY;
    }


    player.setPosition(player.x, player.y);

}


bool suBottone() { // Controlla se il mouse è sopra un bottone
    for (auto& bottone : bottoni) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosInWindow = window.mapPixelToCoords(mousePos);

        if (bottone.area.contains(mousePosInWindow)) {
            return true;
        }
    }
    return false;
}


void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

