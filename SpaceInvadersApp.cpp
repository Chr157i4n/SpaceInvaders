#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <wx/icon.h>
#include <wx/dcbuffer.h>
#include <string>
#include <sstream>


wxBitmap bHintergrund,bRaumschiff,bSchuss,bAlienschuss,bAlien,bLeben;

class alienschuss
{
    public:
        alienschuss(){};
        virtual ~alienschuss(){};
        int x;
        int y;
        bewegen() {y=y+2;};

    protected:

    private:
};

alienschuss Alienschuss[100];

class alien
{
    public:
        alien(){};
        virtual ~alien(){};
        int x;
        int y;


    protected:

    private:
};





alien Alien[20];

class schuss
{
    public:
        schuss(){};
        virtual ~schuss(){};
        int x;
        int y;
        bewegen() {y=y-2;};


    protected:

    private:
};

schuss Schuss[10];


class spiel
{
    public:
            spiel(){};
            virtual ~spiel(){};
            normalerunde();
            tastatureingaben();
            schussbewegen();
            schiessenerlauben();
            schussloeschen();
            alienBewegen();
            trefferregistrieren();
            alienschiessen();
            endeerkennug();

    int spielerX=250-16;        //Anfangspositionen
    int spielerY=350;

    int schussX;
    int schussY;
    int anzahlSchuss=0;
    int anzahlAlien=0;
    int anzahlAlienSchuss=0;
    bool darfschiessen=true;
    bool aliensbewegensichnachrechts=true;
    int leben=3;
    int punkte=0;

protected:

private:
    int fensterHoehe=500, fensterBreite=500;
    int schusszaehler;
};


spiel::normalerunde()
{

    anzahlAlienSchuss=0;
    anzahlAlien=0;
    anzahlSchuss=0;
    spielerX=250-16;


        int spaltealien=0;
        int reihealien=1;
        anzahlAlien=20;
        for (int i=0;i<anzahlAlien;i++)
        {
           spaltealien++;

           if (spaltealien>10)
           {    spaltealien=1;
                reihealien++;   }                               ///Aliens hinzufügen

        Alien[i].x=spaltealien*40;
        Alien[i].y=reihealien*40;

        }

        //leben=3;
}

spiel::tastatureingaben()
{
    if((wxGetKeyState((wxKeyCode)'a') || wxGetKeyState((wxKeyCode)'A')) && (spielerX-5>=0) )
    {
        spielerX=spielerX-2;
    }

    if ((wxGetKeyState((wxKeyCode)'d') || wxGetKeyState((wxKeyCode)'D')) && (spielerX+48<=fensterBreite))
    {
        spielerX=spielerX+2;
    }

    if ((wxGetKeyState((wxKeyCode)' ') || wxGetKeyState((wxKeyCode)' ')) && (darfschiessen==true))
    {
    anzahlSchuss++;
    Schuss[anzahlSchuss-1].x=spielerX+12;      ///Schuss positionieren
    Schuss[anzahlSchuss-1].y=spielerY-8;

    darfschiessen=false;                        ///Beides dafür, dass man nicht durchgehend schießen kann.
    schusszaehler=0;

    }

     if (wxGetKeyState((wxKeyCode)'r') || wxGetKeyState((wxKeyCode)'R'))
    {
        punkte=0;
        anzahlSchuss=0;
        darfschiessen=true;
        leben=3;
        normalerunde();                                         //Restart
    }

}

spiel::schiessenerlauben()
{
    schusszaehler++;

    if (schusszaehler>40)
    {
    darfschiessen=true;
    schusszaehler=0;
    }
}

spiel::schussloeschen()
{
  for (int i=0;i<anzahlSchuss;i++)
        {
          if (Schuss[i].y<0)       ///Schuss oben raus
          {
                for (int c=i;c<anzahlSchuss-1;c++)
                {
                Schuss[c]=Schuss[c+1];
                }
                anzahlSchuss=anzahlSchuss-1;
          }
        }

       for (int i=0;i<anzahlAlienSchuss;i++)
        {
          if (Alienschuss[i].y>fensterHoehe)       ///Alienschuss unten raus
          {
                for (int c=i;c<anzahlAlienSchuss-1;c++)
                {
                Alienschuss[c]=Alienschuss[c+1];
                }
                anzahlAlienSchuss=anzahlAlienSchuss-1;
          }
        }


}

spiel::alienBewegen()
{
    for (int i=0; i<anzahlAlien;i++)
    {

        ///Aliens bewegen
      if (aliensbewegensichnachrechts)  Alien[i].x++;
      if (!aliensbewegensichnachrechts)  Alien[i].x--;


        ///Richtung wechseln und eine Reihe nach unten
      if ((Alien[i].x>fensterBreite-50) && (aliensbewegensichnachrechts))
      {
          aliensbewegensichnachrechts=false;
            for (int c=0;c<anzahlAlien;c++)
                {
                Alien[c].y=Alien[c].y+20;
                }
      }
      if ((Alien[i].x<2) && (!aliensbewegensichnachrechts))
        {
            aliensbewegensichnachrechts=true;
            for (int c=0;c<anzahlAlien;c++)
                {
                Alien[c].y=Alien[c].y+20;
                }
        }
    }

}

spiel::trefferregistrieren()
{
    ///Spieler Schüsse -> Aliens
   for (int i=0;i<anzahlSchuss;i++)
   {
          for (int c=0;c<anzahlAlien;c++)
        {
            if ( (Schuss[i].x>Alien[c].x) && (Schuss[i].x+4<Alien[c].x+30) && (Schuss[i].y>Alien[c].y) & (Schuss[i].y+9<Alien[c].y+30) )
            {

            for (int d=i;d<anzahlSchuss-1;d++)
                {
                Schuss[d]=Schuss[d+1];
                }
            anzahlSchuss--;

            for (int d=c;d<anzahlAlien-1;d++)
                {
                Alien[d]=Alien[d+1];
                }
            anzahlAlien--;
            punkte=punkte+10;
            }
        }
   }


        ///Alienschüsse -> Spieler
        for (int i=0;i<anzahlAlienSchuss;i++)
        {



            if ( (Alienschuss[i].x>spielerX) && (Alienschuss[i].x+3<spielerX+25) && (Alienschuss[i].y>spielerY) & (Alienschuss[i].y+9<spielerY+45 ) )
            {

            for (int d=i;d<anzahlAlienSchuss-1;d++)
                {
                Alienschuss[d]=Alienschuss[d+1];
                }
            anzahlAlienSchuss--;

            spielerX=250-16;
            leben--;

            ///Schüsse beim Spawnpunkt entfernen
            for (int f=0;f<anzahlAlienSchuss;f++)
                {
                    if ((Alienschuss[f].x>220) && (Alienschuss[f].x<280) && (Alienschuss[f].y>250))
                    {

                        for (int e=f;e<anzahlAlienSchuss-1;e++)
                        {
                        Alienschuss[e]=Alienschuss[e+1];
                        }
                        anzahlAlienSchuss--;
                        f--;
                    }
                }
            }

        }


}

spiel::alienschiessen()
{
    for (int i=0;i<anzahlAlien;i++)
    {
        int zufall= std::rand()%1000+1;

                if (zufall>995)
                    {
                    Alienschuss[anzahlAlienSchuss].x=Alien[i].x+14;
                    Alienschuss[anzahlAlienSchuss].y=Alien[i].y+30;

                    anzahlAlienSchuss++;
                    }
    }
}

spiel::endeerkennug()
{
    if (leben<=0)
    {
        punkte=0;                        ///Game Over
        normalerunde();
    }

    if (Alien[anzahlAlien-1].y>=360)
    {
        punkte=0;
        leben=0;
        normalerunde();
    }

    if (anzahlAlien<=0)
    {
        normalerunde();
    }


}
spiel Spiel;


class BasicDrawPane;

class RenderTimer : public wxTimer
{




    BasicDrawPane* pane;
public:
    RenderTimer(BasicDrawPane* pane);
    void Notify();
    void start();
};


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


RenderTimer::RenderTimer(BasicDrawPane* pane) : wxTimer()
{
    RenderTimer::pane = pane;
}

void RenderTimer::Notify()
{
    Spiel.schiessenerlauben();
    Spiel.tastatureingaben();


    Spiel.schussloeschen();

    for (int i=0; i<Spiel.anzahlSchuss;i++)
    {
        Schuss[i].bewegen();
    }

    for (int i=0; i<Spiel.anzahlAlienSchuss;i++)
    {
        Alienschuss[i].bewegen();
    }

    Spiel.trefferregistrieren();


    Spiel.alienBewegen();

    Spiel.alienschiessen();

    Spiel.endeerkennug();


    pane->Refresh();
}

void RenderTimer::start()
{
    wxTimer::Start(15);
}

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{
    RenderTimer* timer;
    BasicDrawPane* drawPane;

public:
    MyFrame() : wxFrame((wxFrame *)NULL, -1,  wxT("Space Invaders"), wxPoint(50,50), wxSize(500,500),wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
    {


        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        drawPane = new BasicDrawPane( this );
        sizer->Add(drawPane, 1, wxEXPAND);
        SetSizer(sizer);

        SetMinSize(GetSize());
        SetMaxSize(GetSize());

        SetIcon(wxICON(spaceinvadersicon));


        timer = new RenderTimer(drawPane);
        Show();
        timer->start();

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


    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CLOSE(MyFrame::onClose)
END_EVENT_TABLE()



bool MyApp::OnInit()
{
    std::srand(std::time(0));   //Zufallszahlen generieren

    ///Bilder Laden
    wxInitAllImageHandlers();
    bHintergrund.LoadFile("Hintergrund.png",wxBITMAP_TYPE_PNG);
    bRaumschiff.LoadFile("Raumschiff.png",wxBITMAP_TYPE_PNG);
    bSchuss.LoadFile("Munition.png",wxBITMAP_TYPE_PNG);
    bAlienschuss.LoadFile("Alienmunition.png",wxBITMAP_TYPE_PNG);
    bAlien.LoadFile("Alien.png",wxBITMAP_TYPE_PNG);
    bLeben.LoadFile("Leben.png",wxBITMAP_TYPE_PNG);

    //wxFrame->GetSize(*Spiel.fensterBreite,*Spiel.fensterHoehe);



    frame = new MyFrame();
    frame->Show();
    frame->SetDoubleBuffered(true);
    frame->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    //frame->SetBackgroundColour(wxColour(0,0,0));


    Spiel.normalerunde();
    return true;
}


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()



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

    if (Spiel.leben>0)
    {

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    dc.SetBackground( *wxBLACK_BRUSH );
   //dc.SetBackgroundMode(1);
    dc.Clear();

            if (bHintergrund.IsOk())
            {
            dc.DrawBitmap(bHintergrund,0,0);

            }

            if (bSchuss.IsOk())
            {
                for (int i=0;i<Spiel.anzahlSchuss;i++)
                {
                dc.DrawBitmap(bSchuss,Schuss[i].x,Schuss[i].y);
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
            dc.DrawBitmap(bRaumschiff,Spiel.spielerX,Spiel.spielerY);
            }


            if (bAlien.IsOk())
            {
                for (int i=0;i<Spiel.anzahlAlien;i++)
                {
                dc.DrawBitmap(bAlien,Alien[i].x,Alien[i].y);
                }

        for (int i=1; i<=Spiel.leben;i++)
        {
        dc.DrawBitmap(bLeben,i*50-40,430);

        }

        ///Punktestand
    dc.SetTextForeground( *wxRED );
    dc.SetFont(wxFontInfo(12).FaceName("Distant Galaxy").Light());

    wxString punktstand="Punkte: ";
    punktstand << Spiel.punkte;

    dc.DrawText(punktstand, 380, 10);

            }


    }

    ///Game Over
 if (Spiel.leben<=0)
 {
    dc.SetTextForeground( *wxRED );
    dc.SetFont(wxFontInfo(28).FaceName("Distant Galaxy").Light());
    dc.DrawText(wxT("Du hast Verloren"), 50, 200);
    dc.SetFont(wxFontInfo(15).FaceName("Distant Galaxy").Light());
    dc.DrawText(wxT("Neustart mit R"), 150, 250);

 }






}
