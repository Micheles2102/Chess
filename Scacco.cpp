//premetto che questo codice è stato creato in giorni diversi quindi potrebbero esserci dei problemi legati alla logica
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<string>
#define N 8
using namespace std;

class TimerScacco {
    private:
         int timer;
         bool scacco;
     bool scaccomatto;
         bool finepartita;
        bool fine;
    public:
        TimerScacco(int orario, bool scaccos,bool scaccomattos):timer(orario),scacco(scaccos),scaccomatto(scaccomattos){}
    
    bool getScaccoMatto(bool scaccomatto){
        this->scaccomatto=scaccomatto;
        cout<<"Scacco Matto la partita finisce qui"<<endl;
        this->timer=0;
        return this->finepartita=true;
    }
    int ScalaTempo(){
        return --timer;     
    }
    int getTimer(){
        return timer;
    }
};

class Tabella {
    protected:
        TimerScacco **wheels;
        int value;
        int **tabella;
        bool **controllo;
        bool values;
        bool errore;
    public:
        Tabella(){
            this->value=0;
            this->wheels = new TimerScacco*[value+1];  
            this->errore=false;
            this->value=0;
            tabella=new int*[N];
            for(int i=0;i<N;i++){
                tabella[i]=new int[N];
                for(int j=0;j<N;j++){
                    tabella[i][j]=++value;          //potere creare la tabella come un bool
                }
            }
            this->values=false;
            controllo=new bool*[N];
            for(int i=0;i<N;i++){
                    controllo[i]=new bool[N];
                for(int j=0;j<N;j++){
                    controllo[i][j]=value;          //potere creare la tabella come un bool
                }
            }
        }
        bool getValues(int i,int j){
            if(controllo[i][j]) {         //vero =occupato false=libero
            return controllo[i][j];}
            cout<<"Errore"<<endl;
            return errore=1;
        }
        bool setValues(int i,int j,bool values){
            if(controllo[i][j])
            return controllo[i][j]=values;
        }
        int getValore(int i,int j){
            if(tabella[i][j]){
            return tabella[i][j];}
            cout<<"Errore"<<endl;
            return errore=1;
        }
        int setPezzo(int i,int j){
            if(tabella[i][j])
            return tabella[i][j];
        }
        int muoviPezzoPedone(int i,int j){
            if(setPezzo(i,j))
            return setPezzo(i,j);       //per il Pedone
        }

        /* int**clear(){
            if(wheels[0]->getScaccoMatto()){
                for(int i=0;i<N;i++){
                    for(int j=0;J<N;j++){

                    }
                }
            }
        } */
       
};


class Pezzi:public Tabella{
    private:
    string nome;
    int mosse;
    public:
    Pezzi(string nome,int mosse){             //mosse massime 5
        this->nome=nome;
        this->mosse=mosse;
    }       
    virtual int setMosse()=0;  
    virtual bool Mangiato()=0; 
    virtual int GetPosizione()=0;     
    virtual bool spostamento()=0;  
};
class Pedone:public Pezzi{
    protected:
    string nome;
    int mosse;
    int spostamento1;
    int spostamento2;
    int posizione1;
    int posizione2;
    bool mangiato;
    bool scacco;
    public:

    Pedone(string nome,int mosse,int posizione1,int posizione2):Pezzi("Pedone",1){  //superfluo?
        scacco=true;
        this->posizione1=posizione1;
        this->posizione2=posizione2;  
        this->mangiato=false;
        this->spostamento1=1;
        this->spostamento2=1;
        this->nome=nome;
        this->mosse=mosse;
        Tabella::setPezzo(posizione1,posizione2);
        Tabella::setValues(posizione1,posizione2,true);
    }
    
    bool spostamento(){
        int x;
        if(mosse!=0){
            cout<<"Inserisci dove vuoi andare; 1 nord,2 sud,3 ovest,4 est<<endl"<<endl;//1 scendi,2 sali,3sinistra,4 destra per array
            cin>>x;
            if(!cin.fail()){
                if(x>=1 && x<=4){
                    if(x==1){
                        if(Tabella::getValues(spostamento1+1,spostamento2)){}
                        else
                            {spostamento1++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1-1,spostamento2,false);mosse--;}      //verificare se è libero(fatto con metodo setValues)
                    }
                    if(x==2){
                        if(Tabella::getValues(spostamento1-1,spostamento2)){}
                        else
                            {spostamento1--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1+1,spostamento2,false);mosse--;}
                    }   
                    if(x==3){
                        if(Tabella::getValues(spostamento1,spostamento2-1)){}
                        else
                            {spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2+1,false);mosse--;}
                    }  
                    if(x==4){
                        if(Tabella::getValues(spostamento1,spostamento2+1)){}
                        else
                            {spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2+1,false);mosse--;}
                    }  
                    setMosse();
                    return 0;
                }
                else{
                    cout<<"Errore,valore inserito non valido"<<endl;
                    return EXIT_FAILURE;
                }
            }
            else{
                cerr << "Errore, il valore inserito e diverso da quelli richiesti";
                return EXIT_FAILURE;
            }
        }
    }
    int setMosse(){
        return this->mosse=1;           //da richiamare
    }
    bool Mangiato(){
        return mangiato=true;
    }
    int GetPosizione(){
        return Tabella::getValore(spostamento1,spostamento2);
    }
    bool Scacco(){
        return scacco;
    }

};
class Cavallo:public Pezzi{
    protected:
    string nome;
    int mosse;
    int spostamento1;
    int spostamento2;
    int posizione1;
    int posizione2;
    bool mangiato;
    bool scacco;
    public:
    Cavallo(string nome,int mosse,int posizione1,int posizione2,int spostamento2):Pezzi("Cavallo",3){
        scacco=true;
        this->posizione1=posizione1;
        this->posizione2=posizione2;  
        this->mangiato=false;   
        this->spostamento1=0;                   //il cavallo incurante se ci sono altri pezzi a meno che l'ultima casella che occuipa non è già occupata da un altra figura quindi controllare l'ultima casella;
        this->spostamento2=spostamento2;
        this->nome=nome;
        this->mosse=mosse;
        Tabella::setPezzo(posizione1,posizione2);
        Tabella::setValues(posizione1,posizione2,true);
    }
    bool spostamento(){
        int x;
        if(mosse!=0){
            cout<<"Inserisci dove vuoi andare; 1 nord,2 sud,3 ovest,4 est"<<endl;//1 scendi,2 sali,3sinistra,4 destra per array
            cin>>x;
            if(!cin.fail()){
                if(x>=1 && x<=4){
                    if(x==1){
                       cout<<"Decidere se spostare a sinistra(1) o destra(2) il cavallo"<<endl;
                       int t;
                       cin>>t;
                       if(t==1){
                            if(Tabella::getValues(spostamento1+2,spostamento2-1)){}
                            else{
                                this->spostamento1+=2;this->spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1-2,spostamento2+1,false);mosse=0;
                            }
                        }
                        if(t==2){
                            if(Tabella::getValues(spostamento1+2,spostamento2+1)){}
                            else{
                                this->spostamento1+=2;this->spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1-2,spostamento2-1,false);mosse=0;
                            }
                        }
                    }
                    if(x==2){
                        cout<<"Decidere se spostare a sinistra(1) o destra(2) il cavallo"<<endl;
                       int t;
                       cin>>t;
                       if(t==1){
                            if(Tabella::getValues(spostamento1-2,spostamento2-1)){}
                            else{
                                this->spostamento1-=2;this->spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1+2,spostamento2+1,false);mosse=0;
                            }
                       }
                       if(t==2){
                            if(Tabella::getValues(spostamento1-2,spostamento2+1)){}
                            else{
                                this->spostamento1-=2;this->spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1+2,spostamento2-1,false);mosse=0;
                            }
                       }
                        
                    }   
                    if(x==3){
                         cout<<"Decidere se spostare a sinistra(1) o destra(2) il cavallo"<<endl;
                       int t;
                       cin>>t;
                       if(t==1){
                         if(Tabella::getValues(spostamento1+1,spostamento2-2)){}//
                            else{
                                this->spostamento1++;this->spostamento2-=2;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2+=2,false);mosse=0;
                            }
                        }
                        if(t==2){
                            if(Tabella::getValues(spostamento1--,spostamento2+2)){}//
                            else{
                                this->spostamento1--;this->spostamento2+=2;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2-=2,false);mosse=0;
                            }
                        }
                    }  
                    if(x==4){
                       cout<<"Decidere se spostare a sinistra(1) o destra(2) il cavallo"<<endl;
                       int t;
                       cin>>t;
                       if(t==1){
                         if(Tabella::getValues(spostamento1--,spostamento2+2)){}//
                            else{
                                this->spostamento1--;this->spostamento2+=2;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2-=2,false);mosse=0;
                            }
                        }
                        if(t==2){
                            if(Tabella::getValues(spostamento1++,spostamento2+2)){}//
                            else{
                                this->spostamento1++;this->spostamento2-=2;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2+=2,false);mosse=0;
                            }
                        }
                    } 
                    setMosse(); 
                    return 0;
                }
                else{
                    cout<<"Errore,valore inserito non valido"<<endl;
                    return EXIT_FAILURE;
                }
            }
            else{
                cerr << "Errore, il valore inserito e diverso da quelli richiesti";
                return EXIT_FAILURE;
            }
        }
    }
    int setMosse(){
        return this->mosse=3;           //da richiamare
    }
    bool Mangiato(){
        return mangiato=true;
    }
    int GetPosizione(){
        return Tabella::getValore(spostamento1,spostamento2);
    }
    bool Scacco(){
        return scacco;
    }
};
class Torre:public Pezzi{
    protected:
    string nome;
    int mosse;
    int spostamento1;
    int spostamento2;
    int posizione1;
    int posizione2;
    bool mangiato;
    bool scacco;
    public:
    Torre(string nome,int mosse,int posizione1,int posizione2,int spostamento2):Pezzi("Torre",3){
        scacco=true;
        this->posizione1=posizione1;
        this->posizione2=posizione2;  
        this->mangiato=false;   
        this->spostamento1=0;                  //la torrre la prende in culo non si può spostare se davanti a lei ci sono altri pezzi quindi in base a quanto si sposta c'è bisogno di fare vari controlli
        this->spostamento2=spostamento2;
        this->nome=nome;
        this->mosse=mosse;
        Tabella::setPezzo(posizione1,posizione2);
        Tabella::setValues(posizione1,posizione2,true);
    }
    bool spostamento(){
        int x;
        int contatore;
        if(mosse!=0){
            cout<<"Inserisci dove vuoi andare; 1 nord,2 sud,3 ovest,4 est"<<endl;//1 scendi,2 sali,3sinistra,4 destra per array
            cin>>x;
            if(!cin.fail()){
                cout<<"Inserisci di quante posizioni vuoi mouovere la tua torre"<<endl;
                cin>>contatore;
                if(!cin.fail()){ 
                    if(x>=1 && x<=4){
                        switch(x){
                            case 1:
                            for(int i=0;i<contatore;i++){
                                if(Tabella::getValues(spostamento1++,spostamento2)){}
                                else
                                {spostamento1++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2,false);mosse--;}
                            }
                            case 2:
                                if(Tabella::getValues(spostamento1--,spostamento2)){}
                                else
                                {spostamento1--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2,false);mosse--;}
                              
                            case 3:
                                if(Tabella::getValues(spostamento1,spostamento2--)){}
                                else
                                {spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2++,false);mosse--;}
                            case 4:
                                if(Tabella::getValues(spostamento1,spostamento2++)){}
                                else
                                {spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2++,false);mosse--;}
                        }
                        setMosse(); 
                        return 0;

                    }
                }
                else{
                    cerr << "Errore, il valore inserito e diverso da quelli richiesti";
                    return EXIT_FAILURE;
                }
            }
            else{
                cout<<"Errore,valore inserito non valido"<<endl;
                return EXIT_FAILURE;
            }
        }
    }
    int setMosse(){
        return this->mosse=7;           //da richiamare
    }
    bool Mangiato(){
        return mangiato=true;
    }
    int GetPosizione(){
        return Tabella::getValore(spostamento1,spostamento2);
    }
    bool Scacco(){
        return scacco;
    }
};
class Alfiere:public Pezzi{
    protected:
    string nome;
    int mosse;
    int spostamento1;
    int spostamento2;
    int posizione1;
    int posizione2;
    bool mangiato;
    bool scacco;
    public:
    Alfiere(string nome,int mosse,int posizione1,int posizione2,int spostamento2):Pezzi("Alfiere",3){
        scacco=true;
        this->posizione1=posizione1;
        this->posizione2=posizione2;  
        this->mangiato=false;   
        this->spostamento1=0;                  //la torrre la prende in culo non si può spostare se davanti a lei ci sono altri pezzi quindi in base a quanto si sposta c'è bisogno di fare vari controlli
        this->spostamento2=spostamento2;
        this->nome=nome;
        this->mosse=mosse;
        Tabella::setPezzo(posizione1,posizione2);
        Tabella::setValues(posizione1,posizione2,true);
    }

    bool spostamento(){
        int x;
        int contatore;
        if(mosse!=0){
            cout<<"Inserisci dove vuoi andare; 1 destro alto,2 sinistra alto,3 destra basso,4 sinistra basso"<<endl;//1 scendi,2 sali,3sinistra,4 destra per array
            cin>>x;
            if(!cin.fail()){
                cout<<"Inserisci di quante posizioni vuoi mouovere il tuo Alfiere"<<endl;
                cin>>contatore;
                if(!cin.fail()){ 
                    if(x>=1 && x<=4){
                        switch(x){
                            case 1:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1++,spostamento2++)){}
                                    else
                                    {spostamento1++;spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2--,false);mosse--;}
                                }
                            case 2:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1++,spostamento2--)){}
                                    else
                                    {spostamento1++;spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2++,false);mosse--;}
                                }
                            case 3:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1--,spostamento2++)){}
                                    else
                                    {spostamento1--;spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2--,false);mosse--;}
                                }
                            case 4:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1--,spostamento2--)){}
                                    else
                                    {spostamento1--;spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2++,false);mosse--;}
                                }
                        }
                        setMosse(); 
                        return 0;
                    }
                }
                else{
                    cerr << "Errore, il valore inserito e diverso da quelli richiesti";
                    return EXIT_FAILURE;
                }
            }
            else{
                cout<<"Errore,valore inserito non valido"<<endl;
                return EXIT_FAILURE;
            }
            
        }
    }

    int setMosse(){
        return this->mosse=7;           //da richiamare
    }
    bool Mangiato(){
        return mangiato=true;
    }
    int GetPosizione(){
        return Tabella::getValore(spostamento1,spostamento2);
    }
    bool Scacco(){
        return scacco;
    }
};
class Regina:public Pezzi{
    protected:
    string nome;
    int mosse;
    int spostamento1;
    int spostamento2;
    int posizione1;
    int posizione2;
    bool mangiato;
    bool scacco;
    public:
    Regina(string nome,int mosse,int posizione1,int posizione2,int spostamento2):Pezzi("Regina",3){
        scacco=true;
        this->posizione1=posizione1;
        this->posizione2=posizione2;  
        this->mangiato=false;   
        this->spostamento1=0;                  //la torrre la prende in culo non si può spostare se davanti a lei ci sono altri pezzi quindi in base a quanto si sposta c'è bisogno di fare vari controlli
        this->spostamento2=spostamento2;
        this->nome=nome;
        this->mosse=mosse;
        Tabella::setPezzo(posizione1,posizione2);
        Tabella::setValues(posizione1,posizione2,true);
    }
    bool spostamento(){
        int x;
        int contatore;
        if(mosse!=0){
            cout<<"Inserisci dove vuoi andare; 1 nord,2 sud,3 ovest,4 est,5 destro alto,6 sinistra alto,7 destra basso,8 sinistra basso"<<endl;//1 scendi,2 sali,3sinistra,4 destra per array
            cin>>x;
            if(!cin.fail()){
                cout<<"Inserisci di quante posizioni vuoi mouovere la tua torre"<<endl;
                cin>>contatore;
                if(!cin.fail()){ 
                    if(x>=1 && x<=4){
                        switch(x){
                            case 1:
                            for(int i=0;i<contatore;i++){
                                if(Tabella::getValues(spostamento1++,spostamento2)){}
                                else
                                {spostamento1++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2,false);mosse--;}
                            }
                            case 2:
                                if(Tabella::getValues(spostamento1--,spostamento2)){}
                                else
                                {spostamento1--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2,false);mosse--;}
                              
                            case 3:
                                if(Tabella::getValues(spostamento1,spostamento2--)){}
                                else
                                {spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2++,false);mosse--;}
                            case 4:
                                if(Tabella::getValues(spostamento1,spostamento2++)){}
                                else
                                {spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2++,false);mosse--;}
                            case 5:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1++,spostamento2++)){}
                                    else
                                    {spostamento1++;spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2--,false);mosse--;}
                                }
                            case 6:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1++,spostamento2--)){}
                                    else
                                    {spostamento1++;spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2++,false);mosse--;}
                                }
                            case 7:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1--,spostamento2++)){}
                                    else
                                    {spostamento1--;spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2--,false);mosse--;}
                                }
                            case 8:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1--,spostamento2--)){}
                                    else
                                    {spostamento1--;spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2++,false);mosse--;}
                                }
                        }
                        setMosse(); 
                        return 0;

                    }
                }
                else{
                    cerr << "Errore, il valore inserito e diverso da quelli richiesti";
                    return EXIT_FAILURE;
                }
            }
            else{
                cout<<"Errore,valore inserito non valido"<<endl;
                return EXIT_FAILURE;
            }
        }
    
    }

    int setMosse(){
        return this->mosse=7;           //da richiamare
    }
    bool Mangiato(){
        return mangiato=true;
    }
    int GetPosizione(){
        return Tabella::getValore(spostamento1,spostamento2);
    }
    bool Scacco(){
        return scacco;
    }
};

class Re:public Pezzi{
    protected:
    string nome;
    int mosse;
    int spostamento1;
    int spostamento2;
    int posizione1;
    int posizione2;
    bool mangiato;
    bool scacco1;
    bool nonsimuove;
    bool scaccomatto;
    public:

    Re(string nome,int mosse,int posizione1,int posizione2):Pezzi("Re",1){  //superfluo?
        nonsimuove=false;
        this->posizione1=posizione1;
        this->posizione2=posizione2;  
        this->mangiato=false;
        this->spostamento1=1;
        this->spostamento2=1;
        this->nome=nome;
        this->mosse=mosse;
        Tabella::setPezzo(posizione1,posizione2);
        Tabella::setValues(posizione1,posizione2,true);
    }
    
    bool spostamento(){
        int x;
        int contatore;
        if(mosse!=0){
            cout<<"Inserisci dove vuoi andare; 1 nord,2 sud,3 ovest,4 est,5 destro alto,6 sinistra alto,7 destra basso,8 sinistra basso"<<endl;//1 scendi,2 sali,3sinistra,4 destra per array
            cin>>x;
            if(!cin.fail()){          
                    if(x>=1 && x<=4){
                        switch(x){
                            case 1:
                            for(int i=0;i<contatore;i++){
                                if(Tabella::getValues(spostamento1++,spostamento2)){nonsimuove=true;}
                                else
                                {spostamento1++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2,false);mosse--;}
                            }
                            case 2:
                                if(Tabella::getValues(spostamento1--,spostamento2)){nonsimuove=true;}
                                else
                                {spostamento1--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2,false);mosse--;}
                              
                            case 3:
                                if(Tabella::getValues(spostamento1,spostamento2--)){nonsimuove=true;}
                                else
                                {spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2++,false);mosse--;}
                            case 4:
                                if(Tabella::getValues(spostamento1,spostamento2++)){nonsimuove=true;}
                                else
                                {spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1,spostamento2++,false);mosse--;}
                            case 5:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1++,spostamento2++)){nonsimuove=true;}
                                    else
                                    {spostamento1++;spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2--,false);mosse--;}
                                }
                            case 6:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1++,spostamento2--)){nonsimuove=true;}
                                    else
                                    {spostamento1++;spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1--,spostamento2++,false);mosse--;}
                                }
                            case 7:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1--,spostamento2++)){nonsimuove=true;}
                                    else
                                    {spostamento1--;spostamento2++;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2--,false);mosse--;}
                                }
                            case 8:
                                for(int i=0;i<contatore;i++){
                                    if(Tabella::getValues(spostamento1--,spostamento2--)){nonsimuove=true;}
                                    else
                                    {spostamento1--;spostamento2--;Tabella::muoviPezzoPedone(spostamento1,spostamento2);Tabella::setValues(spostamento1,spostamento2,true);Tabella::setValues(spostamento1++,spostamento2++,false);mosse--;}
                                }
                        }
                        setMosse(); 
                        return 0;

                    }
            }
            else{
                cout<<"Errore,valore inserito non valido"<<endl;
                return EXIT_FAILURE;
            }
        }
    
    }
    bool getNonsimuove(){
        return nonsimuove;
    }
    int setMosse(){
        return this->mosse=1;           //da richiamare
    }
    bool setMangiato(){
        mangiato==true;
        return mangiato;
    }

    bool Mangiato(){
        if(mangiato==0){
            return true;
        }
        else{
            mangiato=true;
            wheels[0]->getScaccoMatto(true);
        }
    }
    int GetPosizione(){
        return Tabella::getValore(spostamento1,spostamento2);
    }
    void setScacco(){
        scacco1=true;
    }
    bool getScacco(){
        return scacco1=true;
    }
    bool getScaccoMatto(){
        return scaccomatto=true;
    }
};

int main(){
    Pedone*vec[N];Cavallo*vev[2];Torre*veb[2];TimerScacco*ves[0];Alfiere*ven[2];Regina*vem[1];Re*vel[1];           //ogni mossa = ScalaTempo
    ves[0]=new TimerScacco(60,false,false);
    int contatoredefinitivo=10;
    int count1=1;
    int count2=1;
    for(int i=0;i<N;i++){
        vec[i]=new Pedone("Pedone",1,count1,count2);//if(vec[t]->mangiato()){delete vec[t]}
        count2++;
    }
    int count3=0;
    int count4=1;
    int spostamento=1;
    for(int i=0;i<2;i++){
        vev[i]=new Cavallo("Cavallo",3,count3,count4,spostamento);
        spostamento=3;
        count4=6;
    }
    int count5=0;
    int count6=0;
    int spostamento2=0;
    for(int i=0;i<2;i++){
        veb[i]=new Torre("Torre",8,count5,count6,spostamento2);      //gli devo fare scegliere di quanto si deve spostare
        spostamento2=4;
        count6=7;
    }
    int count7=0;
    int count8=2;
    int spostamento3=2;
    for(int i=0;i<2;i++){
        ven[i]=new Alfiere("Alfiere",3,count7,count8,spostamento3);
        spostamento3=5;
        count8=5;
    }
    int count9=0;
    int count10=4;
    int spostamento4=4;
    vem[0]=new Regina("Regina",8,count9,count10,spostamento4);
    int count11=0;
    int count12=4;
    vel[0]=new Re("Re",1,count11,count12);
    TimerScacco*vek[0];
    vek[0]=new TimerScacco(10,false,false);
    do{
        int tiposcelto;
       
        
        cout<<"Quale Pezzo vuoi spostare:"<<endl;cout<<"1)Pedone\n2)Cavallo\n3)Torre\n4)Afliere\n5)Regine\n6)Re"<<endl;
        cin>>tiposcelto;
        if(cin.fail()){
            switch(tiposcelto){
                case 1:
                cout<<"Quale Pezzo Dei Pedoni Vuoi Spostare?"<<endl;            //si considera come la prima riga è da 5 
                    int pezzoscelto0;
                    cin>>pezzoscelto0;
                    vec[pezzoscelto0]->spostamento();
                    vec[pezzoscelto0]->setMosse();
                    if(vec[pezzoscelto0]->Mangiato()==true){
                        vec[pezzoscelto0]=nullptr;
                    };
                    if(vec[pezzoscelto0]->GetPosizione()==vel[0]->GetPosizione()){
                        vel[0]->setScacco();
                        vel[0]->getScacco();
                    }
                    vek[0]->ScalaTempo();
                case 2:
                cout<<"Quale Pezzo Dei Cavalli Vuoi Spostare?(si consideri quello a sinistra come 1 quello a destra come 2"<<endl;
                    int pezzoscelto1;
                    cin>>pezzoscelto1;
                    vev[pezzoscelto1]->spostamento();                        
                    vev[pezzoscelto1]->setMosse();
                    if(vev[pezzoscelto1]->Mangiato()==true){
                        vev[pezzoscelto1]=nullptr;
                    };
                    if(vev[pezzoscelto1]->GetPosizione()==vel[0]->GetPosizione()){
                        vel[0]->setScacco();
                        vel[0]->getScacco();
                    }
                    vek[0]->ScalaTempo();
                case 3:
                cout<<"Quale Pezzo Dei Torre Vuoi Spostare?(si consideri quello a sinistra come 1 quello a destra come 2"<<endl;
                    int pezzoscelto2;
                    cin>>pezzoscelto2;
                    veb[pezzoscelto2]->spostamento();                        
                    veb[pezzoscelto2]->setMosse();
                    if(veb[pezzoscelto2]->Mangiato()==true){
                        veb[pezzoscelto2]=nullptr;
                    };
                    if(veb[pezzoscelto2]->GetPosizione()==vel[0]->GetPosizione()){
                        vel[0]->setScacco();
                        vel[0]->getScacco();
                    }
                    vek[0]->ScalaTempo();
                case 4:
                cout<<"Quale Pezzo Dei Alfiere Vuoi Spostare?(si consideri quello a sinistra come 1 quello a destra come 2"<<endl;
                    int pezzoscelto3;
                    cin>>pezzoscelto3;
                    ven[pezzoscelto3]->spostamento();                        
                    ven[pezzoscelto3]->setMosse();
                    if(ven[pezzoscelto3]->Mangiato()==true){
                        ven[pezzoscelto3]=nullptr;
                    };
                    if(ven[pezzoscelto3]->GetPosizione()==vel[0]->GetPosizione()){
                        vel[0]->setScacco();
                        vel[0]->getScacco();
                    }
                    vek[0]->ScalaTempo();
                case 5:
                    vem[0]->spostamento();
                    vem[0]->setMosse();
                    if(vem[0]->Mangiato()==true){
                            vec[0]=nullptr;
                    };
                    if(vem[0]->GetPosizione()==vel[0]->GetPosizione()){
                        vel[0]->setScacco();
                        vel[0]->getScacco();
                    }
                    vek[0]->ScalaTempo();
                case 6:
                if(vel[0]->getScacco()){
                    if(vel[0]->getNonsimuove()){
                        vek[0]->getScaccoMatto(vel[0]->getScaccoMatto());
                    }
                }
                vel[0]->spostamento();
                vel[0]->setMosse();
                if(vel[0]->Mangiato()==true){
                        vel[0]=nullptr;
                    };
                vek[0]->ScalaTempo();
            }
        }
        if(vek[0]->getTimer()==0){
            cout<<"il tempo a disposizione è finito la partita è finita in un pareggio";
        }
         if(vel[0]->getScacco()){
            cout<<"dio"<<endl;
            cout<<"Scacco"<<endl; 
            tiposcelto=6;
        }
    }
    while(vel[0]);
    return 0;
}

