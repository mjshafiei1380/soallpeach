#include <stdio.h>
#include <math.h>


#define MAX_VAL 99999


unsigned long int m;
unsigned long int num;
unsigned long int primes[MAX_VAL];

typedef enum
{
    false,
    true
} bool;



unsigned long int is_prime(unsigned long int n)
{
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (m = 5; m < (unsigned long int)sqrt(n) + 1; m = m + 6)
    {
        if (n % m == 0 || n % (m + 2) == 0)
            return 0;
    }
    return 1;
}

void SieveOfAtkin(bool *sieve,unsigned long int lmt)
{


    for (unsigned long int i = 0; i < lmt; i++)
        sieve[i] = false;
    for (unsigned long int a = 1; a * a < lmt; a++)
    {
        for (unsigned long int b = 1; b * b < lmt; b++)
        {
            // Main part of Sieve of Atkin
            unsigned long int n = (4 * a* a) + (b * b);
            if (n <= lmt && (n % 12 == 1 || n % 12 == 5))
                sieve[n] ^= true;
            n = (3 * a * a) + (b * b);
            if (n <= lmt && n % 12 == 7)
                sieve[n] ^= true;
            n = (3 * a * a) - (b * b);
            if (a > b && n <= lmt && n % 12 == 11)
                sieve[n] ^= true;
        }
    }
    for (unsigned long int r = 5; r * r < lmt; r++)
    {
        if (sieve[r])
        {
            for (unsigned long int i = r * r; i < lmt; i += r * r)
                sieve[i] = false;
        }
    }

    sieve[3]=sieve[5]=sieve[2]=1;
    sieve[4]=sieve[1]=0;

}

int fast_atoi(const char *buff)
{
    int c = 0, x = 0;
    const char *p = buff;

    //for(c = *(p++); (c < 48 || c > 57); c = *(p++)) {if (c == 45) {sign = 1; c = *(p++); break;}}; // eat whitespaces and check sign
    for(c = *(p++); c > 47 && c < 58; c = *(p++)) x = (x << 1) + (x << 3) + c - 48;

    return x;
}


int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    char buf[1000];
    bool sieve[MAX_VAL];
    size_t count;
    SieveOfAtkin(sieve,MAX_VAL);

     char *line_buf = NULL;
     size_t line_buf_size = 0;
     int line_count = 0;
     ssize_t line_size;


//    count = _IO_getline (file, buf, 1000, '\n', 1);
//    puts(buf);

    line_size = getline(&line_buf, &line_buf_size, file);
    while( line_size >= 0)
       {
    line_count++;
    num = fast_atoi(line_buf);

    if(num<=MAX_VAL)
    {
        sieve[num]?putchar_unlocked('1') :putchar_unlocked('0');
        putchar_unlocked('\n');
    }

    else
    {
        is_prime(num)?putchar_unlocked('1'):putchar_unlocked('0');
        putchar_unlocked('\n');
    }
    line_size = getline(&line_buf, &line_buf_size, file);
    }


    fclose(file);
    return 0;
}
