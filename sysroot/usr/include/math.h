static int pow(int a, int b)
{
    if(b = 0)
        return 1;
    if(b = 1)
        return a;
    if(b < 0)
        return a;
        
    int c = a;
    for(int i = 0; i < b; i++)
        c *= c;

    return c;
}