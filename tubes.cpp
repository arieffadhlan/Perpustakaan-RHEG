#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

void cekFileDataAkun(fstream &data);
void cekFileDataBuku(fstream &data);
int menuAwal();

class Autentikasi {
     private:
          string usernameRegistrasi, passwordRegistrasi, usernameLogin, passwordLogin;

     public:
          void registrasi() {
               system("cls");

               string tempData, line;

               cout << "===============" << endl;
               cout << "Form Registrasi" << endl;
               cout << "===============" << endl;
               cout << "Masukkan Username : ";
               cin.ignore();
               getline(cin, usernameRegistrasi);
               cout << "Masukkan Password : ";
               istream& ignore (streamsize n = 1, int delim = EOF);
               getline(cin, passwordRegistrasi);

               tempData = usernameRegistrasi + "," + passwordRegistrasi + ",user";

               ifstream file("dataAkun.csv", ios::in | ios::out);
               if (file.is_open()) {
                    getline(file, line, '\n');

                    while (getline(file, line, '\n')) {
                         if (tempData == line) {
                              cout << "\nAkun sudah ada!";
                              getch();
                              break;
                         } else {
                              if (!file.eof()) {
                                   continue;
                              } else {
                                   file.close();
                                   ofstream file("dataAkun.csv", ios::app);
                                   if (file.is_open()) {
                                        file << "\n" << tempData;
                                        cout << "\nSelamat! Akun anda telah diregistrasi!";
                                        getch();

                                        file.close();
                                        break;
                                   } else {
                                        cout << "\nDatabase tidak dapat dibuka";
                                        getch();
                                   }
                              }
                         }
                    }
               } else {
                    cout << "\nDatabase tidak dapat dibuka";
                    getch();
               }            
          }

          string login() {
               system ("cls");

               string level;

               cout << "==========" << endl;
               cout << "Form Login" << endl;
               cout << "==========" << endl;
               cout << "Masukkan Username : ";
               cin.ignore();
               getline(cin, usernameLogin);
               cout << "Masukkan Password : ";
               istream& ignore (streamsize n = 1, int delim = EOF);
               getline(cin, passwordLogin);

               string x = usernameLogin + "," + passwordLogin;

               fstream file;
               file.open("dataAkun.csv", ios::in);

               vector<string> row;
               string line, data;

               while (getline(file, line)) {
                    row.clear();

                    istringstream s(line);
                    while (getline(s, data, ',')) {
                         row.push_back(data);
                    }

                    if (x == row[0] + "," + row[1]) {
                         if (row[2] == "admin") {
                              cout << "\nAkun Anda telah diverifikasi!";
                              getch();

                              goto LoginAdmin;
                         } else if (row[2] == "user") {
                              cout << "\nAkun Anda telah diverifikasi!";
                              getch();

                              goto LoginUser;
                         }
                    } else {
                         if (!file.eof()) {
                              continue;
                         } else {
                              goto GagalLogin;
                         }
                    }
               }

               LoginAdmin:
               file.close();
               level = "admin";
               goto BerhasilLogin;

               LoginUser:
               file.close();
               level = "user";
               goto BerhasilLogin;

               GagalLogin:
               file.close();
               level = "gagal";
               goto BerhasilLogin;

               BerhasilLogin:
               return level;
          }
};

class Penambahan {
     private:
          int hargaBuku, banyakBuku;
          string namaBuku;

     public:
          void tambahData() {
               int hargaBuku, JumlahBuku;
               string namaBuku;

               fstream fout;
               fout.open("dataBuku.csv", ios::out | ios::app);
               
               if (fout.is_open()) {
                    cout << "Masukkan Nama Buku : ";
                    cin.ignore();
                    getline(cin, namaBuku);
                    cout << "Harga Buku : ";
                    cin >> hargaBuku;
                    cout << "Jumlah Buku : ";
                    cin >> JumlahBuku;

                    fout << namaBuku << "," << hargaBuku << "," << JumlahBuku << "\n";
                    cout << "\nData buku berhasil ditambahkan!";
                    getch();
               } else {
                    cout << "Database buku tidak ditemukan!";
                    getch();
               }
          }
};

class MenuOpsiAdmin : public Penambahan {
     private:
          int pilihanMenuOpsiAdmin;
     
     public:
          void menu() {               
               system("cls");
               
               cout << "1. Penambahan buku" << endl;
               cout << "2. Exit" << endl;
               cout << "\nMasukkan pilihan anda : ";

               cin >> pilihanMenuOpsiAdmin;
               pilihanOpsiAdmin(pilihanMenuOpsiAdmin);
          }

          void pilihanOpsiAdmin(int pilihan) {
               while (!(pilihanMenuOpsiAdmin < 1) || !(pilihanMenuOpsiAdmin > 2)) {
                    switch(pilihanMenuOpsiAdmin){
                         case 1:
                              system("cls");
                              cout << "===============" << endl;
                              cout << "Penambahan Buku" << endl;
                              cout << "===============" << endl;
                              tambahData();
                              menu();
                              break;

                         case 2:
                              exit(0);
                              break;

                         default:
                              cout << "\nPilihan Anda tidak valid!";
                              menu();
                              break;
                    }
               }
          }
};

class Peminjaman {
     private:
          int dataHarga, hargaBuku, banyakBuku;
          string namaBuku, namaPeminjam;
          char konfirmasiPinjaman;

     public:
          void tampilDataBuku() {
               cout << "===============================================\n";
               cout << "Judul\t\t\t Harga\t\t Jumlah\n";
               cout << "-----------------------------------------------\n";

               fstream fin;
               fin.open("dataBuku.csv", ios::in);

               vector<string> row;
               string line, data;

               while (getline(fin, line)) {
                    row.clear();

                    istringstream s(line);
                    while (getline(s, data, ',')) {
                         row.push_back(data);
                    }

                    for (int i = 0; i < 3; i++) {
                         cout << row[i];
                         
                         if (row[i] == row[0]) {
                              cout << "\t\t ";
                         } else if (row[i] == row[1]) {
                              cout << "\t\t   ";
                         } else if (row[i] == row[2]) {
                              cout << endl;
                         }
                    }
               }
               cout << "===============================================\n";

               fin.close();
               pinjamBuku();
          }

          template <class T>
          T getValue(string s, int col)
          {
               T val;
               int counter = 0;
               string str;
               stringstream ss(s);

               while (counter++ < col) {
                    getline(ss, str, ',');
               }

               stringstream sstr(str);
               sstr >> val;
               return val;
          }
     
          void pinjamBuku() {
               fstream fin, fout, dataBukuBaru;
               fout.open("dataPeminjam.csv", ios::out | ios::app);
               dataBukuBaru.open("dataBukuBaru.csv", ios::out);
               if (!dataBukuBaru.is_open()) {
                    dataBukuBaru.close();
                    dataBukuBaru.open("dataBukuBaru.csv", ios::out);
               }
               
               fin.open("dataBuku.csv", ios::in);
               vector<string> row;
               string line, data;

               if (fin.is_open()) {
                    isiData:
                    cout << "\nMasukkan nama peminjam : ";
                    cin.ignore();
                    getline(cin, namaPeminjam);
                    cout << "Masukkan nama buku yang ingin dipinjam (Case Sensitive) : ";
                    istream& ignore (streamsize n = 1, int delim = EOF);
                    getline(cin, namaBuku);
                    cout << "Masukkan jumlah buku yang ingin dipinjam : ";
                    cin >> banyakBuku;

                    system("cls");

                    while (getline(fin, line)) {
                         row.clear();

                         stringstream s(line);
                         while (getline(s, data, ',')) {
                              row.push_back(data);
                         }

                         if (row[0] == namaBuku) {
                              int totalHarga = getValue<int>(line, 2);
                              int jumlah = getValue<int>(line, 3);
                              totalHarga *= banyakBuku;
                              jumlah -= banyakBuku; 

                              cout << "===================" << endl;
                              cout << "Konfirmasi Pinjaman" << endl;
                              cout << "===================" << endl;
                              cout << "Nama peminjam             : " << namaPeminjam << endl;
                              cout << "Judul buku                : " << namaBuku << endl;
                              cout << "Jumlah buku yang dipinjam : " << banyakBuku << endl;
                              cout << "Total Harga               : " << totalHarga << endl;

                              cout << "\nApakah data Anda sudah benar (y/n) : ";
                              cin >> konfirmasiPinjaman;

                              if (konfirmasiPinjaman == 'Y' | konfirmasiPinjaman == 'y') {
                                   fout << namaPeminjam << "," << namaBuku << "," << banyakBuku << endl;
                                   dataBukuBaru << row[0] << "," << row[1] << "," << jumlah << endl;
                                   cout << "\nData telah disimpan!\n" << endl;
                                   cout << "Jangan lupa untuk mengembalikan buku ya!";
                                   getch();
                              } else if (konfirmasiPinjaman == 'N' | konfirmasiPinjaman == 'n') {
                                   cout << "\nPemesanan dibatalkan!";
                                   getch();

                                   goto selesai;
                              } else {
                                   cout << "\nInput yang anda masukkan salah!";
                                   getch();

                                   system("cls");
                                   tampilDataBuku();

                                   goto isiData;
                              }
                         } else {
                              if (!fin.eof()) {
                                   for (int i = 0; i < row.size() - 1; i++) {
                                        dataBukuBaru << row[i] << ",";
                                   }
                                   dataBukuBaru << row[row.size() - 1] << "\n";
                              }
                         }

                         if (fin.eof()) {
                              break;
                         }
                    }
               }
               fin.close();
               fout.close();        
               dataBukuBaru.close();

               remove("dataBuku.csv");
               rename("dataBukuBaru.csv", "dataBuku.csv");

               selesai:
               fin.close();
               fout.close();
               dataBukuBaru.close();
          }
};

class Pengembalian {
     private:
          int banyakBuku;
          string namaBuku, namaPeminjam;
          char konfirmasiPengembalian;

     public:
          template <class T>
          T getValue(string s, int col)
          {
               T val;
               int counter = 0;
               string str;
               stringstream ss(s);

               while (counter++ < col) {
                    getline(ss, str, ',');
               }

               stringstream sstr(str);
               sstr >> val;
               return val;
          }
     
          void kembalikanBuku() {
               fstream fin, fout, dataPeminjamBaru, dataBukuBaru;
               fout.open("dataPeminjam.csv", ios::in | ios::out | ios::app);
               dataPeminjamBaru.open("dataPeminjamBaru.csv", ios::out);
               if (!dataPeminjamBaru.is_open()) {
                    dataPeminjamBaru.close();
                    dataPeminjamBaru.open("dataPeminjamBaru.csv", ios::out);
               }
               fin.open("dataBuku.csv", ios::in);
               dataBukuBaru.open("dataBukuBaru.csv", ios::out);
               if (!dataBukuBaru.is_open()) {
                    dataBukuBaru.close();
                    dataBukuBaru.open("dataBukuBaru.csv", ios::out);
               }
               
               vector<string> rowPeminjam;
               vector<string> rowBuku;
               string linePeminjam, lineBuku, dataPeminjam, dataBuku;

               if (fout.is_open()) {
                    isiData:
                    cout << "\nMasukkan nama peminjam : ";
                    cin.ignore();
                    getline(cin, namaPeminjam);

                    while (getline(fout, linePeminjam)) {
                         rowPeminjam.clear();

                         stringstream s(linePeminjam);
                         while (getline(s, dataPeminjam, ',')) {
                              rowPeminjam.push_back(dataPeminjam);
                         }
                         
                         if (rowPeminjam[0] == namaPeminjam) {
                              int jumlahPinjaman = getValue<int>(linePeminjam, 3);

                              while(getline(fin, lineBuku)) {
                                   rowBuku.clear();

                                   stringstream str(lineBuku);
                                   while (getline(str, dataBuku, ',')) {
                                        rowBuku.push_back(dataBuku);
                                   }

                                   if (rowPeminjam[1] == rowBuku[0]) { 
                                        banyakBuku = getValue<int>(lineBuku, 3);
                                        banyakBuku += jumlahPinjaman;
                                        
                                        system("cls");

                                        cout << "=======================" << endl;
                                        cout << "Konfirmasi Pengembalian" << endl;
                                        cout << "=======================" << endl;
                                        cout << "Nama peminjam             : " << namaPeminjam << endl;
                                        cout << "Judul buku                : " << rowPeminjam[1] << endl;
                                        cout << "Jumlah buku yang dipinjam : " << jumlahPinjaman << endl;

                                        cout << "\nApakah data Anda sudah benar (y/n) : ";
                                        cin >> konfirmasiPengembalian;

                                        if (konfirmasiPengembalian == 'Y' | konfirmasiPengembalian == 'y') {
                                             dataBukuBaru << rowBuku[0] << "," << rowBuku[1] << "," << banyakBuku << endl;
                                             cout << "\nData telah disimpan!\n" << endl;
                                             cout << "Terima kasih telah mengembalikan buku!";
                                             getch();
                                        } else if (konfirmasiPengembalian == 'N' | konfirmasiPengembalian == 'n') {
                                             cout << "\nPengembalian dibatalkan!";
                                             getch();

                                             goto selesai;
                                        } else {
                                             cout << "\nInput yang anda masukkan salah!";
                                             getch();

                                             system("cls");

                                             goto isiData;
                                        }
                                   } else {
                                        if (!fin.eof()) {
                                             for (int i = 0; i < rowBuku.size() - 1; i++) {
                                                  dataBukuBaru << rowBuku[i] << ",";
                                             }
                                             dataBukuBaru << rowBuku[rowBuku.size() - 1] << "\n";
                                        }
                                   } 

                                   if (fin.eof()) {
                                        break;
                                   }
                              }
                         } else {
                              if (!fout.eof()) {
                                   for (int i = 0; i < rowPeminjam.size() - 1; i++) {
                                        dataPeminjamBaru << rowPeminjam[i] << ",";
                                   }
                                   dataPeminjamBaru << rowPeminjam[rowPeminjam.size() - 1] << "\n";
                              }
                         }

                         if (fout.eof()) {
                              break;
                         }
                    }
               }
               fin.close();
               fout.close();        
               dataBukuBaru.close();
               dataPeminjamBaru.close();

               remove("dataBuku.csv");
               remove("dataPeminjam.csv");
               rename("dataBukuBaru.csv", "dataBuku.csv");
               rename("dataPeminjamBaru.csv", "dataPeminjam.csv");

               selesai:
               fin.close();
               fout.close();
               dataBukuBaru.close();
               dataPeminjamBaru.close();
          }
};

class MenuOpsiUser : public Peminjaman, Pengembalian {
     private:
          int pilihanMenuOpsiUser;
          enum option{PEMINJAMAN = 1, PENGEMBALIAN, KELUAR, BREAK};
     
     public:
          void menu() {               
               system("cls");

               cout << "1. Peminjaman Buku" << endl;
               cout << "2. Pengembalian Buku" << endl;
               cout << "3. Exit" << endl;
               cout << "\nMasukkan pilihan anda : ";

               cin >> pilihanMenuOpsiUser;
               pilihanOpsiUser(pilihanMenuOpsiUser);
          }

          void pilihanOpsiUser(int pilihan) {
               while (!(pilihanMenuOpsiUser < 1) || !(pilihanMenuOpsiUser > 3)) {
                    switch(pilihanMenuOpsiUser){
                         case PEMINJAMAN:
                              system("cls");
                              cout << "===============" << endl;
                              cout << "Peminjaman Buku" << endl;
                              cout << "===============" << endl;
                              tampilDataBuku();
                              menu();
                              break;

                         case PENGEMBALIAN:
                              system("cls");
                              cout << "=================" << endl;
                              cout << "Pengembalian Buku" << endl;
                              cout << "=================" << endl;
                              kembalikanBuku();
                              menu();
                              break;

                         case KELUAR:
                              exit(0);
                              break;

                         default:
                              cout << "\nPilihan Anda tidak valid!";
                              menu();
                              break;
                    }
               }
          }
};

int main() {	
	fstream data;
     Autentikasi auth;
     MenuOpsiUser menuUser;
     MenuOpsiAdmin menuAdmin;

	cekFileDataAkun(data);
	cekFileDataBuku(data);

     menuAwal:
     system("cls");
     int pilihan;
     string level;

     cout << "1. Register Akun" << endl;
	cout << "2. Login Akun" << endl;
	cout << "3. Exit" << endl;
	cout << "\nMasukkan pilihan anda : ";
     cin >> pilihan;

     switch (pilihan) {
          case 1:
               auth.registrasi();
               main();
               break;

          case 2:
               level = auth.login();
               if (level == "admin") {
                    menuAdmin.menu();
               } else if (level == "user") {
                    menuUser.menu();
               } else if (level == "gagal") {
                    cout << "\nData tidak ditemukan!";
                    getch();

                    goto menuAwal;
               }
               break;

          case 3:
               exit(0);
               break;

          default:
               cout << "\nPilihan Anda tidak valid!";
               getch();

               goto menuAwal;
               break;
     }

	return 0;
}

void cekFileDataAkun(fstream &data) {
     data.open("dataAkun.csv", ios::out | ios::in | ios::binary);

	if (!data.is_open()) {
		data.close();
		data.open("dataAkun.csv", ios::trunc | ios::out | ios::in | ios::binary);
	}
	data.close();
}

void cekFileDataBuku(fstream &data) {
     data.open("dataBuku.csv", ios::out | ios::in | ios::binary);

	if (!data.is_open()) {
		data.close();
		data.open("dataBuku.csv", ios::trunc | ios::out | ios::in | ios::binary);
	}
	data.close();
}