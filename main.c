#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Rastgelelik baslatma

    int saglik = 100, enerji = 100, oksijen = 100, su = 0, yedekParca = 0, modulHasari = 0;
    int kilitMuhurlu = 0, gun = 1, tur = 0, gecersiz = 1, firtinaTuru = 5, zorlukFark = 0;
    char zorluk, komut;

    // 1. Zorluk Secimi (SWITCH-CASE ve DO-WHILE)
    do {
        printf("Zorluk Secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        switch (zorluk) {
            case 'k': case 'K':
                su = 30; yedekParca = 10; modulHasari = 10; firtinaTuru = 3; zorlukFark = -10; gecersiz = 0;
                break;
            case 'n': case 'N':
                su = 20; yedekParca = 6; modulHasari = 20; firtinaTuru = 5; zorlukFark = 0; gecersiz = 0;
                break;
            case 'z': case 'Z':
                su = 12; yedekParca = 3; modulHasari = 35; firtinaTuru = 7; zorlukFark = 15; gecersiz = 0;
                break;
            default:
                printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    } while (gecersiz == 1);

    // 2. Ana Oyun Dongusu (DO-WHILE)
    do {
        printf("\n--- GUN: %d/15 | TUR: %d | Saglik:%d Enerji:%d Oksijen:%d Su:%d Parca:%d Hasar:%d ---\n",
               gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari);
        printf("Komut [G:Kesif, O:Oksijen, T:Tamir, D:Durum, U:Uyu, K:Firtina, H:Kilit, Q:Cikis]: ");
        scanf(" %c", &komut);

        int turGecti = 0;

        switch (komut) {
            case 'g': case 'G': { // Kesif
                if (enerji < 15) {
                    printf("Yetersiz enerji! (En az 15 gerekli)\n");
                } else {
                    enerji -= 15; oksijen -= 10; turGecti = 1;
                    int zar = rand() % 100;
                    int esik = (enerji > 40 && oksijen > 30) ? (55 - zorlukFark) : (35 - zorlukFark);
                    printf("Kesif Zar: %d / Esik: %d -> ", zar, esik);

                    if (zar < esik / 2) {
                        su += 8;
                        printf("BASARILI (+8 Su)\n");
                    } else if (zar < esik) {
                        yedekParca += 3;
                        printf("BASARILI (+3 Yedek Parca)\n");
                    } else {
                        printf("BASARISIZ (Eli bos donuldu)\n");
                    }

                    int kazaZar = rand() % 100;
                    printf("Tehlike Zar: %d / Esik: 10 -> ", kazaZar);
                    if (kazaZar < 10 || modulHasari > 70) {
                        saglik -= 12;
                        printf("YARALANDINIZ (-12 Saglik)\n");
                    } else {
                        printf("GUVENLI\n");
                    }
                }
                break;
            }
            case 'o': case 'O': { // Oksijen Uretimi
                int harcanacak;
                if (enerji < 10 || su < 2) {
                    printf("Yetersiz enerji (10) veya su (2)!\n");
                } else {
                    printf("Kullanilacak su (Mevcut %d): ", su);
                    scanf("%d", &harcanacak);
                    if (harcanacak > su || harcanacak < 2) {
                        printf("Gecersiz su miktari!\n");
                    } else {
                        int artik = harcanacak % 2; // Mod operatoru kontrolu
                        int kullanilan = harcanacak - artik;
                        su -= kullanilan;
                        oksijen += (kullanilan / 2) * 3;
                        enerji -= 10; turGecti = 1;
                        printf("%d su kullanildi, +%d oksijen uretildi. (Artik su: %d)\n",
                               kullanilan, (kullanilan / 2) * 3, artik);
                    }
                }
                break;
            }
            case 't': case 'T': { // Tamir (IF-ELSE IF-ELSE)
                if (enerji < 10 || yedekParca <= 0) {
                    printf("Yetersiz enerji veya yedek parca!\n");
                } else if (modulHasari <= 30) {
                    yedekParca -= 1; modulHasari -= 15; enerji -= 10; turGecti = 1;
                    printf("Hafif hasar onarildi (-1 Parca, -15 Hasar).\n");
                } else if (modulHasari <= 70) {
                    if (yedekParca >= 2) {
                        yedekParca -= 2; modulHasari -= 25; enerji -= 10; turGecti = 1;
                        printf("Orta hasar onarildi (-2 Parca, -25 Hasar).\n");
                    } else printf("Orta hasar icin 2 parca gerekli!\n");
                } else {
                    if (yedekParca >= 3) {
                        yedekParca -= 3; modulHasari -= 35; enerji -= 10; turGecti = 1;
                        printf("Agir hasar onarildi (-3 Parca, -35 Hasar).\n");
                    } else printf("Agir hasar icin 3 parca gerekli!\n");
                }
                break;
            }
            case 'd': case 'D': { // Durum Raporu (Tur harcamaz)
                printf("RAPOR -> Saglik:%d Enerji:%d Oksijen:%d Su:%d Parca:%d Hasar:%d Kilit:%d\n",
                       saglik, enerji, oksijen, su, yedekParca, modulHasari, kilitMuhurlu);
                if (oksijen < 25) printf("UYARI: Kritik oksijen!\n");
                if (saglik < 30) printf("UYARI: Kritik saglik!\n");
                if (modulHasari > 70) printf("UYARI: Kritik modul hasari!\n");
                if (oksijen >= 25 && saglik >= 30 && enerji >= 20 && modulHasari <= 70)
                    printf("TUM SISTEMLER NORMAL.\n");
                break;
            }
            case 'u': case 'U': { // Uyu / Dinlen (Ic ice IF)
                enerji += 25; oksijen -= 8; turGecti = 1;
                if (oksijen < 20) {
                    saglik -= 10;
                    printf("Dusuk oksijende uyudunuz! (-10 Saglik, +25 Enerji)\n");
                } else {
                    saglik += 15;
                    printf("Dinlendiniz. (+15 Saglik, +25 Enerji, -8 Oksijen)\n");
                }
                break;
            }
            case 'k': case 'K': { // Kum Firtinasi (FOR, break, continue)
                if (enerji < 10) {
                    printf("Yetersiz enerji! (En az 10 gerekli)\n");
                } else {
                    enerji -= 10; turGecti = 1;
                    int hasarTur = 0, kayipSaglik = 0, kayipOksijen = 0;

                    for (int i = 1; i <= firtinaTuru; i++) {
                        int zar = rand() % 100;
                        int esik = 50 + zorlukFark;
                        int carpan = (i % 2 == 0) ? 2 : 1; // Cift turlarda 2x hasar
                        printf("Tur %d -> Zar: %d / Esik: %d ", i, zar, esik);

                        if (zar < esik) {
                            hasarTur++;
                            int olay = zar % 3;
                            if (olay == 0) {
                                saglik -= 5 * carpan; kayipSaglik += 5 * carpan;
                                printf("-> Can kaybi (-%d)\n", 5 * carpan);
                            } else if (olay == 1) {
                                if (kilitMuhurlu == 1) {
                                    printf("-> Kilit muhurlu, sizinti atlandi (continue).\n");
                                    continue;
                                }
                                oksijen -= 6 * carpan; kayipOksijen += 6 * carpan;
                                printf("-> Oksijen sizintisi (-%d)\n", 6 * carpan);
                            } else {
                                modulHasari += 7 * carpan;
                                printf("-> Modul hasari (+%d)\n", 7 * carpan);
                            }
                        } else {
                            printf("-> Hasar yok.\n");
                        }
                        if (saglik <= 0 || oksijen <= 0) break; // Olumde donguyu kir
                    }
                    printf("FIRTINA OZETI -> Hasarli Tur:%d | Kayip Saglik:%d | Kayip Oksijen:%d\n",
                           hasarTur, kayipSaglik, kayipOksijen);
                }
                break;
            }
            case 'h': case 'H': { // Hava Kilidi (DO-WHILE)
                if (kilitMuhurlu == 1) {
                    printf("Kilit zaten muhurlu.\n");
                } else if (enerji < 5) {
                    printf("Yetersiz enerji!\n");
                } else {
                    char sifre = 'A' + (gun % 26), tahmin;
                    int deneme = 0, basari = 0;
                    printf("IPUCU: 'A' harfinden gun sayisi (%d) kadar ilerideki harf.\n", gun);

                    do {
                        printf("Sifre (Kalan hak %d): ", 3 - deneme);
                        scanf(" %c", &tahmin);
                        if (tahmin >= 'a' && tahmin <= 'z') tahmin -= ('a' - 'A');
                        deneme++;

                        if (tahmin == sifre) {
                            basari = 1; kilitMuhurlu = 1;
                            printf("DOGRU! Hava kilidi muhurlendi.\n");
                        } else {
                            enerji -= 5;
                            printf("YANLIS (-5 Enerji)! %s\n", (tahmin < sifre) ? "Ileri git." : "Geri git.");
                        }
                    } while (basari == 0 && deneme < 3);

                    if (basari == 0) {
                        modulHasari += 20;
                        printf("3 hak bitti! Modul hasari +20 artti.\n");
                    }
                    turGecti = 1;
                }
                break;
            }
            case 'q': case 'Q':
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Tanimsiz komut! Tur harcanmadi.\n");
        }

        // 0-100 Sinirlandirma Kontrolleri
        if (saglik < 0) saglik = 0; else if (saglik > 100) saglik = 100;
        if (enerji < 0) enerji = 0; else if (enerji > 100) enerji = 100;
        if (oksijen < 0) oksijen = 0; else if (oksijen > 100) oksijen = 100;
        if (modulHasari < 0) modulHasari = 0; else if (modulHasari > 100) modulHasari = 100;

        // Zaman Akisi (Her 3 gecerli turda 1 yeni gun)
        if (turGecti == 1) {
            tur++;
            if (tur % 3 == 0) {
                gun++; oksijen -= 8;
                if (modulHasari > 70) saglik -= 5;
                if (oksijen < 0) oksijen = 0;
                if (saglik < 0) saglik = 0;
                printf(">>> YENI GUN (%d)! -8 Oksijen.\n", gun);
            }
        }

        // Oyun Sonu Kontrolleri
        if (saglik <= 0 || oksijen <= 0) {
            printf("\nKAYBETTINIZ! Yasam destek tukendi.\n");
            break;
        }
        if (gun > 15) {
            gun = 15;
            printf("\nKAZANDINIZ! Kurtarma ekibi 15. gunde ulasti.\n");
            break;
        }
    } while (komut != 'q' && komut != 'Q');

    // Sonuc Raporu
    int puan = (gun * 100) + saglik + oksijen - modulHasari;
    printf("\n=== SONUC RAPORU ===\nGun: %d | Tur: %d | Saglik: %d | Oksijen: %d | Hasar: %d | PUAN: %d\n",
           gun, tur, saglik, oksijen, modulHasari, puan);

    return 0;
}
