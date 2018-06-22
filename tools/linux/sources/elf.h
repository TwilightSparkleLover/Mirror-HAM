#ifndef _ELF_H_
#define _ELF_H_

typedef unsigned int	Elf32_Addr;
typedef unsigned short	Elf32_Half;
typedef unsigned int	Elf32_Off;
typedef signed int		Elf32_Sword;
typedef unsigned int	Elf32_Word;

#define	EI_NIDENT		16

typedef struct
{
	unsigned char	EI_MAG0;
	unsigned char	EI_MAG1;
	unsigned char	EI_MAG2;
	unsigned char	EI_MAG3;
	unsigned char	EI_CLASS;
	unsigned char	EI_DATA;
	unsigned char	EI_VERSION;
	unsigned char	EI_PAD[9];

}t_Elf32_EI	;

typedef struct
{
	t_Elf32_EI		e_EI;
	Elf32_Half		e_type;
	Elf32_Half		e_machine;
	Elf32_Word		e_version;
	Elf32_Addr		e_entry;
	Elf32_Off		e_phoff;
	Elf32_Off		e_shoff;
	Elf32_Word		e_flags;
	Elf32_Half		e_ehsize;
	Elf32_Half		e_phentsize;
	Elf32_Half		e_phnum;
	Elf32_Half		e_shentsize;
	Elf32_Half		e_shnum;
	Elf32_Half		e_shstrndx;
}Elf32_Ehdr;

enum
{
	ET_NONE		= 0,
	ET_REL		= 1,
	ET_EXEC		= 2,
	ET_DYN		= 3,
	ET_CORE		= 4,
	ET_LOPROC	= 0xff00,
	ET_HIPROC	= 0xffff,
};


enum
{
	EM_NONE		= 0,
	EM_M32		= 1,
	EM_SPARC	= 2,
	EM_386		= 3,
	EM_68K		= 4,
	EM_88K		= 5,
	EM_860		= 7,
	EM_MIPS		= 8,
};

enum
{
	EV_NONE		= 0,
	EV_CURRENT	= 1,
};


#define	ELFMAG0 0x7f
#define	ELFMAG1 'E'
#define	ELFMAG2 'L'
#define	ELFMAG3 'F'

enum
{
	ELFCLASSNONE	= 0,
	ELFCLASS32		= 1,
	ELFCLASS64		= 2,
};

enum
{
	ELFDATANONE	= 0,
	ELFDATA2LSB	= 1,
	ELFDATA2MSB	= 2,
};


enum
{
	SHN_UNDEF		= 0,
	SHN_LORESERVE	= 0xff00,
	SHN_LOPROC		= 0xff00,
	SHN_HIPROC		= 0xff1f,
	SHN_ABS			= 0xfff1,
	SHN_COMMON		= 0xfff2,
	SHN_HIRESERVE	= 0xffff,
};

enum
{
	SHT_NULL		= 0,
	SHT_PROGBITS	= 1,
	SHT_SYMTAB		= 2,
	SHT_STRTAB		= 3,
	SHT_RELA		= 4,
	SHT_HASH		= 5,
	SHT_DYNAMIC		= 6,
	SHT_NOTE		= 7,
	SHT_NOBITS		= 8,
	SHT_REL			= 9,
	SHT_SHLIB		= 10,
	SHT_SYNSYM		= 11,
	SHT_LOPROC		= 0x70000000,
	SHT_HIPROC		= 0x7fffffff,
	SHT_LOUSER		= 0x80000000,
	SHT_HIUSER		= 0xffffffff,
};

enum
{
	SHF_WRITE		= 0x1,
	SHF_ALLOC		= 0x2,
	SHF_EXECINSTR	= 0x4,
	SHF_MASKPROC	= 0xf0000000
};

enum
{
	STN_UNDEF		= 0,
};

typedef struct
{
	Elf32_Word		st_name;
	Elf32_Addr		st_value;
	Elf32_Word		st_size;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf32_Half		st_shndx;
}Elf32_Sym;

#define	ELF32_ST_BIND(i)	((i)>>4)
#define	ELF32_ST_TYPE(i)	((i)&0xf)
#define	ELF32_ST_INFO(b,t)	(((b)<<4)+((t)&0xf))

enum
{
	STB_LOCAL		= 0,
	STB_GLOBAL		= 1,
	STB_WEAK		= 2,
	STB_LOPROC		= 13,
	STB_HIPROC		= 15,
};

enum
{
	STT_NOTYPE		= 0,
	STT_OBJECT		= 1,
	STT_FUNC		= 2,
	STT_SECTION		= 3,
	STT_FILE		= 4,
	STT_LOPROC		= 13,
	STT_HIPROC		= 15,
};

typedef struct
{
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
}Elf32_Rel;

typedef struct
{
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
	Elf32_Sword		r_addend;
}Elf32_Rela;


#define	ELF32_R_SYM(i)	((i)>>8)
#define	ELF32_R_TYPE(i)	((unsigned char)(i))
#define	ELF32_INFO(s,t)	((s)<<8)+(unsigned char)(t))


typedef struct
{
	Elf32_Word	sh_name;
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	Elf32_Addr	sh_addr;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_addralign;
	Elf32_Word	sh_entsize;
}Elf32_Shdr;


#endif