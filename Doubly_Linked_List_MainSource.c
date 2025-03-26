#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>


typedef struct Node
{
    int data;
    struct Node* Next;
    struct Node* Prev;
}node;

int SayiVarMi(node* r, int data)
{
    node* iter = r;
    while(iter != NULL)
    {
        if(iter->data == data)
            return 1;
        iter = iter->Next;
    }
    return 0;
}

node* YeniListeOlusturVeListele(node* r, int data, int N)
{
    if(r == NULL)
    {
        r = (node*)malloc(sizeof(node));
        r->Next = NULL;
        r->Prev = NULL;
        r->data = data;
        return r;
    }
	
	if(!SayiVarMi(r,data))
	{
	    node* iter = r;
    	while(iter->Next != NULL)
    	{
        	iter = iter->Next;
    	}   

    	node* temp = (node*)malloc(sizeof(node));
    	temp->Next = NULL;
    	iter->Next = temp;
    	temp->Prev = iter;
    	temp->data = data;
	}
	else
	{
		int yeni_sayi;
        do
        {
            yeni_sayi = rand() % N + 1;
        }while (SayiVarMi(r, yeni_sayi));

        r = YeniListeOlusturVeListele(r, yeni_sayi, N);
	}
    return r;
}

int SaymaIslemiYap(struct Node* head) 
{
    struct Node* start = head;
    struct Node* end = head;
    int sagToplam = 0;
    int solToplam= 0;

    while(end->Next != NULL) 
	{
        end = end->Next;
    }
	
	int kontrol = 0;
    while(start != NULL && end != NULL && start != end && start->Prev!=end) 
	{
        printf("Bastan: %d, Sondan: %d\n", start->data, end->data);
        if(start->Next==end)
        {
            if(abs(kontrol+start->data) > abs(kontrol - start->data))
            {
                kontrol -= start->data;
            }
            else
            {
                kontrol+=start->data;
            }

            if(abs(kontrol+end->data) > abs(kontrol - end->data))
            {
                kontrol -= end->data;
            }
            else
            {
                kontrol+=end->data;
            }

        }
        else
        {
            kontrol += start->data-end->data;
        }
        start = start->Next;
        end = end->Prev;
    }
    
	if(start != NULL && start == end) 
	{
        printf("Orta Eleman: %d\n", start->data);
        if(abs(kontrol-(start->data))<abs(kontrol+(start->data)))
        {
        	kontrol -= (start->data);
        	return abs(kontrol);
		}
		else
		{
			kontrol += (start->data);
			return abs(kontrol);
		}
        start=start->Next;
        if(abs(kontrol - start->data) < abs(kontrol + start->data))
        {
            kontrol-=start->data;
        }
        else
        {
            kontrol+=start->data;
        }

        start->Prev->Prev;
        if(abs(kontrol - start->data) < abs(kontrol + start->data))
        {
            kontrol-=start->data;
        }
        else
        {
            kontrol+=start->data;
        }

    }
    else
    {
    	kontrol = abs(kontrol);
        return kontrol;
	}
}

void BasaEkle(node** bas, int data) 
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->Next = (*bas);
    new_node->Prev = NULL;

    if((*bas) != NULL) 
        (*bas)->Prev = new_node;

    (*bas) = new_node;
}

void SonaEkle(node** bas, int data) 
{
    node* new_node = (node*)malloc(sizeof(node));
    node* son = *bas;
    new_node->data = data;
    new_node->Next = NULL;

    while(son->Next != NULL) 
    {
        son = son->Next;
    }

    son->Next = new_node;
    new_node->Prev = son;
}

void DugumEkleyerekFarkiEsitle(node* root, int N)
{
    struct Node* start = root;
    struct Node* end = root;

    while(end->Next != NULL) 
	{
        end = end->Next;
    }

    int kontrol = 0;
    while(start != NULL && end != NULL && start != end && start->Prev!=end) 
	{
        //printf("Bastan: %d, Sondan: %d\n", start->data, end->data);
        if(start->Next==end)
        {
            if(abs(kontrol+start->data) > abs(kontrol - start->data))
            {
                kontrol -= start->data;
            }
            else
            {
                kontrol+=start->data;
            }

            if(abs(kontrol+end->data) > abs(kontrol - end->data))
            {
                kontrol -= end->data;
            }
            else
            {
                kontrol+=end->data;
            }
        }
        else
        {
            kontrol += start->data-end->data;
        }
        start = start->Next;
        end = end->Prev;
    }
    
	if(start != NULL && start == end) 
	{
        if(abs(kontrol-(start->data))<abs(kontrol+(start->data)))
        {
        	kontrol -= (start->data);
		}
		else
		{
			kontrol += (start->data);
		}
    }
    if(kontrol < 0)
    {
        kontrol = abs(kontrol);
        BasaEkle(&root, kontrol);
        printf("\n\nYeni Dugum Basa Eklendi (%d)\n",kontrol);
    }
    else
    {
        printf("\n\nYeni Dugum sona Eklendi (%d)\n",kontrol);
        SonaEkle(&root, kontrol);
    }

    int sonuc = SaymaIslemiYap(root);
    printf("Yeni fark: %d",sonuc);
}

void DugumSil(node** bas, int data) 
{
    node* temp = *bas;
    if(temp != NULL && temp->data == data) 
    {
        *bas = temp->Next;
        if(temp->Next != NULL) 
            temp->Next->Prev = NULL;
        free(temp);
        printf("Silinen dugum: %d\n", data);
        return;
    }

    while(temp != NULL && temp->data != data) 
    {
        temp = temp->Next;
    }


    if(temp == NULL) 
    {
        printf("Data bulunamadi: %d\n", data);
        return;
    }

    if(temp->Next != NULL) 
        temp->Next->Prev = temp->Prev;
    if(temp->Prev != NULL)
        temp->Prev->Next = temp->Next;
    free(temp);
    printf("\nSilinen dugum: %d\n", data);
}




void DugumCikararakFarkiEsitle(node** bas)
{
    int eklenecekSayi = SaymaIslemiYap(*bas);
    node* start = *bas;
    node* end = *bas;

    while(end->Next != NULL)
    {
        end = end->Next;
    }

    if(eklenecekSayi < 0)
    {
        while(start != NULL && end != NULL && start != end && start->Prev!=end)
        {
            if((start->data - end->data) == eklenecekSayi)
            {
                DugumSil(bas, start->data);
                DugumSil(bas, end->data);
            }
            else if(start->data == abs(eklenecekSayi))
            {
                DugumSil(bas, start->data);
            }
            else if(end->data == abs(eklenecekSayi))
            {
                DugumSil(bas, end->data);
            }
            end = end->Prev;
            start = start->Next;
        }
    }
    else
    {
        while(start != NULL && end != NULL && start != end && start->Prev!=end)
        {
            if((start->data + end->data) == eklenecekSayi)
            {
                DugumSil(bas, start->data);
                DugumSil(bas, end->data);
            }
            else if(start->data == abs(eklenecekSayi))
            {
                DugumSil(bas, start->data);
            }
            else if(end->data == abs(eklenecekSayi))
            {
                DugumSil(bas, end->data);
            }
            end = end->Prev;
            start = start->Next;
        }
    }
    int sonuc = SaymaIslemiYap(*bas);
    printf("Yeni Fark: %d",sonuc);
}


void Yazdir(node* iter)
{
    if (iter == NULL)
    {
        printf("\nListe Bos\n");
        return;
    }
    while (iter != NULL)
    {
        printf("%d  ", iter->data);
        iter = iter->Next;
    }
    printf("\n");
}

int main()
{
    node* root = NULL;
    srand(time(NULL));
    

    int secim;
    
    printf("1)YeniListeOlustur ve Goruntule\n2)SaymaIslemiYap\n3)DugumEkleyerekFarkiEsitle\n4)DugumCikararakFarkiEsitle\n0)Cikis");
while(1)
{   
    int N = rand() % 5 + 5;
    printf("\nSecim yapiniz--->");
    scanf("%d",&secim);
    switch (secim)
    {
        case 0:
        {
            printf("Cikis Yapildi");
            exit(1);
            break;
        }
        case 1:
        {
            printf("Olusturulacak rastgele sayi sayisi: %d\n", N);
            while (root != NULL) 
            {
            node* temp = root;
            root = root->Next;
            free(temp);
            }
            
            int sayi;
            for (int i = 0; i < N; i++)
            {
                sayi = rand() % N + 1;
                root = YeniListeOlusturVeListele(root, sayi, N);
            }
            printf("Olusturulan rastgele sayilar: ");
            Yazdir(root);
            break;
        }
        case 2:
        {
            int sonuc = SaymaIslemiYap(root);
	        printf("fark: %d",sonuc);
            break;
        }
        case 3:
        {
            DugumEkleyerekFarkiEsitle(root,N);
            break;
        }
        case 4:
        {
            DugumCikararakFarkiEsitle(&root);
            break;
        }
        default:
            break;
    }
}

 
	
//	SaymaIslemiYap(root);
    
	
    return 0;
}

