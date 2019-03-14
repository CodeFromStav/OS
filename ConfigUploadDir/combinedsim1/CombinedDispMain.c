#include <stdio.h>
#include "ConfigAccess.h"
#include "MetaDataAccess.h"


int main( int argc, char **argv )
	{
		int configAccessResult, mdAccessResult;
		char configFileName[ MAX_STR_LEN ];
		char mdFileName[ MAX_STR_LEN ];
		ConfigDataType *configDataPtr;
		OpCodeType *mdData;

		printf( "\nConfig File Upload Component\n" );
		printf( "============================\n\n" );

		if( argc < 2 )
			{
				printf("ERROR: Program requires file name for config file " );
				printf( "as command line arguement\n" );
				printf( "Program Terminated\n" );



			}
	}