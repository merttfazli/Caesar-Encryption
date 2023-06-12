#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


struct Bilgi{
char Ad_Soyad[500];
int No;
int parola;
FILE* dosya;
}bilgiler;

bool DosyaYaz();
char* DosyaOku();
bool DosyaSil();
bool Sifrele(char* bilgi,int key);
bool SifreCozme(int key);
int AsalHesaplama();

int main(void) {
	
	int key=8;//Ogrenci Numaramin son rakami
	bilgiler.dosya=fopen("sifrelimetin.txt","w+");
	printf("-----------   Bilgileri Doldur   -------------\n");
	
	printf("Ogrenci Adi Soyadi: ");
	fgets(bilgiler.Ad_Soyad,sizeof(bilgiler.Ad_Soyad),stdin);
	
	printf("Ogrenci No: ");
	scanf("%d",&bilgiler.No);
	
	printf("Parola Gir: ");
	scanf("%d",&bilgiler.parola);
	
	printf("-----------   Sifreleme  -------------\n");
	bool kontrol = Sifrele(bilgiler.Ad_Soyad,key);
	
	if(kontrol==true){
		printf("Sifreleme Basarili \n");
	}
	else
	{
		printf("Sifreleme Basarisiz \n");
	}
	printf("-----------   Sifre Cozme  -------------\n");
	printf("Sifreyi Cozmek Icin Parola Giriniz: ");
	int sayi;
	scanf("%d",&sayi);
	if(sayi==AsalHesaplama())
	{
		SifreCozme(key);
	}
	else
	{
		printf("Hatali Sifre Girdiniz: ");
	}
	fclose(bilgiler.dosya);
	return 0;
}

int AsalHesaplama(){
	int y = 0,i=2;
	
	while(bilgiler.No>1)	{
  		while(bilgiler.No % i == 0)
  		{	
			if(i > y)
				y = i;
   			bilgiler.No = bilgiler.No/ i;
  		}
  		i++;
 	}
	return y;
}
bool DosyaYazdirma(char* bilgi)
{
	fputs(bilgi,bilgiler.dosya);
	return true;
}

char* DosyaOku(){
	
	return fgets(bilgiler.Ad_Soyad,sizeof(bilgiler.Ad_Soyad),bilgiler.dosya);
}

bool Sifrele(char* bilgi,int key){
bool chk = false;
    char *temp = bilgi;
    while(*temp != '\0')
    {
        if (isupper(*temp))
        {
            *temp = ((*temp - 65 + key) % 26) + 65;
        }
        else if (islower(*temp))
        {
            *temp = ((*temp - 97 + key) % 26) + 97;
        }
        temp++;
    }
    chk=DosyaYazdirma(bilgi);
    rewind(bilgiler.dosya);
    return chk;
}

bool SifreCozme(int key){

    char *temp = DosyaOku();
    while(*temp != '\0')
    {
        if (isupper(*temp))
        {
            *temp = ((*temp - 65 + (26 - key)) % 26) + 65;
        }
        else if (islower(*temp))
        {
            *temp = ((*temp - 97 + (26 - key)) % 26) + 97;
        }
        temp++;
    }
    printf("\nCozumlenmis bilgi: %s", bilgiler.Ad_Soyad);
}
bool DosyaSil(){
	fclose(bilgiler.dosya);
	remove("sifrelimetin.txt");
	return true;
}
