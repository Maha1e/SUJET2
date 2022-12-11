#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "sujet2.h"

void ajout_activite(File *file, Processus *activite)
{
    Processus *nouveau = malloc(sizeof(*nouveau)); //allocation dynamique
    if (file == NULL || nouveau == NULL)
    {
        exit(0);
    }
    *nouveau = *activite;
    nouveau->suivant = NULL;//le processus ajouté pointe vers NULL = dernier de la file

    if (file->premier != NULL) // La file n'est pas vide 
    {
        Processus *processusActuel = file->premier;
        while (processusActuel->suivant != NULL) // On se positionne à la fin de la file 
        {
            processusActuel = processusActuel->suivant;
        }
        processusActuel->suivant = nouveau;
    }
    else // La file est vide, notre élément est le premier
    {
        file->premier = nouveau;
    }
}

int step(File *file)
{
  if (file==NULL){
    exit(0);
    }
  if (file->premier==NULL){ //la file est vide
      printf("la file est vide");
      exit(0);
    }
  if (file->premier != NULL) //la file n'est pas vide
    {
      Processus *processusDefile = file->premier; //crée une variable temporaire 
      file->premier = processusDefile->suivant;  //le processus suivant de la file devient le premier
      printf("execution  nom:%s duree:%d\n", processusDefile->nom, processusDefile->duree);
      sleep(processusDefile->duree); //patiente simuler l'éxécution du processus
      //free(processusDefile);
      
  }
    
    return 0;
}


int run(File *file)
{
  while(file->premier!=NULL){ //éxécute step jusqu'à avoir une file vide
    step(file);
  }

  return 1;
}  


Processus * Trier(Processus * premier) //algo de tri selon les priorités
{
    Processus * temp , *p;
    int PR;
    if (premier!=NULL)
    {
        for(temp=premier;temp->suivant!=NULL;temp=temp->suivant)
           for(p=temp->suivant;p!=NULL;p=p->suivant)
               {
                if(p->priorite<temp->priorite)
                   {
                       PR=p->priorite;
                       p->priorite=temp->priorite;
                       temp->priorite=PR;
                   }
               }
    }
  
    return premier;
  }

void afficher(File *file) //affiche la file 
{
  if (file==NULL){
    exit(0);
  if (file->premier==NULL){
    printf("la file est vide");
    exit(0);}
  
  }
  Processus *affiche= file->premier;
  printf("voici la file:\n");
  while (affiche!= NULL)
    {
      printf("nom: %s,duree:%d,priorité: %d\n", affiche->nom, affiche->duree, affiche->priorite);
      affiche=affiche->suivant;
    }
  printf("fin\n");
}


int main()
{
  Processus test={"test",2,3}; // on initialise 2 processus arbitrairement pour tester 
  Processus test2={"test2", 1,2};
  File t={}; //t est notre file donc notre ordonnanceur
  File *file=&t;
  Processus *activite=&test;
  Processus *activite2 = &test2;
  
  ajout_activite(file, activite); //ajout des 2 processus
  ajout_activite(file, activite2);
  //Trier(file->premier);
  afficher(file); //doit afficher un ordonnanceur non vide

  
  run(file); //Défile 
  afficher(file); //doit afficher un ordonnanceur vide

  return 1;
} 
