#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structure.h"
#include"prototype.h"

int ListeMatriculVide(listeMatricul l)
{
	if(l==NULL)
		return 0;
	else
		return 1;
}

listeMatricul insererVoiture(listeMatricul l,Matricul *m)
{
	if(ListeMatriculVide(l)==0)
		return m;
	else
		m->suivant=l;

	return m;
}

listeMatricul rechecherMatricul(listeMatricul l,int m)
{
	Matricul *parc;

	if(l!=NULL)
	{
		parc=l;
		while(parc!=NULL)
		{
			if(parc->mat.matricule==m)
				return parc;
			parc=parc->suivant;
		}
	}

	return NULL;
}


listeMatricul RechercheVoitureLibre(listeMatricul lm, char *typ)
{

	if(lm==NULL)
		return NULL;
	if((strcmp(&lm->mat.stats,"n")==0) && (strcmp(lm->mat.type,typ)==0))
		return lm;
	else return RechercheVoitureLibre(lm->suivant,typ);
}

listeMatricul supprimerMatricul(listeMatricul l)
{
	Matricul *parc,*m;
	int mat;

	if(l==NULL)
	{
		MessageUrgence("Pas de voiture a supprimer");
		return l;
	}

	do
	{
		printf("\n\tMatricule :  ");
		scanf("%d",&mat);
	}while((mat<=9999999)&&(mat>=10000)&&(mat==0));
	if(mat!=0)
	{
		m=rechecherMatricul(l,mat);

		if(m!=NULL)
		{
			if(l==m)
			{
				l=l->suivant;
//				free(m);
				MessageUrgence("Voiture supprimer");
				return l;
			}
			parc=l;
			while((parc->suivant!=m)&&(parc!=NULL))
				parc=parc->suivant;

			if(parc->suivant==m)
			{
				parc->suivant=m->suivant;
				MessageUrgence("Voiture supprimer");

			}
			else
				MessageUrgence("Voiture non trouvee");
		}
	}
	return l;


}

int ListeVide(liste l)
{
	if(l==NULL)
		return 0;
	else
		return 1;

}

liste inserer_en_fin(liste l,cellule *elt)
{
	cellule *p;

	p=(cellule *)malloc(sizeof(cellule));

	if (ListeVide(l)==0)
		return elt;

	p=l;
	while(p->suivant!=NULL)
	{
		p=p->suivant;
	}
	p->suivant=elt;
	return l;
}

liste SupprimerPosition(liste l,cellule *supp)
{
	cellule *tmp;
	tmp=l;
	while((tmp->suivant!=supp)&&(tmp!=NULL))
		tmp=tmp->suivant;

	if(tmp->suivant==supp)
	{
		tmp->suivant=supp->suivant;
		free(supp);
	}

	return l;
}






