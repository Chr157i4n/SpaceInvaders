#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <cstdlib>
#include <ctime>
#include <wx/icon.h>
#include <wx/dcbuffer.h>
#include <string>
#include <sstream>
#include <wx/textfile.h>
#include <windows.h>
#include <stdio.h>
#include <wx/textdlg.h>
#include <thread>

#include "alien.h"
#include "explosion.h"
#include "alienschuss.h"
#include "schuss.h"
#include "spieler.h"

class BasicDrawPane;


class RenderTimer : public wxTimer
{
BasicDrawPane* pane;




public:
    RenderTimer(BasicDrawPane* pane);
    void Notify();
    void start(int timerzeit);
    void stop();
};


RenderTimer::RenderTimer(BasicDrawPane* pane) : wxTimer()
{
   RenderTimer::pane = pane;
}
void RenderTimer::start(int timerzeit)
{
    wxTimer::Start(timerzeit);
}

void RenderTimer::stop()
{
    wxTimer::Stop();
}
RenderTimer* timer;




wxBitmap bHintergrund,bRaumschiff,bSchuss,bAlienschuss,bAlien,bLeben,bExplosion;




explosion Explosion[10];

alienschuss Alienschuss[100];

alien Alien[30];

schuss Schuss[10];

spieler Spieler;




class spiel
{
    public:
            spiel(){};
            virtual ~spiel(){};
            normalerunde();
            /*tastatureingaben();
            schussbewegen();
            schiessenerlauben();
            schussloeschen();
            alienBewegen();
            trefferregistrieren();
            alienschiessen();
            endeerkennug();
            explosionenentfernen(); */
            highscore();



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


spiel::normalerunde()
{


    anzahlAlienSchuss=0;

    anzahlSchuss=0;
    Spieler.x=250-16;


        int spaltealien=0;
        int reihealien=1;

        for (int i=0;i<anzahlAlien;i++)
        {
           spaltealien++;

           if (spaltealien>10)
           {    spaltealien=1;
                reihealien++;   }                               ///Aliens hinzufügen

        Alien[i].reseten(spaltealien*40,reihealien*40);


        }


}

spiel::highscore()
{
    bool hso=false,hs=false,chanceled=false;
    _mkdir("Highscore");                                ///erstellt nur, falls nicht vorhanden
    wxTextFile highscoreTXT( wxT("Highscore/Highscore.txt") );

    highscoreTXT.Create("Highscore/Highscore.txt");             ///erstellt nur, falls nicht vorhanden
    highscoreTXT.Open("Highscore/Highscore.txt");




    ///Highscore
    int platz=0;
    wxString highscore,tmp;

    tmp = highscoreTXT.GetFirstLine();

    for (int i=0; i<10; i++)
    {
        if (tmp[i] == ' ')
        {
          for (int c=0;c<i;c++)
          {
             highscore=highscore+tmp[c];
          }
          break;
        }
    }


    do {


        if ((Spieler.punkte>wxAtoi(highscore) || highscore=="")    && !hs && Spieler.punkte>0)
            {


            wxTextEntryDialog *dlg = new wxTextEntryDialog((wxFrame *)NULL,wxT("Gib bitte deinen Namen ein"),wxT("Highscore"));
                if ( dlg->ShowModal() == wxID_OK )
                {
                    dlg->Destroy();
                    wxString punktstand;
                    punktstand << Spieler.punkte;



                        if (Spieler.punkte<100)
                        {
                        punktstand=punktstand+" ";
                        }
                        if (Spieler.punkte<1000)
                        {
                        punktstand=punktstand+" ";
                        }
                        Spieler.name=dlg->GetValue();
                    punktstand=punktstand+"   "+Spieler.name;
                    highscoreTXT.InsertLine( punktstand, platz);
                    highscoreTXT.Write();
                    hs=true;


                }
                else {hs=true;chanceled=true;}

            dlg->Destroy();


            break;
            }
        highscore="";
        tmp = highscoreTXT.GetNextLine();
        for (int i=0; i<10; i++)
    {

        if (tmp[i] == ' ')
        {
          for (int c=0;c<i;c++)
          {
             highscore=highscore+tmp[c];
          }
          break;
        }
    }
        platz++;

    } while(!highscoreTXT.Eof() && platz<10);

    if (platz<10 && !hs && Spieler.punkte>0)
    {

            wxTextEntryDialog *dlg = new wxTextEntryDialog((wxFrame *)NULL,wxT("Gib bitte deinen Namen ein"),wxT("Highscore"));
                if ( dlg->ShowModal() == wxID_OK )
                {
                    dlg->Destroy();
            wxString punktstand;
            punktstand << Spieler.punkte;                   ///Punktzahl ganz am ende
            if (Spieler.punkte<100)
            {
            punktstand=punktstand+" ";
            }
            if (Spieler.punkte<1000)
            {
            punktstand=punktstand+" ";
            }
            Spieler.name=dlg->GetValue();
             punktstand=punktstand+"   "+Spieler.name;
            highscoreTXT.InsertLine( punktstand, platz);
            highscoreTXT.Write();
                } else {chanceled=true;}
                dlg->Destroy();



    }



for(int i=10;i<highscoreTXT.GetLineCount();i++)
{
    highscoreTXT.RemoveLine(i);
}


    highscoreTXT.Write();
    highscoreTXT.Close();







    ///Highscore Online

if (!chanceled){
    wxTextFile highscoreTXTOnline( wxT("Highscore/HighscoreOnline.txt") );
    highscoreTXTOnline.Create("Highscore/HighscoreOnline.txt");
    highscoreTXTOnline.Open("Highscore/HighscoreOnline.txt");



    ///Zeilen wieder formatieren





    platz=0;
    highscore="",tmp="";

    tmp = highscoreTXTOnline.GetFirstLine();

    for (int i=0; i<10; i++)
    {
        if (tmp[i] == ' ')
        {
          for (int c=0;c<i;c++)
          {
             highscore=highscore+tmp[c];
          }
          break;
        }
    }


    do {


        if ((Spieler.punkte>wxAtoi(highscore) || highscore=="")    && !hso && Spieler.punkte>0)
            {



                    wxString punktstand;
                    punktstand << Spieler.punkte;



                        if (Spieler.punkte<100)
                        {
                        punktstand=punktstand+" ";
                        }
                        if (Spieler.punkte<1000)
                        {
                        punktstand=punktstand+" ";
                        }
                    punktstand=punktstand+"   "+Spieler.name;
                    highscoreTXTOnline.InsertLine( punktstand, platz);
                    highscoreTXTOnline.Write();
                    hso=true;

                    break;
                }






        highscore="";
        tmp = highscoreTXTOnline.GetNextLine();
        for (int i=0; i<10; i++)
    {

        if (tmp[i] == ' ')
        {
          for (int c=0;c<i;c++)
          {
             highscore=highscore+tmp[c];
          }
          break;
        }
    }
        platz++;

    } while(!highscoreTXTOnline.Eof() && platz<10);


    if (platz<10 && !hso && Spieler.punkte>0)
    {
            wxString punktstand;
            punktstand << Spieler.punkte;                   ///Punktzahl ganz am ende
            if (Spieler.punkte<100)
            {
            punktstand=punktstand+" ";
            }
            if (Spieler.punkte<1000)
            {
            punktstand=punktstand+" ";
            }
             punktstand=punktstand+"   "+Spieler.name;
            highscoreTXTOnline.InsertLine( punktstand, platz);
            highscoreTXTOnline.Write();
                }








for(int i=10;i<highscoreTXTOnline.GetLineCount();i++)
{
    highscoreTXTOnline.RemoveLine(i);
}


    highscoreTXTOnline.Write();
    highscoreTXTOnline.Close();

}

}

spiel Spiel;




tastatureingaben()
{
    if (Spiel.fensterImVordergrund==GetForegroundWindow())
    {

    if((wxGetKeyState((wxKeyCode)'a') || wxGetKeyState((wxKeyCode)'A') || wxGetKeyState(WXK_LEFT)) && (Spieler.x-5>=0) )
    {
        Spieler.x=Spieler.x-2;

    }

    if ((wxGetKeyState((wxKeyCode)'d') || wxGetKeyState((wxKeyCode)'D') || wxGetKeyState(WXK_RIGHT)) && (Spieler.x+48<=Spiel.fensterBreite))
    {
        Spieler.x=Spieler.x+2;
    }

    if ((wxGetKeyState((wxKeyCode)' ') || wxGetKeyState((wxKeyCode)'w') || wxGetKeyState((wxKeyCode)'W') || wxGetKeyState(WXK_UP)) && (Spieler.darfschiessen==true))
    {

        Spieler.schiessen(&Schuss[Spiel.anzahlSchuss]);
        Spiel.anzahlSchuss++;
    }




    }
}

schussloeschen()
{
  for (int i=0;i<Spiel.anzahlSchuss;i++)
        {
          if (Schuss[i].getY()<0)       ///Schuss oben raus
          {
                for (int c=i;c<Spiel.anzahlSchuss-1;c++)
                {
                Schuss[c]=Schuss[c+1];
                }
                Spiel.anzahlSchuss=Spiel.anzahlSchuss-1;
          }
        }

       for (int i=0;i<Spiel.anzahlAlienSchuss;i++)
        {
          if (Alienschuss[i].y>Spiel.fensterHoehe)       ///Alienschuss unten raus
          {
                for (int c=i;c<Spiel.anzahlAlienSchuss-1;c++)
                {
                Alienschuss[c]=Alienschuss[c+1];
                }
                Spiel.anzahlAlienSchuss--;
          }
        }


}

alienBewegen()
{
    for (int i=0; i<Spiel.anzahlAlien;i++)
    {
        Alien[i].bewegenY(Spiel.geschwY,500);       ///bewegen
        Alien[i].bewegenX(Spiel.fensterBreite);




    }
}

trefferregistrieren()
{
    ///Spieler Schüsse -> Aliens
   for (int i=0;i<Spiel.anzahlSchuss;i++)
   {
          for (int c=0;c<Spiel.anzahlAlien;c++)
        {
                if (Schuss[i].trefferpruefen(&Alien[c],&Explosion[Spiel.anzahlExplosion],&Spiel.anzahlExplosion)==true)     ///Eigentliche Trefferanalyse
            {

                 for (int d=i;d<Spiel.anzahlSchuss-1;d++)
                {                                   ///Schuss löschen
                Schuss[d]=Schuss[d+1];
                }
                Spiel.anzahlSchuss--;

                for (int d=c;d<Spiel.anzahlAlien-1;d++)       ///Alien löschen
                {
                Alien[d]=Alien[d+1];
                }
                Spiel.anzahlAlien--;
                if (Spiel.spiellaeuft)
                {Spieler.punkte=Spieler.punkte+(Spiel.geschwX+Spiel.geschwY+Spiel.schusswahrscheinlichkeit-Spiel.lebenPUNKTE-Spiel.schussgeschwSpieler+Spiel.schussgeschwAliens);}               ///Punkte hinzufügen
            }

        }

    }







        ///Alienschüsse -> Spieler
        for (int i=0;i<Spiel.anzahlAlienSchuss;i++)
        {



            if ( (Alienschuss[i].x>Spieler.x) && (Alienschuss[i].x+3<Spieler.x+25) && (Alienschuss[i].y>Spieler.y) & (Alienschuss[i].y+9<Spieler.y+45 ) )
            {

            //Explosion[anzahlExplosion].x=spielerX;        ///Explosionen an der alten Position des Spielers
            //Explosion[anzahlExplosion].y=spielerY;        ///Spieler müsste erst nach verschwinden der Explosion
            //Explosion[anzahlExplosion].laufzeit=0;        //wieder erscheinen
            //anzahlExplosion++;

            for (int d=i;d<Spiel.anzahlAlienSchuss-1;d++)
                {
                Alienschuss[d]=Alienschuss[d+1];
                }
            Spiel.anzahlAlienSchuss--;

            Spieler.x=250-16;
            Spieler.leben--;

            ///Schüsse beim Spawnpunkt entfernen
            for (int f=0;f<Spiel.anzahlAlienSchuss;f++)
                {
                    if ((Alienschuss[f].x>220) && (Alienschuss[f].x<280) && (Alienschuss[f].y>250))
                    {

                        for (int e=f;e<Spiel.anzahlAlienSchuss-1;e++)
                        {
                        Alienschuss[e]=Alienschuss[e+1];
                        }
                        Spiel.anzahlAlienSchuss--;
                        f--;
                    }
                }
            }

        }


}


alienschiessen()
{
    for (int i=0;i<Spiel.anzahlAlien;i++)
    {
        if (Spiel.anzahlAlienSchuss<100)   ///Schiessen
        {
            if (Alien[i].schiessen(&Alienschuss[Spiel.anzahlAlienSchuss],Spiel.schusswahrscheinlichkeit)==true)
            {Spiel.anzahlAlienSchuss++;}
        }

    }
}

endeerkennug()
{
    if (Spieler.leben<=0 && Spiel.spiellaeuft)
    {

        Spiel.spiellaeuft=false;
        Spiel.highscore();
        Spieler.punkte=0;
        Spiel.normalerunde();
    }

    if (Alien[Spiel.anzahlAlien-1].getY()>=360 && Spiel.spiellaeuft)
    {
        timer->stop();
        Spiel.spiellaeuft=false;
        Spieler.leben=0;
        Spiel.highscore();
        Spieler.punkte=0;
         timer->start(Spiel.timerzeit);
        Spiel.normalerunde();
    }

    if (Spiel.anzahlAlien<=0)
    {
        Spiel.anzahlAlien=Spiel.anzahlAlienNEU;
        Spiel.normalerunde();
    }


}

explosionenentfernen()
{
    for (int i=0;i<Spiel.anzahlExplosion;i++)
    {
        Explosion[i].laufzeit++;

        if (Explosion[i].laufzeit>25)
        {
            for (int c=i;c<Spiel.anzahlExplosion;c++)
            {
            Explosion[c]=Explosion[c+1];
            }
            Spiel.anzahlExplosion--;

        }

    }
}

schiessenerlauben()
{
    Spieler.schiessenerlauben(Spiel.anzahlSchuss);
}

schussbewegen()
{
    for (int i=0; i<Spiel.anzahlSchuss;i++)
    {
        Schuss[i].bewegen(Spiel.schussgeschwSpieler);
    }

    for (int i=0; i<Spiel.anzahlAlienSchuss;i++)
    {
        Alienschuss[i].bewegen(Spiel.schussgeschwAliens);
    }
}




class BasicDrawPane : public wxPanel
{

public:
    BasicDrawPane(wxFrame* parent);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render( wxDC& dc );

    DECLARE_EVENT_TABLE()
};

class MyFrame;

class MyApp: public wxApp
{

    bool OnInit();


    MyFrame* frame;
public:

};


IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{

    BasicDrawPane* drawPane;

public:
    MyFrame() : wxFrame((wxFrame *)NULL, -1,  wxT("Space Invaders"), wxPoint(50,50), wxSize(500,500),wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
    {


        drawPane = new BasicDrawPane( this );
        drawPane->Bind(wxEVT_CHAR_HOOK, &MyFrame::KeyDown, this);

        SetMinSize(GetSize());
        SetMaxSize(GetSize());

        SetIcon(wxICON(spaceinvadersicon));


        timer = new RenderTimer(drawPane);
        Show();
        timer->start(Spiel.timerzeit);

    }
    ~MyFrame()
    {
        delete timer;
    }


    void onClose(wxCloseEvent& evt)
    {
        timer->Stop();
        evt.Skip();
    }
    void KeyDown(wxKeyEvent& event)
    {
    if (Spiel.fensterImVordergrund==GetForegroundWindow())
    {


        if ((event.GetKeyCode()==80))           ///P        Pause
        {
           if (Spiel.spiellaeuft) {timer->Stop(); Spiel.spiellaeuft=false; Spiel.spiellaeuft=false;}
           else {timer->start(Spiel.timerzeit); Spiel.spiellaeuft=true; Spiel.spiellaeuft=true;}
        }

        if ((event.GetKeyCode()==82))           ///R        Neustart
        {
            Spiel.geschwX=Spiel.geschwXNEU;
            Spiel.geschwY=Spiel.geschwYNEU;
            Spiel.schusswahrscheinlichkeit=Spiel.schusswahrscheinlichkeitNEU;
            Spiel.anzahlAlien=Spiel.anzahlAlienNEU;
            Spiel.lebenPUNKTE=Spiel.lebenNEU;

            Spiel.spiellaeuft=true;
            Spieler.punkte=0;
            Spiel.anzahlSchuss=0;
            Spieler.darfschiessen=true;
            Spieler.leben=Spiel.lebenNEU;
            if (Spiel.spiellaeuft) timer->start(Spiel.timerzeit);
            Spiel.normalerunde();
        }

        if (event.GetKeyCode()==WXK_F1)         /// F1      Hilfe
        {
        timer->stop();

        wxMessageBox("A / Pfeiltaste Links                          Raumschiff nach links bewegen \nD / Pfeiltaste Rechts                       Raumschiff nach rechts bewegen \nW / Leertaste / Pfeiltaste oben     schiessen\nR                                                        Neustart \nF1                                                       Hilfe \nH                                                        Highscore","Hilfe" ,wxICON_QUESTION);
        if (Spiel.spiellaeuft) timer->start(Spiel.timerzeit);
        }

        if (event.GetKeyCode()==72)            ///H        Highscore
        {

        timer->stop();

        wxString tmp;
        _mkdir("Highscore");

        wxTextFile highscoreTXT( wxT("Highscore/Highscore.txt") );
        highscoreTXT.Create("Highscore/Highscore.txt");
        highscoreTXT.Open();

        wxTextFile highscoreTXTOnline( wxT("Highscore/HighscoreOnline.txt") );
        highscoreTXTOnline.Create("Highscore/HighscoreOnline.txt");
        highscoreTXTOnline.Open();

        tmp="Lokaler Highscore: \n";
        tmp=tmp+highscoreTXT.GetFirstLine();
        while (!highscoreTXT.Eof())
        {
          tmp=tmp+" \n "+highscoreTXT.GetNextLine();
        }
        tmp=tmp+"\n";

        tmp=tmp+"Globaler Highscore: \n";
        tmp=tmp+highscoreTXTOnline.GetFirstLine();
        while (!highscoreTXTOnline.Eof())
        {
          tmp=tmp+" \n "+highscoreTXTOnline.GetNextLine();
        }


        wxMessageBox( tmp,"Highscore" ,wxICON_INFORMATION);


        highscoreTXT.Close();
         if (Spiel.spiellaeuft) timer->start(Spiel.timerzeit);
    }

        if ((event.GetKeyCode()==27))           ///ESC      Beenden
        {
           Close();
        }

        if ((event.GetKeyCode()==69))         ///E        Einstellungen
        {
            timer->stop();

        wxTextEntryDialog *dlg = new wxTextEntryDialog((wxFrame *)NULL,wxT("Spielgeschwindigkeit (1-100)"),wxT("Einstellungen"),wxT("85"));
             if ( dlg->ShowModal() == wxID_OK )
                {

                 Spiel.timerzeit = 100- wxAtoi(dlg->GetValue());
                }
                dlg->Destroy();


        wxTextEntryDialog *dlg1 = new wxTextEntryDialog((wxFrame *)NULL,wxT("Schwierigkeit (1-10)"),wxT("Einstellungen"),wxT("2"));
             if ( dlg1->ShowModal() == wxID_OK )
                {

                 int tmp =  wxAtoi(dlg1->GetValue());
                 if (tmp>0 && tmp<=10)
                 {
                     Spiel.geschwXNEU=tmp/2;
                     Spiel.geschwYNEU=tmp*5;
                 }

                }
                dlg1->Destroy();


                wxTextEntryDialog *dlg2 = new wxTextEntryDialog((wxFrame *)NULL,wxT("Schusswahrscheinlichkeit der Aliens (1-10)"),wxT("Einstellungen"),wxT("5"));
             if ( dlg2->ShowModal() == wxID_OK )
                {

                 int tmp =  wxAtoi(dlg2->GetValue());
                 if (tmp>0 && tmp<=10)
                 {
                    Spiel.schusswahrscheinlichkeitNEU=tmp;
                 }

                }
                dlg2->Destroy();


                 wxTextEntryDialog *dlg3 = new wxTextEntryDialog((wxFrame *)NULL,wxT("Anzahl deiner Leben (1-10)"),wxT("Einstellungen"),wxT("3"));
             if ( dlg3->ShowModal() == wxID_OK )
                {

                 int tmp =  wxAtoi(dlg3->GetValue());
                 if (tmp>0 && tmp<=10)
                 {
                    Spiel.lebenNEU=tmp;
                 }

                }
                dlg3->Destroy();

                 wxTextEntryDialog *dlg4 = new wxTextEntryDialog((wxFrame *)NULL,wxT("Geschwindigkeit der AlienSchuesse (1-10)"),wxT("Einstellungen"),wxT("2"));
             if ( dlg4->ShowModal() == wxID_OK )
                {

                 int tmp =  wxAtoi(dlg4->GetValue());
                 if (tmp>0 && tmp<=10)
                 {
                    Spiel.schussgeschwAliens=tmp;
                 }

                }
                dlg4->Destroy();

                  wxTextEntryDialog *dlg5 = new wxTextEntryDialog((wxFrame *)NULL,wxT("Geschwindigkeit der Spielerschuesse (1-10)"),wxT("Einstellungen"),wxT("3"));
             if ( dlg5->ShowModal() == wxID_OK )
                {

                 int tmp =  wxAtoi(dlg5->GetValue());
                 if (tmp>0 && tmp<=10)
                 {
                    Spiel.schussgeschwSpieler=tmp;
                 }

                }
                dlg4->Destroy();

            if (Spiel.spiellaeuft) timer->start(Spiel.timerzeit);
        }

    }

        event.Skip();
    }

    DECLARE_EVENT_TABLE()
};



BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CLOSE(MyFrame::onClose)
EVT_KEY_DOWN(MyFrame::KeyDown)
END_EVENT_TABLE()



bool MyApp::OnInit()
{

    std::srand(std::time(0));   //Zufallszahlen generieren





    ///Bilder Laden
    wxInitAllImageHandlers();
    bHintergrund.LoadFile("Images\\Hintergrund.png",wxBITMAP_TYPE_PNG);
    bRaumschiff.LoadFile("Images\\Raumschiff.png",wxBITMAP_TYPE_PNG);
    bSchuss.LoadFile("Images\\Munition.png",wxBITMAP_TYPE_PNG);
    bAlienschuss.LoadFile("Images\\Alienmunition.png",wxBITMAP_TYPE_PNG);
    bAlien.LoadFile("Images\\Alien.png",wxBITMAP_TYPE_PNG);
    bLeben.LoadFile("Images\\Leben.png",wxBITMAP_TYPE_PNG);
    bExplosion.LoadFile("Images\\Explosion.png",wxBITMAP_TYPE_PNG);





    frame = new MyFrame();
    frame->Show();


    Spiel.fensterImVordergrund=GetForegroundWindow();

    Spiel.normalerunde();
    return true;
}




BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()




void RenderTimer::Notify()
{
    std::thread t0(schussbewegen);
    std::thread t1(schiessenerlauben);
    std::thread t2(tastatureingaben);
    std::thread t3(schussloeschen);
    std::thread t4(trefferregistrieren);
    std::thread t5(explosionenentfernen);
    std::thread t6(alienBewegen);


    if (t0.joinable() || Spieler.leben==0) {}{t0.join();}
    if (t1.joinable() || Spieler.leben==0) {t1.join();}
    if (t2.joinable() || Spieler.leben==0) {t2.join();}
    if (t3.joinable() || Spieler.leben==0) {t3.join();}
    if (t4.joinable() || Spieler.leben==0) {t4.join();}
    if (t5.joinable() || Spieler.leben==0) {t5.join();}
    if (t6.joinable() || Spieler.leben==0) {t6.join();}

    endeerkennug();
    alienschiessen();

    pane->Refresh();

}



BasicDrawPane::BasicDrawPane(wxFrame* parent) :
wxPanel(parent)
{
}


void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{

    wxBufferedPaintDC dc(this);
    render(dc);
}

void BasicDrawPane::paintNow()
{

    wxBufferedPaintDC dc(this);
    render(dc);
}

void BasicDrawPane::render( wxDC& dc )
{


    ///Rendering während das Spiel läuft

    if (Spieler.leben>0)
    {

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    ///dc.SetBackground( *wxBLACK_BRUSH );
   //dc.SetBackgroundMode(1);
    ///dc.Clear();

            if (bHintergrund.IsOk())
            {
            dc.DrawBitmap(bHintergrund,0,0);

            }

            if (bSchuss.IsOk())
            {
                for (int i=0;i<Spiel.anzahlSchuss;i++)
                {
                dc.DrawBitmap(bSchuss,Schuss[i].getX(),Schuss[i].getY());
                }
            }

            if (bSchuss.IsOk())
            {
                    for (int i=0;i<Spiel.anzahlAlienSchuss;i++)
                    {
                    dc.DrawBitmap(bAlienschuss,Alienschuss[i].x,Alienschuss[i].y);
                    }
            }


            if (bRaumschiff.IsOk())
            {
            dc.DrawBitmap(bRaumschiff,Spieler.x,Spieler.y);
            }


            if (bAlien.IsOk())
            {
                for (int i=0;i<Spiel.anzahlAlien;i++)
                {
                dc.DrawBitmap(bAlien,Alien[i].getX(),Alien[i].getY());
                }

        for (int i=1; i<=Spieler.leben;i++)
        {
        dc.DrawBitmap(bLeben,i*50-40,430);

        }



            }

             ///Punktestand
    dc.SetTextForeground( *wxRED );
    dc.SetFont(wxFontInfo(12).FaceName("Distant Galaxy").Light());

    wxString punktstand="Punkte: ";
    punktstand << Spieler.punkte;

    dc.DrawText(punktstand, 380, 10);



            if (bExplosion.IsOk())
            {
                    for (int i=0;i<Spiel.anzahlExplosion;i++)
                    {
                    dc.DrawBitmap(bExplosion,Explosion[i].x,Explosion[i].y);
                    }
            }


    }

    ///Game Over
 if (Spieler.leben<=0)
 {
    dc.SetTextForeground( *wxRED );
    dc.SetFont(wxFontInfo(28).FaceName("Distant Galaxy").Light());
    dc.DrawText(wxT("Du hast Verloren"), 50, 200);
    dc.SetFont(wxFontInfo(15).FaceName("Distant Galaxy").Light());
    dc.DrawText(wxT("Neustart mit R"), 150, 250);

 }






}
