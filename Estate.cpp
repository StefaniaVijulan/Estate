#include <iostream>
#include <cstring>
#include <vector>
#include<iterator>
#include<set>
#include<utility>
#include <stdlib.h>
using namespace std;
///-----------------locuinta-------

class locuinta
{
protected:
    string nume_client;
    double suprafata_utila;
    double discount;
public:
    locuinta(string l_nume, double l_suprafata, double l_discount);
    locuinta(const locuinta& ob);
    virtual ~locuinta();

    virtual void citire(istream& in) = 0;
    virtual void afisare(ostream& out) = 0;

    locuinta& operator= (const locuinta& ob);

    friend istream& operator>>(istream&, locuinta&);
    friend ostream& operator<<(ostream&, locuinta&);

};
locuinta::locuinta(string l_nume = "", double l_suprafata = 0, double l_discount = 0)
{
    nume_client = l_nume;
    suprafata_utila = l_suprafata;
    try
    {
        if (l_discount < 0 || l_discount >10)
            throw 10;
    }
    catch (int x)
    {
        cout << "Discountul oferit nu se afla in intervalul disponibil";
    }
    discount = l_discount;
    /* cout<<"Constructor cu parametrii";
     cout<<endl;
     cout<<nume_client<<" "<<suprafata_utila<<" "<<discount<<endl;*/
}
locuinta::~locuinta()
{
    nume_client = "";
    suprafata_utila = 0;
    discount = 0;
    /*cout<<"Destructor"<<endl;
    cout<< nume_client<<" "<<suprafata_utila<<" "<<discount<<endl;*/
}
locuinta::locuinta(const locuinta& ob)
{
    nume_client = ob.nume_client;
    suprafata_utila = ob.suprafata_utila;
    discount = ob.discount;
    /* cout<<"Copy constructor"<<endl;
     cout<< nume_client<<" "<<suprafata_utila<<" "<<discount<<endl;*/
}
locuinta& locuinta::operator=(const locuinta& ob)
{
    if (this != &ob)
    {
        nume_client = ob.nume_client;
        suprafata_utila = ob.suprafata_utila;
        discount = ob.discount;
    }
    return *this;
}
istream& operator>>(istream& in, locuinta& f)
{
    f.citire(in);
    return in;
}
ostream& operator<<(ostream& out, locuinta& f)
{
    f.afisare(out);
    return out;
}


///-----------------clasa apartament--------


class apartament : public locuinta
{
private:

    double pret_chirie;
    int etajul_locuintei;
public:
    apartament();
    apartament(string l_nume, int l_suprafata, double l_discount, int l_etaj_loc, double l_pret);
    apartament(const apartament& ob);
    ~apartament();

    double chirie() const;
    void citire(istream& in);
    void afisare(ostream& out);

    apartament& operator= (const apartament& ob);

};
apartament& apartament::operator= (const apartament& ob)
{

    if (this != &ob)
    {
        locuinta::operator=(ob);
        pret_chirie = ob.pret_chirie;
        etajul_locuintei = ob.etajul_locuintei;
    }
    return *this;

}
apartament::apartament()
{

    ///cout<<"Constructor fara parametrii a clasei apartament";
    etajul_locuintei = 0;
    pret_chirie = 0;

}
apartament::apartament(string l_nume, int l_suprafata, double l_discount, int l_etaj_loc = 0, double l_pret = 0) :locuinta(l_nume, l_suprafata, l_discount)
{
    etajul_locuintei = l_etaj_loc;
    pret_chirie = l_pret;
    /*cout<<"Constructor cu parametrii a clasei apartament"<<endl;
    cout<<l_nume<<" "<<l_suprafata<<" "<<l_discount<<" "<<l_etaj_loc<<endl;*/
}
apartament::apartament(const apartament& ob) :locuinta(ob)
{
    etajul_locuintei = ob.etajul_locuintei;
    pret_chirie = ob.pret_chirie;
    ///cout<<"Constructor de copiere";
}
apartament::~apartament()
{
    //cout<<"Destructor al clasei apartament"<<endl;
    etajul_locuintei = 0;
    pret_chirie = 0;
    //cout<<etajul_locuintei<<endl;
}
double apartament::chirie() const
{
    double suma_chirie;
    if (discount == 0)
    {
        suma_chirie = pret_chirie * suprafata_utila;
    }
    else
    {
        suma_chirie = pret_chirie * suprafata_utila - (pret_chirie * suprafata_utila * discount) / 100;
    }
    return suma_chirie;
}
void apartament::citire(istream& in)
{
    cout<<"\tInformatii despre apartament!"<<endl<<endl;
    int a;
    double b;
    string n;
    cout << "     Citim numele clientului : ";
    in >> n;
    nume_client = n;
    cout << "     Citim suprafata utila: ";
    in >> b;
    suprafata_utila = b;
    cout << "     Citim valuarea discountului: ";
    in >> b;
    discount = b;
    try
    {
        if (discount < 0 || discount>10)
            throw 10;
    }
    catch (int i)
    {
        cout << "   Discountul nu se afla in intervalul posibil. Va rugam sa oferiti alt discount: ";
        in >> b;
        discount = b;

    }
    cout << "     Citim etajul la care se afla: ";
    in >> a;
    etajul_locuintei = a;
    cout << "     Da-ti pretul pe m^2 pentru apartament:";
    in >> b;
    pret_chirie = b;
    cout<<endl;

}
void apartament::afisare(ostream& out)
{
    cout << "     Numele clientului este:";
    out<< nume_client;
    cout << endl;
    cout << "     Suprafata utila este: ";
    out << suprafata_utila;
    cout << endl;
    cout << "     Se ofera un discount de :";
    out << discount << "%";
    cout << endl;
    cout << "     Etajul la care se afla apartamentul este: ";
    out << etajul_locuintei;
    cout << endl<<endl;
    cout<<"       Chiria este: ";
    cout<<chirie();
}

///-----------CASA--------

class casa :public locuinta
{
private:
    double pret_chirie;
    double suprafata_curte;
    int nr_etaje;
    vector<double> et;

public:
    casa();
    casa(string l_nume, int l_suprafata, double l_discount, vector<double> l_v, int l_nr, double l_pret, double l_curte);
    casa(const casa& ob);
    ~casa();

    double chirie()const ;

    void citire(istream& in);
    void afisare(ostream& out);

    casa& operator= (const casa& ob);

};
casa& casa::operator= (const casa& ob)
{

    if (this != &ob)
    {
        locuinta::operator=(ob);
        pret_chirie = ob.pret_chirie;
        suprafata_curte = ob.suprafata_curte;
        nr_etaje = ob.nr_etaje;
        et=ob.et;
    }
    return *this;

}
casa::casa()
{

    // cout<<"Constructor fara parametrii a clasei casa";
    suprafata_curte = 0;
    nr_etaje = 0;
    pret_chirie = 0;

}
casa::casa(string l_nume, int l_suprafata, double l_discount,vector<double> l_v= {}, int l_nr = 0, double l_pret = 0, double l_curte = 0) :locuinta(l_nume, l_suprafata, l_discount)
{
    nr_etaje = l_nr;
    pret_chirie = l_pret;
    suprafata_curte = l_curte;
    et= l_v;
    // cout<<"Constructor cu parametrii a clasei casa"<<endl;
    //  cout<<l_nume<<" "<<l_suprafata<<" "<<l_discount<<" "<<l_nr<<" "<<l_pret<<" "<<l_curte<<endl;
}
casa::casa(const casa& ob) :locuinta(ob)
{
    nr_etaje = ob.nr_etaje;
    pret_chirie = ob.pret_chirie;
    suprafata_curte = ob.suprafata_curte;
    et = ob.et;
    //  cout<<"Constructor de copiere casa";
}
casa::~casa()
{
    //   cout<<"Destructor al clasei apartament"<<endl;
    suprafata_curte = 0;
    nr_etaje = 0;
    pret_chirie = 0;
    et.clear();
    //  cout<<suprafata_curte<<" "<<nr_etaje<<" "<<pret_chirie<<endl;
}
double casa::chirie() const
{
    double suma_chirie;
    if (discount == 0)
    {
        suma_chirie = pret_chirie * suprafata_utila + pret_chirie * suprafata_curte;

    }
    else
    {
        suma_chirie = pret_chirie * suprafata_utila - (pret_chirie * suprafata_utila * discount) / 100 + pret_chirie * suprafata_curte;
    }
    return suma_chirie;
}
void casa::citire(istream& in)
{
    cout<<"\t Informatii despre casa"<<endl;
    cout<<endl;
    int a;
    double b;
    string n;

    cout << "     Citim numele clientului : ";
    in >> n;
    nume_client = n;
    cout << "     Citim suprafata utila: ";
    in >> b;
    suprafata_utila = b;
    cout << "     Citim valuarea discountului: ";
    in >> b;
    discount =b;
    try
    {
        if (discount < 0 || discount>10)
            throw 0;
    }
    catch (int i)
    {
        cout << "   Discountul nu se afla in intervalul posibil. Va rugam sa oferiti alt discount: ";
        in >> b;
        discount = b;

    }

    double e;
    cout << "     Citim numarul de etaje pe care le are casa: ";
    in >> a;
    nr_etaje =a;
    for(int i = 0; i < nr_etaje; i++)
    {
        cout<<"         Suprafata utila pe etajul" << i+1<<" este: ";
        in >> e;
        et.push_back(e);
    }

    cout << "     Suprafata curtii este : ";
    in >> b;
    suprafata_curte = b;


    cout << "     Da-ti pretul pe m^2 pentru casa: ";
    in >> b;
    pret_chirie = b;

    cout<<endl;

}
void casa::afisare(ostream& out)
{
    out << "     Numele clientului este:";
    out << nume_client;
    out << endl;
    out << "     Suprafata utila este: ";
    out << suprafata_utila;
    out << endl;
    out << "     Se ofera un discount de :";
    out << discount;
    out << "%";
    out << endl;
    out << "     Casa are un numar de ";
    out << nr_etaje <<" etaje."<< endl;
    for(int i = 0; i < nr_etaje; i++)
    {
        out<<"          Suprafata utila pe etajul" << i+1<<" este: ";
        out<<et[i];
        out<<endl;
    }

    out << "     Suprafara curtii este: ";
    out << suprafata_curte << endl<<endl;
    out << "     Chiria este:";
    out << chirie() << endl;
}


///------------clasa gestiune------------

template<typename t>
class Gestiune
{
    static t *v;
    static int indice;
public:
    Gestiune() {}
    Gestiune(const Gestiune<t> & ob ) {}
    ~Gestiune() {}
    Gestiune& operator =(const t &ob)
    {
        return *this;
    }
    static int get_indice()
    {
        return indice;
    }
    Gestiune& operator+=(const t &ob)
    {
        v[indice]=ob;
        indice++;
        return *this;
    }
    template <typename u>
    friend ostream &operator<<(ostream &os, const Gestiune<u> &ob) ;


};
template<typename t>
t* Gestiune<t>:: v=new t[1000];
template<typename t>
int Gestiune<t>:: indice=0;
template <typename u>
ostream &operator<<(ostream &out, const Gestiune<u> &ob)
{
    int i;
    out<<"------------Gestiune apartament ----------"<<endl;
    for(i=0; i<ob.indice; i++)
    {
        out<<"Este al "<< i+1<<" apartament. "<<endl;
        out<<ob.v[i]<<endl;
        out<<endl;
    }

    cout<<"In agentie se afla "<<ob.get_indice()<<" apartamente";
    return out;
}
///---------------specializare--------------------
template <>
class Gestiune<casa>
{
    static casa *v;
    static int indice;
    static double chirie_totala;
public:
    Gestiune() {}
    Gestiune(const Gestiune<casa> & ob ) {}
    ~Gestiune() {}
    Gestiune& operator =(const casa &ob)
    {
        return *this;
    }
    Gestiune<casa>& operator+=( casa & ob)
    {
        v[indice]=ob;
        indice++;
        chirie_totala+=ob.chirie();
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Gestiune<casa> &ob) ;

};
template<>
casa* Gestiune<casa>:: v=new casa[1000];
template<>
int Gestiune<casa>:: indice=0;
template<>
double Gestiune<casa>:: chirie_totala=0;

ostream &operator<<(ostream &out, const Gestiune<casa> &ob)
{
    int i;
    out<<"------------ Gestiune pentru case ---------"<<endl;
    for(i=0; i<ob.indice; i++)
    {
        out<<"Este a "<< i+1<<"casa. "<<endl;
        out<<ob.v[i]<<endl<<endl;
    }
    out<<"Afisare chirie totala: "<<ob.chirie_totala<<endl;
    return out;
}

void meniu_out()
{
    cout << "\t Agentie imobiliara";
    cout << endl << endl << endl;
    cout << "\t Meniu";
    cout << endl;
    cout << "0. Iesire";
    cout << endl;
    cout << "1. Ambele timpuri de locuinte + numar locuinte";
    cout <<endl;
    cout << "2. Doar apartamente";
    cout << endl;
    cout << "3. Doar case";
    cout << endl;


}
string tip(locuinta *&loc, int& i)
{
    string a;
    cout << endl;
    cout << " Introduceti tipul locuintei dorite ";
    cin >> a;
    try
    {
        if (a == "apartament")
        {
            loc= new apartament;
            cin>>*loc;
            i++;
            return "apartament";

        }
        else if (a == "casa")
        {
            loc= new casa;
            cin>>*loc;
            i++;
            return "casa";
        }
        else
            throw 0;
    }
    catch (int j)
    {
        cout << "Ne pare rau, insa avem locuinte de tip casa sau apartament. ";
    }
}
void meniu()
{
    int optiune_meniu = 0;
    int n = 0;
    set<pair<locuinta*, string> > s;
    pair< locuinta *, string> l;
    locuinta * t;

    Gestiune<apartament> apart;
    Gestiune<casa>cas;
    string nume;

    do
    {
        meniu_out();
        cout << "Introduceti optiunea din meniu pe care o doresti: ";
        cin >> optiune_meniu;

        if (optiune_meniu == 1)
        {
            cout << "Introduceti numarul de imobiliare dorite: ";
            cin >> n;
            //  t= new locuinta *[n];
            if (n > 0)
            {
                for (int i = 0; i < n;)

                {
                    nume=tip(t, i);

                    l.first=t;
                    l.second=nume;
                    s.insert(l);
                }
                cout << endl;
                cout << "\tAfisam ceea ce am citit mai sus"<<endl;;
                cout<<"----------------------------------------------------------";
                cout << endl;
                set<pair<locuinta*, string> >::iterator i;
                for (i = s.begin(); i != s.end(); ++i)
                {
                    cout<<"Locuinta este de tip:"<< i->second<<endl;
                    cout << *i->first;
                    cout<<endl;
                }
                int nr_apartamente=0, nr_case=0;
                for (i = s.begin(); i != s.end(); ++i)
                {
                    ///dynamic_Cast pentru apartament
                    apartament *ap=dynamic_cast<apartament *>(i->first);
                    ///dynamic_cast pentru casa
                    casa *ca=dynamic_cast<casa *>(i->first);
                    if(ap)
                        nr_apartamente++;
                    if(ca)
                        nr_case++;
                }
                cout<<"Numarul de apartamente: "<<nr_apartamente;
                cout<<endl;
                cout<<"Numarul de case: "<<nr_case;
            }
            else
                cout << "Puteti cauta minim o locuinta.";

        }
        if (optiune_meniu == 2)
        {
            cout<<"Introduceti numarul de apartamente: ";
            cin>>n;
            if(n>0)
            {
                Gestiune<apartament> x;
                for(int i=0; i<n; i++)
                {
                    cout<<"Citim apartamentul "<<i+1<<endl;
                    apartament a;
                    cin>>a;
                    x+=a;
                }
                cout<<x;
            }
            else
                cout << "Puteti cauta minim o locuinta.";
        }
        if (optiune_meniu == 3)
        {
            cout<<"Introduceti numarul de case dorite: ";
            cin>>n;
            if(n>0)
            {
                Gestiune<casa> x;
                for(int i=0; i<n; i++)
                {
                    cout<<"Citim casa "<<i+1<<endl;
                    casa a;
                    cin>>a;
                    x+=a;
                }
                cout<<x;

            }
            else
                cout << "Puteti cauta minim o locuinta.";
        }
        if (optiune_meniu == 0)
        {
            cout << endl;
            cout << "EXIT";
            cout << endl;

        }
        cout << endl;

    }
    while (optiune_meniu != 0);
}
int main()
{
    /* Gestiune<apartament>a;
     apartament b, c;
     cin>>b;
     cin>>c;
     a+=b;
     a+=c;
     cout<<a;*/
    /*Gestiune <casa> d;
    casa e;
    casa f;
    cin>>e;
    cin>>f;
    d+=e;
    d+=f;
    cout<<d;*/
    meniu();

}
