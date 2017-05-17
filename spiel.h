#ifndef SPIEL_H
#define SPIEL_H

class spieler;
class alien;
class schuss;
class explosion;
class alienschuss;

struct anzahl
{
        int Schuss=0;
        int Alien=20;             ///Wird für das löschen und erstellen der Objekte benötigt
        int Alienschuss=0;
        int Explosion=0;
};

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
            objektLoeschen(T Objekt[],int zuLoeschender,spiel* Spiel,char typ)
            {
                int anzahlObjekte;
                switch (typ)
                {
                    case 'a' :          anzahlObjekte=Spiel->getAnzahl().Alien;
                                            Spiel->setAnzahlAlien(Spiel->getAnzahl().Alien-1);
                                            break;

                    case 'l' :    anzahlObjekte=Spiel->getAnzahl().Alienschuss;
                                            Spiel->setAnzahlAlienschuss(Spiel->getAnzahl().Alienschuss-1);
                                            break;

                    case 'e' :      anzahlObjekte=Spiel->getAnzahl().Explosion;
                                            Spiel->setAnzahlExplosion(Spiel->getAnzahl().Explosion-1);
                                            break;

                    case 's' :         anzahlObjekte=Spiel->getAnzahl().Schuss;
                                            Spiel->setAnzahlSchuss(Spiel->getAnzahl().Schuss-1);
                                            break;
                }

                for (int d=zuLoeschender; d<anzahlObjekte-1; d++)
                {
                    Objekt[d]=Objekt[d+1];
                }

            }

            spawnReinigen(alienschuss ObjectList[]);
            void addPunkte(spieler* Spieler);
            void werteuebernehmen();
            void saveForegroundWindow(){fensterImVordergrund=GetForegroundWindow();};

            int getSpielgeschwindigkeit(){return timerzeit;};
            int getAliensProRunde(){anzahlAlienNEU++; return anzahlAlienNEU;};
            int getlebenNEU(){return lebenNEU;};
            int getBreite(){return fensterBreite;};
            int getHoehe(){return fensterHoehe;};
            wxPoint getAlienGeschw(){return geschwAlien;};
            int getschusswahrscheinlichkeit(){return schusswahrscheinlichkeit;};
            int getschussgeschwAliens(){return schussgeschwAliens;};
            int getschussgeschwSpieler(){return schussgeschwSpieler;};

            bool isGameRunning(){return spiellaeuft;};
            void stopGame(){if (spiellaeuft)spiellaeuft=false;};
            void resumeGame(){if (!spiellaeuft) spiellaeuft=true;};
            bool isGameInForeground();



            anzahl getAnzahl(){return Anzahl;};

            void setAnzahlAlien(int anzahl){if (anzahl<=40) Anzahl.Alien=anzahl;};
            void setAnzahlExplosion(int anzahl){if (anzahl<=10) Anzahl.Explosion=anzahl;};
            void setAnzahlAlienschuss(int anzahl){if (anzahl<=100) Anzahl.Alienschuss=anzahl;};
            void setAnzahlSchuss(int anzahl){if (anzahl<=10) Anzahl.Schuss=anzahl;};




    private:


        anzahl Anzahl;

        wxPoint geschwAlien;
        int schusswahrscheinlichkeit;           ///aktuelle Spielwerte
        int schussgeschwAliens=2, schussgeschwSpieler;


    bool spiellaeuft=true;
    HWND fensterImVordergrund;
    int geschwXNEU=1, geschwYNEU=15, schusswahrscheinlichkeitNEU=5;       ///Einstellungen
    int lebenNEU=3, anzahlAlienNEU=20, lebenPUNKTE=3, schussgeschwSpielerNEU=3;
    int timerzeit=15;
    int fensterHoehe=500, fensterBreite=500;
};

#endif // SPIEL_H
