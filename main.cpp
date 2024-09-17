#include <iostream>
#include <elfutils.h>
#include <cpu.h>

using namespace std;
using namespace arm2x;

int main( int argc, char* argv[] ){
	if ( argc < 2 ) {
		cout << "ERROR: binary not found." << endl;
		return 1;
	}

	ELF elf( argv[1] );

	if ( !elf.isValid() ) {
		cout << "ERROR: " << argv[1] << " is not a ARM32 elf file." << endl;
		return 1;
	}

	Memory::getInstance().init( elf );

	CPU arm;
	arm.setPC( elf.getEntryPointAddress() );
	arm.start();
	return 0;
}
