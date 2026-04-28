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
                 << "Antrian: " << serv -> antri << endl
                 << "Model Mobil: " << serv -> tipeMobil << endl
                 << "Merek Mobil: " << serv -> merekMobil << endl
                 << "Kendala: " << serv -> kendala << endl
                 << "Montir: " << serv -> namaMontir << endl
                 << "Nama Pelanggan: " << serv -> namaCust << endl
                 << "Urgensi: " << serv -> urgensi << endl
                 << "Tanggal Ambil: " << serv -> tanggal << endl;
        }
        serv = serv -> next;
    }
    cout << "-----------------------" << endl;
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
            if(stoi(pointer -> antri) < stoi(keep -> antri))
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
    if(serv == NULL || serv -> next == NULL)
    {
        return;
    }

    while(serv != NULL)
    {
        Service *keep = serv;
        int keepHari, keepBulan, keepTahun;
        sscanf(keep -> tanggal.c_str(), "%d-%d-%d", &keepHari, &keepBulan, &keepTahun);
        Service *pointer = serv -> next;
        int thisHari, thisBulan, thisTahun;

        while(pointer != NULL)
        {
            sscanf(pointer -> tanggal.c_str(), "%d-%d-%d", &thisHari, &thisBulan, &thisTahun);
            if(thisTahun < keepTahun)
            {
                keep = pointer;
            }
            else if(thisTahun == keepTahun)
            {
                if(thisBulan < keepBulan)
                {
                    keep = pointer;
                }
                else if (thisBulan == keepBulan)
                {
                    if (thisHari < keepHari)
                    {
                        keep = pointer;
                    }
                }
            }

            if(keep == pointer)
            {
                keepHari = thisHari;
                keepBulan = thisBulan;
                keepTahun = thisTahun;
            }
            pointer = pointer -> next;
        }
        if (keep != serv)
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
            if(stoi(pointer -> urgensi) > stoi(keep -> urgensi))
            {
                keep = pointer;
            }
            else if(stoi(pointer -> urgensi) == stoi(keep -> urgensi))
            {
                int keepHari, keepBulan, keepTahun, thisHari, thisBulan, thisTahun;
                sscanf(keep -> tanggal.c_str(), "%d-%d-%d", &keepHari, &keepBulan, &keepTahun);
                sscanf(pointer -> tanggal.c_str(), "%d-%d-%d", &thisHari, &thisBulan, &thisTahun);
                if(thisTahun < keepTahun)
                {
                    keep = pointer;
                }
                else if(thisTahun == keepTahun)
                {
                    if(thisBulan < keepBulan)
                    {
                        keep = pointer;
                    }
                    else if (thisBulan == keepBulan)
                    {
                        if (thisHari < keepHari)
                        {
                            keep = pointer;
                        }
                    }
                }
                if(keep == pointer)
                {
                    keepHari = thisHari;
                    keepBulan = thisBulan;
                    keepTahun = thisTahun;
                }
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
        getline(fileServ, servBaru -> tanggal);
        getline(fileServ, servBaru -> antri);
        getline(fileServ, servBaru -> doneServ);
        getline(fileServ, servBaru -> kosong);        
        servBaru -> next = NULL;
        servBaru -> prev = NULL;
        
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
        fileServ << serv -> namaCust << endl
                 << serv -> tipeMobil << endl
                 << serv -> merekMobil << endl
                 << serv -> kendala << endl
                 << serv -> namaMontir << endl
                 << serv -> urgensi << endl
                 << serv -> tanggal << endl
                 << serv -> antri << endl
                 << serv -> doneServ << endl
                 << serv -> kosong << endl;
        serv = serv -> next;
    }
    fileServ.close();
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
    queueSort();
    updateServ();
}

string dateMover(string tanggalStr) 
{
    int hari, bulan, tahun;
    sscanf(tanggalStr.c_str(), "%d-%d-%d", &hari, &bulan, &tahun);
    int hariTotal[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (tahun % 4 == 0) 
    {
        hariTotal[2] = 29;
    }
    hari++;
    if (hari > hariTotal[bulan]) 
    {
        hari = 1;
        bulan++;
        if (bulan > 12) 
        {
            bulan = 1;
            tahun++;
        }
    }
    char buffer[20];
    sprintf(buffer, "%02d-%02d-%02d", hari, bulan, tahun);
    return string(buffer);
}

string freeLooker(string targetMontir, string checkDate, int count, Service* ignoreServ) 
{
    int h = 0, b = 0, t = 0;
    sscanf(checkDate.c_str(), "%d-%d-%d", &h, &b, &t);
    char cBuf[20];
    sprintf(cBuf, "%02d-%02d-%02d", h, b, t);
    checkDate = string(cBuf);

    Service *serv = headServ;
    bool crash = false;

    while (serv != NULL) 
    {
        if (serv != ignoreServ && serv -> doneServ == "0") 
        {
            sscanf(serv->tanggal.c_str(), "%d-%d-%d", &h, &b, &t);
            char sBuf[20];
            sprintf(sBuf, "%02d-%02d-%02d", h, b, t);
            string sTanggal = string(sBuf);

            if (sTanggal == checkDate)
            {
                crash = true;
                break;
            }
        }
        serv = serv -> next;
    }
    if (crash) 
    {
        if (count < 5) 
        {
            cout << "Tanggal sudah dijadwalkan oleh servis lain" << endl;
            cout << "Tanggal diundur " << count + 1 << " hari setelah tanggal baru!!." << endl;
            
            string tanggalBesok = dateMover(checkDate);
            return freeLooker(targetMontir, tanggalBesok, count + 1, ignoreServ);
        } 
        else 
        {
            string inputBaru;
            cout << "Tanggal sudah diundur sebanyak 5 kali, masukkan tanggal baru: ";
            getline(cin, inputBaru);
            return freeLooker(targetMontir, inputBaru, 0, ignoreServ);
        }
    }
    return checkDate;
}

void reschedule()
{
    system("cls");
    dateSort();
    string montirAktif[20]; 
    int jumlahMontir = 0;
    Service *serv = headServ;

    while(serv != NULL)
    {
        if (serv -> doneServ == "0")
        {
            bool ada = false;
            for (int i = 0; i < jumlahMontir; i++)
            {
                if (montirAktif[i] == serv -> namaMontir)
                {
                    ada = true;
                    break;
                }
            }
            if(!ada)
            {
                montirAktif[jumlahMontir] = serv -> namaMontir;
                jumlahMontir++;
            }
        }
        serv = serv -> next;
    }
    
    if(jumlahMontir == 0)
    {
        cout << "====== Reschedule ======" << endl
             << "Tidak ada antrian servis yang pending saat ini." << endl;
        system("pause");
        return;
    }

    cout << "====== Reschedule ======" << endl
         << "Pilih Montir: " << endl;
    for (int i = 0; i < jumlahMontir; i++)
    {
        cout << i + 1 << ". " << montirAktif[i] << endl;
    }
    cout << "Pilihan: ";
    int pil;
    cin >> pil;
    cin.ignore();

    if (pil < 1 || pil > jumlahMontir) 
    {
        cout << "Pilihan tidak valid!" << endl;
        system("pause");
        return;
    }
    
    string targetMontir = montirAktif[pil - 1];
    Service *servN = headServ;
    bool adaIn = false;
    system("cls");
    
    cout << endl << "====== Reschedule ======" << endl;
    int nomor = 1;
    while (servN != NULL)
    {
        if (servN -> namaMontir == targetMontir && servN -> doneServ == "0")
        {
            adaIn = true;
            cout << nomor << ". Servis:" << endl
                 << "Tipe Mobil: " << servN -> tipeMobil << endl
                 << "Merek Mobil: " << servN -> merekMobil << endl
                 << "Kendala: " << servN -> kendala << endl
                 << "Nama Montir: " << servN -> namaMontir << endl
                 << "Tanggal Ambil: " << servN -> tanggal << endl
                 << "-----------------------------" << endl;
            nomor++;
        }
        servN = servN -> next;
    }
    
    if (!adaIn) 
    {
        cout << endl << "Tidak ada antrian pekerjaan untuk montir " << targetMontir << "." << endl;
        system("pause");
        return;
    }
    cout << "Pilih nomor servis yang mau di-reschedule: ";
    int pilihanServis;
    cin >> pilihanServis;
    cin.ignore();

    Service *targetServ = headServ;
    int hitung = 1;
    bool ketemu = false;
    
    while (targetServ != NULL) 
    {
        if (targetServ -> namaMontir == targetMontir && targetServ -> doneServ == "0") 
        {
            if (hitung == pilihanServis) 
            {
                ketemu = true;
                break;
            }
            hitung++;
        }
        targetServ = targetServ -> next;
    }

    if (!ketemu) 
    {
        cout << "Nomor servis tidak valid!" << endl;
        system("pause");
        return;
    }

    cout << "Masukkan tanggal baru: ";
    string tanggalBaru;
    getline(cin, tanggalBaru);

    string tanggalFix = freeLooker(targetMontir, tanggalBaru, 0, targetServ);

    targetServ -> tanggal = tanggalFix;
    cout << "Tanggal ambil yang baru adalah " << tanggalFix << endl;
    cout << "Servis " << targetServ -> tipeMobil << " berhasil di undur!!" << endl;

    queueSort();
    updateServ();
    system("pause");
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
    cout << "Tanggal Ambil: ";
    getline(cin, servBaru -> tanggal);
    
    servBaru -> tanggal = freeLooker(servBaru->namaMontir, servBaru->tanggal, 0, servBaru);

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
    queueSort();
    updateServ();
}

void finish()
{
    system("cls");
    urgencySort();
    string montirAktif[20]; 
    int jumlahMontir = 0;
    Service *serv = headServ;
    while(serv != NULL)
    {
        if (serv -> doneServ == "0")
        {
            bool ada = false;
            for (int i = 0; i < jumlahMontir; i++)
            {
                if (montirAktif[i] == serv -> namaMontir)
                {
                    ada = true;
                    break;
                }
            }
            if(!ada)
            {
                montirAktif[jumlahMontir] = serv -> namaMontir;
                jumlahMontir++;
            }
        }
        serv = serv -> next;
    }
    if(jumlahMontir == 0)
    {
        cout << "====== Finish Job ======" << endl
             << "Tidak ada antrian servis yang pending saat ini." << endl;
        system("pause");
        return;
    }
    cout << "====== Finish Job ======" << endl
         << "Pilih Montir: " << endl;

    for (int i = 0; i < jumlahMontir; i++)
    {
        cout << i + 1 << ". " << montirAktif[i] << endl;
    }
    cout << "Pilihan: ";
    int pil;
    cin >> pil;
    if (pil < 1 || pil > jumlahMontir) 
    {
        cout << "Pilihan tidak valid!" << endl;
        system("pause");
        return;
    }
    string targetMontir = montirAktif[pil - 1];
    Service *servN = headServ;
    bool adaIn = false;
    while (servN != NULL)
    {
        if (servN -> namaMontir == targetMontir && servN -> doneServ == "0")
        {
            adaIn = true;
            cout << endl << "====== Service ======" << endl
                 << "Tipe Mobil: " << servN -> tipeMobil << endl
                 << "Merek Mobil: " << servN -> merekMobil << endl
                 << "Kendala: " << servN -> kendala << endl
                 << "Nama Montir: " << servN -> namaMontir << endl
                 << "Tanggal Ambil: " << servN -> tanggal << endl
                 << "Urgensi: " << servN -> urgensi << endl
                 << "Nama Customer: " << servN -> namaCust << endl
                 << "-----------------------------" << endl;

            cout << "Apakah servis ini sudah selesai? (Y/N): ";
            string jawaban;
            cin >> jawaban;

            if (jawaban == "y" || jawaban == "Y")
            {
                servN -> doneServ = "1";
                Service *antrian = headServ;
                int antri = 1;
                while (antrian != NULL)
                {
                    if (antrian -> doneServ == "0")
                    {
                        antrian -> antri = to_string(antri);
                        antri++;
                    }
                    else
                    {
                        antrian -> antri = "0";
                    }
                    antrian = antrian -> next;
                }
                queueSort();
                updateServ();
                cout << "Servis berhasil diselesaikan!" << endl;
            }
            else {
                cout << "Servis dibatalkan / belum diselesaikan." << endl;
            }
            break;
        }
        servN = servN -> next;
    }
    if (!adaIn) cout << endl << "Tidak ada antrian pekerjaan untuk montir " << targetMontir << "." << endl;
    system("pause");
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
        reschedule();
    }
    else if (pil == "3")
    {
        queue();
    }
    else if (pil == "4")
    {
        finish();
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