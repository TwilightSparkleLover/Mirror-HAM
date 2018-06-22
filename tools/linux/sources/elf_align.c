#include <stdio.h>
#include <string.h>
//#include <process.h>
#include <malloc.h>

#include "elf.h"

char	*memory=NULL;

Elf32_Ehdr	Header;
FILE		*fp = NULL;

Elf32_Shdr	*sections=NULL;

int	ALIGN = 0;

void	end(unsigned char * string,int reply)
{
	if(memory)free(memory);
	if(sections) free(sections);
	if(fp)	fclose(fp);
	printf(string);
	exit(reply);
}

int	main(int argc , char *argv[])
{
	unsigned int		amount,i;

	if(argc != 3)	end("elf <input> align",-1);

	fp = fopen(argv[1],"r+b");
	if(fp == NULL)
	{
		printf("Cannot open input file %s",argv[1]);
		exit(-1);
	}

	sscanf(argv[2],"%d",&ALIGN);

	amount = fread(&Header,sizeof(Elf32_Ehdr),1,fp);
	if(amount != 1 )					end("Could not read ELF Header",-1);
	if(Header.e_type != ET_REL)			end("Not a Relcoatable File",-1);
	if(Header.e_version != EV_CURRENT)	end("Not a current file version",-1);
	
	if(Header.e_shoff == 0)				end("No Section Header offset",-1);
	if(Header.e_shentsize == 0)			end("Section Header size of 0 !!!",-1);
	if(Header.e_shnum == 0)				end("0 number of section headers..",-1);
	
	if(Header.e_shstrndx == SHN_UNDEF)	end("no symbol names",-1);

	sections = malloc(Header.e_shnum * Header.e_shentsize);
	if(sections == 0)					end("cannot allocate memory for section headers",-1);
	
	amount = fseek(fp,Header.e_shoff,SEEK_SET);
	amount = fread(sections,Header.e_shentsize,Header.e_shnum,fp);

	memory = malloc(sections[Header.e_shstrndx].sh_size);
	if(memory == NULL)					end("Cannot allocate memory for section names",-1);

	amount = fseek(fp,sections[Header.e_shstrndx].sh_offset,SEEK_SET);
	amount = fread(memory,1,sections[Header.e_shstrndx].sh_size,fp);

	for(i =0;i<Header.e_shnum;i++)
	{
		if(strcmp(".rodata",&memory[sections[i].sh_name])==0)
		{
			sections[i].sh_addralign = ALIGN;
			printf("%3d %40s %p %p %d\n",i,&memory[sections[i].sh_name],sections[i].sh_offset,sections[i].sh_size,sections[i].sh_addralign);
		}
	}
	amount = fseek(fp,Header.e_shoff,SEEK_SET);
	amount = fwrite(sections,Header.e_shentsize,Header.e_shnum,fp);

	end("all ok",0);
}
