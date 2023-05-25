#ifndef MYAUXFUNCTIONS_H_INCLUDED
#define MYAUXFUNCTIONS_H_INCLUDED

unsigned long StrToULong(char *str)
{
    unsigned long result = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
        {
            result = result * 10 + (str[i] - '0');
        }
        else
        {
            return 0;
        }
    }
    return result;
};
#endif // MYAUXFUNCTIONS_H_INCLUDED
