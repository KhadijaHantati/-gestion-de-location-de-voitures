#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"structure.h"
#include"prototype.h"

liste RechercheTypeVoiture(liste l,char rech[3])
{
	liste tmp;


	tmp=(cellule *)malloc(sizeof(cellule));

	tmp=l;


	if(tmp==NULL)
		return NULL;

	if(strcmp(tmp->voit.identit,rech)==0)
		return tmp;
	else
		return RechercheTypeVoiture(tmp->suivant,rech);

}
liste SaisieTypeVoiture(liste l)
{


	cellule *voit_final;
	voiture voit;

	EnTete();

	voit_final=(cellule *)malloc(sizeof(cellule));

	printf("\n\n\tSaisie d'un type de voiture......\n");

	printf("\n\tMarque        :  ");
	scanf("%s",&voit.marque);

	printf("\tNom           :  ");
	scanf("%s",&voit.nom);


	do
	{
		printf("\n\tABS    (o/n)  :  ");
		scanf("%s",&voit.abs);
	}while((voit.abs!='o')&&(voit.abs!='n'));

	do
	{
		printf("\n\tDir.Assi (o/n):  ");
		scanf("%s",&voit.dirAssis);
	}while((voit.dirAssis!='o')&&(voit.dirAssis!='n'));


	printf("\n\tCylindree     :  ");
	scanf("%d",&voit.cylindree);
	do
	{
		printf("\n\tMoteur  (e/d) :  ");
		scanf("%s",&voit.moteur);
	}while((voit.moteur!='d')&&(voit.moteur!='e'));

	printf("\n\tPuissance     :  ");
	scanf("%d",&voit.puissance);

	do
	{
		printf("\n\tClimatiseur   :  ");
		scanf("%s",&voit.clim);
	}while((voit.clim!='o')&&(voit.clim!='n'));

	do
	{
		printf("\n\tInterieur     :  ");
		scanf("%s",&voit.interieur);
	}while((voit.interieur!='o')&&(voit.interieur!='n'));

	do
	{
		printf("\n\tVit. elect.   :  ");
		scanf("%s",&voit.vitElec);
	}while((strcmp(voit.vitElec,"av")!=0)&&(strcmp(voit.vitElec,"tt")!=0)&&(strcmp(voit.vitElec,"n")!=0));



	do
	{
		printf("\n\tSonorisation  :  ");
		scanf("%s",&voit.sono);
	}while((voit.sono!='o')&&(voit.sono!='n'));


	printf("\n\tCouleur       :  ");
	scanf("%s",&voit.couleur);

	printf("\n\tNb de place :  ");
	scanf("%d",&voit.nbplace);

	printf("\n\tTarif par Km (millime)  :  ");
	scanf("%d",&voit.prixKilo);

	printf("\n\tTarif par jour (millime):  ");
	scanf("%d",&voit.prixJour);

	do
	{
		printf("\n\tIdentificateur    :  ");
		scanf("%s",&voit.identit);
	}while(RechercheTypeVoiture(l,voit.identit)!=NULL);


	voit_final->voit=voit;
	voit_final->suivant=NULL;


	return voit_final;

}
listeMatricul saisieMatricul(listeMatricul l1,liste l)
{
	Matricul *m;


	EnTete();

	m=(Matricul *)malloc(sizeof(Matricul));

	if(ListeVide(l)==1)
	{	do
		{
			printf("\n\tType      :  ");
			scanf("%s",&m->mat.type);
		}while((RechercheTypeVoiture(l,m->mat.type)==NULL)&&(strcmp(m->mat.type,"exit")));

		if(strcmp(m->mat.type,"exit")!=0)
		{
			do
			{
				do
				{
					printf("\n\tMatricule :  ");
					scanf("%d",&m->mat.matricule);
				}while((m->mat.matricule>9999999)||(m->mat.matricule<10000));
			}while((rechecherMatricul(l1,m->mat.matricule)==NULL)&&(m->mat.matricule==0));

			if(rechecherMatricul(l1,m->mat.matricule)!=NULL)
			{
				MessageUrgence("Matricul existant");
				goto FIN;
			}

			printf("\n\tKilometrage   :  ");
			scanf("%d",&m->mat.kilometrage);

			strcpy(&m->mat.stats,"n");
		}
		else
			return NULL;

	}
	else
	{
		MessageUrgence("Pas de type disponible");
		return NULL;
	}
	m->suivant=NULL;
	return m;

FIN : return NULL;

}
liste ModifierTypeVoiture(liste l)
{
	liste modif;
	cellule *v_modif;
	char rech[3];

	printf("\n\tDonnee identifiant du type   :  ");
	scanf("%s",&rech);

	modif=RechercheTypeVoiture(l,rech);

	if(ListeVide(modif)==1)
	{
		printf("\n\n\n\t\tRe-saisie de la voiture....");
		v_modif=SaisieTypeVoiture(l);
		modif->voit=v_modif->voit;
	}
	else
	MessageUrgence("Voiture non trouvee");

	return l;
}

liste SupprimerVoiture(liste l)
{
	liste supp;
	char rech[3];

	if(ListeVide(l)==0)
		MessageUrgence("Suppression impossible\n\t\t\t\tPas de voiture en stock");
	else
	{
		printf("Donner identifiant type :  ");
		scanf("%s",&rech);

		supp=RechercheTypeVoiture(l,rech);

		if(supp==NULL)			//Voiture non trouver
			MessageUrgence("Voiture non trouver");
		else
		{
			if(l==supp)
			{
				l=l->suivant;
				free(supp);
			}
			else
				l=SupprimerPosition(l,supp);
			MessageUrgence("Voiture supprimer");
		}
	}

	return l;
}

void AfficheType(voiture voit)
{
	EnTete();

	printf("\tIdentifiant   :  %s",voit.identit);
	printf("\n\n\t\tMarque          :  %s",voit.marque);
	printf("\n\t\tNom             :  %s",voit.nom);
	printf("\n\t\tNb place        :  %d",voit.nbplace);
	printf("\n\t\tCouleur         :  %s",voit.couleur);
	printf("\n\t\tMotorisation    :  %c",voit.moteur);
	printf("\n\t\tPuissance       :  %d",voit.puissance);
	printf("\n\n\t\tOption...");
	printf("\n\t\tDir.Ass  :  %c\t\tABS   :  %c\t\tVit.Elec  :  %c",voit.dirAssis,voit.abs,voit.vitElec);
	printf("\n\t\tInterieur:  %c\t\tSono  :  %c",voit.interieur,voit.sono);
	printf("\n\t\tTarif par jour  :  %d",voit.prixJour);
	printf("\n\t\tTarif par Km    :  %d",voit.prixKilo);


	printf("\n\n");
	system("pause");

}
void AfficheVoiture(matriculVoiture mt)
{
	EnTete();

	printf("\n\n\t\tType            :  %s",mt.type);
	printf("\n\n\t\tMatricul        :  %d TUN %d",mt.matricule/10000,mt.matricule%10000);
	printf("\n\n\t\tKilometrage     :  %d",mt.kilometrage);

	if(mt.stats=='l')
		printf("\n\n\t\tStatut          :  Louee");
	if(mt.stats=='n')
		printf("\n\n\t\tStatut          :  Non-louee");

	printf("\n\n");
	system("pause");

}
