#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MEMSIZE 4096
using namespace std;

class readFile{
	private:
		string fileName;
		FILE *file;
		size_t size;
		char *buff;
		char rom[MEMSIZE];
		int alocSize;
		
		void parseRom(){
			int i = 512;
			printf("Rom transferida..."); // debug
			while(1){
				switch(rom[i] << 8 | rom[i + 1]){
					case 0x6A:
						printf("\nInstrucao 0x%X - %c", rom[i], rom[i]);
						break;
					case 0x7D:
						printf("\nInstrucao 0x%X", rom[i]);
						break;
					default:
						printf("\nInstrucao desconhecida: 0x%X", rom[i]);
						break;
				}
				getch();
				i++;
			}
		}
	public:
		readFile(string N)
		{
			fileName = N;
				if(fileName.length() == 0)
				printf("Nenhum arquivo foi especificado.");
			else{
				printf("%s", fileName.c_str());
			}
		}
		~readFile(){
			delete buff, file, rom;
		}
		
		void init(){
			file = fopen(fileName.c_str(), "rb");
			if(file == NULL)
				perror("Erro ");
			else{
				fseek(file, 0, SEEK_END);
				size = ftell(file);
				rewind(file);
				printf(" - %i bytes\n", size);
				alocSize = size * sizeof(char );
				
				buff = (char *)malloc(alocSize);
				
				if(buff == NULL){
					printf("Erro ao alocar arquivo na memória.");
				}
				else
				{
					int i;
					
					if(fread(buff, 1, size, file))
					{
					
						for(i = 0; i < size; i++)
								rom[i + 512] = buff[i];
					fclose(file);
					}
					if(rom != NULL)
						parseRom();
							else
						printf("Erro ao transferir memória!");
				}
			}
			
		}	
};

int main(int argc, char **argv){
	if(argc > 1){
		readFile rf(argv[1]);
		rf.init();
	}
	cout << "Nenhum arquivo especificado. USO: chip8.exe romname" << endl;
	return 0;
}
