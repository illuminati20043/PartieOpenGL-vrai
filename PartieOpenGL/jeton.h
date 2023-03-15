//énumération des différents types de lexems existants
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef enum {
	REEL,
	OPERATEUR,
	FONCTION,
	ERREUR,
	FIN,
	PAR_OUV,
	PAR_FERM,
	VARIABLE,
	ABSOLU
} typelexem;
//énumération des différents types d'opérateurs existants
typedef enum { PLUS, MOINS, FOIS, DIV, PUISS } typeoperateur;
//énumération des différents types de fonctions éxistantes
typedef enum {
	ABS,
	SIN,
	SQRT,
	LOG,
	COS,
	TAN,
	EXP,
	ENTIER,
	VAL_NEG,
	SINC
} typefonction;
//énumération des différents types d'erreurs éxistantes
typedef enum { AREMPLIR } typeerreur;
//énumération des différents types de valeurs éxistantes
typedef union {
	float reel;
	typefonction fonction;
	typeoperateur operateur;
	typeerreur erreur;
} typevaleur;
//énumération des différents types de jetons éxistants
typedef struct {
	typelexem lexem;
	typevaleur valeur;
} typejeton;
// déclaration de l'arbre
typedef struct Node {
	typejeton jeton;
	struct Node* pjeton_preced;
	struct Node* pjeton_suiv;
} Node;
typedef Node* Arbre;