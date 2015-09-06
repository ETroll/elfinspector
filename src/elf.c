#include <stdlib.h>
#include <string.h>
#include "elf.h"


const char* Elf32_Shdr_Types[] = {
    "SHT_NULL",
    "SHT_PROGBITS",
    "SHT_SYMTAB",
    "SHT_STRTAB",
    "SHT_RELA",
    "SHT_HASH",
    "SHT_DYNAMIC",
    "SHT_NOTE",
    "SHT_NOBITS",
    "SHT_REL",
    "SHT_SHLIB",
    "SHT_DYNSYM"
};

const char* Elf32_Ehdr_Types[] = {
    "ET_NONE",
    "ET_REL",
    "ET_EXEC",
    "ET_DYN",
    "ET_CORE"
};

const char* Elf32_Ehdr_Machines[] = {
    "EM_NONE",
    "EM_M32",
    "EM_SPARC",
    "EM_386",
    "EM_68K",
    "EM_88K",
    "EM_860",
    "EM_MIPS"
};

const char* Elf32_Phdr_Types[] = {
    "PT_NULL",
    "PT_LOAD",
    "PT_DYNAMIC",
    "PT_INTERP",
    "PT_NOTE",
    "PT_SHLIB",
    "PT_PHDR"
};

/*
 * elf_open(char* path)
 * Opens a elf file and returns a ELF structure if successfull
 */
Elf_t* elf_open(char* path)
{
    Elf_t* data = NULL;

    if(path)
    {
        FILE *pFile = fopen(path, "rb");
        if (pFile)
        {
            data = (Elf_t*)malloc(sizeof(Elf_t));
            data->file = pFile;

            fseek(pFile, 0, SEEK_END);
            data->size = ftell(pFile);
            rewind(pFile);

            data->header = (Elf32_Ehdr_t*)malloc(sizeof(Elf32_Ehdr_t));
            fread(data->header, sizeof(Elf32_Ehdr_t), 1, pFile);
            rewind(pFile);

            strcpy(data->type_description, Elf32_Ehdr_Types[data->header->e_type]);
            strcpy(data->machine_description, Elf32_Ehdr_Machines[data->header->e_machine]);

        }
    }
    return data;
}

/*
 * elf_close(Elf_t* elf)
 * Closes an ELF file and cleans up memory used
 */
void elf_close(Elf_t* elf)
{
    if(elf)
    {
        fclose(elf->file);
        free(elf->header);
        free(elf);
    }
}
