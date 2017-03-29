#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <cstdlib>
//#include <iostream>
#include <ctime>
#include <wx/icon.h>
#include <wx/dcbuffer.h>
#include <string>
#include <sstream>
#include <wx/textfile.h>
#include <windows.h>
#include <stdio.h>
#include <wx/textdlg.h>




class BasicDrawPane;

class RenderTimer : public wxTimer
{




    BasicDrawPane* pane;
public:
    RenderTimer(BasicDrawPane* pane);
    void Notify();
    void start();
    void stop();
};


RenderTimer::RenderTimer(BasicDrawPane* pane) : wxTimer()
{
    RenderTimer::pane = pane;
}
void RenderTimer::start()
{
    wxTimer::Start(15);
}

void RenderTimer::stop()
{
    wxTimer::Stop();
}
RenderTimer* timer;




wxBitmap bHintergrund,bRaumschiff,bSchuss,bAlienschuss,bAlien,bLeben,bExplosion;


class explosion
{
    public:
        explosion(){};
        virtual ~explosion(){};
        int x;
        int y;
        int laufzeit;

};

explosion Explosion[10];

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

alien Alien[30];





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
            explosionenentfernen();
            highscore();

    int spielerX=250-16;        //Anfangspositionen
    int spielerY=350;

    int schussX;
    int schussY;
    int anzahlSchuss=0;
    int anzahlAlien=0;
    int anzahlAlienSchuss=0;
    int anzahlExplosion=0;
    bool darfschiessen=true;
    bool aliensbewegensichnachrechts=true;
    int leben=3;
    int punkte=0;
    bool spiellaeuft=true;
    wxString name="";
    HWND fensterImVordergrund;

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
    if (fensterImVordergrund==GetForegroundWindow())
    {

    if((wxGetKeyState((wxKeyCode)'a') || wxGetKeyState((wxKeyCode)'A') || wxGetKeyState(WXK_LEFT)) && (spielerX-5>=0) )
    {
        spielerX=spielerX-2;

    }

    if ((wxGetKeyState((wxKeyCode)'d') || wxGetKeyState((wxKeyCode)'D') || wxGetKeyState(WXK_RIGHT)) && (spielerX+48<=fensterBreite))
    {
        spielerX=spielerX+2;
    }

    if ((wxGetKeyState((wxKeyCode)' ') || wxGetKeyState((wxKeyCode)'w') || wxGetKeyState((wxKeyCode)'W') || wxGetKeyState(WXK_UP)) && (darfschiessen==true))
    {
    anzahlSchuss++;
    Schuss[anzahlSchuss-1].x=spielerX+12;      ///Schuss positionieren
    Schuss[anzahlSchuss-1].y=spielerY-8;

    darfschiessen=false;                        ///Beides dafür, dass man nicht durchgehend schießen kann.
    schusszaehler=0;

    }




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
            {               ///Treffer erkennen

            Explosion[anzahlExplosion].x=Alien[c].x;
            Explosion[anzahlExplosion].y=Alien[c].y;
            Explosion[anzahlExplosion].laufzeit=0;
            anzahlExplosion++;

            for (int d=i;d<anzahlSchuss-1;d++)
                {                                   ///Schuss löschen
                Schuss[d]=Schuss[d+1];
                }
            anzahlSchuss--;

            for (int d=c;d<anzahlAlien-1;d++)       ///Alien löschen
                {
                Alien[d]=Alien[d+1];
                }
            anzahlAlien--;
            if (spiellaeuft)
            {punkte=punkte+10;}               ///Punkte hinzufügen


            }
        }
   }


        ///Alienschüsse -> Spieler
        for (int i=0;i<anzahlAlienSchuss;i++)
        {



            if ( (Alienschuss[i].x>spielerX) && (Alienschuss[i].x+3<spielerX+25) && (Alienschuss[i].y>spielerY) & (Alienschuss[i].y+9<spielerY+45 ) )
            {

            //Explosion[anzahlExplosion].x=spielerX;        ///Explosionen an der alten Position des Spielers
            //Explosion[anzahlExplosion].y=spielerY;        ///Spieler müsste erst nach verschwinden der Explosion
            //Explosion[anzahlExplosion].laufzeit=0;        //wieder erscheinen
            //anzahlExplosion++;

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
    if (leben<=0 && spiellaeuft)
    {
         timer->stop();
        spiellaeuft=false;
        highscore();
        punkte=0;
        timer->start();                      ///Game Over
        normalerunde();
    }

    if (Alien[anzahlAlien-1].y>=360 && spiellaeuft)
    {
        timer->stop();
        spiellaeuft=false;
        leben=0;
        highscore();
        punkte=0;
         timer->start();
        normalerunde();
    }

    if (anzahlAlien<=0)
    {
        normalerunde();
    }


}

spiel::explosionenentfernen()
{
    for (int i=0;i<anzahlExplosion;i++)
    {
        Explosion[i].laufzeit++;

        if (Explosion[i].laufzeit>25)
        {
            for (int c=i;c<anzahlExplosion;c++)
            {
            Explosion[c]=Explosion[c+1];
            }
            anzahlExplosion--;

        }

    }
}

spiel::highscore()
{
    bool hso=false,hs=false;
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


        if ((punkte>wxAtoi(highscore) || highscore=="")    && !hs && punkte>0)
            {


            wxTextEntryDialog *dlg = new wxTextEntryDialog((wxFrame *)NULL,wxT("Gib bitte deinen Namen ein"),wxT("Highscore"));
                if ( dlg->ShowModal() == wxID_OK )
                {
                    dlg->Destroy();
                    wxString punktstand;
                    punktstand << punkte;



                        if (punkte<100)
                        {
                        punktstand=punktstand+" ";
                        }
                        if (punkte<1000)
                        {
                        punktstand=punktstand+" ";
                        }
                        name=dlg->GetValue();
                    punktstand=punktstand+"   "+name;
                    highscoreTXT.InsertLine( punktstand, platz);
                    highscoreTXT.Write();
                    hs=true;


                }

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

    if (platz<10 && !hs && punkte>0)
    {

            wxTextEntryDialog *dlg = new wxTextEntryDialog((wxFrame *)NULL,wxT("Gib bitte deinen Namen ein"),wxT("Highscore"));
                if ( dlg->ShowModal() == wxID_OK )
                {
                    dlg->Destroy();
            wxString punktstand;
            punktstand << punkte;                   ///Punktzahl ganz am ende
            if (punkte<100)
            {
            punktstand=punktstand+" ";
            }
            if (punkte<1000)
            {
            punktstand=punktstand+" ";
            }
            name=dlg->GetValue();
             punktstand=punktstand+"   "+name;
            highscoreTXT.InsertLine( punktstand, platz);
            highscoreTXT.Write();
                }
                dlg->Destroy();



    }



for(int i=10;i<highscoreTXT.GetLineCount();i++)
{
    highscoreTXT.RemoveLine(i);
}


    highscoreTXT.Write();
    highscoreTXT.Close();







    ///Highscore Online


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


        if ((punkte>wxAtoi(highscore) || highscore=="")    && !hso && punkte>0)
            {



                    wxString punktstand;
                    punktstand << punkte;



                        if (punkte<100)
                        {
                        punktstand=punktstand+" ";
                        }
                        if (punkte<1000)
                        {
                        punktstand=punktstand+" ";
                        }
                    punktstand=punktstand+"   "+name;
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


    if (platz<10 && !hso && punkte>0)
    {
            wxString punktstand;
            punktstand << punkte;                   ///Punktzahl ganz am ende
            if (punkte<100)
            {
            punktstand=punktstand+" ";
            }
            if (punkte<1000)
            {
            punktstand=punktstand+" ";
            }
             punktstand=punktstand+"   "+name;
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


spiel Spiel;



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
    void KeyDown(wxKeyEvent& event)
    {
       if (Spiel.fensterImVordergrund==GetForegroundWindow())
    {
        if ((event.GetKeyCode()==80))
        {
           if (Spiel.spiellaeuft) {timer->Stop(); Spiel.spiellaeuft=false; Spiel.spiellaeuft=false;}
           else {timer->Start(); Spiel.spiellaeuft=true; Spiel.spiellaeuft=true;}
        }

        if ((event.GetKeyCode()==82))           ///Neustart
        {
            Spiel.spiellaeuft=true;
            Spiel.punkte=0;
            Spiel.anzahlSchuss=0;
            Spiel.darfschiessen=true;
            Spiel.leben=3;
            if (Spiel.spiellaeuft) timer->start();
            Spiel.normalerunde();
        }

        if (event.GetKeyCode()==WXK_F1)
        {
        timer->stop();

        wxMessageBox("A / Pfeiltaste Links                          Raumschiff nach links bewegen \nD / Pfeiltaste Rechts                       Raumschiff nach rechts bewegen \nW / Leertaste / Pfeiltaste oben     schiessen\nR                                                        Neustart \nF1                                                       Hilfe \nH                                                        Highscore","Hilfe" ,wxICON_QUESTION);
        if (Spiel.spiellaeuft) timer->start();
        }

         if (event.GetKeyCode()==72)
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
         if (Spiel.spiellaeuft) timer->start();
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

    //wxFrame->GetSize(*Spiel.fensterBreite,*Spiel.fensterHoehe);



    frame = new MyFrame();
    frame->Show();
    frame->SetDoubleBuffered(true);
    frame->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    //frame->SetBackgroundColour(wxColour(0,0,0));
    Spiel.fensterImVordergrund=GetForegroundWindow();

    Spiel.normalerunde();
    return true;
}




BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()



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

    Spiel.explosionenentfernen();

    Spiel.alienBewegen();

    Spiel.alienschiessen();

    Spiel.endeerkennug();


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



            }

             ///Punktestand
    dc.SetTextForeground( *wxRED );
    dc.SetFont(wxFontInfo(12).FaceName("Distant Galaxy").Light());

    wxString punktstand="Punkte: ";
    punktstand << Spiel.punkte;

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
 if (Spiel.leben<=0)
 {
    dc.SetTextForeground( *wxRED );
    dc.SetFont(wxFontInfo(28).FaceName("Distant Galaxy").Light());
    dc.DrawText(wxT("Du hast Verloren"), 50, 200);
    dc.SetFont(wxFontInfo(15).FaceName("Distant Galaxy").Light());
    dc.DrawText(wxT("Neustart mit R"), 150, 250);

 }






}
