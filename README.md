# 🚀 Mars Kolonisi Yaşam Destek Simülatörü

C programlama dilinin temel kontrol yapıları, döngüleri, aritmetik ve mantıksal operatörleri kullanılarak geliştirilmiş metin tabanlı hayatta kalma simülasyonudur. Oyuncu, Mars'taki bir araştırma istasyonunda tek başına kalmış bir mühendisi yöneterek kurtarma ekibi gelene kadar **15 gün** hayatta kalmaya çalışır.

---

## 📋 Özellikler ve Oyun Mekaniği

* **Zorluk Seviyeleri (`switch-case`):** Kolay (`K`), Normal (`N`) ve Zor (`Z`) olmak üzere üç farklı zorluk seviyesi bulunur. Seçilen seviye başlangıç kaynaklarını, kum fırtınası süresini ve olay eşiklerini dinamik olarak değiştirir.
* **Durum Takibi:** Sağlık, Enerji, Oksijen, Su, Yedek Parça, Modül Hasarı, Hava Kilidi Durumu, Gün ve Tur sayacı anlık olarak takip edilir. Tüm kritik değerler `0 - 100` aralığında sınırlandırılmıştır.
* **Zaman Akışı:** Geçerli her 3 turda bir (`tur % 3 == 0`) yeni güne geçilir ve günlük yaşam destek tüketimi uygulanır.
* **Dinamik Şifreleme:** Hava kilidi şifresi sabit değildir; o anki gün sayısından ASCII aritmetiği (`'A' + (gun % 26)`) ile türetilir.

---

## 🎮 Komut Listesi

Simülasyon büyük/küçük harf duyarsız tek karakterli komutlarla yönetilir:

| Komut | İşlev | Açıklama |
| :---: | :--- | :--- |
| **`G`** | Keşif Görevi | Enerji ve oksijen harcayarak su veya yedek parça arar; tehlike zarına göre yaralanma riski taşır. |
| **`O`** | Oksijen Üretimi | Her 2 birim suyu 3 birim oksijene dönüştürür. Tek sayı girilirse 1 birim artık su depoda kalır (`%` operatörü). |
| **`T`** | Tamir | Modül hasarını hafif, orta ve ağır olarak 3 kademede değerlendirip yedek parça karşılığında onarır. |
| **`D`** | Durum Raporu | Tur harcamadan tüm istatistikleri ve kritik seviye uyarılarını görüntüler. |
| **`U`** | Uyu / Dinlen | Enerji ve sağlık yeniler; ancak oksijen 20'nin altındaysa sağlık kaybına yol açar. |
| **`K`** | Kum Fırtınası | `for` döngüsü ile fırtına simüle eder. Çift turlarda hasar 2 katına çıkar; kilit mühürlüyse sızıntı atlanır. |
| **`H`** | Hava Kilidi Şifresi | `do-while` döngüsü ile en fazla 3 denemede şifreyi çözerek hava kilidini mühürler. |
| **`Q`** | Çıkış | Simülasyonu sonlandırır ve sonuç raporunu ekrana yazdırır. |

---

## 🛠️ Kurulum ve Çalıştırma

Projeyi yerel bilgisayarınızda derleyip çalıştırmak için herhangi bir C derleyicisi (GCC, MinGW, Dev-C++, Code::Blocks vb.) kullanabilirsiniz.

### Terminal (GCC) ile Çalıştırma:
```bash
# Repoyu klonlayın
git clone https://github.com/kullaniciadi/mars-kolonisi-simulatoru.git

# Proje dizinine gidin
cd mars-kolonisi-simulatoru

# Kodu derleyin
gcc mars_kolonisi.c -o mars_kolonisi

# Programı çalıştırın
./mars_kolonisi
```

---

## 📊 Puanlama Sistemi

Oyun kazanılarak (15. günün tamamlanması), kaybedilerek (sağlık veya oksijenin 0'a düşmesi) ya da çıkış yapılarak sona erdiğinde aşağıdaki formül ile sonuç puanı hesaplanır:

$$\text{Puan} = (\text{Gün} \times 100) + \text{Sağlık} + \text{Oksijen} - \text{Modül Hasarı}$$

---

## 👤 Geliştirici

* **Ad Soyad:** [Adınız Soyadınız]
* **Bölüm:** Yazılım Mühendisliği (1. Sınıf)
* **Ders:** Algoritma ve Programlama