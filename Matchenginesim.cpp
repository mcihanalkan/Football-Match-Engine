#include <iostream>
#include <array>
#include <cstdlib>
#include <string>
#include <set>
#include <vector>
#include <ctime>
using namespace std;

// Ortak kullanılabilecek veri yapısı
struct MatchFactors {
    string turnuva;
    string hakemKararlari;
    string taraftarEtkisi;
    string havaDurumu;
};

class Futbolcu {
    public:
        string isim;
        string pozisyon;
        int fifaRating;
    
        Futbolcu(string isim, string pozisyon, int rating)
            : isim(isim), pozisyon(pozisyon), fifaRating(rating) {}
};

class Takim {
    public:
        string isim;
        int formasyon = 4231;
        vector<Futbolcu> tumOyuncular;
        vector<Futbolcu> ilk11;
    
        Takim(string isim) : isim(isim), formasyon(4231) {}
    
        void oyuncuEkle(const Futbolcu& oyuncu) {
            tumOyuncular.push_back(oyuncu);
        }
    
        void ilk11Sec() {
            bool tekrarSec = true;
        
            while (tekrarSec) {
                ilk11.clear(); // Her girişte ilk11 temizlenir
                cout << "\n" << isim << " takımı için ilk 11 oyuncuyu seçin:\n";
        
                for (int i = 0; i < tumOyuncular.size(); ++i) {
                    cout << i << ": " << tumOyuncular[i].isim << " (" << tumOyuncular[i].pozisyon
                        << ", Rating: " << tumOyuncular[i].fifaRating << ")\n";
                }
        
                vector<bool> secildi(tumOyuncular.size(), false);
        
                for (int i = 0; i < 11; ++i) {
                    int secim;
                    cout << i + 1 << ". oyuncunun indexini gir: ";
                    cin >> secim;
        
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Geçersiz giriş. Lütfen sadece sayı girin.\n";
                        --i;
                        continue;
                    }
        
                    if (secim >= 0 && secim < tumOyuncular.size()) {
                        if (!secildi[secim]) {
                            ilk11.push_back(tumOyuncular[secim]);
                            secildi[secim] = true;
                        } else {
                            cout << "Bu oyuncu zaten seçildi. Lütfen başka bir oyuncu seçin.\n";
                            --i;
                        }
                    } else {
                        cout << "Geçersiz index. Tekrar gir.\n";
                        --i;
                    }
                }
        
                // Kadro tamamlandıktan sonra kullanıcıya tekrar sor
                int cevap;
                while (true) {
                    cout << "\nKadroyu tekrar seçmek ister misiniz?\n1: Evet, tekrar seçeceğim\n2: Hayır, devam et\nSeçim: ";
                    cin >> cevap;
        
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Geçersiz giriş. Lütfen 1 ya da 2 giriniz.\n";
                        continue;
                    }
        
                    if (cevap == 1) {
                        cout << "\nKadro sıfırlandı. Yeni seçim yapınız.\n";
                        break; // while (true) içinden çık, ama dıştaki while(tekrarSec) devam eder
                    } else if (cevap == 2) {
                        tekrarSec = false; // döngü bitecek
                        break;
                    } else {
                        cout << "Lütfen 1 veya 2 giriniz.\n";
                    }
                }
            }
        }
        
        void FormasyonSec() { // Diziliş seçimi
            bool tekrarSec = true;
        
            while (tekrarSec) {
                cout << "\n" << isim << " takımı için formasyon seçin:\n";
                int formasyonicin;
        
                while (true) {
                    cout << "1: 4-2-3-1\n";
                    cout << "2: 5-3-2\n";
                    cout << "3: 3-5-2\n";
                    cout << "4: 4-1-4-1\n";
                    cout << "5: 4-4-2\n";
                    cout << "Seçiminizi girin (1-5): "; // Hangi diziliş seçtiğini sor
                    cin >> formasyonicin;
        
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Geçersiz giriş. Lütfen sadece sayı girin.\n";
                        continue;
                    }
        
                    if (formasyonicin == 1) {
                        formasyon = 4231;
                        break;
                    } else if (formasyonicin == 2) {
                        formasyon = 532;
                        break;
                    } else if (formasyonicin == 3) {
                        formasyon = 352;
                        break;
                    } else if (formasyonicin == 4) {
                        formasyon = 4141;
                        break;
                    } else if (formasyonicin == 5) {
                        formasyon = 442;
                        break;
                    } else {
                        cout << "Geçersiz giriş. Lütfen 1 ile 5 arasında bir sayı girin.\n";
                    }
                }
        
                cout << isim << " takımı " << formasyon << " formasyonunu seçti.\n";
        
                // Kullanıcıya tekrar seçmek isteyip istemediğini sor
                int cevap;
                while (true) {
                    cout << "Formasyonu tekrar seçmek ister misiniz?\n1: Evet\n2: Hayır\nSeçim: ";
                    cin >> cevap;
        
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Geçersiz giriş. Lütfen 1 ya da 2 giriniz.\n";
                        continue;
                    }
        
                    if (cevap == 1) {
                        cout << "Formasyon seçimi sıfırlandı. Lütfen yeniden seçiniz.\n";
                        break; // içteki while'dan çık, dış döngü (tekrarSec) devam eder
                    } else if (cevap == 2) {
                        tekrarSec = false;
                        break;
                    } else {
                        cout << "Lütfen 1 veya 2 giriniz.\n";
                    }
                }
            }
        }

};

class macOrtamAyarlayici {
  public:
    MatchFactors factors;
    
    void faktorleriKullanicidanAl() {
        int secim;
        while(true) {
            while(true) { // Turnuva Faktörü Seçimi
                cout<<"\nTurnuva faktörünü seçiniz (1-4):\n1: Süper Lig\n2: Ziraat Türkiye Kupası\n3: UEFA Maçı\n4: UEFA Final maçı\n";
                cin>>secim;
                if(secim==1) {
                    factors.turnuva="superlig";
                    break;
                } else if(secim==2) {
                    factors.turnuva="ztk";
                    break;
                } else if(secim==3) {
                    factors.turnuva="uefa";
                    break;
                } else if(secim==4) {
                    factors.turnuva="uefafinal";
                    break;
                } else {
                    cout<<"Geçersiz giriş. Lütfen 1, 2 veya 3 girin.\n";
                }
            }
            
            while(true) { // Hava Durumu Seçimi
                cout<<"\n1: Güzel\n2: Yağmurlu\n3: Karlı, Kötü\nHava Durumunu Seçiniz (1-3): ";
                cin>>secim;
                if(secim==1) {
                    factors.havaDurumu="guzel";
                    break;
                } else if(secim==2) {
                    factors.havaDurumu="yagmurlu";
                    break;
                } else if(secim==3) {
                    factors.havaDurumu="karli";
                    break;
                } else {
                    cout<<"Geçersiz giriş. Lütfen 1,2 veya 3 giriniz.\n";
                }
            }
            
            while(true) { // Hakem Kararları Seçimi
                cout<<"\n1: Oyun durmuyor, soğukkanlı\n2: Normal, oyun ortalama\n3: Oyun çok duruyor. kızgın\nHakem kararları için seçim yapınız (1-3): ";
                cin>>secim;
                if(secim==1) {
                    factors.hakemKararlari="oyundurmuyor";
                    break;
                } else if(secim==2) {
                    factors.hakemKararlari="normal";
                    break;
                } else if(secim==3) {
                    factors.hakemKararlari="cokduruyor";
                    break;
                } else {
                    cout<<"Geçersiz giriş. Lütfen 1, 2 veya 3 giriniz.\n";
                }
            }
            
            while (true) { // Taraftar Desteği seçimi
                cout << "\n1: Yüksek Taraftar Desteği\n";
                cout << "2: Orta Taraftar Desteği\n";
                cout << "3: Düşük Taraftar Desteği\n";
                cout << "Ev sahibi için taraftar etkisi seçiminizi girin (1-3): ";
                cin >> secim;
            
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Geçersiz giriş. Lütfen 1, 2 veya 3 girin.\n";
                    continue;
                }
            
                if (secim == 1) {
                    factors.taraftarEtkisi = "yuksek";
                    break;
                } else if (secim == 2) {
                    factors.taraftarEtkisi = "orta";
                    break;
                } else if (secim == 3) {
                    factors.taraftarEtkisi = "dusuk";
                    break;
                } else {
                    cout << "Lütfen 1, 2 veya 3 değerlerinden birini seçin.\n";
                }
            }
            
            int tekrar;
            while(true) {
                cout<<"\nSeçimlerinizi tekrarlamak ister misiniz?\n1: Evet\n2: Hayır\nSeçiminizi Giriniz (1-2): ";
                cin>>tekrar;
                if(cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout<<"Geçersiz giriş. Lütfen 1 veya 2 giriniz.\n";
                    continue;
                }
                if(tekrar==1) {
                    cout<<"Tekrar seçim yapılıyor...\n";
                    break;
                } else if(tekrar==2) {
                    return;
                } else {
                    cout<<"Lütfen 1 veya 2 seçiniz.\n";
                }
            }
        }
    }
    
    void faktorleriGoster() { // Faktörleri Ekrana gösterme
        cout<<"\nMaç Faktörleri:";
        cout<<"\nHava Durumu: "<<factors.havaDurumu;
        cout<<"\nHakem Kararları: "<<factors.hakemKararlari;
        cout<<"\nTurnuva Faktörü: "<<factors.turnuva;
        cout<<"\nTaraftar Etkisi (Ev sahibi için): "<<factors.taraftarEtkisi;    
    }
};

class Game {
    public:
        MatchFactors factors;
        Game(const MatchFactors& gelenFaktorler) {
            factors = gelenFaktorler;
        }
        void macOncesiOyuncuIstatistikleriAyarlama(Takim& takim, bool evSahibiMi) {
            
            double taraftarKatSayisi=1.00;
            if(evSahibiMi) {
                if(factors.taraftarEtkisi=="yuksek") {
                    taraftarKatSayisi=1.2;
                } else if (factors.taraftarEtkisi=="orta") {
                    taraftarKatSayisi=1.1;
                } else if(factors.taraftarEtkisi=="dusuk") {
                    taraftarKatSayisi=1;
                }
            } else {
                if(factors.taraftarEtkisi=="yuksek") {
                    taraftarKatSayisi=0.85;
                } else if(factors.taraftarEtkisi=="orta") {
                    taraftarKatSayisi=0.90;
                } else if(factors.taraftarEtkisi=="dusuk") {
                    taraftarKatSayisi=0.95;
                }
            }
            
            double hakemKatSayisi=1;
            if(factors.hakemKararlari=="oyundurmuyor") {
                hakemKatSayisi=0.9;
            } else if(factors.hakemKararlari=="normal") {
                hakemKatSayisi=1;
            } else if(factors.hakemKararlari=="cokduruyor") {
                hakemKatSayisi=1.2;
            }
            
            double havaKatSayisi=1;
            if(factors.havaDurumu=="guzel") {
                havaKatSayisi=1.05;
            } else if(factors.havaDurumu=="yagmurlu") {
                havaKatSayisi=0.95;
            } else if(factors.havaDurumu=="karli") {
                havaKatSayisi=0.9;
            }
            
            double turnuvaKatSayisi=1;
            if(factors.turnuva=="superlig") {
                turnuvaKatSayisi=1;
            } else if(factors.turnuva=="ztk") {
                turnuvaKatSayisi=0.9;
            } else if(factors.turnuva=="uefa") {
                turnuvaKatSayisi=1.15;
            } else if(factors.turnuva=="uefafinal") {
                turnuvaKatSayisi=1.25;
            }
            
             // Katsayıları ekrana yazdır
            cout << "\n[" << takim.isim << "] Takımı için katsayılar:\n";
            cout << "- Taraftar Katsayısı: " << taraftarKatSayisi << endl;
            cout << "- Hakem Katsayısı:    " << hakemKatSayisi << endl;
            cout << "- Hava Katsayısı:     " << havaKatSayisi << endl;
            cout << "- Turnuva Katsayısı:  " << turnuvaKatSayisi << endl;
        }
};

int main()
{
    srand(time(NULL));
    vector<Takim> tumTakimlar;
    
    // Takımları ekleme
    Takim realmadrid("Real Madrid");
    realmadrid.oyuncuEkle(Futbolcu("Courtois","KL",711));
    realmadrid.oyuncuEkle(Futbolcu("Fran Gonzalez","KL",630));
    realmadrid.oyuncuEkle(Futbolcu("Hato","SLB",684));
    realmadrid.oyuncuEkle(Futbolcu("Ferland Mendy","SLB",682));
    realmadrid.oyuncuEkle(Futbolcu("Militao","STP",721));
    realmadrid.oyuncuEkle(Futbolcu("Rüdiger","STP",703));
    realmadrid.oyuncuEkle(Futbolcu("Huijsen","STP",723));
    realmadrid.oyuncuEkle(Futbolcu("Ito","STP",700));
    realmadrid.oyuncuEkle(Futbolcu("Arnold","SĞB",725));
    realmadrid.oyuncuEkle(Futbolcu("Carvajal","SĞB",726));
    realmadrid.oyuncuEkle(Futbolcu("Vasquez","SĞB",705));
    realmadrid.oyuncuEkle(Futbolcu("Kimmich","DOS",791));
    realmadrid.oyuncuEkle(Futbolcu("Tchouameni","DOS",710));
    realmadrid.oyuncuEkle(Futbolcu("Valverde","GÖ",747));
    realmadrid.oyuncuEkle(Futbolcu("Ceballos","GÖ",713));
    realmadrid.oyuncuEkle(Futbolcu("Bellingham","OOS",745));
    realmadrid.oyuncuEkle(Futbolcu("Modric","OOS",738));
    realmadrid.oyuncuEkle(Futbolcu("Vinicius","SLA",737));
    realmadrid.oyuncuEkle(Futbolcu("Foden","SLA",724));
    realmadrid.oyuncuEkle(Futbolcu("Rordygo","SĞA",740));
    realmadrid.oyuncuEkle(Futbolcu("Brahim Diaz","SĞA",689));
    realmadrid.oyuncuEkle(Futbolcu("Mbappe","SF",770));
    realmadrid.oyuncuEkle(Futbolcu("Sesko","SF",693));

    Takim mancity("Manchester City");
    mancity.oyuncuEkle(Futbolcu("Ederson","KL",89));
    mancity.oyuncuEkle(Futbolcu("Carson","KL",62));
    mancity.oyuncuEkle(Futbolcu("Gvardiol","SLB",77));
    mancity.oyuncuEkle(Futbolcu("Kerkez","SLB",82));
    mancity.oyuncuEkle(Futbolcu("Ruben Dias","STP",85));
    mancity.oyuncuEkle(Futbolcu("Stones","STP",88));
    mancity.oyuncuEkle(Futbolcu("Khusanov","STP",78));
    mancity.oyuncuEkle(Futbolcu("Rico Lewis","SĞB",78));
    mancity.oyuncuEkle(Futbolcu("Rodri","DOS",86));
    mancity.oyuncuEkle(Futbolcu("Zubimendi","DOS",79));
    mancity.oyuncuEkle(Futbolcu("Matheus Nunes","GÖ",86));
    mancity.oyuncuEkle(Futbolcu("Nico Gonzalez","GÖ",88));
    mancity.oyuncuEkle(Futbolcu("Mac Allister","GÖ",84));
    mancity.oyuncuEkle(Futbolcu("Bernardo","OOS",88));
    mancity.oyuncuEkle(Futbolcu("Martinelli","SLA",80));
    mancity.oyuncuEkle(Futbolcu("Doku","SLA",89));
    mancity.oyuncuEkle(Futbolcu("Estevao","SĞA",85));
    mancity.oyuncuEkle(Futbolcu("Arda Güler","SĞA",90));
    mancity.oyuncuEkle(Futbolcu("Haaland","SF",86));
    mancity.oyuncuEkle(Futbolcu("Marmoush","SF",86));
    
    Takim inter("Inter");
    inter.oyuncuEkle(Futbolcu("Sommer","KL",87));
    inter.oyuncuEkle(Futbolcu("Dimarco","SLB",85));
    inter.oyuncuEkle(Futbolcu("Pau Torres","STP",81));
    inter.oyuncuEkle(Futbolcu("Pavard","STP",84));
    inter.oyuncuEkle(Futbolcu("Bastoni","STP",87));
    inter.oyuncuEkle(Futbolcu("Frimpong","SĞB",84));
    inter.oyuncuEkle(Futbolcu("Çalhanoğlu","DOS",86));
    inter.oyuncuEkle(Futbolcu("Milinkovic-Savic","GÖ",78));
    inter.oyuncuEkle(Futbolcu("Barella","GÖ",87));
    inter.oyuncuEkle(Futbolcu("Marcus Thuram","SF",84));
    inter.oyuncuEkle(Futbolcu("Lautaro","SF",88));
    inter.oyuncuEkle(Futbolcu("Santiago Gimenez","SF",79));
    inter.oyuncuEkle(Futbolcu("De Vrij","STP",83));
    inter.oyuncuEkle(Futbolcu("Frattesi","GÖ",82));
    inter.oyuncuEkle(Futbolcu("Mkhitaryan","GÖ",83));
    inter.oyuncuEkle(Futbolcu("Alaba","STP",84));
    inter.oyuncuEkle(Futbolcu("Ndidi","DOS",77));
    inter.oyuncuEkle(Futbolcu("Henrique","SĞA",79));

    // 2. Listeye Ekle
    tumTakimlar.push_back(realmadrid);
    tumTakimlar.push_back(mancity); 
    tumTakimlar.push_back(inter);

    // 3. Takım seçimi
    cout << "Takımlar:\n";
    for (int i = 0; i < tumTakimlar.size(); ++i) {
        cout << i << ": " << tumTakimlar[i].isim << endl;
    }

    int t1, t2;
    while (true) {
        cout << "Ev sahibi takimin indexini gir: ";
        cin >> t1;
        cout << "Deplasman takiminin indexini gir: ";
        cin >> t2;
    
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Geçersiz giriş. Lütfen sayısal değer girin.\n";
            continue;
        }
    
        if (t1 == t2 || t1 >= tumTakimlar.size() || t2 >= tumTakimlar.size() || t2 < 0 || t1 < 0) {
            cout << "Geçersiz seçim. Lütfen farkli ve geçerli takımlar seçin.\n";
        } else {
            break;  // Geçerli seçim, döngüden çık
        }
    }


    
    tumTakimlar[t1].FormasyonSec();
    tumTakimlar[t2].FormasyonSec();
    tumTakimlar[t1].ilk11Sec();
    tumTakimlar[t2].ilk11Sec();
    macOrtamAyarlayici ortam;
    ortam.faktorleriKullanicidanAl();
    ortam.faktorleriGoster();
    Game game(ortam.factors);
    game.macOncesiOyuncuIstatistikleriAyarlama(tumTakimlar[t1], true);
    game.macOncesiOyuncuIstatistikleriAyarlama(tumTakimlar[t2], false);
}
