#include <stdio.h>

void makeNullEvent(int *E[], int nullNumber, int size)
{
    for (int i = 1; i <= size; i++)
        *E[i] = nullNumber;
}

int isPrime2(int a, int b)
{
    for (int i = 2; i <= a; i++)
        if (a % i == 0 && b % i == 0)
            return 0;
    return 1;
}

void sort(int a[], int n){
    int tg;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(a[i] > a[j]){
                // Hoan vi 2 so a[i] va a[j]
                tg = a[i];
                a[i] = a[j];
                a[j] = tg;        
            }
        }
    }
}
//int endEvent(int E[], int nullNumber)
//{
//    int count = 0;
//    for (int i = 1; i <= 1001; i++)
//        if (E[i] != nullNumber)
//            count++;
//    return count;
//}

//a
void foundTSLG(int *TSLG)
{
    *TSLG += 1;
}

//c
int isPrime(int a)
{
    if (a == 0 || a == 1)
        return 0;
    for (int i = 2; i < a; i++)
        if (a % i == 0)
            return 0;
    return 1;
}

int canFight(int R, int HP, int M, int currentEvent, int E[], int ID)
{
    int h1 = currentEvent % (100 + R);
    int h2 = E[currentEvent] % (100 + R);
    if (isPrime(h2) != 0 && h2 <= M && ID == 1 && E[currentEvent] < 200)
        return 1;
    int result = h1 - h2;
    if (result >= 0)
        return 1;
    else
        return 0;
}

//b
int fight(int R, int *HP, int *M, int currentEvent, int cloak, int E[], int ID)
{
    if (cloak == 1)
    {
        if (canFight(R, *HP, *M, currentEvent, E, ID) == 0)
        {
            currentEvent++;
            return -1;
        }
    }

    int h1 = currentEvent % (100 + R);
    int h2 = E[currentEvent - 1] % (100 + R);
    if (isPrime(h2) != 0 && h2 <= *M && ID == 1 && E[currentEvent - 1] < 200)
    {
        *M += E[currentEvent - 1];
        if (*M > 999)
            *M = 999;
        return 1;
    }

    int result = h1 - h2;
    if (result >= 0)
    {
        *M += E[currentEvent - 1];
        if (*M > 999)
            *M = 999;
        return 1;
    }
    else
    {
        *HP -= E[currentEvent - 1];
        return 0;
    }
}

//d
void takeABreak(int *M, int *HP, int maxHP)
{
    int denta = maxHP - *HP;
    if (*M >= denta)
    {
        *HP += denta;
        *M -= denta;
    }
    else
    {
        *HP += *M;
        *M = 0;
    }
}

//e
void theHaughtyRon(int R, int *M, int *HP, int maxHP)
{
	if (*M < 3)
		return;
    int P;
    for (int i = 2; i < R; i++)
        if (isPrime(i))
            P = i;
    while(*M >= P)
    {
    	*HP++;
    	if(*HP == maxHP)
    		break;
    	*M-=P;
	}
}

//f g

void foundMuggle(int *M, int E[], int *currentEvent, int cloak, int *meetMuggle, int *turnARound, int *HP)
{
    if (cloak == 1)
    {
        *currentEvent++;
        return;
    }
    if (*meetMuggle == 1)
    {
        *meetMuggle--;
        return;
    }
    int XX = E[*currentEvent - 1] - 200;
    int dentaM = *M - XX;
    if (dentaM <= 4 && *turnARound != 1)
    {
        if (*currentEvent < 3)
        {
        	*HP = 0;
			return;
		}
        *currentEvent -= 3;
        *meetMuggle = 1;
        *turnARound = 1;
        return;
    }
    int rM, i = 1;
    while (1)
    {
        rM = i * i;
        i++;
        if((i*i) > dentaM)
        	break;
    }
    *M = rM;
}

//h
void foundSphinx(int R, int *HP, int *M, int currentEvent, int *cloak, int E[], int ID, int *TSLG)
{
    if (*cloak == 1)
        return;
    int tmp_HP = *HP;
    int result = fight(R, &tmp_HP, M, currentEvent, *cloak, E, ID);
    if (result == 0)
        *TSLG = 0;
    else if (result == 1)
        *cloak = 1;
}

//i
void foundGiant(int R, int *HP, int *M, int ID, int currentEvent, int E[], int cloak)
{
    int XX = E[currentEvent] - 500;
    if (ID == 2 || ID == 4)
    {
        if (isPrime2(XX, *HP))
            return;
    }
    int result = fight(R, HP, M, currentEvent, cloak, E, ID);
    if (result == 1)
        return;
    else
    {
        int Q = 1;
        for (int i = 2; i < XX; i++)
            if (isPrime(i) == 1 && XX % i == 0)
                Q = i;
        if (Q > *M)
            *M = 0;
        else
            *M -= Q;
    }
}

//j
void foundBellatrix(int R, int *HP, int *M, int cloak, int currentEvent, int E[], int size, int ID, int *TSLG)
{
    if (cloak == 1)
        return;
    int E_tmp[size];
    for (int i = 0; i < size; i++)
        E_tmp[i] = E[i];
    sort(E_tmp, size);
    int result = fight(R, HP, M, currentEvent, cloak, E, ID);
    if (result == 0)
    {
        int lienTiep = 0;
        int maxLienTiep = 0;
        for (int i = 0; i < size; i++)
        {
            if (E_tmp[i] + 1 == E_tmp[i + 1])
                lienTiep++;
            else
                lienTiep = 0;
            if (lienTiep > maxLienTiep)
                maxLienTiep = lienTiep;
        }
        if (*TSLG < maxLienTiep)
            *TSLG = 0;
        else
            *TSLG -= maxLienTiep;
    }
    else
        *TSLG--;
}

void foundSnape(int R, int *HP, int *M, int ID, int cloak, int *elderWand, int Fibo[])
{
    if (cloak == 1)
        return;
    if (ID == 4)
        *HP = -1;
    else if (ID == 1)
    {
        *HP = 999;
        *M = 999;
        *elderWand = 1;
    }
    else
    {
        int i = 0;
        while (Fibo[i] < *HP)
            i++;
        *HP = Fibo[i];
    }
}

void foundBoss(int R, int *HP, int *M, int ID, int currentEvent, int E[], int cloak, int Fibo[], int elderWand, int maxHP)
{
    int checkFibo = 0;
    for (int i = 0; i < 15; i++)
        if (currentEvent == Fibo[i])
        {
            checkFibo = 1;
            break;
        }
    if (ID == 1 && elderWand == 1)
    {
        *HP = maxHP;
        *M = 999;
    }
    else if (checkFibo == 1)
    {
        int result = fight(R, HP, M, currentEvent, cloak, E, ID);

        if (result == 0)
            *HP = -1;
        else
        {
            *HP = maxHP;
            *M = 999;
        }
    }
    else
        *HP = -1;
}

void journey(int R, int N, int ID, int M, int E[], int size)
{
    //makeNullEvent;
	int HP = 0;
    int maxHP = 0;
    int currentEvent = 1;
    const int nullNumber = -1000000;
    int TSLG = 0;
    int meetMuggle = 0;
    int turnAround = 0;
    int cloak = 0;
    int Fibo[15] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987};
    int elderWand = 0;
    switch (ID)
    {
    case 1:
        HP = 999;
        maxHP = 999;
        break;
    case 2:
        HP = 900;
        maxHP = 900;
        break;
    case 3:
        HP = 888;
        maxHP = 888;
        break;
    case 4:
        HP = 777;
        maxHP = 777;
        break;
    default:
        break;
    }
    while (currentEvent <= size && TSLG < N && HP > 0)
    {
        if (E[currentEvent - 1] == 0)
        {
            foundTSLG(&TSLG);
        }
        else if (E[currentEvent - 1] == 1)
        {
            if (ID == 3)
                theHaughtyRon(R, &M, &HP, maxHP);
            else
                takeABreak(&M, &HP, maxHP);
        }
        else if (E[currentEvent - 1] < 200 && E[currentEvent - 1] > 100)
        {
            fight(R, &HP, &M, currentEvent, cloak, E, ID);
        }
        else if (E[currentEvent - 1] > 200 && E[currentEvent - 1] < 300)
            foundMuggle(&M, E, &currentEvent, cloak, &meetMuggle, &turnAround, &HP);
        else if (E[currentEvent - 1] > 300 && E[currentEvent - 1] < 400)
            foundSphinx(R, &HP, &M, currentEvent, &cloak, E, ID, &TSLG);
        else if (E[currentEvent - 1] > 500 && E[currentEvent - 1] < 600)
            foundGiant(R, &HP, &M, ID, currentEvent, E, cloak);
        else if (E[currentEvent - 1] == 666)
            foundBellatrix(R, &HP, &M, cloak, currentEvent, E, size, ID, &TSLG);
        else if (E[currentEvent - 1] == 777)
            foundSnape(R, &HP, &M, ID, cloak, &elderWand, Fibo);
        else if (E[currentEvent - 1] == 999)
            foundBoss(R, &HP, &M, ID, currentEvent, E, cloak, Fibo, elderWand, maxHP);
        currentEvent++;
    }
    if (TSLG == N)
        printf("%d", HP + M);
    else if (TSLG < N)
    {
        if (HP == -1)
            printf("-1");
        else
            printf("0");
    }
    return;
}

int main()
{
	int list8 [] = {0,108,0,234,235,0,666,0,0,0,0,0,106,107,0};
	journey(0,5,4,711, list8 ,15);
}
