#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"structure.h"
#include"prototype.h"

int ConditionLocation(client cl)
{
	int tmp;
	int aa,mm,jj;

	if(cl.age>=25)
	{
		tmp=cl.date_permi;

		jj=tmp/1000000;
		mm=((tmp%1000000)/10000);
		aa=((tmp%1000000)%10000);

		if((convertDate().aa+2000)-aa>=2)
			return 0;
	}

	return 1;

}

ListeContrat saisieContrat(cellule_client *person,listeMatricul l)
{
	CelluleContrat *cel;
	Matricul *mat;
	int verif=0;
	char typ[5];

	if(ConditionLocation(person->person)!=0)
		return NULL;

	EnTete();

	mat=(Matricul *)malloc(sizeof(Matricul));
	cel=(CelluleContrat *)malloc(sizeof(CelluleContrat));

	strcpy(cel->cont.nom,person->person.nom);
	strcpy(cel->cont.pnom,person->person.prenom);

	cel->cont.num=generationCode();

	printf("\n\tNumero contrat : %.0f",cel->cont.num);

	do
	{
		if(verif==3)
			goto END_SAISIE;

		printf("\n\n\tType Voiture louee     :  ");
		scanf("%s",&typ);
		mat=RechercheVoitureLibre(l,typ);
		if(mat==NULL)
		{
			printf("\n\t\tPas de voiture disponible");
			verif++;
		}

	}while(mat==NULL);

	printf("\n\tVoiture disponible : %i TUN %i",mat->mat.matricule/10000,mat->mat.matricule%10000);
	cel->cont.voit_loue=mat->mat.matricule;
	do
	{
		printf("\n\tType de location (km/jr) :  ");
		scanf("%s",&cel->cont.type);
	} while((strcmp(cel->cont.type,"km")!=0)&&(strcmp(cel->cont.type,"jr")!=0));

	if(strcmp(cel->cont.type,"km")==0)
	{
		cel->cont.debu=mat->mat.kilometrage;
		printf("\n\t\tKilometrage actuel du vehicule  :  %d",cel->cont.debu);
		cel->cont.fin=0;
	}
	else
	{
		printf("\n\tDate du debut    :  ");
		scanf("%d",&cel->cont.debu);

		printf("\n\tDate retour      :  ");
		scanf("%d",&cel->cont.fin);
	}

	printf("\n\tAgence de location   :  ");
	scanf("%s",&cel->cont.agencDepar);

	printf("\n\t\tLes options......");

	do
	{
		printf("\n\t2eme conducteur (o/n) :");
		scanf("%s",&cel->cont.supcond);
	} while((cel->cont.supcond!='o')&&(cel->cont.supcond!='n'));

	do
	{
		printf("\n\tLivraison  (o/n) :  ");
		scanf("%s",&cel->cont.liv);
	}while((cel->cont.liv!='o')&&(cel->cont.liv!='n'));

	do
	{
		printf("\n\tSiege bebe (o/n) :  ");
		scanf("%s",&cel->cont.bebe);
	} while((cel->cont.bebe!='o')&&(cel->cont.bebe!='n'));


	do
	{
		printf("\n\n\t\tValider location oui(o) / non(n)");
		verif=getch();
	}while((verif!=111)&&(verif!=110));
	if(verif==110)
		return NULL;

	strcpy(cel->cont.agencRetour,"TMP");

	cel->cont.cout=0;

	person->person.ctr=cel->cont.num;

	mat->mat.stats='l';

	return cel;

	END_SAISIE :
	MessageUrgence("Contrat Annule");
	return NULL;

}

ListeContrat RechercheContrat(ListeContrat l)
{
	ListeContrat parc;
	int mat;
	char nom[20],pnom[20];

	parc=(ListeContrat)malloc(sizeof(ListeContrat));

	printf("\n\tMatricul voiture louee   :  ");
	scanf("%d",&mat);
	printf("\n\tNom      :  ");
	scanf("%s",&nom);
	printf("\n\tPrenom   :  ");
	scanf("%s",&pnom);

	parc=l;
	while(parc!=NULL)
	{
		if(parc->cont.voit_loue==mat)
			if(strcmp(parc->cont.nom,nom)==0)
				if(strcmp(parc->cont.pnom,pnom)==0)
					return parc;

		parc=parc->suivant;

	}

	return NULL;

}

void RetourContrat(ListeContrat lcr,listeMatricul lm,liste l)
{
	ListeContrat crt;
	listeMatricul mat;
	liste typ;

	int supcond=20;
	int bebe =15;
	int livraison =20;

	crt=(ListeContrat)malloc(sizeof(ListeContrat));
	mat=(listeMatricul)malloc(sizeof(listeMatricul));
	typ=(liste)malloc(sizeof(liste));

	EnTete();

	crt=RechercheContrat(lcr);

	if(crt==NULL)
		MessageUrgence("Contrat non-trouve");
	else
	{
		crt->cont.cout=0;
		mat=rechecherMatricul(lm,crt->cont.voit_loue);
		typ=RechercheTypeVoiture(l,mat->mat.type);

		printf("\n\tContrat numero   :  %.0f",crt->cont.num);

		printf("\n\tAgence de retour   :  ");
		scanf("%s",&crt->cont.agencRetour);

		if(strcmp(crt->cont.type,"km")==0)
		{
			printf("\n\tKilometrage retour  :  ");
			scanf("%d",&crt->cont.fin);
			 mat->mat.kilometrage=crt->cont.fin;
		}
		else
		{
			printf("\n\tDuree (jour)  :  ");
			scanf("%d",&crt->cont.fin);
			printf("\n\tKilometrage retour  :  ");
			scanf("%d",&mat->mat.kilometrage);
		}

		if(crt->cont.bebe=='o')
			crt->cont.cout+=bebe;
		if(crt->cont.liv=='o')
			crt->cont.cout+=livraison;
		if(crt->cont.supcond=='o')
			crt->cont.cout+=supcond;

		if(strcmp(crt->cont.type,"km")==0)
			crt->cont.cout+=(crt->cont.fin-crt->cont.debu)*typ->voit.prixKilo;
		else
			crt->cont.cout+=crt->cont.fin*typ->voit.prixJour;

		printf("\n\tCout   :  %d\n\n",crt->cont.cout);

		strcpy(&mat->mat.stats,"n");

	}


	system("pause");
}
void AfficheContrat(contrat crt)
{
	EnTete();

	printf("\n\tN\xf8 du contrat  :  %.0f",crt.num);

	printf("\n\n\tAgence de location :  %s",crt.agencDepar);
	printf("\t\tAgence de retour   :  %s",crt.agencRetour);

	printf("\n\n\tNom locataire      :  %s",crt.nom);
	printf("\t\tType de location   :  %s",crt.type);

	printf("\n\n\tPrenom             :  %s",crt.pnom);
	printf("\t\tVoiture loue       :  %dTUN%d",crt.voit_loue/10000,crt.voit_loue%10000);

	printf("\n\n\tDebut              :  %d",crt.debu);
	printf("\t\tFin                :  %d",crt.fin);

	printf("\n\n\tLes options...");
	printf("\n\n\tLivraison  : %c\t\tSup.conducteur  : %c\t\tSiege beb\x82  : %c",crt.liv,crt.supcond,crt.bebe);

	printf("\n\n\tCout location    :   %d TTC",crt.cout);

	printf("\n\n");

	system("pause");

}


ListeContrat SupprimerContrat(ListeContrat l,CelluleContrat *supp)
{
	ListeContrat parc;



	if(supp==l)
	{
		l=l->suivant;

	}

	parc=(CelluleContrat *)malloc(sizeof(CelluleContrat));

	parc=l;
	while((parc!=NULL)&&(parc->suivant!=supp))
		parc=parc->suivant;

	if(parc->suivant==supp)
	{
		parc->suivant=supp->suivant;

	}

	return l;

}
ListeContrat ModifierContrat(ListeContrat l,listeMatricul m)
{
	ListeContrat rech;
	listeMatricul mat;
	contrat crt;
	int verif=0;


	if(l==NULL)
	{
		MessageUrgence("Pas de contrat disponible");
		return l;
	}

	rech=(ListeContrat)malloc(sizeof(ListeContrat));

	rech=RechercheContrat(l);

	if(rech==NULL)
	{
		MessageUrgence("Contrat non-trouve");
		return l;
	}

	mat=(listeMatricul)malloc(sizeof(listeMatricul));

	mat=rechecherMatricul(m,rech->cont.voit_loue);
	strcpy(&mat->mat.stats,"n");
	strcpy(crt.nom,rech->cont.nom);
	strcpy(crt.pnom,rech->cont.pnom);
	crt.num=rech->cont.num;
	do
	{
		if(verif==2)
			goto END_SAISIE;

		printf("\n\n\tVoiture louee     :  ");
		scanf("%d",&crt.voit_loue);
		mat=rechecherMatricul(m,crt.voit_loue);
		if((mat->mat.stats=='l')&&(mat!=NULL))
		{
			printf("\n\t\t\tVoiture louee");
			verif++;
		}

	}while((mat!=NULL)&&(mat->mat.stats!='n'));

	do
	{
		printf("\n\tType de location  :  ");
		scanf("%s",&crt.type);
	} while((strcmp(crt.type,"km")!=0)&&(strcmp(crt.type,"jr")!=0));

	if(strcmp(crt.type,"km")==0)
	{
		crt.debu=mat->mat.kilometrage;
		printf("\n\t\tKilometrage actuel du vehicule  :  %d",crt.debu);
	}
	else
	{
		printf("\n\tDate du debut    :  ");
		scanf("%d",&crt.debu);

		printf("\n\tDate retour      :  ");
		scanf("%d",&crt.fin);
	}

	printf("\n\tAgence de location   :  ");
	scanf("%s",&crt.agencDepar);

	printf("\n\t\tLes options......");

	do
	{
		printf("\n\t2eme conducteur :  ");
		scanf("%s",&crt.supcond);
	} while((crt.supcond!='o')&&(crt.supcond!='n'));

	do
	{
		printf("\n\tSiege bebe      :  ");
		scanf("%s",&crt.bebe);
	} while((crt.bebe!='o')&&(crt.bebe!='n'));

	do
	{
		printf("\n\tLivraison       :  ");
		scanf("%s",&crt.liv);
	}while((crt.liv!='o')&&(crt.liv!='n'));

	do
	{
		printf("\n\n\t\tValider location oui(o) / non(n)");
		verif=getch();
	}while((verif!=111)&&(verif!=110));
	if(verif==110)
		return l;

	strcpy(crt.agencRetour,rech->cont.agencRetour);

	crt.cout=0;

	mat->mat.stats='l';
	rech->cont=crt;

	MessageUrgence("Contrat modifie");
	return l;

END_SAISIE:
	MessageUrgence("Modification annule");
	return l;

}
float generationCode()
{
	char *dat_buff;
	int jj,mm,aa,tmp2,tmp;
	float code;

	dat_buff=(char *)malloc(sizeof (char));
	_strdate(dat_buff);

	strncpy(dat_buff+2,"0",1);
	strncpy(dat_buff+5,"0",1);
	tmp=atoi(dat_buff);///************

	mm=tmp/1000000;
	jj=((tmp%1000000)/1000);
	aa=((tmp%1000000)%1000);
	tmp=jj*10000+mm*100+aa;

	_strtime(dat_buff);
	strncpy(dat_buff+2,"0",1);
	strncpy(dat_buff+5,"0",1);
	tmp2=atoi(dat_buff);

	jj=tmp2/1000000;
	mm=((tmp2%1000000)/1000);
	aa=((tmp2%1000000)%1000);
	tmp2=(jj*10000+mm*100+aa)/100;

	code=(float)tmp*10000+tmp2;

	return code;
}
