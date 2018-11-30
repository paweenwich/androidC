/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   elf_help.h
 * Author: kwang
 *
 * Created on November 30, 2018, 10:38 AM
 */

#ifndef ELF_HELP_H
#define ELF_HELP_H

// NOTE: <stdint.h> is required here before <elf.h>. This is a NDK header bug.
#include <stdint.h>
#include <elf.h>


#ifdef __cplusplus
extern "C" {
#endif


// ELF is a traits structure used to provide convenient aliases for
// 32/64 bit Elf types, depending on the target CPU bitness.
#if __SIZEOF_POINTER__ == 4
struct ELF {
  typedef Elf32_Ehdr Ehdr;
  typedef Elf32_Phdr Phdr;
  typedef Elf32_Word Word;
  typedef Elf32_Sword Sword;
  typedef Elf32_Addr Addr;
  typedef Elf32_Dyn Dyn;
  typedef Elf32_Sym Sym;
  typedef Elf32_Rel Rel;
  typedef Elf32_Rela Rela;
  typedef Elf32_auxv_t auxv_t;

  enum { kElfClass = ELFCLASS32 };
  enum { kElfBits = 32 };

#ifndef ELF_R_TYPE
#define ELF_R_TYPE ELF32_R_TYPE
#endif

#ifndef ELF_R_SYM
#define ELF_R_SYM ELF32_R_SYM
#endif
};
#elif __SIZEOF_POINTER__ == 8
struct ELF {
  typedef Elf64_Ehdr Ehdr;
  typedef Elf64_Phdr Phdr;
  typedef Elf64_Word Word;
  typedef Elf64_Sword Sword;
  typedef Elf64_Addr Addr;
  typedef Elf64_Dyn Dyn;
  typedef Elf64_Sym Sym;
  typedef Elf64_Rel Rel;
  typedef Elf64_Rela Rela;
  typedef Elf64_auxv_t auxv_t;

  enum { kElfClass = ELFCLASS64 };
  enum { kElfBits = 64 };

#ifndef ELF_R_TYPE
#define ELF_R_TYPE ELF64_R_TYPE
#endif

#ifndef ELF_R_SYM
#define ELF_R_SYM ELF64_R_SYM
#endif
};
#else
#error "Unsupported target CPU bitness"
#endif

#ifdef __arm__
#define ELF_MACHINE EM_ARM
#elif defined(__i386__)
#define ELF_MACHINE EM_386
#elif defined(__mips__) && !defined(__LP64__)  // mips64el defines __mips__ too
#define ELF_MACHINE EM_MIPS
#elif defined(__aarch64__)
#define ELF_MACHINE EM_AARCH64
#else
//#error "Unsupported target CPU architecture"
#endif


#ifdef __cplusplus
}
#endif

#endif /* ELF_HELP_H */

