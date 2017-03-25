#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>







wxBitmap bHintergrund,bRaumschiff,bSchuss,bAlienschuss,bAlien;

class alien
{
    public:
        alien(){};
        virtual ~alien(){};
        int x;
        int y;
        schiessen();

    protected:

    private:
};
alien::schiessen()
{

}




alien Alien[20];

class schuss
{
    public:
        schuss(){};
        virtual ~schuss(){};
        int x;
        int y;
        bewegen();


    protected:

    private:
};

schuss::bewegen()
{
    y=y-2;
}



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

    int spielerX=250-16;        //Anfangspositionen
    int spielerY=350;

    int schussX;
    int schussY;
    int anzahlSchuesse=0;
    int anzahlAliens=0;
    bool darfschiessen=true;
    bool aliensbewegensichnachrechts=true;

protected:

private:
    int fensterHoehe=500, fensterBreite=500;
    int schusszaehler;
};


spiel::normalerunde()
{
        int spaltealien=0;
        int reihealien=1;
        anzahlAliens=20;
        for (int i=0;i<anzahlAliens;i++)
        {
           spaltealien++;

           if (spaltealien>10)
           {    spaltealien=1;
                reihealien++;   }                               ///Aliens hinzufügen

        Alien[i].x=spaltealien*40;
        Alien[i].y=reihealien*40;

        }
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
    anzahlSchuesse++;
    Schuss[anzahlSchuesse-1].x=spielerX+12;      ///Schuss positionieren
    Schuss[anzahlSchuesse-1].y=spielerY-8;

    darfschiessen=false;                        ///Beides dafür, dass man nicht durchgehend schießen kann.
    schusszaehler=0;

    }

}



spiel::schiessenerlauben()
{
    schusszaehler++;

    if (schusszaehler>50)
    {
    darfschiessen=true;
    schusszaehler=0;
    }
}

spiel::schussloeschen()
{
  for (int i=0;i<anzahlSchuesse;i++)
        {
          if ((Schuss[i].y<50) || (Schuss[i].y>fensterHoehe))       ///Schuss oben raus
          {
                for (int c=i;c<anzahlSchuesse-1;c++)
                {
                Schuss[c]=Schuss[c+1];
                }
                anzahlSchuesse=anzahlSchuesse-1;
          }
        }
}

spiel::alienBewegen()
{
    for (int i=0; i<anzahlAliens;i++)
    {

        ///Aliens bewegen
      if (aliensbewegensichnachrechts)  Alien[i].x++;
      if (!aliensbewegensichnachrechts)  Alien[i].x--;


        ///Richtung wechseln und eine Reihe nach unten
      if ((Alien[i].x>fensterBreite-50) && (aliensbewegensichnachrechts))
      {
          aliensbewegensichnachrechts=false;
            for (int c=0;c<anzahlAliens;c++)
                {
                Alien[c].y=Alien[c].y+20;
                }
      }
      if ((Alien[i].x<2) && (!aliensbewegensichnachrechts))
        {
            aliensbewegensichnachrechts=true;
            for (int c=0;c<anzahlAliens;c++)
                {
                Alien[c].y=Alien[c].y+20;
                }
        }
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

    for (int i=0; i<Spiel.anzahlSchuesse;i++)
    {
        Schuss[i].bewegen();
        Spiel.schussloeschen();
    }


    Spiel.alienBewegen();
    for (int i=0; i<Spiel.anzahlAliens;i++)
    {
        Alien[i].schiessen();
    }


    pane->Refresh();
}

void RenderTimer::start()
{
    wxTimer::Start(30);
}

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{
    RenderTimer* timer;
    BasicDrawPane* drawPane;

public:
    MyFrame() : wxFrame((wxFrame *)NULL, -1,  wxT("Space Invaders"), wxPoint(50,50), wxSize(500,500))
    {



        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        drawPane = new BasicDrawPane( this );
        sizer->Add(drawPane, 1, wxEXPAND);
        SetSizer(sizer);




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


    ///Bilder Laden
    wxInitAllImageHandlers();
    bHintergrund.LoadFile("Hintergrund.png",wxBITMAP_TYPE_PNG);
    bRaumschiff.LoadFile("Raumschiff.png",wxBITMAP_TYPE_PNG);
    bSchuss.LoadFile("Munition.png",wxBITMAP_TYPE_PNG);
    bAlienschuss.LoadFile("Alienmunition.png",wxBITMAP_TYPE_PNG);
    bAlien.LoadFile("Alien.png",wxBITMAP_TYPE_PNG);

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

    wxPaintDC dc(this);
    render(dc);
}

void BasicDrawPane::paintNow()
{

    wxPaintDC dc(this);
    render(dc);
}

void BasicDrawPane::render( wxDC& dc )
{
   // SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    dc.SetBackground( *wxBLACK_BRUSH );
   //dc.SetBackgroundMode(1);
    dc.Clear();




    if (bHintergrund.IsOk())
    {
    dc.DrawBitmap(bHintergrund,0,0);

    }
    if (bRaumschiff.IsOk())
    {
    dc.DrawBitmap(bRaumschiff,Spiel.spielerX,Spiel.spielerY);
    }

    if (bSchuss.IsOk())
    {
        for (int i=0;i<Spiel.anzahlSchuesse;i++)
        {
        dc.DrawBitmap(bSchuss,Schuss[i].x,Schuss[i].y);
        }
    }
    if (bAlien.IsOk())
    {
        for (int i=0;i<Spiel.anzahlAliens;i++)
        {
        dc.DrawBitmap(bAlien,Alien[i].x,Alien[i].y);
        }
    }
//if (Spiel.anzahlSchuesse>sizeof(schuss))



}
