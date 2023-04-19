#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <windows.h>

int macierz_bycia[12][12];       //0-nie byliœmy tam, 1- bylismy tam

void show_more(int ilosc_bomb, int tab[], int x, int y, sf::Sprite warstwa1[12][12], sf::Sprite warstwa2[12][12])   //funkcja odkrywa pola wokol po kliknieciu kiedy 
{                                                                                                                   //obok nie ma bomby
    if (x == 0 || y == 0 || x == 11 || y == 11|| macierz_bycia[x][y] == 1)
        return;
    int licznik{ 0 };
    for (int k = 0; k < ilosc_bomb; k++)
    {
        if ((x - 1) == tab[k] && (y - 1) == tab[k + ilosc_bomb])
            licznik++;
        if ((x - 1) == tab[k] && y == tab[k + ilosc_bomb])
            licznik++;
        if ((x - 1) == tab[k] && (y + 1) == tab[k + ilosc_bomb])
            licznik++;
        if (x == tab[k] && (y + 1) == tab[k + ilosc_bomb])
            licznik++;
        if ((x + 1) == tab[k] && (y + 1) == tab[k + ilosc_bomb])
            licznik++;
        if ((x + 1) == tab[k] && y == tab[k + ilosc_bomb])
            licznik++;
        if ((x + 1) == tab[k] && (y - 1) == tab[k + ilosc_bomb])
            licznik++;
        if (x == tab[k] && (y - 1) == tab[k + ilosc_bomb])
            licznik++;
    }
    if (licznik == 0)
    {
        warstwa1[x - 1][y - 1] = warstwa2[x - 1][y - 1];
        warstwa1[x - 1][y] = warstwa2[x - 1][y];
        warstwa1[x - 1][y + 1] = warstwa2[x - 1][y + 1];
        warstwa1[x][y + 1] = warstwa2[x][y + 1];
        warstwa1[x + 1][y + 1] = warstwa2[x + 1][y + 1];
        warstwa1[x + 1][y] = warstwa2[x + 1][y];
        warstwa1[x + 1][y - 1] = warstwa2[x + 1][y - 1];
        warstwa1[x][y - 1] = warstwa2[x][y - 1];
    }
    else
        return;
    macierz_bycia[x][y] = 1;
    show_more(ilosc_bomb, tab, x - 1, y - 1, warstwa1, warstwa2);
    show_more(ilosc_bomb, tab, x - 1, y, warstwa1, warstwa2);
    show_more(ilosc_bomb, tab, x - 1, y + 1, warstwa1, warstwa2);
    show_more(ilosc_bomb, tab, x, y + 1, warstwa1, warstwa2);
    show_more(ilosc_bomb, tab, x + 1, y + 1, warstwa1, warstwa2);
    show_more(ilosc_bomb, tab, x + 1, y + 1, warstwa1, warstwa2);
    show_more(ilosc_bomb, tab, x + 1, y, warstwa1, warstwa2);
    show_more(ilosc_bomb, tab, x, y - 1, warstwa1, warstwa2);
}

int main()
{
    srand(time(NULL));

    int skala{ 5 };
    float skalowanie{ 1 / (float)skala };
    int piksele{ 300 };   //wymiary obrazkow 300x300
    sf::RenderWindow gra(sf::VideoMode((piksele / skala) * 12, (piksele / skala) * 12), "Saper");

    sf::Texture pole;
    pole.loadFromFile("zdj\\pole.jpg");
    sf::Texture klikniete;
    klikniete.loadFromFile("zdj\\klikniete.jpg");
    sf::Texture bomba;
    bomba.loadFromFile("zdj\\bomba.jpg");
    sf::Texture flaga;
    flaga.loadFromFile("zdj\\flaga.jpg");
    sf::Texture _1;
    _1.loadFromFile("zdj\\1.jpg");
    sf::Texture _2;
    _2.loadFromFile("zdj\\2.jpg");
    sf::Texture _3;
    _3.loadFromFile("zdj\\3.jpg");
    sf::Texture _4;
    _4.loadFromFile("zdj\\4.jpg");
    sf::Texture _5;
    _5.loadFromFile("zdj\\5.jpg");
    sf::Texture _6;
    _6.loadFromFile("zdj\\6.jpg");
    sf::Texture _7;
    _7.loadFromFile("zdj\\7.jpg");
    sf::Texture _8;
    _8.loadFromFile("zdj\\8.jpg");
    sf::Texture odnowa;
    odnowa.loadFromFile("zdj\\od_nowa.jpg");

    sf::Sprite warstwa_1[12][12];
    sf::Sprite warstwa_2[12][12];

od_nowa_gra:

    for (int i = 0; i < 12; i++)        //tworzymy plansze
        for (int j = 0; j < 12; j++)
        {
            warstwa_1[i][j].setTexture(pole);
            warstwa_1[i][j].setScale(skalowanie, skalowanie);
            warstwa_1[i][j].setPosition((i * piksele / skala), (j * piksele / skala));
            warstwa_2[i][j].setTexture(klikniete);
            warstwa_2[i][j].setScale(skalowanie, skalowanie);
            warstwa_2[i][j].setPosition((i * piksele / skala), (j * piksele / skala));
        }
    warstwa_1[11][0].setTexture(odnowa);

    for (int i = 0; i < 12; i++)  //dla funkcji show_more zeby wiedziala gdzie byla
        for (int j = 0; j < 12; j++)
            macierz_bycia[i][j] = 0;

    //generator mapy(bomb)
    const int ilosc_bomb{ 10  };
    int tab[2 * ilosc_bomb]{ 0 };
    for (int i = 0; i < ilosc_bomb; i++)
    {
    here:
        int x = std::rand() % 10 + 1;
        int y = std::rand() % 10 + 1;
        tab[i] = x;
        tab[i + ilosc_bomb] = y;
        for (int k = 0; k < i; k++)
            if (x == tab[k] && y == tab[k + ilosc_bomb])
                goto here;
        warstwa_2[x][y].setTexture(bomba);
    }
  
    for (int i = 1; i < 11; i++)            //generator liczb na planszy
    {
        for (int j = 1; j < 11; j++)
        {
            int licznik{ 0 };
            for (int k = 0; k < ilosc_bomb; k++)
            {
                if (i == tab[k] && j == tab[k + ilosc_bomb])
                {
                    licznik = 0;
                    break;
                }
                if ((i - 1) == tab[k] && (j - 1) == tab[k + ilosc_bomb])
                    licznik++;
                if ((i - 1) == tab[k] && j == tab[k + ilosc_bomb])
                    licznik++;
                if ((i - 1) == tab[k] && (j + 1) == tab[k + ilosc_bomb])
                    licznik++;
                if (i == tab[k] && (j + 1) == tab[k + ilosc_bomb])
                    licznik++;
                if ((i + 1) == tab[k] && (j + 1) == tab[k + ilosc_bomb])
                    licznik++;
                if ((i + 1) == tab[k] && j == tab[k + ilosc_bomb])
                    licznik++;
                if ((i + 1) == tab[k] && (j - 1) == tab[k + ilosc_bomb])
                    licznik++;
                if (i == tab[k] && (j - 1) == tab[k + ilosc_bomb])
                    licznik++;
            }
            if (licznik == 8)
                warstwa_2[i][j].setTexture(_8);
            if (licznik == 7)
                warstwa_2[i][j].setTexture(_7);
            if (licznik == 6)
                warstwa_2[i][j].setTexture(_6);
            if (licznik == 5)
                warstwa_2[i][j].setTexture(_5);
            if (licznik == 4)
                warstwa_2[i][j].setTexture(_4);
            if (licznik == 3)
                warstwa_2[i][j].setTexture(_3);
            if (licznik == 2)
                warstwa_2[i][j].setTexture(_2);
            if (licznik == 1)
                warstwa_2[i][j].setTexture(_1);
        }
    }

    while (gra.isOpen())
    { 
        sf::Event cos;
        while (gra.pollEvent(cos))
        {
            sf::Vector2i poz_myszki = sf::Mouse::getPosition(gra);
            int poz_x = (poz_myszki.x / (piksele / skala));
            int poz_y = (poz_myszki.y / (piksele / skala));

            if (cos.type == sf::Event::Closed())
                gra.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                warstwa_1[poz_x][poz_y] = warstwa_2[poz_x][poz_y];

                if (poz_x == 11 && poz_y == 0)                  //reset (niebieski guzik)
                    goto od_nowa_gra;

                for (int k = 0; k < ilosc_bomb; k++)            //jesli bombe klikniemy
                    if (poz_x == tab[k] && poz_y == tab[k + ilosc_bomb])
                    {
                        for (int i = 1; i < 11; i++)
                            for (int j = 1; j < 11; j++)
                                gra.draw(warstwa_1[i][j]);
                        gra.display();
                        Sleep(1000);
                        goto od_nowa_gra;
                    }
                    
                show_more(ilosc_bomb, tab, poz_x, poz_y, warstwa_1, warstwa_2);                          
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))   //stawianie flagi
                warstwa_1[poz_x][poz_y].setTexture(flaga);               
        }
        for (int i = 1; i < 11; i++)
            for (int j = 1; j < 11; j++)
                gra.draw(warstwa_1[i][j]);
        gra.draw(warstwa_1[11][0]);
        
        gra.display();
    }
}