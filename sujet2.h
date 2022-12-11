typedef struct Processus Processus;
struct Processus
{	
	char nom[50];
	int duree;
	int priorite;
	Processus *suivant;
};

typedef struct File File;
struct File
{
	Processus *premier;

};

