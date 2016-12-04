#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

class Slowa{
protected:
    string obiekt,wyraz,ntf="aaaaaaa",polskieZnakiMale,polskieZnakiDuze;
    int dlugosc,lPoziomow=2;
    string losuj(int i){
        fstream plik("bazawyrazow.txt");
        int licznik=1;
        string wyraz;
        while(getline(plik,wyraz)){
            if(licznik==i){
                return wyraz;
            }
            licznik++;
        }
        return wyraz;
    }

    void ukryj(){
        wyraz="";
        for(int i=0;i<dlugosc;i++)
            wyraz.append("*");
    }

    void start(string co){
        if(co=="losuj"){
            int i=(rand()%80)+3;
            obiekt=losuj(i);
        } else if(co=="kampania"){
            obiekt=poziom();
        }
        dlugosc=obiekt.length();
        ukryj();
    }

    string naDuza(string & wyraz){
        transform(wyraz.begin(),wyraz.end(),wyraz.begin(),::toupper);
        for(int i=0;i<9;i++){
            if(polskieZnakiMale[i]==wyraz[0])
                wyraz[0]=polskieZnakiDuze[i];
        }
        return wyraz;
    }

    string poziom(){
        fstream plik("bazawyrazow.txt");
        int licznik=1;
        string wyraz;
        while(getline(plik,wyraz)){
            if(licznik==lPoziomow){
                return wyraz;
            }
            licznik++;
        }
        return wyraz;
    }

    void polskieZnaki(){
    string wyraz;
    int licznik=1;
    fstream plik("bazawyrazow.txt");
    while(getline(plik,wyraz) && licznik<3){
        if(licznik==1)
            polskieZnakiMale=wyraz;
        if(licznik==2)
            polskieZnakiDuze=wyraz;
        licznik++;
    }
    }

};

class Wisielec :protected Slowa{
protected:
    bool sprawdz(string litera){
        for(int i=0;i<dlugosc;i++){
            if(litera[0]==obiekt[i])
                return true;
        }
        return false;
    }

    void odkryj(string litera){
        for(int i=0;i<dlugosc;i++){
            if(litera[0]==obiekt[i])
                wyraz[i]=litera[0];
        }
    }

    void pudla(int szanse){
        int ile=7-szanse;
        cout<<"Pudˆa: ";
        for(int i=0;i<ile;i++)
            if(ile==i+1)
                cout<<ntf[i]<<endl;
            else
                cout<<ntf[i]<<", ";
    }

    bool czyBylaTrafiona(string litera){
        for(int i=0;i<dlugosc;i++){
            if(litera[0]==wyraz[i]){
                cout<<"Ta litera ju¾ raz wyst¥piˆa!"<<endl<<"Podaj inna:"<<endl;
                return true;
            }
        }
        return false;
    }

    bool czyByla(string litera){
        for(int i=0;i<dlugosc;i++){
            if(ntf[i]==litera[0]){
                cout<<"Ta litera ju¾ raz wyst¥piˆa!"<<endl<<"Podaj inna:"<<endl;
                return true;
            }
        }
        return false;
    }

};

class Gra :public Wisielec{
    int szanse=7;
    string litera;
public:
    Gra(string mode){
        polskieZnaki();
        if(mode=="single"){
            start("losuj");
            graj();
            system("pause");
        } else if(mode=="kampania"){
            kampania();
        }
        system("cls");
    }

    bool graj(){
        do{
        system("cls");
        if(lPoziomow>2)
            cout<<"Obecny poziom: "<<lPoziomow-2<<endl;
        cout<<"Wyraz do odgadni©cia: "<<wyraz<<endl<<"Pozostaˆo Ci: "<<szanse<<" pr¢b"<<endl;
        if(szanse<7 && ntf!="aaaaaaa")
            pudla(szanse);
        cout<<"Podaj liter© albo szukany wyraz: "<<endl;
        wprowadz();
        if(litera==obiekt){
            wyraz=litera;
        }else if(sprawdz(litera)){
            odkryj(litera);
            cout<<"trafiˆe˜!"<<endl;
            system("pause");
        }else{
            cout<<"ups...pudˆo."<<endl;
            if(szanse!=1)
                cout<<"spr¢buj jeszcze raz"<<endl;
            szanse--;
            ntf[6-szanse]=litera[0];
            if(szanse!=0)
            system("pause");
        }
        cin.clear();
        cin.sync();
        }while(wyraz!=obiekt && szanse!=0);
        if(lPoziomow==2 || wyraz==obiekt)
            cout<<"Wyraz to: "<<obiekt<<endl;
        if(szanse!=0){
            cout<<"Gratulacje!"<<endl<<endl;
            return true;
        }
        else{
            cout<<"Game Over!"<<endl<<endl;
            return false;
        }
    }

    void wprowadz(){
        string temp;
        do{
            cin>>litera;
            temp=litera;
            if(naDuza(temp)==obiekt){
                naDuza(litera);
                return;
            }
            while(litera.length()!=1){
                cout<<"Zˆy znak!"<<endl;
                cin.clear();
                cin.sync();
                cin>>litera;
                temp=litera;
                    if(naDuza(temp)==obiekt){
                    naDuza(litera);
                    return;
                }
            }
            litera=naDuza(litera);
        }while(czyBylaTrafiona(litera) || czyByla(litera));
    }

    void kampania(){
        bool gra;
        lPoziomow++;
        do{
            start("kampania");
            gra=graj();
            if(gra){
                system("pause");
                if(szanse<6)
                    szanse+=2;
                else
                    szanse=7;
            }
            lPoziomow++;
            ntf="aaaaaaa";
        }while(lPoziomow!=83 && gra);
        system("pause");
    }

};

int main(){
    srand(time(NULL));
    string co;
    do{
        system("cls");
        cout<<"Wpisz \"kampania\" aby zagra† w trybie kampanii, lub wpisz \"single\" aby rozegrac pojedyäcz¥ gr©."<<endl;
        cin>>co;
        Gra *game=new Gra(co);
        delete game;
        cout<<"Je˜li chcesz spr¢bowa† jeszcze raz wpisz \"y\""<<endl;
        cin>>co;
    }while(co=="y");
}
