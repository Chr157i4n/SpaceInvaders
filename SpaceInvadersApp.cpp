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
#include <thread>



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
    int schusszaehler;
    int fensterHoehe=500, fensterBreite=500;
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

}

spiel Spiel;




tastatureingaben()
{
    if (Spiel.fensterImVordergrund==GetForegroundWindow())
    {

    if((wxGetKeyState((wxKeyCode)'a') || wxGetKeyState((wxKeyCode)'A') || wxGetKeyState(WXK_LEFT)) && (Spiel.spielerX-5>=0) )
    {
        Spiel.spielerX=Spiel.spielerX-2;

    }

    if ((wxGetKeyState((wxKeyCode)'d') || wxGetKeyState((wxKeyCode)'D') || wxGetKeyState(WXK_RIGHT)) && (Spiel.spielerX+48<=Spiel.fensterBreite))
    {
        Spiel.spielerX=Spiel.spielerX+2;
    }

    if ((wxGetKeyState((wxKeyCode)' ') || wxGetKeyState((wxKeyCode)'w') || wxGetKeyState((wxKeyCode)'W') || wxGetKeyState(WXK_UP)) && (Spiel.darfschiessen==true))
    {
    Spiel.anzahlSchuss++;
    Schuss[Spiel.anzahlSchuss-1].x=Spiel.spielerX+12;      ///Schuss positionieren
    Schuss[Spiel.anzahlSchuss-1].y=Spiel.spielerY-8;

    Spiel.darfschiessen=false;                        ///Beides dafür, dass man nicht durchgehend schießen kann.
    Spiel.schusszaehler=0;

    }




    }
}

schussloeschen()
{
  for (int i=0;i<Spiel.anzahlSchuss;i++)
        {
          if (Schuss[i].y<0)       ///Schuss oben raus
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

        ///Aliens bewegen
      if (Spiel.aliensbewegensichnachrechts)  Alien[i].x++;
      if (!Spiel.aliensbewegensichnachrechts)  Alien[i].x--;


        ///Richtung wechseln und eine Reihe nach unten
      if ((Alien[i].x>Spiel.fensterBreite-50) && (Spiel.aliensbewegensichnachrechts))
      {
          Spiel.aliensbewegensichnachrechts=false;
            for (int c=0;c<Spiel.anzahlAlien;c++)
                {
                Alien[c].y=Alien[c].y+20;
                }
      }
      if ((Alien[i].x<2) && (!Spiel.aliensbewegensichnachrechts))
        {
            Spiel.aliensbewegensichnachrechts=true;
            for (int c=0;c<Spiel.anzahlAlien;c++)
                {
                Alien[c].y=Alien[c].y+20;
                }
        }
    }

}

trefferregistrieren()
{
    ///Spieler Schüsse -> Aliens
   for (int i=0;i<Spiel.anzahlSchuss;i++)
   {
          for (int c=0;c<Spiel.anzahlAlien;c++)
        {
            if ( (Schuss[i].x>Alien[c].x) && (Schuss[i].x+4<Alien[c].x+30) && (Schuss[i].y>Alien[c].y) & (Schuss[i].y+9<Alien[c].y+30) )
            {               ///Treffer erkennen

            Explosion[Spiel.anzahlExplosion].x=Alien[c].x;
            Explosion[Spiel.anzahlExplosion].y=Alien[c].y;
            Explosion[Spiel.anzahlExplosion].laufzeit=0;
            Spiel.anzahlExplosion++;

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
            {Spiel.punkte=Spiel.punkte+10;}               ///Punkte hinzufügen


            }
        }
   }


        ///Alienschüsse -> Spieler
        for (int i=0;i<Spiel.anzahlAlienSchuss;i++)
        {



            if ( (Alienschuss[i].x>Spiel.spielerX) && (Alienschuss[i].x+3<Spiel.spielerX+25) && (Alienschuss[i].y>Spiel.spielerY) & (Alienschuss[i].y+9<Spiel.spielerY+45 ) )
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

            Spiel.spielerX=250-16;
            Spiel.leben--;

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
        int zufall= std::rand()%1000+1;

                if (zufall>995)
                    {
                    Alienschuss[Spiel.anzahlAlienSchuss].x=Alien[i].x+14;
                    Alienschuss[Spiel.anzahlAlienSchuss].y=Alien[i].y+30;

                    Spiel.anzahlAlienSchuss++;
                    }
    }
}

endeerkennug()
{
    if (Spiel.leben<=0 && Spiel.spiellaeuft)
    {

        Spiel.spiellaeuft=false;
        Spiel.highscore();
        Spiel.punkte=0;
        Spiel.normalerunde();
    }

    if (Alien[Spiel.anzahlAlien-1].y>=360 && Spiel.spiellaeuft)
    {
        timer->stop();
        Spiel.spiellaeuft=false;
        Spiel.leben=0;
        Spiel.highscore();
        Spiel.punkte=0;
         timer->start();
        Spiel.normalerunde();
    }

    if (Spiel.anzahlAlien<=0)
    {
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
    Spiel.schusszaehler++;

    if (Spiel.schusszaehler>40)
    {
    Spiel.darfschiessen=true;
    Spiel.schusszaehler=0;
    }
}

schussbewegen()
{
    for (int i=0; i<Spiel.anzahlSchuss;i++)
    {
        Schuss[i].bewegen();
    }

    for (int i=0; i<Spiel.anzahlAlienSchuss;i++)
    {
        Alienschuss[i].bewegen();
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
     if ((event.GetKeyCode()==27))           ///ESC
        {
           Close();
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


    if (t0.joinable() || Spiel.leben==0) {}{t0.join();}
    if (t1.joinable() || Spiel.leben==0) {t1.join();}
    if (t2.joinable() || Spiel.leben==0) {t2.join();}
    if (t3.joinable() || Spiel.leben==0) {t3.join();}
    if (t4.joinable() || Spiel.leben==0) {t4.join();}
    if (t5.joinable() || Spiel.leben==0) {t5.join();}
    if (t6.joinable() || Spiel.leben==0) {t6.join();}

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

    if (Spiel.leben>0)
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
