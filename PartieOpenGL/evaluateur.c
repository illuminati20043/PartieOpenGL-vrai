#include "jeton.h"



float Parcourir(struct Node* Arbre, float X) {
    float res;

    switch (Arbre->jeton.lexem)
    {
    case REEL:
        res = Arbre->jeton.valeur.reel;
        break;
    case VARIABLE:
        Arbre->jeton.valeur.reel = X;
        //printf("X = %f\n", res);
        res = Arbre->jeton.valeur.reel;
        //printf("X = %f\n", res);
        break;
    case OPERATEUR:
        switch (Arbre->jeton.valeur.operateur)
        {
        case PLUS:
            res = Parcourir(Arbre->pjeton_preced, X) + Parcourir(Arbre->pjeton_suiv, X);
            break;
        case MOINS:
            res = Parcourir(Arbre->pjeton_preced, X) - Parcourir(Arbre->pjeton_suiv, X);
            break;
        case FOIS:
            res = Parcourir(Arbre->pjeton_preced, X) * Parcourir(Arbre->pjeton_suiv, X);
            break;
        case DIV:
            res = Parcourir(Arbre->pjeton_preced, X) / Parcourir(Arbre->pjeton_suiv, X);
            break;
        case PUISS:
            res = pow(Parcourir(Arbre->pjeton_preced, X), Parcourir(Arbre->pjeton_suiv, X));
            break;
        default:
            printf("Erreur operateur inconnu"); // Au cas où l'utilisateur met factorielle
            return 0;
        }
        break;
    case FONCTION:
        switch (Arbre->jeton.valeur.fonction)
        {
        case ABS:
            res = abs(Parcourir(Arbre->pjeton_preced, X)); //Fonction abs pour valeur absolue
            break;
        case SIN:
            //printf("SIN trouve\n");
            res = sin(Parcourir(Arbre->pjeton_preced, X));
            break;
        case SQRT:
            res = sqrt(Parcourir(Arbre->pjeton_preced, X));
            break;
        case LOG:
            res = logf(Parcourir(Arbre->pjeton_preced, X));
            break;
        case COS:
            res = cosf(Parcourir(Arbre->pjeton_preced, X));
            break;
        case TAN:
            res = tan(Parcourir(Arbre->pjeton_preced, X));
            break;
        case EXP:
            res = expf(Parcourir(Arbre->pjeton_preced, X));
            break;
        case ENTIER:
            res = floor(Parcourir(Arbre->pjeton_preced, X));
            break;
        case VAL_NEG:
            res = -(Parcourir(Arbre->pjeton_preced, X));
            break;
        case SINC:
            res = (sin(Parcourir(Arbre->pjeton_preced, X))) / (Parcourir(Arbre->pjeton_preced, X));
            break;
        default:
            printf("Erreur fonction inconnue"); // Au cas où l'utilisateur rentre une fonction pas dans jeton.h
            return 0;
        }
    default:
        break;
    }
    return res;
}


//n= nbr échantillon
float* Eval_Arbre_Range_x(struct Node* Arbre, float x_min, float x_max, int n) {
    float step = (x_max - x_min) / (n - 1);
    float x_temp;
    float* results = malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        x_temp = x_min + i * step;
        results[i] = x_temp;
    }
    return results;
}

float* Eval_Arbre_Range_y(struct Node* Arbre, float x_min, float x_max, int n) {
    float step = (x_max - x_min) / (n - 1);
    float x_temp;
    float y_temp;
    float* results = malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        x_temp = x_min + i * step;
        y_temp = Parcourir(Arbre, x_temp);
        results[i] = y_temp;
    }
    return results;
}




int evaluer() {

    Node Node8 = { {REEL,{.reel = 3}},NULL,NULL };
    Node Node7 = { {VARIABLE,{.reel = 0}},NULL,NULL };
    Node Node6 = { {OPERATEUR,{.operateur = PLUS}},&Node7,&Node8 };
    Node Node5 = { {FONCTION,{.fonction = SIN}},&Node6,NULL };
    Node Node4 = { {REEL,{.reel = 6}},NULL,NULL };
    Node Node3 = { {OPERATEUR,{.operateur = FOIS}},&Node4,&Node5 };
    Node Node2 = { {REEL,{.reel = 4}},NULL,NULL };
    Node Node1 = { {OPERATEUR,{.operateur = PLUS}},&Node2,&Node3 };

    float step;
    float x_min;
    float x_max;
    int nb_echantillon;

    printf("Choississez votre x minimum : ");
    scanf("%f", &x_min);
    printf("Choississez votre x maximum : ");
    scanf("%f", &x_max);
    printf("Choississez le pas : ");
    scanf("%f", &step);

    nb_echantillon = ((x_max - x_min) / step) + 1;

    for (int i = 0; i < nb_echantillon; i++) {
        printf("x = %f ; ", Eval_Arbre_Range_x(&Node1, x_min, x_max, nb_echantillon)[i]);
        printf("y = %f\n", Eval_Arbre_Range_y(&Node1, x_min, x_max, nb_echantillon)[i]);
        //printf("4+6*SIN(X+3) = %f\n", 4+6*sinf(i+4));
    }
    //printf("%f\n", Parcourir(&Node1,3.14));


    return 0;
}
