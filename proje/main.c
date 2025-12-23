#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Yurttan izin almaya, yeni kayýt yapmaya ve profil fotoðrafý güncellemeye yarayan bir sistem. Sistemin baþlýk kýsmý en üstte yer almaktadýr.
 Yeni kayýt için 1,yeni izin için 2, yeni profil fotoðrafý için 3 tuþlamasýyla sistem baþlamaktadýr. 
1 Tuþlamasý yapýlýp yeni kayýt için ad,soyad, doðum yýlý, tc bilgileri istenmektedir 
2  Tuþlamasý yapýldýðýnda  Ad Soyad Yaþ bilgileri alýnacaktýr (Yýl hesaplamasýmevcut yýl girdisi alýnarak yapýlacaktýr 1700 yýlý öncesi ve 2025 sonrasý yýllar dikkate alýnmayacaktýr). 
Reþit deðilse veli numarasý 10 haneden oluþacak ve kontrol edilecektir. 
Yeni izin oluþturulurken izin sebebi ve izin tarihi
istenmektedir toplam 45 gün izin hakký vardýr.Ýzin alýndýkça hak azalmaktadýr.Kalan hak ekrana yazdýrýlacaktýr. 
Öðrenci tek seferde en  fazla 7 gün izin alabilmektedir. 
3 Tuþlamasý yapýlýnca Profil fotoðrafý güncellemesi fotoðraf yükleme iþlemi yapýlamadýðý için geçici olarak kapalý gösterilecektir.
0 Tuþlamasý yapýldýðýnda sistem kapanmaktadýr.
*/

void baslikGoster();
void adSoyadAl(char ad[], char soyad[], FILE *dosya);
void tcDogrula(char tc[], FILE *dosya);
int yasHesapla(int dogumYili, int mevcutYil);
int menu[] = {1, 2, 3};


int main() {
  FILE *dosya;
  dosya = fopen("veriler3.txt", "a+");
  
  int dogumYili, islem, mevcutYil, yas, i;
  int kalanHak = 45;
  char ad[30], soyad[30], tc[12], veliNo[12], izinNedeni[200];
  char devamSecimi;

  do 
{
    baslikGoster();
    printf("Seciminiz:");
    scanf("%d", &islem);

    if (islem == menu[0]) 
	  {
      fprintf(dosya, "\n--- YENI KAYIT ---\n");
      adSoyadAl(ad, soyad, dosya);

      while (1) 
	  {
        printf("Dogum Yiliniz: ");
        scanf("%d", &dogumYili);
        if (dogumYili < 1700 || dogumYili > 2026)
          printf("Hatali dogum yili girdiniz\n");
        else
          break;
      }
      fprintf(dosya, "Dogum Yili: %d\n", dogumYili);

      tcDogrula(tc, dosya);

      fprintf(dosya, "Kayit Durumu: Basarili\n");
      printf("\n Kayit basariyla tamamlandi.\n");
    }

    else if (islem == menu[1]) 
	  {
      fprintf(dosya, "\n--- IZIN TALEBI ---\n");
      adSoyadAl(ad, soyad, dosya);

      while (1) 
	  {
        printf("Dogum Yiliniz: ");
        scanf("%d", &dogumYili);
        if (dogumYili < 1700 || dogumYili > 2026)
        printf("Hatali dogum yili girdiniz\n");
        else
          break;
      }
      fprintf(dosya, "Dogum Yili: %d\n", dogumYili);

      while (1) 
	  {
        printf("Icinde bulundugumuz yil: ");
        scanf("%d", &mevcutYil);
        if (mevcutYil < 2025)
          printf("Hatali yil girdiniz\n");
        else
          break;
      }

      yas = yasHesapla(dogumYili, mevcutYil);
      fprintf(dosya, "Yas: %d\n", yas);

      if (yas < 18) 
	  {
        printf("Yasiniz 18'den kucuk. \n");
        do 
			{
          	printf("Veli Telefon (10 hane): ");
          	scanf("%s", veliNo);
        	} 
			while (strlen(veliNo) != 10);        
		fprintf(dosya, "Veli Telefon: %s\n", veliNo);
      }

      fprintf(dosya, "Izin Tarihleri:\n");
      for (i=1;i<=7;i++) 
	  {
        char tarih[11];
        printf("%d. gunun tarihini girin (GG/AA/YYYY): ",i);
        scanf("%s", tarih);
        fprintf(dosya, " %d. Gun: %s\n", i, tarih);

        kalanHak--;

        printf("Baska gun ekleyecek misiniz? (E/H): ");
        scanf(" %c", &devamSecimi);

        if (devamSecimi == 'H' || devamSecimi == 'h')
          break;
      }

      printf("Izin Nedeni: ");
      scanf(" %s", izinNedeni);
      fprintf(dosya, "Izin Nedeni: %s\n", izinNedeni);
      fprintf(dosya, "Kalan Izin Hakki: %d\n", kalanHak);
      printf("\n Islem basarili. Kalan izin hakkiniz: %d\n", kalanHak);
    }

    else if (islem == menu[2]) 
	{
      printf("\n Sistem bakimda. Fotograf guncelleme su an yapilamiyor lütfen "
             "daha sonra tekrar deneyiniz.\n");
    }

  } while (islem != 0);

  fclose(dosya);
  return 0;
}

void baslikGoster() {
  printf("\n============================\n");
  printf("    YURT OTOMASYON SISTEMI   \n");
  printf("============================\n");
  printf("1. Yeni Kayit\n");
  printf("2. Izin Al\n");
  printf("3. Profil Guncelle\n");
  printf("0. Cikis\n");
}

void adSoyadAl(char ad[], char soyad[], FILE *dosya) {
  printf("Adiniz: ");
  scanf(" %s", ad);
  printf("Soyadiniz: ");
  scanf(" %s", soyad);
  fprintf(dosya, "Ad: %s\n", ad);
  fprintf(dosya, "Soyad: %s\n", soyad);
}

void tcDogrula(char tc[], FILE *dosya) {
  while (1) {
    printf("TC Kimlik No (11 hane): ");
    scanf(" %s", tc);
    if (strlen(tc) == 11)
      break;
    printf("TC No 11 hane olmalidir!\n");
  }
  fprintf(dosya, "TC Kimlik No: %s\n", tc);
}

int yasHesapla(int dogumYili, int mevcutYil) { return mevcutYil - dogumYili; }
