//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#pragma hdrstop

#include "Unit1.h"
//#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
/*
 - p[0] odpowiada za to kogo jest ruch,
 - pola od p[1]-p[9] (p[1] to lewa gora)
   odpowiadaja pola planszy i p=:
    - 'n' - pole puste,
    - 'x' - odznaczone przez gracza x,
    - 'o' - odznaczone przez gracza o,

*/
int ilosc_lini = 3;
int rozmiar = ilosc_lini*ilosc_lini+1; //dodajemy 1 poniewaz pole 0 to urzytkownik grajacy.
char *p = new char[rozmiar]; //ilosc pol


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void sprawdz()
        {
        bool prawda=true,wygrana=false;
        //SZUKANIE W PIONIE
        for(int i=1;i<rozmiar;i=i+ilosc_lini)
                {
                prawda=true;
                for(int j=i;j<i+ilosc_lini;j++)
                        {
                        if(p[j]!=p[i]) {prawda=false;}
                        }
                if(prawda && (p[i]!='n')){wygrana=true;}
                }
      //SZUKANIE W POZIOMIE
        for(int i=1;i<ilosc_lini+1;i++)
                {
                prawda=true;
                for(int j=i;j<rozmiar;j=j+ilosc_lini)
                        {
                        if(p[j]!=p[i]) {prawda=false;}
                        }
                 if(prawda && (p[i]!='n')){wygrana=true;}
                }
        //SZUKANIE LEWY SKOS
        prawda=true;
        for(int i=1;i<rozmiar;i=i+ilosc_lini+1)
            {
            if(p[i]!=p[1]){prawda=false;}
            }
        if(prawda && (p[1]!='n')){wygrana=true;}

        //SZUKANIE PRAWY SKOS
        prawda=true;
        for(int i=ilosc_lini;i<rozmiar-1;i=i+ilosc_lini-1)
            {
            if(p[i]!=p[ilosc_lini]){prawda=false;}
            }
        if(prawda &&(p[ilosc_lini]!='n')){wygrana=true;}

        /*INSTRUKCJA W RAZIE WYGRANEJ*/
        if(wygrana)
                {
                char *w;
                if(p[0]=='x') w="Wygrywa kó³ko!";
                else w="Wygrywa krzy¿yk!";

                Application->MessageBox(w, "Koniec Gry",MB_OK);
                }
        }

void __fastcall TForm1::FormCreate(TObject *Sender)
{       //wczytanie obrazow
        pole1->Picture->LoadFromFile("img/nic.bmp");
        pole2->Picture->LoadFromFile("img/nic.bmp");
        pole3->Picture->LoadFromFile("img/nic.bmp");
        pole4->Picture->LoadFromFile("img/nic.bmp");
        pole5->Picture->LoadFromFile("img/nic.bmp");
        pole6->Picture->LoadFromFile("img/nic.bmp");
        pole7->Picture->LoadFromFile("img/nic.bmp");
        pole8->Picture->LoadFromFile("img/nic.bmp");
        pole9->Picture->LoadFromFile("img/nic.bmp");
        tura->Picture->LoadFromFile("img/osmall.bmp");
        //oznaczenie urzytkownika
        p[0]='o';
        //oznaczenie pustych pol przy wczytaniu
        for(int i=1;i<rozmiar;i++){p[i]='n';}
        pole1->Enabled=true;
        pole2->Enabled=true;
        pole3->Enabled=true;
        pole4->Enabled=true;
        pole5->Enabled=true;
        pole6->Enabled=true;
        pole7->Enabled=true;
        pole8->Enabled=true;
        pole9->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::pole1Click(TObject *Sender)
{
 if(p[1]=='n')
        {
        if(p[0]=='o')
                {
                pole1->Picture->LoadFromFile("img/o.bmp");
                p[1]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole1->Picture->LoadFromFile("img/x.bmp");
                p[1]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole1->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole2Click(TObject *Sender)
{
 if(p[2]=='n')
        {
        if(p[0]=='o')
                {
                pole2->Picture->LoadFromFile("img/o.bmp");
                p[2]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole2->Picture->LoadFromFile("img/x.bmp");
                p[2]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole2->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole3Click(TObject *Sender)
{
 if(p[3]=='n')
        {
        if(p[0]=='o')
                {
                pole3->Picture->LoadFromFile("img/o.bmp");
                p[3]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole3->Picture->LoadFromFile("img/x.bmp");
                p[3]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole3->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole4Click(TObject *Sender)
{
 if(p[4]=='n')
        {
        if(p[0]=='o')
                {
                pole4->Picture->LoadFromFile("img/o.bmp");
                p[4]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole4->Picture->LoadFromFile("img/x.bmp");
                p[4]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole4->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole5Click(TObject *Sender)
{
 if(p[5]=='n')
        {
        if(p[0]=='o')
                {
                pole5->Picture->LoadFromFile("img/o.bmp");
                p[5]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole5->Picture->LoadFromFile("img/x.bmp");
                p[5]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole5->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole6Click(TObject *Sender)
{
 if(p[6]=='n')
        {
        if(p[0]=='o')
                {
                pole6->Picture->LoadFromFile("img/o.bmp");
                p[6]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole6->Picture->LoadFromFile("img/x.bmp");
                p[6]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole6->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole7Click(TObject *Sender)
{
 if(p[7]=='n')
        {
        if(p[0]=='o')
                {
                pole7->Picture->LoadFromFile("img/o.bmp");
                p[7]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole7->Picture->LoadFromFile("img/x.bmp");
                p[7]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole7->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole8Click(TObject *Sender)
{
 if(p[8]=='n')
        {
        if(p[0]=='o')
                {
                pole8->Picture->LoadFromFile("img/o.bmp");
                p[8]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole8->Picture->LoadFromFile("img/x.bmp");
                p[8]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole8->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pole9Click(TObject *Sender)
{
 if(p[9]=='n')
        {
        if(p[0]=='o')
                {
                pole9->Picture->LoadFromFile("img/o.bmp");
                p[9]='o';
                p[0]='x';
                tura->Picture->LoadFromFile("img/xsmall.bmp");
                }
        else
                {
                pole9->Picture->LoadFromFile("img/x.bmp");
                p[9]='x';
                p[0]='o';
                tura->Picture->LoadFromFile("img/osmall.bmp");
                }
        pole9->Enabled=False;
        sprawdz();
        }
}
//---------------------------------------------------------------------------

