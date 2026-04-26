#include <iostream>
#include <fstream>
using namespace std;

struct Service;
int tutup = 0;

struct Service
{
    string tipeMobil, merekMobil, namaCust, kendala, namaMontir, tanggal, kosong, urgensi, doneServ, antri;
    Service *next = NULL;
    Service *prev = NULL;
};

Service *headServ = NULL;
Service *tailServ = NULL;

void readServ()
{
    ifstream fileServ("Service3.txt");
    string namaCustInsert;
    while (getline(fileServ, namaCustInsert)) 
    {
        if (namaCustInsert == "") continue;
        Service *servBaru = new Service();
        getline(fileServ, servBaru -> tipeMobil);
        getline(fileServ, servBaru -> merekMobil);
        getline(fileServ, servBaru -> kendala);
        getline(fileServ, servBaru -> namaMontir);
        getline(fileServ, servBaru -> urgensi);
        getline(fileServ, servBaru -> antri);
        getline(fileServ, servBaru -> doneServ);
        getline(fileServ, servBaru -> kosong);        
        servBaru -> next = NULL;
        servBaru -> prev = NULL;
        Service* serv = headServ;
        if (headServ == NULL)
        {
            headServ = servBaru;
            tailServ = servBaru; 
        }
        else
        {
            tailServ -> next = servBaru;
            servBaru -> prev = tailServ;
            tailServ = servBaru;
        }
    }
    fileServ.close();
}

void updateServ()
{
    ofstream fileServ("Service3.txt", ios::trunc);
    Service* serv = headServ;
    while(serv != NULL)
    {
        {
            fileServ << serv -> namaCust << endl
                     << serv -> tipeMobil << endl
                     << serv -> merekMobil << endl
                     << serv -> kendala << endl
                     << serv -> namaMontir << endl
                     << serv -> urgensi << endl
                     << serv -> antri << endl
                     << serv -> doneServ << endl
                     << serv -> kosong << endl;
        }
        serv = serv -> next;
    }
    fileServ.close();
}

void newServ()
{
    system("cls");
    Service *servBaru = new Service();
    cout << "====== New Service ======" << endl;
    cout << "Tipe Mobil: ";
    getline(cin, servBaru -> tipeMobil);
    cout << "Merk Mobil: ";
    getline(cin, servBaru -> merekMobil);
    cout << "Kendala: ";
    getline(cin, servBaru -> kendala);
    cout << "Montir: ";
    getline(cin, servBaru -> namaMontir);
    cout << "Nama Pelanggan: ";
    getline(cin, servBaru -> namaCust);
    cout << "Urgensi: ";
    getline(cin, servBaru -> urgensi);

    int antri = 1;
    Service *countAntri = headServ;
    while (countAntri != NULL)
    {
        if (countAntri -> doneServ == "0")
        {
            antri++;
        }
        countAntri = countAntri -> next;
    }
    servBaru -> antri = to_string(antri);
    servBaru -> doneServ = "0";
    
    Service *serv = headServ;
    if (serv == NULL)
    {
        headServ = servBaru;
        tailServ = servBaru;
    }
    else
    {
        tailServ -> next = servBaru;
        servBaru -> prev = tailServ;
        tailServ = servBaru;
    }
    updateServ();
}

void queue()
{
    system("cls");
    Service *serv = headServ;

    cout << "====== All Services ======" << endl;
    
    while (serv != NULL)
    {
        if(serv -> doneServ == "0")
        {
            cout << "-----------------------" << endl
                 << "Model Mobil: " << serv -> tipeMobil << endl
                 << "Merek Mobil: " << serv -> merekMobil << endl
                 << "Kendala: " << serv -> kendala << endl
                 << "Montir: " << serv -> namaMontir << endl
                 << "Nama Pelanggan: " << serv -> namaCust << endl
                 << "Urgensi: " << serv -> urgensi << endl
                 << "-----------------------" << endl;
        serv = serv -> next;
        }
    }
    system("pause");
}

void finish()
{
}

void menu()
{
    string pil;
    system("cls");
    cout << "====== Welcome to Lognuts! ======" << endl
         << "Pilih Menu! " << endl << endl
         << "1. Service Baru" << endl
         << "2. Ganti Tanggal" << endl
         << "3. Antrean" << endl 
         << "4. Selesaikan Service" << endl
         << "5. Keluar" << endl << endl
         << "Pilihan: ";
    cin >> pil;
    cin.ignore();
    if (pil == "1")
    {
        newServ();
    }
    else if (pil == "2")
    {
        // Ganti Tanggal
    }
    else if (pil == "3")
    {
        queue();
    }
    else if (pil == "4")
    {
        // Selesaikan Service
    }
    else if (pil == "5")
    {
        cout << endl << "====== Thank you for using Lognuts! ======";
        tutup = 1;
    }
}

int main()
{
    readServ();
    while (tutup != 1)
    {
        menu();
    }
    return 0;
}