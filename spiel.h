#ifndef SPIEL_H
#define SPIEL_H

class spieler;
class alien;
class schuss;
class explosion;
class alienschuss;



class spiel
{
     public:
            spiel();
            virtual ~spiel();
            void normalerunde(spieler* Spieler, alien Alien[]);

            highscore(spieler* Spieler);

            einstellungen();
            highscoreZeigen();

            aliensGeschwindigkeitErhoehen(alien Alien[]);

            template< class T >
            objektLoeschen(T Objekt[],int zuLoeschender, int* anzahlObjekte)
            {


                for (int d=zuLoeschender; d<*anzahlObjekte-1; d++)
                {
                    Objekt[d]=Objekt[d+1];
                }
                (*anzahlObjekte)--;
            }

            spawnReinigen(alienschuss ObjectList[]);
            void addPunkte(spieler* Spieler);
            void werteuebernehmen();

            int getSpielgeschwindigkeit(){return timerzeit;};
            int getAliensProRunde(){anzahlAlienNEU++; return anzahlAlienNEU;};
            int getlebenNEU(){return lebenNEU;};
            bool isGameRunning(){return spiellaeuft;};
            void stopGame(){if (spiellaeuft) spiellaeuft=false;};
            void resumeGame(){if (!spiellaeuft) spiellaeuft=true;};


    int anzahlSchuss=0;
    int anzahlAlien=20;             ///Wird für das löschen und erstellen der Objekte benötigt
    int anzahlAlienSchuss=0;
    int anzahlExplosion=0;

    bool aliensbewegensichnachrechts=true;

    HWND fensterImVordergrund;
    int fensterHoehe=500, fensterBreite=500;
    int geschwX=1,geschwY=10,schusswahrscheinlichkeit=5;
    int schussgeschwAliens=2, schussgeschwSpieler=3;

    private:

    bool spiellaeuft=true;

    int geschwXNEU=1, geschwYNEU=10, schusswahrscheinlichkeitNEU=5;       ///Einstellungen
    int lebenNEU=3, anzahlAlienNEU=20, lebenPUNKTE=3;
    int timerzeit=15;
};

#endif // SPIEL_H
