#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const string testoCaselle[58] = {
    "Inizio",//inizio (casella 0)
    "Pensavi fosse stato un tiro sfortunato 2 e 1, invece no! D'ora in poi ogni turno tira 4 dadi invece che 2, almeno finché non atterri su una casella pari",//1
    "La professoressa Pellegrini ha riconosciuto il tuo impegno e ha deciso di premiarti, aumentando il tuo voto da 2 a 4. Avanza di due caselle!",//2
    "Che peccato! Torna indietro di 2 caselle.",//3
    "Una stradina molto tranquilla vicino a un laghetto.",//4
    "Una stradina molto tranquilla vicino a un laghetto.",//5
    "Un inizio sfortunato, sei stato maledetto! Resta fermo un turno dopo ogni tiro di dadi, l'unico modo per spezzare il marchio è atterrare su una casella dispari.",//6
    "Zani ti fa compagnia nelle caselle 7, 8 e 9",//7
    "Zani ti fa compagnia nelle caselle 7, 8 e 9",//8
    "Zani ti fa compagnia nelle caselle 7, 8 e 9",//9
    "Peccato, sei inciampato sul pavimento rotto del Fermi, cadi al indietro di una casella!",//10
    "Una casella vuota, che noia.",//11
    "Il karma non è dalla tua parte. Vai alla casella 5.",//12
    "La casella 13 non perdona: qui è tutto un fallimento! Non hai altra scelta che tornare all’inizio. Riprova, sarà meglio la prossima volta.",//13
    "Che c'è ti aspettavi succedesse qualcosa in ogni casella?",//14
    "Che fortuna, una fermata del Gello Express! Avanza fino alla casella 25.",//15
    "Che sfiga, ti sei slogato una caviglia, per un po' zoppicherai e balbetterai. Per i prossimi 3 turni tira un dado invece che 2",//16
    "Goditi un attimo di quiete, fidati ti servira",//17
    "C'è fila in bagno, aspetta un turno.",//18
    "Tira 2 dadi, se esce lo stesso numero avanza di uno altrimenti torna indietro di 3 caselle!",//19
    "Qui c'è un albero molto bello.",//20
    "Un signore per strada ti saluta, non succede nulla.",//21
    "MOV AX, 31",//22
    "Trovi una bici, la usi per avanzare di 3 caselle poi ti si rompe.",//23
    "Ti fermi a accarezzare un gatto. Stai fermo un turno",//24
    "Oh! Il capolinea del Gello Express.",//25
    "Passi davanti a un bar, la tentazione di fermarti è forte ma vai avanti.",//26
    "Iti riders crew ti ha approcciato, tira un dado, se minore di 4 resta 2 turni a subire i loro rumori molesti",//27
    "È lunedì, lancia un dado, se minore di 6 hai finito le ore di assenza con Cellulari e stai fermo 3 turni a seguire la sua lezione.",//28
    "Febbraio ha 29 giorni solo ogni 4 anni... E tu sei finito nella casella 29 proprio adesso. Aspetta che arrivi il prossimo anno bisestile e resta fermo 4 turni!",//29
    "Devi andare alla palestra ma la stradina è di nuovo piena di fango, fai il giro per passare dal viale Adua. Torna indietro di 4 caselle.",//30
    "Hey non puoi fermarti qui ci sono dei lavori in corso! Avanza di uno e non disturbare gli operai.",//31
    "Mentre passi osservi il cantiere dei lavori sulla piscina dell'I.T.TS.",//32
    "Il signor Buongiorno ti da il buongiorno e con esso un aiuto emotivo. Tira di nuovo!",//33
    "Wow qui è pieno di diramazioni, ne scegli una e vai avanti.",//34
    "La strada è chiusa torna indietro e passa da un altra.",//35
    "Un suino ti offre un passaggio in cambio di qualche carezza. Avanza di 5 caselle",//36
    "Non succede nulla ma c'è un bel paesaggio quindi sei felice.",//37
    "Non succede nulla ma c'è un bel paesaggio quindi sei felice.",//38
    "Una vespa ti entra nei pantaloni e ti punge un polpaccio, il dolore ti rallenta. Torna indietro di una casella",//39
    "Sciaulino ti chiama su discord per vedere i reels, il suo unemployment ti contagia e perdi 2 ore su Instagram. Torna indietro di 2 caselle.",//40
    "Stai passando davanti a una casetta molto carina, bella vista.",//41
    "Stai passando davanti a una casetta molto carina, bella vista.",//42
    "Vedi una ragazza venire verso di te, la tua paura per le donne ti fa correre per non farti approcciare. Avanza di due caselle.",//43
    "Tira un dado , se esce 4 vai avanti di due caselle altrimenti torna indietro di 2.",//44
    "Qui sei al sicuro, per ora.",//45
    "La professoressa Ricci ti interroga, stai fermo 2 turni a parlare di Petrarca.",//46
    "Ci sono 4 cartelli che ti dicono di andare a sinistra. Tira 4 dadi se esce 4 volte 1 sei così stupido da non vederne nessuno e vai a desta finendo nella casella 17.",//47
    "Hai incontrato Pietro per strada, il solo vederlo ti ha dato la carica per aumentare il passo. Tira di nuovo.",//48
    "C'è un muro che separa te e la vittoria, letteralmente, prova a scavalcarlo. Tira 4 dadi, se sono esce 4 volte 1 hai vinto, altrimenti continua per la strada normale.",//49
    "Manca poco ormai, sei motivato a aumentare il passo. Avanza di una casella.",//50
    "Ritieniti fortunato a essere qui...",//51
    "La casella 52 non mi piace, ritira i dadi.",//52
    "Ti sei addormentato sul bus! Aspetta la prossima coincidenza stando fermo un turno.",//53
    "Avanza di una casella, è un bene vero? Vero?",//54
    "Sì, chiunque abbia progettato questo gioco ti vuole male. Torna indietro di 2 caselle.",//55
    "Così vicino… eppure così lontano. Rimbalzi indietro di 10 caselle!",//56
    "fine"//fine (casella dove va quando vinci)
};


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
    bool zoppo = false;
    bool turnoDoppio = false;
    bool turniAlterni = false;
    int turniZoppo = 0;
    int turniFermo = 0;
    sf::Color colore;
    sf::CircleShape shape; // Rappresenta il giocatore con un cerchio

    Player(string nome, sf::Color colore, int numero, int x, int y) {
        this->x = initX = x;
        this->y = initY = y;
        this->numero = numero;
        this->nome = nome;
        this->colore = colore;
        shape.setRadius(WIDTH * 0.008); // Imposta il raggio della "pietra" che rappresenta il giocatore
        shape.setFillColor(colore);
        shape.setOutlineColor(sf::Color::Black);//mette il colore del bordo pedone
        shape.setOutlineThickness(2);//mette lo spessore al bordo pedone
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
        testo.setCharacterSize(WIDTH / 35);

        testo.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = testo.getLocalBounds();
        testo.setOrigin(textBounds.width / 2, textBounds.height / 2);
        testo.setPosition(sf::Vector2f(x * 0.995, y * 0.975));  // Posiziona il testo al centro
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
Sprite mappa(WIDTH * 2.65 / 4, HEIGHT * 1.435 / 4, 0.8, "data/mappa.png");
Sprite d1(0, 0, 0.4, "data/d1.png");
Sprite d2(0, 0, 0.4, "data/d2.png");
Sprite d3(0, 0, 0.4, "data/d3.png");
Sprite d4(0, 0, 0.4, "data/d4.png");
Sprite d5(0, 0, 0.4, "data/d5.png");
Sprite d6(0, 0, 0.4, "data/d6.png");


bool suBottone(int nBottone);
int tiraDadi(int nDadi);
void creazioneMenu(sf::RectangleShape& shape, sf::Text& testo);
void creazioneImpostazioni(sf::RectangleShape& shape, sf::Text& testo, sf::Text& n, sf::Text& c, sf::Text& numeroGiocatori);
void creazionePausa();
void creazioneCrediti(sf::Text& testo);
void drawMenu(sf::RectangleShape shape, sf::Text testo);
void drawPartita();
void drawPausa(sf::RectangleShape shape);
void drawCrediti(sf::Text testo);
void drawDado();
void drawCasella();
void drawImpostazioni(sf::RectangleShape shape, sf::Text testo, sf::Text n, sf::Text c, sf::Text numeroGiocatori);
void input(sf::Text& n, sf::Text& c);
void update();
void turnoPlayer(Player& player);
void controlloCasella(Player& player);
void sleep(int ms);

bool crediti = false;
bool menu = true;
bool partita = false;
bool impostazioni = false;
bool pausa = false;
bool escPress = false;
int totaleDadi;
int n_player = 1;
int n_cpu = 3;
string testoCasella = "";
vector<int> facciaDadi;



int main() {
    srand(time(NULL));
    mappa.sprite.setScale(0.8, 0.85); // Risetta la scala della mappa
    font.loadFromFile("data/arial.ttf"); // Carica il font
    // Crea i player
    players.push_back(Player("Giocatore", sf::Color::Red, 1, WIDTH * 0.2745, HEIGHT * 2.6669 / 4));
    players.push_back(Player("CPU 1", sf::Color::Blue, 2, WIDTH * 0.2995, HEIGHT * 2.6669 / 4));
    players.push_back(Player("CPU 2", sf::Color::Green, 3, WIDTH * 0.2745, HEIGHT * 2.796 / 4));
    players.push_back(Player("CPU 3", sf::Color::Yellow, 4, WIDTH * 0.2995, HEIGHT * 2.796 / 4));
    // Crea il menu
    sf::RectangleShape shape;
    sf::Text testoMenu;
    sf::Text testoImpostazioni;
    sf::Text n;
    sf::Text c;
    sf::Text numeroGiocatori;
    n.setString(std::to_string(n_player));
    c.setString(std::to_string(n_cpu));
    creazioneMenu(shape, testoMenu);
    creazioneImpostazioni(shape, testoImpostazioni, n, c, numeroGiocatori); // Crea le impostazioni
    creazionePausa(); // Crea la pausa
    // Crea i crediti
    sf::Text testoCrediti;
    creazioneCrediti(testoCrediti);


    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            n.setString(std::to_string(n_player));
            c.setString(std::to_string(n_cpu));
            if (event.type == sf::Event::Closed)
                window.close();

            input(n, c);
        }

        update();

        window.clear(sf::Color::Cyan);
        if (menu) { // Disegna il menu
            drawMenu(shape, testoMenu);
        }
        else if (crediti) {
            drawCrediti(testoCrediti); // Disegna i crediti
        }
        else if (impostazioni) {

            drawImpostazioni(shape, testoImpostazioni, n, c, numeroGiocatori); // Disegna le impostazioni
        }
        else if (partita) { // Disegna la partita
            drawPartita();
        }
        else if (pausa) { // Disegna la pausa
            drawPausa(shape);
        }
        window.display();
    }
}

void input(sf::Text& n, sf::Text& c) {
    // Gestione input nel menu
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menu) {
        if (suBottone(0)) { // Bottone START nel menu
            menu = false;
            impostazioni = true;
        }
        else if (suBottone(1)) { // Bottone CREDITI nel menu
            crediti = true;
            menu = false;
        }
        else if (suBottone(2)) { // Bottone ESCI nel menu
            window.close();
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && impostazioni) {
        if (suBottone(3)) { // Bottone START nel menu
            impostazioni = false;
            partita = true;
        }
        else if (suBottone(4)) { // Bottone <
            n_player--;
            if (n_player < 1) n_player = 1; // Limite minimo
            n.setString(std::to_string(n_player));
            sf::FloatRect nBounds = n.getLocalBounds();
            n.setOrigin(nBounds.width / 2, nBounds.height / 2);
        }
        else if (suBottone(5)) { // Bottone >
            n_player++;
            if (n_player + n_cpu > 4) n_player--; // Limite massimo (opzionale)
            n.setString(std::to_string(n_player));
            sf::FloatRect nBounds = n.getLocalBounds();
            n.setOrigin(nBounds.width / 2, nBounds.height / 2);
        }
        else if (suBottone(6)) { // Bottone <
            n_cpu--;
            if (n_cpu < 1) n_cpu = 1; // Limite minimo
            c.setString(std::to_string(n_cpu));
            sf::FloatRect nBounds = c.getLocalBounds();
            c.setOrigin(nBounds.width / 2, nBounds.height / 2);
        }
        else if (suBottone(7)) { // Bottone >
            n_cpu++;
            if (n_cpu + n_player > 4) n_cpu--; // Limite massimo (opzionale)
            c.setString(std::to_string(n_cpu));
            sf::FloatRect nBounds = c.getLocalBounds();
            c.setOrigin(nBounds.width / 2, nBounds.height / 2);
        }
    }

    // Gestione input nella pausa
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pausa) {
        if (suBottone(8)) { // Bottone RIPRENDI
            pausa = false;
            partita = true;
        }
        else if (suBottone(9)) { // Bottone TORNA AL MENU
            menu = true;
            pausa = false;
        }
        else if (suBottone(10)) { // Bottone ESCI DAL GIOCO
            window.close();
        }
    }


    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && partita) { // Input per lanciare i dadi
        players[0].staGiocando = true; // Il giocatore 1 inizia il turno
    }

    static bool escReleased = true; // Flag per rilevare quando il tasto viene rilasciato
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escReleased) {
        escReleased = false; // Impedisce la ripetizione finché il tasto non viene rilasciato
        if (partita) {
            partita = false;
            pausa = true;
        }
        else if (pausa) {
            partita = true;
            pausa = false;
        }
        else if (crediti) {
            crediti = false;
            menu = true;
        }
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        escReleased = true; // Permette di nuovo la pressione dopo il rilascio
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
    // Bottoni
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT * 0.52, WIDTH * 0.12, HEIGHT * 0.055, "INIZIA", sf::Color::Yellow));
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT * 0.61, WIDTH * 0.12, HEIGHT * 0.055, "CREDITI", sf::Color(40, 40, 255)));
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT * 0.7, WIDTH * 0.24, HEIGHT * 0.055, "ESCI DAL GIOCO", sf::Color::Red));
}

void creazioneImpostazioni(sf::RectangleShape& shape, sf::Text& testo, sf::Text& n, sf::Text& c, sf::Text& numeroGiocatori) {
    shape.setSize(sf::Vector2f(WIDTH / 1.8, HEIGHT / 1.8));
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
    testo.setFont(font);
    testo.setString("IMPOSTAZIONI");
    testo.setCharacterSize(WIDTH / 22);
    testo.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = testo.getLocalBounds();
    testo.setOrigin(textBounds.width / 2, textBounds.height / 2);
    testo.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 3));
    numeroGiocatori.setFont(font);
    numeroGiocatori.setString("Player                          CPU");
    numeroGiocatori.setCharacterSize(WIDTH / 40);
    numeroGiocatori.setFillColor(sf::Color::Black);
    sf::FloatRect numGiocatoriBounds = numeroGiocatori.getLocalBounds();
    numeroGiocatori.setOrigin(numGiocatoriBounds.width / 2, numGiocatoriBounds.height / 2);
    numeroGiocatori.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT * 0.45));
    n.setFont(font);
    n.setCharacterSize(WIDTH / 22);
    n.setFillColor(sf::Color::Black);
    n.setString(std::to_string(n_player));
    sf::FloatRect nBounds = n.getLocalBounds();
    n.setOrigin(nBounds.width / 2, nBounds.height / 2);
    n.setPosition(sf::Vector2f(WIDTH / 2.55, HEIGHT * 0.5));
    c.setFont(font);
    c.setCharacterSize(WIDTH / 22);
    c.setFillColor(sf::Color::Black);
    c.setString(std::to_string(n_cpu));
    sf::FloatRect cBounds = n.getLocalBounds();
    c.setOrigin(cBounds.width / 2, cBounds.height / 2);
    c.setPosition(sf::Vector2f(WIDTH / 1.62, HEIGHT * 0.5));
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT * 0.63, WIDTH * 0.12, HEIGHT * 0.055, "INIZIA", sf::Color::Yellow));
    bottoni.push_back(Bottone(HEIGHT * 0.6, HEIGHT * 0.52, WIDTH * 0.051, HEIGHT * 0.06, "<", sf::Color::Red));
    bottoni.push_back(Bottone(HEIGHT * 0.8, HEIGHT * 0.52, WIDTH * 0.051, HEIGHT * 0.06, ">", sf::Color::Red));
    bottoni.push_back(Bottone(HEIGHT * 1.01, HEIGHT * 0.52, WIDTH * 0.051, HEIGHT * 0.06, "<", sf::Color::Green));
    bottoni.push_back(Bottone(HEIGHT * 1.2, HEIGHT * 0.52, WIDTH * 0.051, HEIGHT * 0.06, ">", sf::Color::Green));
}



void creazionePausa() {
    // Bottone RIPRENDI
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT / 3, WIDTH * 0.14, HEIGHT * 0.11, "RIPRENDI", sf::Color::Blue));
    // Bottone TORNA AL MENU
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT / 2, WIDTH * 0.14, HEIGHT * 0.11, "TORNA AL\n   MENU", sf::Color::Red));
    // Bottone ESCI DAL GIOCO
    bottoni.push_back(Bottone(WIDTH / 2, HEIGHT / 1.5, WIDTH * 0.14, HEIGHT * 0.11, "ESCI DAL\n  GIOCO", sf::Color::Green));
}


void creazioneCrediti(sf::Text& testo) {
    testo.setFont(font);
    testo.setString("GRAZIE PER STAR GIOCANDO AL NOSTRO GIOCO DELL'OCA  By: \n \n  - Totti Alberto - \n  - Cai Dal Pino Gabriele - \n  - Arinci Andrea -");

}


void drawMenu(sf::RectangleShape shape, sf::Text testo) {
    menuWP.draw(); // Disegna il background del menu
    window.draw(shape); // Disegna il rettangolo
    window.draw(testo); // Disegna il testo
    bottoni[0].draw(); // Disegna il bottone INIZIA
    bottoni[1].draw(); // Disegna il bottone CREDITI
    bottoni[2].draw(); // Disegna il bottone ESCI
}


void drawPartita() {
    mappa.draw();
    drawDado(); // Chiamata per il dado
    for (auto& player : players) {
        player.draw();

        drawCasella();
    }
}


void drawImpostazioni(sf::RectangleShape shape, sf::Text testo, sf::Text n, sf::Text c, sf::Text numeroGiocatori) {
    window.draw(shape); // Disegna il rettangolo di sfondo
    window.draw(testo); // Disegna il testo delle impostazioni
    window.draw(n); // Disegna il testo dei numeri
    window.draw(c); // Disegna il testo dei numeri
    window.draw(numeroGiocatori); // Disegna il testo dei numeri
    bottoni[3].draw();  // Disegna il bottone INIZIA PARTITA
    bottoni[4].draw();  // Disegna il bottone < player
    bottoni[5].draw();  // Disegna il bottone > player
    bottoni[6].draw();  // Disegna il bottone < cpu
    bottoni[7].draw();  // Disegna il bottone > cpu
}

void drawPausa(sf::RectangleShape shape) {
    window.draw(shape); // Disegna il rettangolo di sfondo
    bottoni[8].draw();  // Disegna il bottone RIPRENDI  
    bottoni[9].draw();  // Disegna il bottone TORNA AL MENU
    bottoni[10].draw();  // Disegna il bottone ESCI DAL GIOCO
}


void drawCrediti(sf::Text testo) {
    window.draw(testo); // Disegna il testo dei crediti
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


void drawCasella() {
    // Disegna la casella in base al numero
    sf::Text testoCasella;
    testoCasella.setFont(font);
    testoCasella.setString(testoCaselle[players[1].casella]);
    testoCasella.setCharacterSize(WIDTH / 35);
    testoCasella.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = testoCasella.getLocalBounds();
    testoCasella.setOrigin(textBounds.width / 2, textBounds.height / 2);
    testoCasella.setPosition(players[0].x, players[0].y);
    window.draw(testoCasella);
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
    d1.draw();
    controlloCasella(player);
}


void controlloCasella(Player& player) {
    // Gestisci il comportamento quando un giocatore finisce su una casella

    if (player.casella > 56) {
        player.casella = 57;
    }

    if (player.casella % 2 == 0) {
        if (player.turnoDoppio) {
            player.turnoDoppio = false;
        }
    }
    else {
        if (player.turniAlterni) {
            player.turniAlterni = false;
        }
    }

    switch (player.casella) {
    case 0:
        break;
    case 1:
        player.turnoDoppio = true;
        break;
    case 2:
        player.casella += 2;
        break;
    case 3:
        player.casella -= 2;
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        player.turniAlterni = true;
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        player.casella -= 1;
        break;
    case 11:
        break;
    case 12:
        player.casella = 5;
        break;
    case 13:
        player.casella = 0;
        break;
    case 14:
        break;
    case 15:
        player.casella = 25;
        break;
    case 16:
        player.zoppo = true;
        player.turniZoppo = 3;
        break;
    case 17:
        break;
    case 18:
        player.turniFermo = 1;
        break;
    case 19:
        //
        break;
    case 20:
        break;
    case 21:
        break;
    case 22:
        player.casella = 31;
        break;
    case 23:
        player.casella += 3;
        break;
    case 24:
        player.turniFermo = 1;
        break;
    case 25:
        break;
    case 26:
        break;
    case 27:
        //
        break;
    case 28:
        //
        break;
    case 29:
        player.turniFermo = 4;
        break;
    case 30:
        player.casella -= 4;
        break;
    case 31:
        player.casella += 1;
        break;
    case 32:
        break;
    case 33:
        //
        break;
    case 34:
        break;
    case 35:
        player.casella -= 1;
        break;
    case 36:
        player.casella += 5;
        break;
    case 37:
        break;
    case 38:
        break;
    case 39:
        player.casella -= 1;
        break;
    case 40:
        player.casella -= 2;
        break;
    case 41:
        break;
    case 42:
        break;
    case 43:
        player.casella += 2;
        break;
    case 44:
        //
        break;
    case 45:
        break;
    case 46:
        player.turniFermo = 2;
        break;
    case 47:
        //
        break;
    case 48:
        //
        break;
    case 49:
        //
        break;
    case 50:
        player.casella += 1;
        break;
    case 51:
        break;
    case 52:
        //
        break;
    case 53:
        player.turniFermo = 1;
        break;
    case 54:
        player.casella += 1;
        break;
    case 55:
        player.casella -= 2;
        break;
    case 56:
        player.casella -= 10;
        break;
    default:
        break;
    }


    const float casellaX = WIDTH * 0.073;
    const float casellaY = HEIGHT * 0.06534;

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
        player.x = player.initX + 3 * casellaX;
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


bool suBottone(int nBottone) { // Controlla se il mouse è sopra un bottone
    // Se l'indice non è valido, restituisci false
    if (nBottone < 0 || nBottone >= bottoni.size()) {
        return false;
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosInWindow = window.mapPixelToCoords(mousePos);

    if (bottoni[nBottone].area.contains(mousePosInWindow)) {
        return true;
    }
    return false;
}


void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

