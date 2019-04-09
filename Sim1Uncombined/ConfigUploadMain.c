//header files
#include <stdio.h>
#include "ConfigAccess.h"



/*
Function name: main
Algorithm: driver function to test the config file upload operation
Precondition:none
Postcondition: return 0 on success
Exceptions: none
Note: demonstrates development and use of config file upload operations and function
*/

int main( int argc, char **argv ) //**argv a pointer to a set of strings that come along with the argument on command line
    {
        //initialize function/variables
        int configAccessResult;
        char configFileName[ MAX_STR_LEN ];
        ConfigDataType *configDataPtr;
            
        //display title
            //function: printf
        printf( "\nConfig File Upload Program\n" );
        printf( "==========================\n\n" );

        //check for not correct number of command line arguments (two)
        if( argc < 2 )
            {
                //print missing command line argument error
                    //function: printf
                printf ( "ERROR: Program requires file name for config file " );
                printf ( "as command line argument\n" );
                printf ( "Program Terminated\n" );

                //return non-normal program result (anything other than 0)
                return 1;
            }
        
        //get data from configuration file
            //function: copyString, getConfigData
        copyString( configFileName, argv[ 1 ] );
        configAccessResult = getConfigData( configFileName, &configDataPtr);

        //check for succeful upload
        if( configAccessResult == NO_ERR )
            {
                //display config file
                    //function: displayConfigData
                displayConfigData( configDataPtr );                  
            }

        //otherwise, assume failed upload
        else
            {
                 //display configuration upload error
                //function: displayConfigError
                displayConfigError( configAccessResult );
            }
        
        //shut down program

            //clear configuration data
                //function: clearConfigData
            clearConfigData( &configDataPtr );

            //add endline vertical spacing
                //function: printf
            printf( "\n" );

            //return program success
        return 0;
    }

















