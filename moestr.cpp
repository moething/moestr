/*
Copyright (c) Moe~/moething
Licensed under MIT License

This flie provides the basic string search algorithm
All functions return the offset where the first substring appears
*/

#include "moestr.h"

int Str_Len(char* str)
{
	int i = 0;
	for (; str[i] != '\0'; i++);
	return(i);
}

//Searching String Using Sunday Algorithm
int Str_Sunday(char* str, char* sub)
{
	int c = Str_Len(sub);
	int i = 0, j = 0;
	int *s = (int*)malloc(256 * sizeof(int));
	if (s == NULL)return(-1);
	//processing for the skip array
	j = c + 1;
	for (i = 0; i < 256; s[i] = j, i++);
	for (i = 1; i <= c; i++)
	{
		if (s[sub[c - i]]>i)s[sub[c - i]] = i;
	}
	//finding the string
	i = 0;
	while (str[i + c] != '\0')
	{
		for (j = 0; (str[i + j] == sub[j]) && (str[i + j] != '\0'); j++)
		{
			if (c - j == 1)
			{
				free(s);
				return(i);
			}
		}
		i += s[str[i + c]];
	}
	free(s);
	return(-1);
}

//Searching String Using Boyer-Moore Algorithm
int Str_BM(char* str, char* sub)
{
	int c = Str_Len(sub);
	int i = 0, j = 0;
	int *m = (int*)malloc(256 * sizeof(int));
	int *n = (int*)malloc(c * sizeof(int));
	int *o = (int*)malloc(c * sizeof(int));
	if (!(m&&n))
	{
		if (m)free(m);
		if (n)free(n);
		return(-1);
	}
	//processing for the bc array
	for (; i < 256; m[i] = c, i++);
	j = c - 1;
	for (i = 0; i < c; i++)
	{
		if (m[sub[j - i]]>i)m[sub[j - i]] = i;
	}
	//processing for the gs array
	i = c - 1;
	j = c - 2;
	n[i] = 1;
	o[i] = 0;
	o[j] = 0;
	//for case 1
	while (j > 0)
	{
		n[j] = c;
		if (sub[i] == sub[j])
		{
			i--;
			j--;
			o[j] = c - 1 - i;
			if (sub[i] != sub[j])
			{
				n[i] = i - j;
				i = c - 1 - o[i];
			}
		}
		else
		{
			i = c - 1;
			j--;
			o[j] = 0;
		}
	}
	//for case 2
	if (i != c - 1)
	{
		j = i - j;
		while (i > 0)
		{
			i--;
			n[i] = j;
		}
	}
	else
	{
		n[j] = i;
	}
	free(o);
	//finding the string
	i = 0;
	while (str[i] != '\0')
	{
		for (j = c - 1; str[i + j] == sub[j]; j--)
		{
			if (j == 0)
			{
				free(m);
				free(n);
				return(i);
			}
		}
		if (m[str[i + j]] > n[j + 1])
		{
			i += m[str[i + j]];
		}
		else
		{
			i += n[j];
		}
	}
	free(m);
	free(n);
	return(-1);
}

//Searching String Using Knuth-Morris-Pratt Algorithm
int Str_KMP(char* str, char* sub)
{
	int c = Str_Len(sub);
	int i = 0, j = -1;
	int *s = (int*)malloc(c*sizeof(int));
	if (s == NULL)return(-1);
	//processing for the "next" array
	s[0] = -1;
	c--;
	while (i < c)
	{
		if ((j == -1) || (sub[i] == sub[j]))
		{
			i++;
			j++;
			if (sub[i] != sub[j])
			{
				s[i] = j;
			}
			else
			{
				s[i] = s[j];
			}
		}
		else
		{
			j = s[j];
		}
	}
	c++;
	//finding the string
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sub[j])
		{
			i++;
			j++;
			if (j == c)
			{
				free(s);
				return(i - j);
			}
		}
		else
		{
			j = s[j];
			if (j == -1)
			{
				i++;
				j = 0;
			}
		}
	}
	free(s);
	return(-1);
}

//Searching String Using No Algorithm
int Str_BF(char* str, char* sub)
{
	int i = 0, j = 0;
	while (1)
	{
		for (; !((str[i] == sub[0]) || (str[i] == '\0')); i++);
		if (str[i] == '\0')
		{
			return(-1);
		}
		for (j = 0; (str[i + j] == sub[j]) && (str[i + j] != '\0'); j++)
		{
			if (sub[j + 1] == '\0')
			{
				return(i);
			}
		}
		if (str[i + j] == '\0')
		{
			return(-1);
		}
		i++;
	}
}
