#ifndef SPIEL_H
#define SPIEL_H

class spieler;
class alien;

class spiel
{
     public:
            spiel();
            virtual ~spiel();
            void normalerunde(spieler* Spieler, alien Alien[]);

            highscore(spieler* Spieler);

            einstellungen();
            highscoreZeigen();



    int anzahlSchuss=0;
    int anzahlAlien=20;             ///Wird für das löschen und erstellen der Objekte benötigt
    int anzahlAlienSchuss=0;
    int anzahlExplosion=0;

    bool aliensbewegensichnachrechts=true;
    bool spiellaeuft=true;
    HWND fensterImVordergrund;
    int fensterHoehe=500, fensterBreite=500;
    int geschwX=1,geschwY=10,schusswahrscheinlichkeit=5;
    int geschwXNEU=1,geschwYNEU=10,schusswahrscheinlichkeitNEU=5;       ///Einstellungen
    int lebenNEU=3,lebenPUNKTE=3,anzahlAlienNEU=20;
    int timerzeit=15,schussgeschwAliens=2,schussgeschwSpieler=3;
};

#endif // SPIEL_H
