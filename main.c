#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define DOSYA_ADI "prolab.txt"

typedef struct Node
{
    char *kelime;
    int miktar;
    struct Node *next;

} node;

node *head = NULL;
node *tail = NULL;

void basa_ekle(node *new);
void sona_ekle(node *new);
int araya_ekle(node *new, int index);
void liste_yazdir();
int miktar_bul(char *str);
int listedemi(char *str);

int main()
{

    FILE *file; 

    char *kelime;
    kelime = (char *)malloc(sizeof(char) * 100);

    file = fopen(DOSYA_ADI, "r");

    while (fscanf(file, "%s", kelime) != EOF)
    {

        if (!head)
        {

            node *new = (node *)malloc(sizeof(node));
            new->kelime = (char *)malloc(sizeof(char) * 100);
            strcpy(new->kelime, kelime);
            new->miktar = miktar_bul(kelime);
            new->next = NULL;

            basa_ekle(new);
            tail = new;
        }
        else
        {

            if (listedemi(kelime))
            {

                node *new = (node *)malloc(sizeof(node));
                new->kelime = (char *)malloc(sizeof(char) * 100);
                strcpy(new->kelime, kelime);
                new->miktar = miktar_bul(kelime);
                new->next = NULL;

                node *tmp;
                tmp = head;
                int index = 0;
                int flag = 1;

                if (new->miktar > head->miktar)
                {
                    basa_ekle(new);
                    tmp = NULL;
                    flag = 0;
                }

                while (tmp)
                {

                    if (new->miktar > tmp->miktar)
                    {
                        araya_ekle(new, index);
                        flag = 0;
                        break;
                    }

                    index++;
                    tmp = tmp->next;
                }

                if (flag)
                    sona_ekle(new);
            }
        }
    }

    liste_yazdir();

    fclose(file);

    return 0;
}

void basa_ekle(node *new)
{

    if (head)
        new->next = head;

    head = new;
}

void sona_ekle(node *new)
{

    if (tail)
        tail->next = new;

    tail = new;
}

int araya_ekle(node *new, int index)
{

    node *tmp = head;

    while (index - 1)
    {

        if (tmp->next != NULL)
            tmp = tmp->next;
        else
            return -1;

        index--;
    }

    node *tmp2 = tmp->next;
    tmp->next = new;
    new->next = tmp2;

    return 1;
}

void liste_yazdir()
{

    int index = 1;
    node *tmp = head;

    while (tmp)
    {
        printf("%d. %s : %d\n", index, tmp->kelime, tmp->miktar);
        index++;
        tmp = tmp->next;
    }
}

int miktar_bul(char *str)
{

    FILE *file2;
    file2 = fopen(DOSYA_ADI, "r");

    int n = 0;
    char *kelime;
    kelime = (char *)malloc(sizeof(char) * 100);

    while (fscanf(file2, "%s", kelime) != EOF)
    {
        if (strcmp(str, kelime) == 0)
            n++;
    }

    fclose(file2);
    return n;
}

int listedemi(char *str)
{

    node *tmp = head;

    int i = 0;

    while (tmp)
    {

        if (strcmp(str, tmp->kelime) == 0)
        {
            return 0;
        }

        i++;
        tmp = tmp->next;
    }

    return 1;
}
