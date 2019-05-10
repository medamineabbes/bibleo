#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct mots_cles{
	char *mots;
	struct mots_cles *next;
}mots_cles;
typedef struct livre{
	char *titre;
	char *auteur;
	char *editeur;
	char *date;
	int prix;
	char *ISBN;
	int quantite;
	char *categorie;
	mots_cles *list;
	char *resume;
	char *info;
	struct livre *suivant;
}livre;
typedef struct emprunteur{
	char *ninscription;
	char *date_inscription;
	char *prenom;
	char *nom;
	char *date_naissance;
	char *adress;
	char *n_telephone;
	struct emprunteur *next;
}emprunteur;
typedef struct emprunt{
	char *identifiant;
	char *date_emprunt;
	char *date_prevu_retour;
	int  etat_eprunt;//1 si rendu 0 sinon
	struct emprunt *next;
	struct emprunt *privious;
}emprunt;
void convert_to_str(int a,char *p)
{
    int i=0;
    int b=100;
    while(a!=0)
    {
        *(p+i)=(char)((a/b) + 48);
        a%=b;
        b/=10;
        i++;
    }
}



//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void write_books(livre *book)
{
    FILE *fp;
    int i=1;
    int j;
    char *t,*p;
    mots_cles *a;
    t=malloc(sizeof(char*));
    p=malloc(sizeof(char*));
    strcpy(p,"livres/");
    while(book!=NULL)
    {
        convert_to_str(i,t);
        for(j=0;j<strlen(t);j++)
        {
            *(p+j+7)=*(t+j);
        }
        fp=fopen(p,"w");
        fprintf(fp,"%s;%s:%s,%s!%d?%s<%d*%s+%s=%s>",book->titre,book->auteur,book->editeur,book->date,book->prix,book->ISBN,book->quantite,book->categorie,book->resume,book->info);
        fclose(fp);
        i++;
        fp=fopen(p,"a");
        if(book->list!=NULL)
        fprintf(fp,"%s",book->list->mots);
        book->list=book->list->next;
        while(book->list!=NULL)
        {
            fprintf(fp,"@%s",book->list->mots);
            book->list=book->list->next;
        }
    fclose(fp);
    book=book->suivant;
    }
    fp=fopen(p,"a");
    fprintf(fp,"@");
    fclose(fp);
}



//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void write_emprunteur(emprunteur *amine)
{
    FILE *fp;
    int i,j;
    char *p,*t;
    emprunteur *a;
    a=amine;
    p=malloc(sizeof(char)*14);
    t=malloc(sizeof(char*));
    i=1;
    strcpy(p,"emprunteur/   ");
    while(a!=NULL)
    {
        convert_to_str(i,t);
        *(p+11)=*t;
        *(p+12)=*(t+1);
        *(p+13)=*(t+2);
        *(p+14)='\0';
        fp=fopen(p,"w");
        fprintf(fp,"%s;%s:%s,%s!%s?%s+%s*",a->ninscription,a->date_inscription,a->prenom,a->nom,a->date_naissance,a->adress,a->n_telephone);
        fclose(fp); 
        i++;
        a=a->next;
    }
}
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
emprunteur* read_one_emprunteur(int n)
{
    char *f,*ch1,*ch,c,*t,*p;
    int i,j,g;
    FILE *fp;
    emprunteur *a;
    p=malloc(sizeof(char*));
    a=malloc(sizeof(emprunteur));
    f=malloc(sizeof(char)*3);
    ch1=malloc(sizeof(char)*15);
    ch=malloc(sizeof(char)*100);
    t=malloc(sizeof(char)*15);
    convert_to_str(n,f);
    strcpy(ch1,"emprunteur/   ");
    *(ch1+11)=*f;
    *(ch1+12)=*(f+1);
    *(ch1+13)=*(f+2);;
    *(ch1+14)='\0';
    fp=fopen(ch1,"r");
    i=0;
    while ((c = getc(fp)) != EOF && c!='\n')
    {
        *( ch + i )=c;
        i++;
    }
    fclose(fp);
    //printf("%s\n",ch);
    g=strlen(ch);
    j=0;
    for(i=0;i<g;i++)
    {
        if(*(ch+i)==';')
        {
            *(t+j)='\0';
            strcpy(p,t);
            j=0;
            a->ninscription=p;
            p=malloc(sizeof(char*));
        }
        else if(*(ch+i)==':')
        {
            *(t+j)='\0';
            strcpy(p,t);
            j=0;
            a->date_inscription=p;
            p=malloc(sizeof(char*));
        }
        else if(*(ch+i)==',')
        {
            *(t+j)='\0';
            strcpy(p,t);
            j=0;
            a->prenom=p;
            p=malloc(sizeof(char*));
        }
        else if(*(ch+i)=='!')
        {
            *(t+j)='\0';
            strcpy(p,t);
            j=0;
            a->nom=p;
            p=malloc(sizeof(char*));
        }
        else if(*(ch+i)=='?')
        {
            *(t+j)='\0';
            strcpy(p,t);
            j=0;
            a->date_naissance=p;
            p=malloc(sizeof(char*));
        }
        else if(*(ch+i)=='+')
        {
            *(t+j)='\0';
            strcpy(p,t);
            j=0;
            a->adress=p;
            p=malloc(sizeof(char*));
        }
        else if(*(ch+i)=='*')
        {
            *(t+j)='\0';
            strcpy(p,t);
            j=0;
            a->n_telephone=p;
            p=malloc(sizeof(char*));
        }
        else
        {
            *(t+j)=*(ch+i);
            j++;
        }
    }
    return a;
}
emprunteur* read_all_emprunteur(int n)
{
    emprunteur *a,*b,*c;
    int i;
    if(n==0)
    return NULL;
    a=read_one_emprunteur(1);
    if(n==1)
    return a;
    if(n>=2)
    b=a;
    for(i=2;i<=n;i++)
    {
        c=read_one_emprunteur(i);
        a->next=c;
        a=c;
    }
    return b;
}
/*
    reads book number count
*/
livre* read_one_book(int count)
{
    FILE *fp;
    char c,*t,*ch1,*p,*ch;
    int k,j,g,i,l;
    livre *a,*f;
    mots_cles *b;
    b=malloc(sizeof(mots_cles));
    ch=malloc(sizeof(char*));
    a=malloc(sizeof(livre));
    f=a;
    ch1=malloc(sizeof(char)*500);
    t=malloc(sizeof(char)*11);
    p=malloc(sizeof(char*));
    a->list=b;
    strcpy(t,"livres/");
        convert_to_str(count,p);
        *(t+7)=*p;
        *(t+8)=*(p+1);
        *(t+9)=*(p+2);
        *(t+10)='\0';
        fp=fopen(t,"r");
        i=0;
        while ((c = getc(fp)) != EOF && c!='\n')
        {
            *( ch1 + i )=c;
            i++;
        }
        j=i;
        k=0;
        for(i=0;i<j;i++)
        {
            if(*(ch1+i)==';')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->titre=ch;
                k=0;
            }
            else if(*(ch1+i)==':')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->auteur=ch;
                k=0;
            }
            else if(*(ch1+i)==',')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->editeur=ch;
                k=0;
            }
            else if(*(ch1+i)=='!')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->date=ch;
                k=0;
            }
            else if(*(ch1+i)=='?')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                l=atoi(ch);
                a->prix=l;
                k=0;
            }
            else if(*(ch1+i)=='<')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->ISBN=ch;
                k=0;
            }
            else if(*(ch1+i)=='*')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                l=atoi(ch);
                a->quantite=l;
                k=0;
            }
            else if(*(ch1+i)=='+')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->categorie=ch;
                k=0;
            }
            else if(*(ch1+i)=='=')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->resume=ch;
                k=0;
            }
            else if(*(ch1+i)=='>')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->info=ch;
                k=0;
            }
            else if(*(ch1+i)=='@')
            {
                ch=malloc(sizeof(char*));
                *(p+k)='\0';
                strcpy(ch,p);
                a->list->mots=ch;
                a->list->next=malloc(sizeof(mots_cles));
                a->list=a->list->next;
                k=0;
            }
            else
            {
                *(p+k)=*(ch1+i);
                k++;
            }
        }
    a->list=b;
    a=f;
    return a;
}

/*
    very very fine working hhhhhhhhhhhhhh
*/

livre* read_all_books(int number)
{
    int i;
    livre *a,*b,*c;
    a=read_one_book(1);
    b=a;
    for(i=2;i<=number;i++)
    {
        c=read_one_book(i);
        a->suivant=c;
        a=a->suivant;
    }
    return b;
}

/*
    very very fine woking
*/

emprunt* read_one_emprunt(int a)
{
    emprunt *emp;
    FILE *fp;
    int i=0;
    int g,j,l;
    char *ch1,c,*t,*ch,*p;
    emp=malloc(sizeof(emprunt));
    ch1=malloc(sizeof(char)*50);
    t=malloc(sizeof(char)*3);
    ch=malloc(sizeof(char)*12);
    p=malloc(sizeof(char)*15);
    convert_to_str(a,t);
    strcpy(ch,"emprunt/   ");
    *(ch+8)=*t;
    *(ch+9)=*(t+1);
    *(ch+10)=*(t+2);
    fp=fopen(ch,"r");
    while ((c = getc(fp)) != EOF && c!='\n')
    {
        *( ch1 + i )=c;
        i++;
    }
    g=strlen(ch1);
    j=0;
    for(i=0;i<g;i++)
    {
        if(*(ch1+i)==';')
        {
            emp->identifiant=p;
            j=0;
            p=malloc(sizeof(char)*15);
        }
        else if(*(ch1+i)==':')
        {
            emp->date_emprunt=p;
            j=0;
            p=malloc(sizeof(char)*15);
        }
        else if(*(ch1+i)==',')
        {
            emp->date_prevu_retour=p;
            j=0;
            p=malloc(sizeof(char)*15);
        }
        else if(*(ch1+i)=='@')
        {
            emp->etat_eprunt=atoi(p);
        }
        else
        {
            *(p+j)=*(ch1+i);
            j++;
        }
    }
    return emp;
}

/*
    works very great
*/
void write_emprunt(emprunt *tete)
{
    int i,j;
    FILE *fp;
    char *ch,*t;
    ch=malloc(sizeof(char)*12);
    t=malloc(sizeof(char)*3);
    strcpy(ch,"emprunt/   ");
    j=1;
    while(tete!=NULL)
    {
        convert_to_str(j,t);
        *(ch+8)=*t;
        *(ch+9)=*(t+1);
        *(ch+10)=*(t+2);
        *(ch+11)='\0';
       // printf("emprunt ##%s\n",ch);
        fp=fopen(ch,"w");
        fprintf(fp,"%s;%s:%s,%d@",tete->identifiant,tete->date_emprunt,tete->date_prevu_retour,tete->etat_eprunt);
        j++;
        tete=tete->next;
    }
    fclose(fp);
}
///fine working
int books_number()
{
    FILE *fp;
    int *a;
    a=malloc(sizeof(int));
    fp=fopen("livres/a.txt","r");
    fscanf(fp,"%d",a);
    fclose(fp);
    return *a;
}
//////////////////////////////////////////////////
/////////////////////////////////////////////////
////////////////////////////////////////////////
int emprunteur_number()
{
    int *a;
    FILE *fp;
    a=malloc(sizeof(int));
    fp=fopen("emprunteur/a.txt","r");
    fscanf(fp,"%d",a);
    fclose(fp);
    return *a;
}
///////////////////////////////////////
//////////////////////////////////////
int emprunt_number()
{
    FILE *fp;
    int *a;
    a=malloc(sizeof(int));
    fp=fopen("emprunt/a.txt","r");
    fscanf(fp,"%d",a);
    return *a;
}
emprunt* read_all_emprunt(int number)
{
    int i;
    emprunt *a,*b,*c;
    a=read_one_emprunt(1);
    b=a;
    a->privious=NULL;
    for(i=2;i<=number;i++)
    {
        c=read_one_emprunt(i);
        a->next=c;
        c->privious=a;
        a=a->next;
    }
    return b;
}


emprunteur* emprunteur_reader()
{
    emprunteur *a;
    a=malloc(sizeof(emprunteur));
    a->ninscription=malloc(sizeof(char*));
    a->date_inscription=malloc(sizeof(char*));
    a->prenom=malloc(sizeof(char*));
    a->nom=malloc(sizeof(char*));
    a->date_naissance=malloc(sizeof(char*));
    a->adress=malloc(sizeof(char*));
    a->n_telephone=malloc(sizeof(char*));
    printf("donner le numero d' inscription:");
    scanf("%s",a->ninscription);
    printf("donner la date d' inscription:");
    scanf("%s",a->date_inscription);
    printf("donner le prenom:");
    scanf("%s",a->prenom);
    printf("donner le nom:");
    scanf("%s",a->nom);
    printf("donner la date de naissnce:");
    scanf("%s",a->date_naissance);
    printf("donner l' adress:");
    scanf("%s",a->adress);
    printf("donner le numero de telephone:");
    scanf("%s",a->n_telephone);
    return a;
}
emprunt* read_from_user_emprunt()
{
    emprunt *a;
    a=malloc(sizeof(emprunt));
    a->identifiant=malloc(sizeof(char*));
    a->date_emprunt=malloc(sizeof(char*));
    a->date_prevu_retour=malloc(sizeof(char*));
    printf("donner l' identifiant:");
    scanf("%s",a->identifiant);
    printf("donner la date de l' emprunt:");
    scanf("%s",a->date_emprunt);
    printf("donner la date prevu retour:");
    scanf("%s",a->date_prevu_retour);
    printf("donner l' etat 1 si rendu 0 sinon:");
    scanf("%d",&a->etat_eprunt);
    return a;
}
/*
    work great
*/

//      bug fil list  seg fault
livre* read_book_from_user()
{
	int i,a;
    mots_cles *l,*aux;
    livre *new;
    char *ch;
    ch=malloc(sizeof(char*));
    new=malloc(sizeof(livre));
    new->titre=malloc(sizeof(char*));
    new->auteur=malloc(sizeof(char*));
    new->editeur=malloc(sizeof(char*));
    new->date=malloc(sizeof(char*));
    new->ISBN=malloc(sizeof(char*));
    new->categorie=malloc(sizeof(char*));
    new->resume=malloc(sizeof(char*));
    new->info=malloc(sizeof(char*));
    new->list=malloc(sizeof(mots_cles));
    l=new->list;
    printf("donner le titre :");
    scanf("%s",new->titre);
    printf("donner l' auteur:");
    scanf("%s",new->auteur);
    printf("donner l' editeur:");
    scanf("%s",new->editeur);
    printf("donner la date:");
    scanf("%s",new->date);
    printf("donner l' ISBN:");
    scanf("%s",new->ISBN);
    printf("donner la categorie:");
    scanf("%s",new->categorie);
    printf("donner le resume:");
    scanf("%s",new->resume);
    printf("donner les info d' emprunt:");
    scanf("%s",new->info);
    printf("donner le prix:");
    scanf("%d",&new->prix);
    printf("donner la quantite:");
    scanf("%d",&new->quantite);
    printf("combien de mot cles:");
    scanf("%d",&a);
    printf(">>>");
    scanf("%s",ch);
    new->list->mots=ch;
    for(i=0;i<a-1;i++)
    {
        ch=malloc(sizeof(char*));
        aux=malloc(sizeof(mots_cles));
        printf(">>>");
        scanf("%s",ch);
        aux->mots=ch;
        new->list->next=aux;
        new->list=aux;
    }
    new->list=l;
    return new;
}
/*
        works
*/
emprunteur* add_emprunteur(emprunteur *a)
{
    emprunteur *new;
    new=emprunteur_reader();
    new->next=a;
    return new;
}
emprunt* add_emprunt(emprunt *a)
{
    emprunt *new;
    new=read_from_user_emprunt();
    new->next=a;
    new->privious=NULL;
    a->privious=new;
    return new;
}
livre* add_book(livre *l)
{
    livre *new;
    new=read_book_from_user();
    new->suivant=l;
    return new;
}
void print_book(livre *l)
{
    mots_cles *a;
    printf("titre : %s\n",l->titre);
    printf("auteur : %s\n",l->auteur);
    printf("editeur : %s\n",l->editeur);
    printf("date : %s\n",l->date);
    printf("isbn : %s\n",l->ISBN);
    printf("categorie : %s\n",l->categorie);
    printf("resume : %s\n",l->resume);
    printf("info : %s\n",l->info);
    printf("prix : %d\n",l->prix);
    printf("quantite : %d\n",l->quantite);
    a=l->list;
    printf("mots cles : ");
    while(a!=NULL)
    {
        printf("%s,",a->mots);
        a=a->next;
    }
    printf("\n############################\n");
}
void print_emprunteur(emprunteur *a)
{
    printf("n instcription : %s\n",a->ninscription);
    printf("date inscription : %s\n",a->date_inscription);
    printf("prenom : %s\n",a->prenom);
    printf("nom : %s\n",a->nom);
    printf("date naissance : %s\n",a->date_naissance);
    printf("adress : %s\n",a->adress);
    printf("n telephone : %s\n#####################\n",a->n_telephone);
}
void print_emprunt(emprunt *e)
{
    if(e!=NULL)
    {
        printf("identifient : %s\ndate emprunt : %s\ndate prevu retour : %s\n",e->identifiant,e->date_emprunt,e->date_prevu_retour);
        printf("etat : ");
        if(e->etat_eprunt)
        printf("rendu\n#########################\n");
        else
        printf("non rendu\n#########################\n");
    }
}
void print_all_books(livre *l)
{
    livre *parcour;
    parcour=l;
    while(parcour->suivant)
    {
        print_book(parcour);
        parcour=parcour->suivant;
    }
}


void deleter(int book_number,int emprunteur_number,int emprunt_number)
{
    int i;
    char *ch,*t;
    ch=malloc(sizeof(char)*18);
    t=malloc(sizeof(char)*3);
    strcpy(ch,"rm livres/   ");
    for(i=1;i<=book_number;i++)
    {
        convert_to_str(i,t);
        *(ch+10)=*t;
        *(ch+11)=*(t+1);
        *(ch+12)=*(t+2);
        system(ch);
    }
        strcpy(ch,"rm emprunt/   ");
    for(i=1;i<=emprunt_number;i++)
    {
        convert_to_str(i,t);
        *(ch+11)=*t;
        *(ch+12)=*(t+1);
        *(ch+13)=*(t+2);
        system(ch);
    }
    strcpy(ch,"rm emprunteur/   ");
    for(i=1;i<=emprunteur_number;i++)
    {
        convert_to_str(i,t);
        *(ch+14)=*t;
        *(ch+15)=*(t+1);
        *(ch+16)=*(t+2);
        system(ch);
    }
}


void save(livre *book,emprunteur *e,emprunt *e1,int a,int b,int c)
{
    FILE *fp,*fp1,*fp2;
    if(book!=NULL)
    write_books(book);
    if(e!=NULL)
    write_emprunteur(e);
    if(e1!=NULL)
    write_emprunt(e1);
    fp=fopen("livres/a.txt","w");
    fprintf(fp,"%d",a);
    fclose(fp);
    fp2=fopen("emprunt/a.txt","w");
    fprintf(fp2,"%d",c);
    fclose(fp2);
    fp1=fopen("emprunteur/a.txt","w");
    fprintf(fp1,"%d",b);
    fclose(fp1);
}

void main()
{
    livre *a;
    emprunteur *e;
    emprunt *e1;
    int choice,numberofbooks,numberofemprunteur;
    int numberofemprunt,quit,x,y,z,s;
    s=0;
    x=numberofbooks=books_number();
    y=numberofemprunteur=emprunteur_number();
    z=numberofemprunt=emprunt_number();
    a=read_all_books(x);
    e=read_all_emprunteur(y);
    e1=read_all_emprunt(z);
    quit=0;
    while(1-quit)
    {
        printf("[0]aff les livres\n[1]aff les emprunteur\n[2]aff les emprunt\n[3]ajouter un livre\n[4]ajouter un emprunteur\n[5]ajouter un emprunt\n[6]quit\n");
        scanf("%d",&choice);
        if(choice==0 && a!=NULL)
        {
            print_all_books(a);
        }
        else if(choice==0 && a==NULL)
        {

        }
        else if(choice==1 && e!=NULL)
        {
            print_emprunteur(e);
        }
        else if(choice==1 && e==NULL)
        {

        }
        else if(choice==2 && e1==NULL)
        {

        }
        else if(choice==2 && e1!=NULL)
        {
            print_emprunt(e1);
        }
        else if(choice==3)
        {
            a=add_book(a);
            x++;
        }
        else if(choice==4)
        {
            e=add_emprunteur(e);
            y++;
        }
        else if(choice==5)
        {
            e1=add_emprunt(e1);
            z++;
        }
        else
        {
            quit=1;
            printf("[0]enregistrer\n[1]ne pas enregistrer\n");
            scanf("%d",&s);
            if(1-s)
            {
                deleter(numberofbooks,numberofemprunteur,numberofemprunt);
                save(a,e,e1,x,y,z);
            }
        }
    }
}  