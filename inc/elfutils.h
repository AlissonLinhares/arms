#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

using namespace std;

class ELF {
public:
	ELF( const char* path ) {
		file = fopen ( path , "rb" );

		if ( file ) {
			fseek( file, 0, SEEK_SET );
			fread( (char*) &eh, sizeof(eh), 1, file );
		}
	}

	const uint32_t getEntryPointAddress() const {
		return eh.e_entry;
	}

	const uint32_t getNumberOfProgramSections() const {
		return eh.e_phnum;
	}

	const uint32_t getSectionOffset( const uint32_t index ) const {
		return eh.e_phoff + sizeof(Elf32_Phdr) * index;
	}

	const uintptr_t loadSections( char *memory, size_t size ) const {
		Elf32_Phdr ph;
		uintptr_t maxAddr = 0;

		for ( uint32_t i = 0; i < getNumberOfProgramSections(); i++ ) {
			uintptr_t offset = getSectionOffset(i);

			fseek( file, offset, SEEK_SET );
			fread( (char*) &ph, sizeof(ph), 1, file );

			if ( ph.p_type == PT_LOAD ) {
				uintptr_t curr = ph.p_vaddr + ph.p_filesz;

				if ( curr > size )
					return 0;

				fseek( file, ph.p_offset, SEEK_SET );
				fread( (char*) (memory + ph.p_vaddr), ph.p_filesz, 1, file );

				if ( curr > maxAddr )
					maxAddr = curr;
			}
		}

		return maxAddr;
	}

	const bool isValid() const {
		if ( file                   == 0 ||
			 eh.e_phentsize         != sizeof(Elf32_Phdr) ||
			 eh.e_ident[EI_MAG0]    != ELFMAG0 ||
			 eh.e_ident[EI_MAG1]    != ELFMAG1 ||
			 eh.e_ident[EI_MAG2]    != ELFMAG2 ||
			 eh.e_ident[EI_MAG3]    != ELFMAG3 ||
			 eh.e_ident[EI_CLASS]   != ELFCLASS32 ||
			 eh.e_ident[EI_DATA]    != ELFDATA2LSB ||
			 eh.e_ident[EI_VERSION] == EV_NONE ||
			 eh.e_type              != ET_EXEC ||
			 eh.e_machine           != EM_ARM ) {
			return false;
		}

		return true;
	}

	~ELF() {
		fclose( file );
	}

private:
	Elf32_Ehdr eh;
	FILE* file;
};
