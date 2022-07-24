#ifndef __PLIKOWANIE__HPP
#define __PLIKOWANIE__HPP

#include <iostream>
#include <iomanip>
#include <dirent.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <string>
#include <fstream>
#include <list>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/tuple/tuple.hpp>
//#include "stdafx.h"
using namespace std;
using namespace boost;

const char * typPliku( unsigned typ ) { // (1)
    switch( typ ) {
    case DT_UNKNOWN: return "Nieznany typ, nie wszystkie systemy rozró¿niaja typy, czesto jest zwracana ta wartosc";
    case DT_REG: return "Regularny plik";
    case DT_DIR: return "Katalog";
    case DT_FIFO: return "Potok nazwany";
    case DT_SOCK: return "Lokalne gniazdo";
    case DT_CHR: return "Urz¹dzenie znakowe 'A character device'";
    case DT_BLK: return "Urzadzenie blokowe 'A block device'";
    case DT_LNK: return "Dowiazanie symboliczne";
    };
}

int pokazErrno() {
    int errno_kopia = errno;
    if( errno ) {
        printf( "errno = %d:\t", errno ); fflush( stdout );
        switch( errno ) {
        case EACCES: perror( "! (problem w OPENDIR) brak dostepu do czytanej sciezki" ); break;
        case ELOOP: perror( "! (problem w OPENDIR) zbyt wiele symbolicznych powi¹zañ napotkanych w œcie¿ce" ); break;
        case ENAMETOOLONG: perror( "! (problem w OPENDIR) d³ugoœæ œcie¿ki przekracza PATH_MAX, lub d³ugoœæ nazw jej komponentów przekracza NAME_MAX" ); break;
        case ENOENT: perror( "! (problem w OPENDIR) œcie¿ka jest pustym stringiem, lub (problem w OPENDIR lub READDIR) sk³adnik œcie¿ki nie jest nazw¹ istniej¹cej œcie¿ki\n" ); break;
        case ENOTDIR: perror( "! (problem w OPENDIR) komponent lub nazwa œcie¿ki nie jest œcie¿k¹" ); break;
        case EMFILE: perror( "! (problem w OPENDIR) jest otwarta liczba plików równa OPEN_MAX" ); break;
        case ENFILE: perror( "! (problem w OPENDIR) zbyt wiele plików jest obecnie otwartych przez system" ); break;
        case EOVERFLOW: perror( "! (problem w READDIR) jedna z wartoœci w strukturze nie mo¿e byæ zwrócona poprawnie" ); break;
        case EBADF: perror( "! (problem w READDIR lub CLOSEDIR) argument funkcji readdir nie odnosi siê do otwartego strumienia œcie¿ki" ); break;
        case EINTR: perror( "! (problem w CLOSEDIR) pojawia siê wtedy gry funkcja jest przerwana przez sygna³" ); break;
        };
        errno = 0;
        printf( "\n" );
    }
    return errno_kopia;
}

struct Element {
    string adres;
    string nazwa;
    int nr_seryjny;
    unsigned typ;
    
    Element( string adress, string nazwa, int nr_seryjny, unsigned typ )
        : adres( adress )
        , nazwa( nazwa )
        , nr_seryjny( nr_seryjny )
        , typ( typ )
    {
        trim_left_if( adres, is_any_of( "." ) ); // (2)
        trim_left_if( nazwa, is_any_of( "." ) );
    }
    
    virtual ostream & drukuj( int( * filtr )( const Element & ) = NULL, unsigned glebokosc = 0, ostream & os = cout, bool nazwa_i_adres = true, unsigned dlugosc_nazwy = 30 ) {
        if( filtr == NULL ) { //	(3)
            string tmp( glebokosc, '\t' );
            os << tmp;
            if( nazwa_i_adres )
                 os << setw( dlugosc_nazwy ) << left << nazwa << '\t' << adres << '\n';
            else
                 os << adres << '\n';
            
        }
        else if( filtr( * this ) ) {
            string tmp( glebokosc, '\t' );
            os << tmp;
            if( nazwa_i_adres )
                 os << setw( dlugosc_nazwy ) << left << nazwa << '\t' << adres << '\n';
            else
                 os << adres << '\n';
            
        }
        return os;
    }
    
    virtual unsigned usunZawierajaceWNazwie( string nazwa ) {
        return 0;
    }
    
    virtual unsigned przeliczElementy() {
        return 1;
    }
    
    virtual list < tuple < string, string, string > > plikiZawierajaceWTresci( string tresc ) = 0; // (4)
    
    virtual unsigned long long rozmiar( int( * filtr )( const Element & ) = NULL ) = 0;
    
    virtual unsigned zmienNazwyZawierajace( string szukany, string docelowy = "", int( * filtr )( const Element & ) = NULL ) {
        return 0;
    }
    
    virtual long unsigned drzewoKatalogowDoPliku( ostream & strumien, int( * filtr )( const Element & ) = NULL, string odstep = "\n", bool chce_nazwe_adres = true ) = 0;
};

inline bool operator <( const Element & l, const Element & r ) {
    return l.nazwa < r.nazwa;
}

struct Plik
    : public Element
{
    Plik( string adres, string nazwa, int nr_seryjny, unsigned typ )
        : Element( adres, nazwa, nr_seryjny, typ )
    { }
    
    virtual unsigned usunZawierajaceWNazwie( string fragment_nazwy ) { // (5)
        if( fragment_nazwy.empty() )
             cout << "Nie podano nazwy, usunal bys wszystko!" << endl;
        else if( nazwa.find( fragment_nazwy ) != string::npos ) {
            trim_left_if( adres, is_any_of( "/" ) );
            return( !remove( adres.c_str() ) );
        }
        return 0;
    }
    
    virtual list < tuple < string, string, string > > plikiZawierajaceWTresci( string tresc ) { // (6)
        list < tuple < string, string, string > > out;
        if( typ == DT_REG ) {
            string tmp;
            trim_left_if( adres, is_any_of( "/" ) );
            
            ifstream plik( adres.c_str() );
            
            if( plik.bad() ) {
                throw string( "Plik nie istnieje lub nie masz do niego praw!" );
            }
            while( !plik.eof() ) {
                getline( plik, tmp );
                if( tmp.find( tresc ) != string::npos ) { // (7)
                    out.push_back( make_tuple( nazwa, adres, tmp ) );
                    break;
                }
            }
        }
        return out;
    }
    
    virtual unsigned long long rozmiar( int( * filtr )( const Element & ) = NULL ) { // (8)
        unsigned long long roz = nazwa.size();
        if( typ == DT_REG ) {
            if( filtr == NULL ) {
                ifstream p( adres.c_str() );
                if( p.bad() )
                     cout << "!!! Nie mozna otworzyc pliku\n";
                else
                     roz +=( p.seekg( 0, ios::end ).tellg() );
                
            }
            else if( filtr( * this ) ) {
                ifstream p( adres.c_str() );
                if( p.bad() )
                     cout << "!!! Nie mozna otworzyc pliku\n";
                else
                     roz +=( p.seekg( 0, ios::end ).tellg() );
                
            }
        }
        return roz;
    }
    
    virtual unsigned zmienNazwyZawierajace( string szukany, string docelowy = "", int( * filtr )( const Element & ) = NULL ) { // (9)
        if( szukany.empty() )
             cout << "Nie podano nazwy, wyczyscil bys wszystkie nazwy!" << endl;
        else if( nazwa.find( szukany ) != string::npos ) {
            if( filtr == NULL ) {
                trim_left_if( adres, is_any_of( "/" ) );
                string obecny_adres = adres;
                replace_first( nazwa, szukany, docelowy );
                replace_first( adres, szukany, docelowy );
                return !rename( obecny_adres.c_str(), adres.c_str() );
            }
            else if( filtr( * this ) ) {
                trim_left_if( adres, is_any_of( "/" ) );
                string obecny_adres = adres;
                replace_first( adres, szukany, docelowy );
                return !rename( obecny_adres.c_str(), adres.c_str() );
            }
        }
        return 0;
    }
    
    virtual long unsigned drzewoKatalogowDoPliku( ostream & strumien, int( * filtr )( const Element & ) = NULL, string odstep = "\n", bool chce_nazwe_adres = true ) {
        if( typ == DT_REG ) {
            if(( filtr == NULL ) ? true
                : filtr( * this ) )
            { // (10)
                trim_left_if( adres, is_any_of( "/" ) );
                ifstream plik( adres.c_str() );
                if( plik.bad() )
                     cout << "!!! Nie mozna otworzyc pliku\n";
                else {
                    string tmp;
                    if( chce_nazwe_adres )
                         strumien << '\t' << nazwa << '\t' << adres << ":\n";
                    
                    while( !plik.eof() ) {
                        getline( plik, tmp );
                        strumien << tmp << '\n';
                    }
                    strumien << odstep;
                    return 1;
                }
            }
        }
        return 0;
    }
    
};

struct Katalog
    : public Element
{
    ptr_set < Element > elementy;
    DIR * sciezka;
    
    Katalog( string adres, string nazwa = "", int nr_seryjny = 0, unsigned typ = DT_DIR )
        : Element( adres, nazwa, nr_seryjny, typ )
    {
        sciezka = NULL;
        reorganizujSciezke( adres );
    }
    
    virtual list < tuple < string, string, string > > plikiZawierajaceWTresci( string tresc ) {
        list < tuple < string, string, string > > out, tmp;
        string nazwy, adresy, linijki;
        
        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it ) {
            tmp = it->plikiZawierajaceWTresci( tresc );
            out.insert( out.end(), tmp.begin(), tmp.end() ); // (11)
        }
        return out;
    }
    
    static void wyswietlTuplePlikow( list < tuple < string, string, string > > pliki, ostream & os = cout, string szukana = "" ) { // (12)
        unsigned long licznik = 0;
        os << "W sumie znaleziono " << pliki.size() << " plikow zawierajacych szukany tekst " << szukana << '\n';
        for( list < tuple < string, string, string > >::iterator it = pliki.begin(); it != pliki.end(); ++it ) {
            cout << '\n' << ++licznik << "\tPLIK: '" << it->get < 0 >() << "' LEZACY POD ADRESEM: '" << it->get < 1 >() << "' MIESCI FRAZE W LINIJCE:\n";
            cout << it->get < 2 >() << '\n';
        }
    }
    
    void reorganizujSciezke( string & adres ) {
        struct dirent * plik;
        
        string tmp_adres = adres;
        elementy.clear();
        
        if( tmp_adres.empty() )
             tmp_adres = ".";
        
        trim_left_if( tmp_adres, is_any_of( "/" ) ); // (13)
        
        if( sciezka != NULL )
             closedir( sciezka );
        
        if(( sciezka = opendir( tmp_adres.c_str() ) ) == NULL )
             pokazErrno();
        else {
            while( plik = readdir( sciezka ) ) {
                string adres_obecnego_pliku =( tmp_adres + "/" + plik->d_name );
                if( !strcmp( plik->d_name, "." ) ) {
                }
                else if( !strcmp( plik->d_name, ".." ) ) {
                }
                else if( jestKatalogiek( plik ) )
                     elementy.insert( new Katalog( adres_obecnego_pliku, plik->d_name, plik->d_ino, plik->d_type ) );
                else
                     elementy.insert( new Plik( adres_obecnego_pliku, plik->d_name, plik->d_ino, plik->d_type ) );
                
            }
        }
        closedir( sciezka ); // (14)
        sciezka = NULL;
    }
    
    virtual unsigned przeliczElementy() {
        unsigned suma = 0;
        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
             suma += it->przeliczElementy();
        
        return suma;
    }
    
    virtual unsigned usunZawierajaceWNazwie( string nazwa ) { // (15)
        unsigned licznik = 0;
        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
             licznik += it->usunZawierajaceWNazwie( nazwa );
        
        if( licznik )
             reorganizujSciezke( adres );
        
        return licznik;
    }
    
    virtual ostream & drukuj( int( * filtr )( const Element & ) = NULL, unsigned glebokosc = 0, ostream & os = cout, bool nazwa_i_adres = true, unsigned dlugosc_nazwy = 30 ) {
        string tmp( glebokosc, '\t' ); // (16)
        os << tmp;
        if( nazwa_i_adres )
             os << setw( dlugosc_nazwy ) << nazwa << '\t' << adres << '\n';
        else
             os << adres << '\n';
        
        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
             it->drukuj( filtr, glebokosc + 1, os, nazwa_i_adres, dlugosc_nazwy );
        
        return os;
    }
    
    static bool jestKatalogiek( dirent * plik ) { // (17)
        return( plik->d_type ) == DT_DIR; // || (plik->d_type)==DT_LNK;
    }
    
    virtual unsigned long long rozmiar( int( * filtr )( const Element & ) = NULL ) {
        unsigned long long roz = nazwa.size();
        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
             roz += it->rozmiar( filtr );
        
        return roz;
    }
    
    virtual unsigned zmienNazwyZawierajace( string szukany, string docelowy = "", int( * filtr )( const Element & ) = NULL ) {
        unsigned zmienione = 0;
        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
             zmienione += it->zmienNazwyZawierajace( szukany, docelowy, filtr );
        
        return zmienione;
    }
    
    virtual long unsigned drzewoKatalogowDoPliku( ostream & strumien, int( * filtr )( const Element & ) = NULL, string odstep = "\n", bool chce_nazwe_adres = true ) {
        unsigned ilosc_plikow = 0;
        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
             ilosc_plikow += it->drzewoKatalogowDoPliku( strumien, filtr, odstep, chce_nazwe_adres );
        
        return ilosc_plikow;
    }
};

#endif