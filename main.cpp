#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#define DIM 3   ///definisco il numero di utenti

using namespace std;


 int dim=DIM;

///struct
struct sito{
    int id;                          ///identificatore utente
    string password;                   ///password utente
    string cognome;                    ///cognome
    string nome;                      ///nome
}utente[DIM];

void inserimento()
{
    ofstream file("MioFile.dat",ios::out|ios::binary);
    if(!file)
        cout<<"errore apertura file ";
    else
    {

        for(int i=0;i<dim;i++)
        {
            ///carico la struct
            cout<<"Inserimento dell'utente n."<<(i+1)<<endl;
            utente[i].id=(i+1);     ///id utente
            ///inserisco password
            do
            {
              cout<<"Password: ";
              fflush(stdin);
              getline(cin,utente[i].password);
            }
            while(utente[i].password.length()>20);   ///con la condizione di max 20 caratteri

            cout<<endl;
            ///inserisco cognome
            do
            {
            cout<<"Cognome:";
            fflush(stdin);
            getline(cin,utente[i].cognome);
            } while(utente[i].cognome.length()>30);   ///con la condizione di max 30 caratteri

            cout<<endl;
            ///inserisco nome
            do
            {
            cout<<"Nome contatto:";
            fflush(stdin);
            getline(cin,utente[i].nome);
            }while(utente[i].nome.length()>20);   ///con la condizione di max 20 caratteri

            cout<<endl;
            ///carico la struct sul file tramite il metodo write
            file.write((char *)&utente[i],sizeof(utente[i]));
        }
file.close();

    }
}

void stampa()
{

     ifstream file("MioFile.dat",ios::in|ios::binary);
    if(!file)
        cout<<"errore apertura file ";
    else
    {
        for(int i=0;i<dim;i++)
        ///attraverso il metodo read carico il file sulla struct
            file.read((char *)&utente[i],sizeof(utente[i]));
            cout<<"ELENCO UTENTI:"<<endl;
       for(int c=0; c<dim; c++)
          {
             cout<<"utente "<<utente[c].id<<"  "<<utente[c].cognome<<" "<<utente[c].nome<<" con password: "<<utente[c].password<<endl;

          }
    }
    file.close();

}

void eliminazione()
{

    fstream file("MioFile.dat",ios::in|ios::out|ios::binary);
    if(!file)
        cout<<"errore apertura file "<<endl;
    else
    {

     sito temp;
     long codic,c=0;     ///codice-->ID dell'utente da eliminare      c-->contatore
     string str;
     while(file.read((char *)&temp,sizeof(temp)))
            c++;

     cout<<"Inserire id dell'utente da eliminare: "<<endl;
     stampa();
     cin>>codic;

     file.clear();       ///cancello
     codic--;           ///decremento codic perchè la struct parte da 0
     file.seekg(codic*sizeof(temp),ios::beg);       ///ios::beg-->lo fa partire dalla prima posizione sizeof(temp)-->lunghezza  codic-->codice da ricercare per eliminarlo
     file.read((char*)&temp,sizeof(temp));          ///attraverso il metodo read carico il file sulla struct
     cout<<"L'utente da eliminare e': ";           ///stampo record dell'utente da eliminare
     cout<<temp.id<<": "<<temp.cognome<<"\t"<<temp.nome<<" con password"<<temp.password<<endl;

     file.seekg(0); ///metto il puntatore all'inizio del file
     for(int i=0;i<(dim-1);i++)
     {
         file.read((char*)&temp,sizeof(temp));
         if(codic!=temp.id)
         {
             file.read((char*)&temp,sizeof(temp));
         }
         utente[i]=temp;
         cout<<utente[i].id<<": "<<utente[i].cognome<<"\t"<<utente[i].nome<<" con password "<<utente[i].password<<endl;

     }
    dim--;

    }

   file.seekp(0);
    for(int c=0;c<dim;c++)
        {
            file.write((char*)&utente[c],sizeof(utente[c]));
        }

    file.close();
}

void modifica()
{
    fstream file("MioFile.dat",ios::in|ios::app|ios::binary);
    if(!file)
        cout<<"errore apertura file "<<endl;
    else
    {
        sito temp;
        long codic,c=0,campo=0;     //!codice-->ID da modificare     c-->contatore      campo-->campo da modificare
        while(file.read((char *)&temp,sizeof(temp)))
            c++;

        cout<<"Inserire codice del campo che si vuole modificare: "<<endl;
        stampa();
        cin>>codic;
        if(codic<=c)
        {
            codic--;        ///decremento codic perchè la struct parte da 0
            file.clear();       ///cancello
            file.seekg(codic*sizeof(temp),ios::beg);    ///ios::beg-->lo fa partire dalla prima posizione   sizeof(temp)-->lunghezza   codic-->codice da ricercare per la modifica
            file.read((char*)&temp,sizeof(temp));       ///attraverso il metodo read carico il file sulla struct
            cout<<"Che campo del record vuoi modificare?"<<endl;
            cout<<"1)password"<<endl;
            cout<<"2)cognome"<<endl;
            cout<<"3)nome"<<endl;
            cin>>campo;
            utente[codic]=temp;
            switch(campo)
        {
            case 1:
                   cout<<"modifica numero di telefono"<<endl;
                   utente[codic].password="        ";
                   fflush(stdin);
                   getline(cin,utente[codic].password);
                   break;
            case 2:
                   cout<<"modifica cognome"<<endl;
                  utente[codic].cognome="        ";
                   fflush(stdin);
                   getline(cin,utente[codic].cognome);
                   break;
            case 3:
                   cout<<"modifica nome"<<endl;
                   utente[codic].nome="        ";
                   fflush(stdin);
                   getline(cin,utente[codic].nome);
                   break;
        }


            file.write((char *)&utente[codic],sizeof utente[codic]);    ///carico la struct sul file tramite il metodo write
            cout<<"Record modificato"<<endl;
            cout<<utente[codic].id<<": "<<utente[codic].cognome<<"\t"<<utente[codic].nome<<" con password "<<utente[codic].password<<endl; //!vado a leggere il file.
            cout<<"stampa modifica"<<endl;
             for(int i=0;i<dim;i++)
                {
                     cout<<utente[i].id<<": "<<utente[i].cognome<<"\t"<<utente[i].nome<<" con password "<<utente[i].password<<endl;
                }
        }
        else
            cout<<"ID non presente nel file.";
    }

     file.close();
}

int main()
{
    int scelta;
    do
    {
        do
        {   cout<<"GESTIONE FILE DI RECORD"<<endl;
            cout<<"MENU' PRINCIPALE"<<endl;
            cout<<"Quale operazione vuoi eseguire?"<<endl;
            cout<<"1)Inserimento utente"<<endl;
            cout<<"2)Modifica utente"<<endl;
            cout<<"3)Elimina utente"<<endl;
            cout<<"4)Visualizza elenco utenti"<<endl;
            cout<<"5)Exit"<<endl;
            cin>>scelta;
        }
        while(scelta<1||scelta>5);
         system("cls");
        switch(scelta)
        {
            case 1:
                   inserimento();
                   break;
            case 2:
                   modifica();
                   break;
            case 3:
                   eliminazione();
                   break;
            case 4:
                   stampa();
                   break;
            case 5:
                   cout<<"Fine programma XD";
                   break;
        }
    }
    while(scelta!=5);
    return 0;
}

