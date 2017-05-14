#include <wx/dcbuffer.h>
#include <wx/textfile.h>
#include <thread>

#include "alien.h"
#include "explosion.h"
#include "alienschuss.h"
#include "schuss.h"
#include "spieler.h"
#include "spiel.h"

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

spiel Spiel;



tastatureingaben()
{
    if (Spiel.fensterImVordergrund==GetForegroundWindow())
    {

    if((wxGetKeyState((wxKeyCode)'a') || wxGetKeyState((wxKeyCode)'A') || wxGetKeyState(WXK_LEFT)) && (Spieler.getX()-5>=0) )
    {
        Spieler.bewegen(-2);

    }

    if ((wxGetKeyState((wxKeyCode)'d') || wxGetKeyState((wxKeyCode)'D') || wxGetKeyState(WXK_RIGHT)) && (Spieler.getX()+48<=Spiel.fensterBreite))
    {
        Spieler.bewegen(+2);
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
          if (Alienschuss[i].getY()>Spiel.fensterHoehe)       ///Alienschuss unten raus
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
                if (Schuss[i].trefferpruefen(&Alien[c],&Explosion[Spiel.anzahlExplosion],&Spiel, &Spieler)==true)     ///Eigentliche Trefferanalyse
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
                 }

        }

    }







        ///Alienschüsse -> Spieler
        for (int i=0;i<Spiel.anzahlAlienSchuss;i++)
        {


            if (Alienschuss[i].trefferpruefen(&Spieler)==true)     ///Eigentliche Trefferanalyse
            {

                 for (int d=i;d<Spiel.anzahlAlienSchuss-1;d++)
                {
                Alienschuss[d]=Alienschuss[d+1];
                }
                    Spiel.anzahlAlienSchuss--;



                ///Schüsse beim Spawnpunkt entfernen
                for (int f=0;f<Spiel.anzahlAlienSchuss;f++)
                {
                    if ((Alienschuss[f].getX()>220) && (Alienschuss[f].getX()<280) && (Alienschuss[f].getY()>250))
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
        Spiel.highscore(&Spieler);
        Spieler.punkte=0;
        Spiel.normalerunde(&Spieler,Alien);
    }

    if (Alien[Spiel.anzahlAlien-1].getY()>=360 && Spiel.spiellaeuft)
    {
        timer->stop();
        Spiel.spiellaeuft=false;
        Spieler.leben=0;
        Spiel.highscore(&Spieler);
        Spieler.punkte=0;
         timer->start(Spiel.timerzeit);
        Spiel.normalerunde(&Spieler,Alien);
    }

    if (Spiel.anzahlAlien<=0)
    {
        Spiel.anzahlAlien=Spiel.anzahlAlienNEU;
        Spiel.normalerunde(&Spieler,Alien);
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
            Spiel.normalerunde(&Spieler,Alien);
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
            Spiel.highscoreZeigen();
            if (Spiel.spiellaeuft) timer->start(Spiel.timerzeit);
        }

        if ((event.GetKeyCode()==27))           ///ESC      Beenden
        {
           Close();
        }

        if ((event.GetKeyCode()==69))         ///E        Einstellungen
        {
            timer->stop();

            Spiel.einstellungen();

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

    Spiel.normalerunde(&Spieler,Alien);
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


    if (t0.joinable() || Spieler.leben==0) {t0.join();}
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
                    dc.DrawBitmap(bAlienschuss,Alienschuss[i].getX(),Alienschuss[i].getY());
                    }
            }


            if (bRaumschiff.IsOk())
            {
            dc.DrawBitmap(bRaumschiff,Spieler.getX(),Spieler.getY());
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
