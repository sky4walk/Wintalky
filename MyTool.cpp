#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

char* FileRead(char* FileName)
{
	char* dat = NULL;
	FILE *file = fopen(FileName,"rb");
	if(file!=NULL)
	{
		fseek(file,0,SEEK_END);
		long len = ftell(file);
		fseek(file,0,SEEK_SET);	
		dat = new char[len+1];
		int i;
		char buffer;
		long pos = 0;
		do
		{
			i = fread(&buffer,sizeof(buffer),1,file);
			if(i>0)
			{
				dat[pos++]= buffer;
			}

		}while(i>0&&pos<len);
		dat[pos] = 0;
		fclose(file);
	}
	return dat;
}

int main(int argc,char** argv)
{
	int errorlevel = 0;
	if(argc>1)
	{
		char* cmd = argv[1];
		if(strcmp(cmd,"ir")==0)
		{
			if(argc==5)
			{
				char szText[255];
				DWORD ret = GetPrivateProfileString(argv[2],argv[3],NULL,szText,255,argv[4]);
				if(ret==0)
				{
					printf("empty\n");
					errorlevel = 1;
				}
				else
				{
					printf("%s",szText);
				}
			}
			else
			{
				printf("Usage: %s ir <Head> <Key> <INI-File>\n",argv[0]);
				errorlevel = 1;
			}
		}
		else if(strcmp(cmd,"iw")==0)
		{
			if(argc==6)
			{
				char* dat = FileRead(argv[4]);
				if(dat!=NULL)
				{
					
					if(WritePrivateProfileString(argv[2],argv[3],dat,argv[5])==FALSE)
					{
						printf("error writing\n");
						errorlevel = 1;
					}
				}
				else
				{
					printf("Input File Error %s\n",argv[4]);
					errorlevel = 1;
				}
			}
			else
			{
				printf("Usage: %s iw <Head> <Key> <Text> <INI-File>\n",argv[0]);
				errorlevel = 1;
			}
		}
		else if(strcmp(cmd,"sl")==0)
		{
			if(argc==3)
			{
				int scnds = atoi(argv[2]);
				printf("%d\n",scnds);
				Sleep(scnds*1000);
			}
			else
			{
				printf("Usage: %s sl <Seconds> \n",argv[0]);
				errorlevel = 1;
			}
		}
		else if(strcmp(cmd,"kb")==0)
		{
			if(argc==2)
			{
				errorlevel = getch();
			}
			else
			{				
				printf("Usage: %s kb \n",argv[0]);
			}
		}
		else if(strcmp(cmd,"mb")==0)
		{
			if(argc==5)
			{
				int ent = atoi(argv[4]);
				int type = 0;
				switch(ent)
				{
				case 1: 
					{
						type = MB_YESNO;
						break;
					}
				case 2:
					{
						type = MB_OKCANCEL;
						break;
					}
				case 3:
					{
						type = MB_RETRYCANCEL;
						break;
					}
				case 4:
					{
						type = MB_YESNOCANCEL;
						break;
					}
				default:
					type = MB_OK;

				}
				errorlevel = MessageBoxEx(NULL,argv[2],argv[3],type,MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
			}
			else
			{				
				printf("Usage: %s mb <Text> <Caption> <Type>\n",argv[0]);
				printf("Type 0: OK\n");
				printf("Type 1: YesNo\n");
				printf("Type 2: OkCancel\n");
				printf("Type 3: RetryCancel\n");
				printf("Type 4: YesNoCancel\n");
				errorlevel = 1;
			}
		}
		else if(strcmp(cmd,"rr")==0)
		{
			if(argc==5)
			{
				int keyNr = atoi(argv[2]);
				HKEY hKey = 0;
				switch(keyNr)
				{
				case 1:
					hKey = HKEY_CLASSES_ROOT;
					break;
				case 2:
					hKey = HKEY_CURRENT_USER;
					break;
				case 3:
					hKey = HKEY_LOCAL_MACHINE;
					break;
				case 4:
					hKey = HKEY_USERS;
					break;
				default:
					break;
				}

				HKEY hKeyOut;
				long lResult = 0;
				DWORD dwValue = 0;

				lResult = RegOpenKeyEx(hKey,argv[3],0,KEY_ALL_ACCESS,&hKeyOut) ;
				if(lResult == ERROR_SUCCESS)
				{
					DWORD dwValueType = 0;
					DWORD dwValueLen = 0;
					lResult = RegQueryValueEx(hKeyOut,argv[4],0,&dwValueType,0,&dwValueLen);
					if(lResult==ERROR_SUCCESS)
					{
						if(dwValueType==REG_SZ||dwValueType==REG_EXPAND_SZ||dwValueType==REG_MULTI_SZ)
						{
							LPSTR lpReturnStr = new char[dwValueLen];
							lResult = RegQueryValueEx(hKeyOut,argv[4],0,&dwValueType,(unsigned char *)lpReturnStr, &dwValueLen);
							if (lResult == ERROR_SUCCESS)
							{
								printf("%s",lpReturnStr);
							}
							else
							{
								printf("Error reading\n");
								errorlevel = 1;
							}
							delete lpReturnStr;
						}
						else if (dwValueType == REG_DWORD||dwValueType == REG_BINARY)
						{
							lResult = RegQueryValueEx(hKeyOut,argv[4],0,&dwValueType,(unsigned char *)&dwValue, &dwValueLen);
							if (lResult == ERROR_SUCCESS)
							{
								printf("%d",dwValue);
							}
							else
							{
								printf("Error reading\n");
								errorlevel = 1;
							}
						}
						else
						{
							printf("ValueName not found\n");
							errorlevel = 1;
						}
					}
					RegCloseKey(hKeyOut);
				}
				else
				{
					printf("Key or Subkey not found\n");
					errorlevel = 1;
				}
			}
			else
			{
				printf("Usage: %s rr <KEY> <Subkey> <ValueName>\n",argv[0]);
				printf("KEY 1: HKEY_CLASSES_ROOT\n");
				printf("KEY 2: HKEY_CURRENT_USER\n");
				printf("KEY 3: HKEY_LOCAL_MACHINE\n");
				printf("KEY 4: HKEY_USERS\n");
				printf("Example: %s rr 3 \"SYSTEM\\\\CurrentControlSet\\\\Control\\\\Session Manager\\\\Environment\" Path\n",argv[0]);
				errorlevel = 1;
			}
		}
		else if(strcmp(cmd,"rw")==0)
		{
			if(argc==7)
			{
				int keyNr = atoi(argv[2]);
				HKEY hKey = 0;
				switch(keyNr)
				{
				case 1:
					hKey = HKEY_CLASSES_ROOT;
					break;
				case 2:
					hKey = HKEY_CURRENT_USER;
					break;
				case 3:
					hKey = HKEY_LOCAL_MACHINE;
					break;
				case 4:
					hKey = HKEY_USERS;
					break;
				default:
					break;
				}
				int tpNr = atoi(argv[5]);
				DWORD regtype = 0;
				switch(tpNr)
				{
				case 1:
					regtype = REG_DWORD;
					break;
				default:
					regtype = REG_SZ;
				}
				HKEY hKeyOut;
				long lResult = 0;
				DWORD dwValue = 0;

				lResult = RegOpenKeyEx(hKey,argv[3],0,KEY_ALL_ACCESS,&hKeyOut) ;
				if(lResult == ERROR_SUCCESS)
				{
					if(regtype==REG_SZ)
					{
						lResult = RegSetValueEx(hKeyOut,argv[4],NULL,REG_SZ,(CONST BYTE*)argv[6],strlen(argv[6]));
						if(lResult!= ERROR_SUCCESS)
						{
							printf("writing error\n");
							errorlevel = 1;
						}
					}
					else if(regtype==REG_DWORD)
					{
						int value = atoi(argv[6]);
						lResult = RegSetValueEx(hKeyOut,argv[4],NULL,REG_DWORD,(CONST BYTE*)&value,sizeof(value));
						if(lResult!= ERROR_SUCCESS)
						{
							printf("writing error\n");
							errorlevel = 1;
						}
					}
					else
					{
						printf("wrong type\n");
						errorlevel = 1;
					}
					RegCloseKey(hKeyOut);
				}
				else
				{	
					printf("Key or Subkey not found\n");
					errorlevel = 1;
				}
			}
			else
			{
				printf("Usage: %s rw <KEY> <Subkey> <ValueType> <ValueName>\n",argv[0]);
				printf("KEY 1: HKEY_CLASSES_ROOT\n");
				printf("KEY 2: HKEY_CURRENT_USER\n");
				printf("KEY 3: HKEY_LOCAL_MACHINE\n");
				printf("KEY 4: HKEY_USERS\n");
				printf("ValueType 1: REG_DWORD\n");
				printf("ValueType 2: REG_SZ\n");
				printf("Example: %s rw 3 \"SYSTEM\\\\CurrentControlSet\\\\Control\\\\Session Manager\\\\Environment\" Neu 2 Test\n",argv[0]);
				errorlevel = 1;
			}
		}
		else if(strcmp(cmd,"fe")==0)
		{
			if(argc==4)
			{
				FILE *file1 = fopen(argv[2],"r");
				if(file1!=NULL)
				{
					FILE *file2 = fopen(argv[3],"r");
					if(file2!=NULL)
					{
						char buffer1[1];
						char buffer2[1];
						fseek(file1, 0, SEEK_SET);
						fseek(file2, 0, SEEK_SET);
						int i1 = 0;
						int i2 = 0;
						BOOL equal = TRUE;
						do
						{
							i1 = fread(buffer1,sizeof(buffer1),1,file1);
							i2 = fread(buffer2,sizeof(buffer2),1,file2);
							if(i1!=i2||buffer1[0]!=buffer2[0])
							{
								equal = FALSE;
								errorlevel = 1;
							}
						}while(equal&&i1>0&&i2>0);
						
						fclose(file2); 
					}
					else
					{
						printf("file2 not found\n");
						errorlevel = 1;
					}
					fclose(file1); 
				}
				else
				{
					printf("file1 not found\n");
					errorlevel = 1;
				}
			}
			else
			{
				printf("Usage: %s fe <file1> <file2>\n",argv[0]);
				errorlevel = 1;
			}
		}
		else
		{
			printf("Usage: %s <cmnd>    - Show help to commands\n",argv[0]);
			printf("Usage: %s iw        - write into Inifile \n",argv[0]);
			printf("Usage: %s ir        - read from Inifile \n",argv[0]);
			printf("Usage: %s sl        - sleeping \n",argv[0]);
			printf("Usage: %s kb        - set ERRORLEVEL from keyboard\n",argv[0]);
			printf("Usage: %s rr        - registry read \n",argv[0]);
			printf("Usage: %s rw        - registry write \n",argv[0]);
			printf("Usage: %s fe        - compare files \n",argv[0]);
		}

	}
	else
	{
		printf("(C) Andre Betz 2006 mail@AndreBetz.de\n");
		printf("Usage: %s <cmnd> \n",argv[0]);
		printf("Usage: %s ?  -  list commands\n",argv[0]);
	}

	return errorlevel;
}
