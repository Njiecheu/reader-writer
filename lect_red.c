#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

sem_t rd;
pthread_mutex_t mutex;
int cnt = 1;
int nb_lt = 0;

void red(void *wno)
{
    sem_wait(&rd);
    cnt *= 2;
    printf("le redacteur %d a modifie cnt en %d\n", (*((int *)wno)),cnt);
    sem_post(&rd);
}

void lect(void *rno)
{
    // le lecteur acquiert le verrou avant de modifier le nombre de lecteur
    pthread_mutex_lock(&mutex);
    nb_lt++;
    if (nb_lt == 1)
    {
        sem_wait(&rd); // si c'est le premier lecteur il va bloquer le redacteur
    }
    pthread_mutex_unlock(&mutex);
    printf("le lecteur %d: a lu cnt comme %d\n", *((int *)rno),cnt);

    // le lecteur acquiert le verrou avant de modifier le nombre de lecteur
    pthread_mutex_lock(&mutex);
    nb_lt--;
    if (nb_lt == 0)
    {
        sem_post(&rd); // si c'est le dernier lecteur il va reveiller le redacteur
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t rdr[10],wrt[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&rd,0,1);

    int t[10] = {1,2,3,4,5,6,7,8,9,10};

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&rdr[i],NULL,(void *)lect, (void *)&t[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&wrt[i],NULL,(void *)red, (void *)&t[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_join(rdr[i],NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(wrt[i],NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&rd);

    return 0;
}