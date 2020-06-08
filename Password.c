#include <stdio.h>
#define ENTER 13
#define TAB 13
#define BKSP 13

char pass[100];

int main()
{
	int i=0;
	char ch;
	
	printf("Ingrese password: ");
	
	while(1)
	{
		//Obtencion de caracter
		ch=getch();
		
		//Si es boton ENTER o TAB
		if(ch==ENTER || ch==TAB)
		{
			pass[i]='\0';
			break;
		}
		//Si el BACKSPACE
		else if(ch==BKSP)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
		}
		else
		{
			pass[i++]=ch;
			//Reemplazar caracter por *
			printf("* \b");
		}
	}
	
	printf("\nPassword: %s",pass);
	
}

