static inline void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

int main(int argc, char **argv)
{
        int i;
        for (i = 0; i < 999999999; i++) {
                int a = 2;
                int b = 123;
                swap(&a, &b);
        }
        return 0;
}
