#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc==4)
		{
			FILE *fp;

			if((fp = fopen(argv[3],"r+")))
			{
				int klen=strlen(argv[1]);

				for (int i = 0; i < klen; ++i)
				{
					if (isalpha(argv[1][i])==0)
					{
						printf("Key index %d not alpha!\n", i);
						exit(1);
					}
				}

				fseek(fp,0,SEEK_SET);
				char c;
				int l = 0;
				while(1)
				{
					if(feof(fp))
						break;
					fgetc(fp);
					l++;
				}

				fseek(fp,0,SEEK_SET);

				
				for (int i = 0,j = 0; i < l; ++i, ++j)
				{

					if(j==strlen(argv[1]))
						j=0;

					int k = tolower(argv[1][j]) - 97;

					c = fgetc(fp);	
					
					fseek(fp,ftell(fp)-1,SEEK_SET);

					if(argv[2][0] == '+' || argv[2][0] == '-')
						{
							if(argv[2][0] == '-')
								k *= -1;

							fputc(c+k, fp);
						}
					else
						printf("Specify +/-\n\n USAGE: encrypt [key(alphabetical)] ['+'/'-'] [file address]\n");
					//printf("%c\n", c);
				}
				fclose(fp);
			}

			else
				printf("Unable to open file.\n\n USAGE: encrypt [key(alphabetical)] ['+'/'-'] [file address]\n");
		}
	else
		printf("USAGE: encrypt [key(alphabetical)] ['+'/'-'] [file address]\n");
	return 0;
}