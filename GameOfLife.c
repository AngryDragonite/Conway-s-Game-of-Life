#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#ifndef WIERSZE
    #define WIERSZE 22
#endif
#ifndef KOLUMNY
    #define KOLUMNY 80
#endif

static int iloscWierszy=0, wierszPocz=1, kolumnaPocz=1;


//lista typu T, w niej będą zawierane informacje o numerach kolumn
typedef struct TLista {
    bool zywy;
    int iloscZ;
    int k;
    struct TLista *nextK, *prevK;
} TLista;


//lista typu D, w niej będą zawierane informacje o numerach wierszy
typedef struct DLista {
    int w;
    struct DLista *nextW, *prevW;
    struct TLista *nextK; 
} DLista;


//usuwa element poczatkowy z listy typu T
void usunZpoczatkuT(TLista **head) {
    TLista *pom = (*head);
    if (!(*head)->nextK) {
        free(pom);
        (*head)=NULL;
    } else {
        (*head)=(*head)->nextK;
        (*head)->prevK=NULL;
        free(pom);
    }
}

//usuwa element x z listy typu T
void usunZT(TLista **head, int x) {
    //zakladamy, ze x jest w tej liscie
    TLista *pom, *current;
    current=*head;
    if ((*head)->k==x) {
        usunZpoczatkuT(head);
    } else {
        while(current->nextK->k!=x) current=current->nextK;
        pom=current->nextK;
        if(current->nextK->nextK!=NULL) {
            current->nextK = pom->nextK;
        } else {
            current->nextK=NULL;
        }
        free(pom);
    }
}

//usuwa pierwszy element z listy typu D
void usunZPoczatkuD(DLista **head) {
    DLista *pom = *head;
    if ((*head)->nextW==NULL) {
        (*head)=NULL;
    } else {
        (*head) = (*head)->nextW;
    }
    free(pom);
}

//usuwa element x z listy typu D
void usunZD(DLista **head,int x) {
    //zakladamy, ze x jest w tej liscie
    DLista *pom, *current= *head;
    if ((*head)->w==x) {
        usunZPoczatkuD(head);
    } else {
        while(current->nextW->w!=x) current=current->nextW;
        pom = current->nextW;
        if (current->nextW->nextW!=NULL) {
            current->nextW = pom->nextW;
            pom->nextW->prevW=current;
        } else {
            current->nextW=NULL;
        }
        free(pom);

    }
}   

//wstawia na poczatek listy T, lub jesli nie istnieje to tworzy ją.
void wstawNaPoczatekT(TLista **head, int x) {
  
    TLista *new;
    new = (TLista*)malloc(sizeof(TLista));

    new->k=x;
    new->prevK=NULL;
    new->zywy=false;
    new->nextK=NULL;

    if((*head)==NULL) {
        (*head)=new;
        return;
    }

    new->nextK=(*head);
    (*head)->prevK=new;
    (*head)=new;  
}


//wstawia element x do listy T
void wstawDoT(TLista **headKom, int x, bool zywy) {
    //zakładamy ze posortowane rosnaco;   
    
    TLista *current = *headKom;
    TLista *new,*pom;

    new = (TLista*)malloc(sizeof(TLista));
    new->k=x;
    new->iloscZ=1;
    new->nextK=NULL;
    new->prevK=NULL;

    if (zywy) new->zywy=zywy;
    else new->zywy=false;

    if (*headKom==NULL) {
        *headKom=new;
        return;
    }

    if ((*headKom)->k>=x) {

        if ((*headKom)->k==x) {
            free(new);
            new=NULL;
            if (zywy) current->zywy=zywy;
            else if (!current->zywy && zywy==false) current->zywy=false;
            current->iloscZ++;
            return;
        }
        if (zywy) {
            current->zywy=zywy;
        } else if (!current->zywy && zywy==false) {
            current->zywy=false;
        }

        wstawNaPoczatekT(headKom,x);
        (*headKom)->iloscZ=1;
        free(new);
        new=NULL;

    } else {
        if (current->nextK==NULL) {
            if (current->k==x) {
                if (zywy) {
                    current->zywy=zywy;
                } else if(!current->zywy && zywy==false){
                    current->zywy=false;
                }
                free(new);
                new=NULL;
                current->iloscZ++;
                return;
            }
            
            current->nextK=new;
            new->nextK=NULL;
            new->prevK=current;

        } else {
            bool czy = true;
            while (czy && current->nextK->k<x) {
                current=current->nextK;
                if (current->nextK==NULL) czy=false;
            }
            if (czy) {
                if (current->nextK->k==x) {
                    
                    free(new);
                    new=NULL;
                    current->nextK->iloscZ++;
                    if (zywy) {
                        current->nextK->zywy=zywy;
                    } else if ( !current->zywy && zywy==false) {
                        current->zywy=false;
                    }
                    return;
                }
                
                pom=current->nextK;
                current->nextK=new;
                new->nextK=pom;
                new->prevK=current;
                pom->prevK=new;

            } else {
                if (current->k==x) {
                    
                    free(new);
                    new=NULL;
                    current->iloscZ++;
                    if (zywy) {
                        current->zywy=zywy;
                    } else if (!current->zywy && zywy==false) {
                        current->zywy=false;
                    }
                    return;
                }
                
                current->nextK=new;
                new->prevK=current;
                new->nextK=NULL;
            }
        }
    }
}

//wstawia element x na początek listy typu D
void wstawNaPoczatekD(DLista **headKom, int x) {
    
    DLista *new = (DLista*)malloc(sizeof(DLista));
    
    new->w=x;
    new->prevW=NULL;
    new->nextK=NULL;
    new->nextW=(*headKom);
    (*headKom)->prevW=new;
    (*headKom)=new;
}

//wstawia element x do listy typu D tak, zeby byla posortowana rosnąco
void wstawDoD(DLista **headKom, int x) {
    //zakładamy ze posortowane rosnaco;
    DLista *head = *headKom;
    DLista *new,*pom;

    new = (DLista*)malloc(sizeof(DLista));
    new->w=x;
    new->nextK=NULL;
    new->nextW=NULL;
    new->prevW=NULL;

    if (head==NULL) {
        (*headKom)=new;
        return;
    }

    if ((*headKom)->w>x) {
        wstawNaPoczatekD(headKom,x);
        free(new);
        new=NULL;
    } else {
        if (head->nextW==NULL) {
        
            if (head->w==x) {
                free(new);
            } else {            
                head->nextW=new;
                new->nextW=NULL;
                new->prevW=head;
            }
        } else {
            bool czy = true;
            while (czy && head->nextW->w<x) {
                head=head->nextW;
                if (!head->nextW) czy=false;
            }
            if (czy) {
                if (head->w==x || head->nextW->w==x) {
                    free(new);
                } else {
                
                    pom=head->nextW;
                    head->nextW=new;
                    new->nextW=pom;
                    new->prevW=head;
                    pom->prevW=new;
                }
            } else {
                if (head->w==x) {
                    free(new);
                } else {
                    head->nextW=new;
                    new->prevW=head;
                    new->nextW=NULL;
                }
            }
        }
    }
}


//Funkcja do zwalniania pamięci
void Zwolnij(DLista **head) {
    
    TLista *pom=NULL;
    
    while(*head!=NULL) {
        if((*head)->nextK) pom=(*head)->nextK;
        else pom=NULL;
        while(pom) usunZpoczatkuT(&pom);
        usunZPoczatkuD(head);
    }
}

//Funkcja używana do usuwania komórek które nie powinny być żywe w następnej generacji
void Czysc(DLista **head) {
    
    DLista *currentD=*head;
    TLista *currentT;

    bool czy=true;
    int w,k;

    while(currentD!=NULL) {
        
        czy=true;
        currentT=currentD->nextK;
        w=currentD->w;

        while(czy && currentT!=NULL){
            
            if (currentT->iloscZ!=3 && currentT->iloscZ!=4 && currentT->zywy==true) {
                
                currentT->zywy=false;
                k=currentT->k;
                if(currentD->nextK!=NULL) currentT=currentT->nextK;
                else currentT=NULL;
                usunZT(&currentD->nextK,k);

            } else if (currentT->iloscZ!=3 && currentT->zywy==false) {
                
                k=currentT->k;
                if(currentD->nextK!=NULL) currentT=currentT->nextK;
                else currentT=NULL;
                usunZT(&currentD->nextK,k);

            } else {
                
                currentT->zywy=true;
                currentT=currentT->nextK;
            }
        }
        if (currentD->nextK==NULL) {
            w=currentD->w;
            currentD=currentD->nextW;
            usunZD(head,w);

        } else currentD=currentD->nextW;
    }
}
//Funkcja do wczytywania danych początkowych
DLista *Wczytaj() {
    
    DLista *head=NULL, *current=NULL, *nowa=NULL;
    TLista *nowy=NULL, *nowy1=NULL;

    bool czyKordyKomorki=true;
    int licznik=0;
    int *A = NULL;

    while(czyKordyKomorki){
        //podgladamy drugi znak
        int i = getchar();
        int j = getchar();
        //jesli drugi znak to '\n', to konczymy pętle odczytywania
        if (i==47 && j==10) {
            
            czyKordyKomorki = false;
            if (head==NULL)return NULL;

        } else {       //jesli nie to wczytujemy dane z stdin
            
            ungetc(j, stdin);
            licznik = 0;
            A =(int*)malloc(sizeof(int));

            while(scanf("%d", &A[licznik])) {
                
                licznik++;
                int l = getchar();
                if(l)l=1; //zeby nie bylo Werror unused variable
                    A = realloc(A, (size_t) (licznik+1)*sizeof*A);
                }

                if (iloscWierszy==0) {
                    
                    current=(DLista*) malloc(sizeof(DLista));
                    current->nextW=NULL;
                    current->nextK=NULL;
                    current->prevW=NULL;
                    current->w=A[0];
                    head=current;
                    iloscWierszy++;
                    
                } else {

                    nowa = (DLista*) malloc(sizeof(DLista));
                    nowa->w = A[0];
                    nowa->nextW=NULL;
                    nowa->nextK=NULL;
                    current->nextW=nowa;
                    nowa->prevW=current;
                    current=nowa;
                    iloscWierszy++;
                }
            
                nowy = (TLista*)malloc(sizeof(TLista));
                nowy->k =A[1];
                nowy->nextK=NULL;
                nowy->prevK=NULL;

                if (current!=NULL && licznik>1) current->nextK=nowy;
                else free(nowy);

                for (int l=2; l<licznik; l++) {

                    nowy1 = (TLista*)malloc(sizeof(TLista));
                    nowy1->k = A[l];
                    nowy1->nextK=NULL;
                    nowy->nextK=nowy1;
                    nowy1->prevK=nowy;
                    nowy=nowy->nextK; 
                }
                free(A);
            }
        }
    return head;
}

//Funkcja do rysowania planszy
void RysujPlansze(DLista *headKom) {
    
    DLista *head=headKom;
    TLista *pom=NULL;

    int w=INT_MAX,k=INT_MAX;

    if (head!=NULL) {
        
        while (head->nextW!=NULL && head->w<wierszPocz) head=head->nextW;
        
        w = head->w;

        if (head->nextK) pom = head->nextK;
        else pom = NULL;

        while (pom && pom->k<kolumnaPocz) pom=pom->nextK;
    
        if (pom!=NULL) k = pom->k;

    } else {
        pom=NULL;
    }

    for (int i=wierszPocz; i<wierszPocz+WIERSZE; i++) {
        for (int j=kolumnaPocz; j<kolumnaPocz+KOLUMNY; j++) {
            if (!pom) {
                printf(".");
            } else {
                k=pom->k;
                if (i==w && j==k) {
                    printf("0");
                    pom=pom->nextK;
                } else printf (".");
            }
        }
        if (i==w && head->nextW!=NULL) {
            
            head=head->nextW;
            pom=head->nextK;
            while(pom && pom->k<kolumnaPocz) pom=pom->nextK;
            w=head->w;
        }
        printf("\n");
    }
    for (int m=kolumnaPocz; m<kolumnaPocz+KOLUMNY;m++) printf("=");
    printf("\n");
}

//Funkcja używana do wypisywania informacji o żywych komórkach
void zrzutInformacji(DLista*headKom) {
    
    DLista *head=headKom;
    
    while(head!=NULL){
        
        printf("/");
        printf("%d",head->w);
        TLista *pom =head->nextK;
        while(pom!=NULL) {
            printf(" %d", pom->k);
            pom=pom->nextK;
        }
        printf("\n");
        head=head->nextW;
    }
    printf("/\n");
}

//Funkcja alokująca pola, które mogą być żywe w następnej generacji
DLista *alokujNowaPlansze(DLista *head) {
    
    DLista *zwracanyHead=NULL, *currentD, *current1D=NULL;
    TLista *currentT;

    zwracanyHead=NULL;
    currentD=head;
    int w,k;

    while(currentD!=NULL) {
        
        w=currentD->w;
        currentT=currentD->nextK;
        if (zwracanyHead==NULL) {
            wstawDoD(&zwracanyHead,w);
            current1D = zwracanyHead;
        } else {
            wstawDoD(&zwracanyHead,w);
            while(current1D->w!=w) current1D=current1D->nextW;
        }

        while(currentT!=NULL) {
            
            k=currentT->k;
            
            wstawDoT(&current1D->nextK, k-1,false);
            wstawDoT(&current1D->nextK, k,true);
            wstawDoT(&current1D->nextK, k+1,false);

            wstawDoD(&zwracanyHead,w-1);

            wstawDoT(&current1D->prevW->nextK, k-1,false);
            wstawDoT(&current1D->prevW->nextK, k,false);
            wstawDoT(&current1D->prevW->nextK, k+1,false);

            wstawDoD(&zwracanyHead,w+1);

            wstawDoT(&current1D->nextW->nextK, k-1,false);
            wstawDoT(&current1D->nextW->nextK, k,false);
            wstawDoT(&current1D->nextW->nextK, k+1,false);
            
            currentT=currentT->nextK;    
        }
    currentD=currentD->nextW;

    }
    return zwracanyHead;
}

//Funkcja obliczająca stan następnej generacji
DLista *obliczNext(DLista **head) {
    
    DLista *nowa=NULL;

    nowa=alokujNowaPlansze((*head));
    Czysc(&nowa);
    Zwolnij(head);

    return nowa;
}

//Funkcja obliczająca stan n-tej generacji
DLista *obliczGeneracje(DLista **head, int n) {
    
    DLista *nowa=NULL;
    
    for (int i=0; i<n; i++) {
        nowa = alokujNowaPlansze((*head));
        Czysc(&nowa);
        Zwolnij(head);
        *head=nowa;
    }

    return nowa;
}


//Glowna pętla programu
void glownaPetla(DLista **komorki) {
    
    bool warunekPetli=true;

    while(warunekPetli) {

        RysujPlansze(*komorki);
        int i = getchar();
        if (i=='\n') {
            *komorki = obliczNext(komorki);
        } else {
            
            int b = getchar();
            ungetc(b, stdin);

            if (i=='.') {

                warunekPetli=false;
                Zwolnij(komorki);

            }  else if (i==48 && b!=' ') {

                zrzutInformacji(*komorki);
                getchar();

            } else {
                
                ungetc(i, stdin);
                int k,l;
                int g = scanf("%d", &k);
                if(g)g=1; //tak samo jak poprzednio, zeby nie było Werror=unused-variable
                int j = getchar();

                if (j==' ') { 
                    
                    int o = scanf("%d", &l);
                    if(o)o=1;
                    wierszPocz=k;
                    kolumnaPocz=l;
                    getchar();

                } else {
                    *komorki=obliczGeneracje(komorki,k);
                } 
            }
        }   
    }
}

int main() {
    
    DLista *head = Wczytaj();    
    glownaPetla(&head);
    Zwolnij(&head);
}