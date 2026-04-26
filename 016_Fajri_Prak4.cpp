#include <iostream>
#include <fstream>
#include <stdio.h>
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

void displayQueue()
{
    Service *serv = headServ;
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
                 << "Urgensi: " << serv -> urgensi << endl;
        serv = serv -> next;
        }
    }
    cout << "-----------------------" << endl;
}

void urgencySort()
{
    Service *serv = headServ;
    if(serv == NULL || serv -> next == NULL)
    {
        return;
    }

    while(serv != NULL)
    {
        Service *keep = serv;
        Service *pointer = serv -> next;
        while(pointer != NULL)
        {
            if (stoi(pointer -> urgensi) > stoi(keep -> urgensi))
            {
                keep = pointer;
            }
            pointer = pointer -> next;
        }
        if(keep != serv)
        {
            Service *keepNext = keep -> next;
            Service *keepPrev = keep -> prev;
            Service *servNext = serv -> next;
            Service *servPrev = serv -> prev;

            Service temp = *serv;
            *serv = *keep;
            *keep = temp;

            serv -> next = servNext;
            serv -> prev = servPrev;
            keep -> next = keepNext;
            keep -> prev = keepPrev;
        }
        serv = serv -> next;
    }
}

void queueSort()
{
    Service *serv = headServ;
    if(serv == NULL || serv -> next == NULL)
    {
        return;
    }

    while(serv != NULL)
    {
        Service *keep = serv;
        Service *pointer = serv -> next;
        while(pointer != NULL)
        {
            if (stoi(pointer -> antri) < stoi(keep -> antri))
            {
                keep = pointer;
            }
            pointer = pointer -> next;
        }
        if(keep != serv)
        {
            Service *keepNext = keep -> next;
            Service *keepPrev = keep -> prev;
            Service *servNext = serv -> next;
            Service *servPrev = serv -> prev;

            Service temp = *serv;
            *serv = *keep;
            *keep = temp;

            serv -> next = servNext;
            serv -> prev = servPrev;
            keep -> next = keepNext;
            keep -> prev = keepPrev;
        }
        serv = serv -> next;
    }
}

void dateSort()
{
    Service *serv = headServ;
    int hari, bulan, tahun;
    sscanf(serv->tanggal.c_str(), "%d-%d-%d", &hari, &bulan, &tahun);
    if(serv == NULL || serv -> next == NULL)
    {
        return;
    }

    while(serv != NULL)
    {
        sscanf(cur->tanggal.c_str(), "%d-%d-%d", &hari, &bulan, &tahun);

    }
}

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
        servBaru -> namaCust = namaCustInsert;
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

    cout << "====== All Services ======" << endl;
    displayQueue();

    string pilChar;
    while(pilChar != "X")
    {
        cout << "[U] Urgency [D] Date [Q] Queue [X] Exit" << endl << "Pilihan: ";
        cin >> pilChar;

        if(pilChar == "U")
        {
            system("cls");
            cout << "====== Sort by Urgency ======" << endl;
            urgencySort();
            displayQueue();
        }
        else if(pilChar == "D")
        {
            system("cls");
            cout << "====== Sort by Date ======" << endl;
            dateSort();
            displayQueue();
        }
        else if(pilChar == "Q")
        {
            system("cls");
            cout << "====== Sort by Queue ======" << endl;
            queueSort();
            displayQueue();
        }
    }
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