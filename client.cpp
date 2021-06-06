#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"structure.h"
#include"prototype.h"

cellule_client* RetourTete(cellule_client *t)
{
	if(t!=NULL)

		while(t->precedent!=NULL)
			t=t->precedent;

	return t;
}

liste_client SaisieClient()
{
	client *clt;
    liste_client retour;

	EnTete();

	retour=(cellule_client *)malloc(sizeof(cellule_client));
	clt=(client *)malloc(sizeof(client));

	printf("\nSaisie personne........");

	printf("\n\t\tNom           : ");
	scanf("%s",&clt->nom);

	printf("\n\t\tPrenom        : ");
	scanf("%s",&clt->prenom);

	printf("\n\t\tAge           : ");
	scanf("%d",&clt->age);

	printf("\n\tAdresse...");

	printf("\n\t\tNum. CIN      : ");
	scanf("%d",&clt->cin);

	clt->ctr=0;

	///****INITIALISATION DE LA CELLULE CLIENT****
	retour->person=*clt;
	retour->suivant=NULL;
	retour->precedent=NULL;

	return retour;
}



liste_client RechercheClient(liste_client l,char *nom,char *pnom)
{

	l=RetourTete(l);


	while(l!=NULL)
		{
			if(strcmp(l->person.nom,nom)==0)
				if(strcmp(l->person.prenom,pnom)==0)
					return l;

			l=l->suivant;
		}

 	return NULL;

}

liste_client modifierClient(liste_client l)
{
	liste_client modif;
	cellule_client *save;
	char nom[20],pnom[20];

	l=RetourTete(l);

	if(l==NULL)
		MessageUrgence("Pas de client");
	else
	{
		printf("\n\t\tNom    ( \x22 exit \x22 pour annuler) :  ");
		scanf("%s",&nom);
		if(strcmp(nom,"exit")!=0)
		{
			printf("\n\t\tPrenom ( \x22 exit \x22 pour annuler) :  ");
			scanf("%s",&pnom);
		}

		if((strcmp(pnom,"exit")!=0)&&(strcmp(nom,"exit")!=0))
		{
			modif=RechercheClient(l,nom,pnom);

			if(modif==NULL)
				MessageUrgence("Client non trouve");
			else
			{
				save=modif;
				modif=SaisieClient();
				save->person=modif->person;
				MessageUrgence("Client modifie");
			}
		}
	}

	return l;
}

liste_client supprimerClient(liste_client l)
{
	cellule_client *supp;
	char nom[20],pnom[20];



	if(l==NULL)//*** si la liste est vide
		MessageUrgence("Pas de client");
	else
	{
		printf("\n\t\tNom    :  ");
		scanf("%s",&nom);
		if(strcmp(nom,"exit")!=0)
		{
			printf("\n\t\tPrenom :  ");
			scanf("%s",&pnom);
		}

			l=RetourTete(l);
			supp=RechercheClient(l,nom,pnom);
			if(supp!=NULL)
			{
				if(supp==l)
				{
					l=l->suivant;

					free(supp);
					MessageUrgence("Client supprime");
					return l;
				}

				else
					if(supp->suivant==NULL)
					{
						supp->precedent->suivant=NULL;
				//		free(supp);
						MessageUrgence("Client supprime");
						return l;

					}
					else
					{
						supp->precedent->suivant=supp->suivant;
						supp->suivant->precedent=supp->precedent;
						free(supp);
						MessageUrgence("Client supprime");
						return l;
					}
			}
			else
				MessageUrgence("Client non trouve");

	}

	return l;

}

void AfficheClient(client cl)
{
	EnTete();

	printf("\n\tNom          : %s",cl.nom);
	printf("\t\tPrenom         : %s",cl.prenom);

	printf("\n\n\tAge          : %d",cl.age);
	printf("\t\tCIN          : %d",cl.cin);

	printf("\n\n\tDate permis  : %d/%d/%d",cl.date_permi/10000,(cl.date_permi%10000)/100,(cl.date_permi%10000)%100);
	printf("\t\tNum telephone: %d",cl.telephone);

	printf("\n\n\tTravail      : %s",cl.travail);

	printf("\n\n\tAdresse...");

	printf("\n\n\tNum          : %d",cl.num);
	printf("\t\tRue          : %s",cl.rue);

	printf("\n\n\tVille        : %s",cl.ville);
	printf("\t\tCode postal  : %d",cl.cpostal);

	printf("\n\n\n");

	system("pause");
}


liste_client InsererEnFinClient(liste_client l,client cl)
{
	cellule_client *inser;

	inser=(cellule_client *)malloc(sizeof(cellule_client));
	inser->person=cl;

	l=RetourTete(l);

	if(l==NULL)
	{
		inser->precedent=NULL;
		inser->suivant=NULL;
		l=inser;
	}
	else
	{
		while(l->suivant!=NULL)
			l=l->suivant;

		inser->precedent=l;
		l->suivant=inser;
		inser->suivant=NULL;
	}

	return RetourTete(l);
}
