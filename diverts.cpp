#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include"structure.h"
#include"prototype.h"

void sauvgarde(liste l,char nom[25])
{
	FILE* stock;
	liste sauv;


	stock=fopen(nom,"w");

	sauv=(cellule *)malloc(sizeof(cellule));
	sauv=l;

	while(sauv!=NULL)
	{
		fwrite(&sauv->voit,sizeof(voiture),1,stock);
		sauv=sauv->suivant;
	}

	fclose(stock);


	msgSauvCharg("Sauvgarde des type");
}

liste chargementType(char *nom)
{
	FILE* stock;
	liste charge,retour;
	cellule *p;
	voiture voit;

	p=(cellule *)malloc(sizeof(cellule));

	retour=(cellule *)malloc(sizeof(cellule));
	retour=NULL;
	stock=fopen(nom,"r");

	if(stock!=NULL)
	{
		while(fread(&voit,sizeof(voiture),1,stock))
		{
			charge=(cellule *)malloc(sizeof(cellule));
			charge->voit=voit;
			charge->suivant=NULL;

			if (retour==NULL)
				retour=charge;
			else
			{
				p=retour;
				while(p->suivant!=NULL)
					p=p->suivant;
				p->suivant=charge;
			}
		}
	}

	msgSauvCharg("Chargement des types");
	return retour;
}

void SauvgardeMatricule(listeMatricul l,char *nom)
{
	FILE *fp;

	fp=fopen(nom,"w");

	while(l!=NULL)
	{
		fwrite(&l->mat,sizeof(matriculVoiture),1,fp);
		l=l->suivant;
	}


	fclose(fp);

	msgSauvCharg("Sauvgarde des matriculs");
}

listeMatricul ChargementMatricul(char *nom)
{
	FILE *stock;
	matriculVoiture mat;
	listeMatricul l,parc,retour;

	stock=fopen(nom,"r");

	retour=(listeMatricul )malloc(sizeof(listeMatricul));
	parc=(listeMatricul )malloc(sizeof (listeMatricul));
	retour=NULL;

	if(stock!=NULL)
	{
		while(fread(&mat,sizeof(matriculVoiture),1,stock))
		{
			l=(listeMatricul )malloc(sizeof(listeMatricul));
			l->mat=mat;
			l->suivant=NULL;

			if(retour==NULL)
				retour=l;
			else
			{
				parc=retour;
				while(parc->suivant!=NULL)
					parc=parc->suivant;
				parc->suivant=l;
			}
		}
	//	fclose(stock);
	}

	msgSauvCharg("Chargement des matriculs");

	return retour;
}

void sauvgardeClient(liste_client l,char *nom)
{
	FILE *fp;

	l=RetourTete(l);

	fp=fopen(nom,"w");

	while(l!=NULL)
	{
		fwrite(&l->person,sizeof(client),1,fp);
		l=l->suivant;
	}

	fclose(fp);

	msgSauvCharg("Sauvgarde des clients");
}
liste_client chargementClient(char *nom)
{
	FILE *fp;
	client person;
	liste_client parc,retour;

	fp=fopen(nom,"r");

	retour=(liste_client)malloc(sizeof(liste_client));
	parc=(liste_client)malloc(sizeof(liste_client));
	retour=NULL;


	if(fp!=NULL)
	{
		while(fread(&person,sizeof(client),1,fp))
		{
			retour=InsererEnFinClient(retour,person);
		}

	}

	msgSauvCharg("Chargement des clients...");

	return retour;
}

void SauvgardeContrat(ListeContrat l,char *nom)
{
	FILE *fp;

	fp=fopen(nom,"w");

	while(l!=NULL)
	{
		fwrite(&l->cont,sizeof(contrat),1,fp);
		l=l->suivant;
	}


	fclose(fp);


	msgSauvCharg("Sauvgarde des contrats");

}

ListeContrat chargementContrat(char *nom)
{
	FILE* fp;
	contrat cont;
	ListeContrat l,parc,retour;

	fp=fopen(nom,"r");

	retour=(ListeContrat)malloc(sizeof(ListeContrat));
	parc=(ListeContrat)malloc(sizeof(ListeContrat));
	retour=NULL;


	if(fp!=NULL)
	{
		while(fread(&cont,sizeof(contrat),1,fp))
		{
			l=(ListeContrat)malloc(sizeof(ListeContrat));
			l->cont=cont;
			l->suivant=NULL;
			if(retour==NULL)
				retour=l;
			else
			{
				parc=retour;
				while(parc->suivant!=NULL)
					parc=parc->suivant;
				parc->suivant=l;
			}
		}

	}

	msgSauvCharg("Chargement des contrats");

	return retour;
}

void SauvgardeGeneral(int verif,liste stock_voiture,liste_client lesclients,ListeContrat lescontrat,listeMatricul stock_matricul)
{
	int tmp;

	if(verif==9)
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements ?     \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();

			if(tmp==111)
			{
				sauvgarde(stock_voiture,"type.txt");
				SauvgardeMatricule(stock_matricul,"matricul.txt");
				sauvgardeClient(lesclients,"client.txt");
				SauvgardeContrat(lescontrat,"contrat.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

	if(verif==1)
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements       \xb3");
			printf("\n                    \xb3     effectuer sur les contrat ?      \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();

			if(tmp==111)
			{
				SauvgardeContrat(lescontrat,"contrat.txt");
				sauvgardeClient(lesclients,"client.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

	if(verif==2)
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements       \xb3");
			printf("\n                    \xb3     effectuer sur les voitures ?     \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();

			if(tmp==111)
			{
				SauvgardeMatricule(stock_matricul,"matricul.txt");
				sauvgarde(stock_voiture,"type.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

	if(verif==3)
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\n                    \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n                    \xb3     Sauvgarder les changements       \xb3");
			printf("\n                    \xb3     effectuer sur les clients ?      \xb3");
			printf("\n                    \xb3          oui(o)    non(n)            \xb3");
			printf("\n                    \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
			tmp=getch();

			if(tmp==111)
			{
				sauvgardeClient(lesclients,"client.txt");
			}
			if(tmp==110)
				MessageUrgence("Pas de sauvgarde");
		}while((tmp!=111)&&(tmp!=110));
	}

}
void MessageUrgence(char *msg)
{
	int i;


	for(i=0;i<2;i++)
	{

		system("cls");
		Sleep(500);
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\a\a%s",msg);
		Sleep(500);
	}
}

void  msgSauvCharg(char *msg)
{
	int j;

	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t%s",msg);
	for(j=0;j<=5;j++)
	{
		Sleep(120);
		printf(".");
	}

}

date convertDate()
{
	char *dat_buff;
	int tmp;
	date d;

	dat_buff=(char *)malloc(sizeof(char));
	_strdate(dat_buff);
	tmp=atoi(dat_buff);

	d.mm=tmp/1000000;

	d.jj=((tmp%1000000)/1000);

	d.aa=((tmp%1000000)%1000)+2000;

	return d;

}
void A_Propos()
{


	EnTete();


	printf("\n\t\tECOLE SUPERIEUR DE TECHNOLOGIE ET D'INFORMTIQUE");

	printf("\n\n\n\t\tMini projet  : Gestion location de voiture");

	printf("\n\n\n\t\tRealiser par :\tREZGUI Mohamed");
	printf("\n\n\t\t              \tMLAOUHI Hamdi");

	printf("\n\n\n\t\tEncadrer par :\tMr. KADRI *****");
	printf("\n\n\t\t              \tMr. BENNARI *****");

	printf("\n\n\n\n\t\t\tAnnee universitaire   2005/2006");

	printf("\n\n");
	system("pause");


}

void Statistique(liste typ,liste_client clt,listeMatricul mat,ListeContrat crt)
{
	int NBtyp=0,NBmat=0,NBcrt=0,NBclt=0,total=0,NBvoit=0,NBvoitl=0,cout=0;

	liste l;
	liste_client client;
	ListeContrat contrat;
	listeMatricul matricul;


	system("cls");

	EnTete();

	l=(liste)malloc(sizeof(liste));

	l=typ;

	while(l!=NULL)
	{
		NBtyp++;
		l=l->suivant;
	}

	matricul=(listeMatricul)malloc(sizeof(listeMatricul));
	matricul=mat;

	while(matricul!=NULL)
	{
		NBvoit++;
		if(strcmp(&matricul->mat.stats,"l")==0)
			NBvoitl++;
		matricul=matricul->suivant;
	}

	client=(liste_client)malloc(sizeof(liste_client));

	client=RetourTete(clt);
	while(client!=NULL)
	{
		NBclt++;
		client=client->suivant;
	}


	contrat=(ListeContrat)malloc(sizeof(ListeContrat));

	contrat=crt;

	while(contrat!=NULL)
	{
		NBcrt++;
		cout+=contrat->cont.cout;
		contrat=contrat->suivant;
	}

	printf("\n\n\n \xda");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4");
	printf("\xbf\n");

	printf(" \xb3         \xb3");
	printf("    TYPE   \xb3");
	printf("  VOITURE  \xb3");
	printf("  CONTRAT  \xb3");
	printf("   CLIENT  \xb3");
	printf("  COUT LOCATION  \xb3");

	printf("\n \xc3");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4");
	printf("\xb4\n");

	printf(" \xb3  TOTALE \xb3");
	printf("   %3.0d     \xb3",NBtyp);
	printf("   %3.0d     \xb3",NBvoit);
	printf("   %3.0d     \xb3",NBcrt);
	printf("   %3.0d     \xb3",NBclt);
	printf("    %7.0d      \xb3",cout);

	printf("\n \xc0");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1");
	printf("\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4");
	printf("\xd9\n");



	printf("\n\n");
	system("pause");
}


