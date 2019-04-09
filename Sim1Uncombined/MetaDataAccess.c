#include "MetaDataAccess.h"

int getOpCommand( FILE *filePtr, OpCodeType *inData )
	{
		const int MAX_OP_NAME_LENGTH = 10;
		const int MAX_OP_VALUE_LENGTH = 9;
		int intBuffer = 0;
		int sourceIndex = 0, destIndex = 0;
		int accessResult;
		char strBuffer[ STD_STR_LEN ];

		accessResult = getLineTo( filePtr, STD_STR_LEN, SEMICOLON,
															strBuffer, IGNORE_LEADING_WS );

		if( accessResult == NO_ERR )
			{
				inData->opLtr = strBuffer[ sourceIndex ];
			}
		else
			{
				inData = NULL;
				return OPCMD_ACCESS_ERR;
			}

		switch( inData->opLtr )
			{
				case 'S':
				case 'A':
				case 'P':
				case 'M':
				case 'I':
				case 'O':
					break;

				default:
					inData = NULL;

					return CORRUPT_OPCMD_LETTER_ERR;
			}

		while( sourceIndex < STD_STR_LEN && strBuffer[ sourceIndex ] != LEFT_PAREN )
			{
				sourceIndex++;
			}
		sourceIndex++;

		while( sourceIndex < STD_STR_LEN	
					&& destIndex < MAX_OP_NAME_LENGTH
						&& strBuffer[ sourceIndex ] != RIGHT_PAREN )
			{
				inData->opName[ destIndex ] = strBuffer[ sourceIndex ];

				destIndex++; sourceIndex++;

				inData->opName[ destIndex ] = NULL_CHAR;
			}

		if( checkOpString( inData->opName ) == False )
			{
				inData = NULL;
				return CORRUPT_OPCMD_NAME_ERR;
			}
		
		sourceIndex++;
		destIndex = 0;

		while( sourceIndex < STD_STR_LEN	
					&& destIndex < MAX_OP_VALUE_LENGTH
						&& isDigit( strBuffer[ sourceIndex ] ) == True )
				{
					intBuffer *= 10;
					intBuffer += (int)( strBuffer[ sourceIndex ] - '0' );

					destIndex++; sourceIndex++;
				}
		if( sourceIndex == STD_STR_LEN || destIndex == MAX_OP_VALUE_LENGTH )
			{
				inData = NULL;
				return CORRUPT_OPCMD_VALUE_ERR;

			}
		
		inData->opValue = intBuffer;

		if( inData ->opLtr == 'S'
				&& compareString( inData->opName, "end" ) == STR_EQ )
			{
				return LAST_OPCMD_FOUND_MSG;
			}
		
		return COMPLETE_OPCMD_FOUND_MSG;
	}

int getOpCodes( char *fileName, OpCodeType **opCodeDataHead )
   {
		const char READ_ONLY_FLAG[] = "r";

		int startCount = 0, endCount = 0;

		OpCodeType *localHeadPtr = NULL;

		int accessResult;
		char dataBuffer[ MAX_STR_LEN ];
		OpCodeType *newNodePtr;
		FILE *fileAccessPtr;

	*opCodeDataHead = NULL;

	fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );

	if( fileAccessPtr == NULL )
		{
			return MD_FILE_ACCESS_ERR;
		}

	if( getLineTo( fileAccessPtr, MAX_STR_LEN, COLON,
									dataBuffer, IGNORE_LEADING_WS ) != NO_ERR 
				|| compareString( dataBuffer, "Start Program Meta-Data Code" ) != STR_EQ )
		{
			fclose( fileAccessPtr );
			return MD_CORRUPT_DESCRIPTOR_ERR;
		}

	newNodePtr = (OpCodeType * ) malloc( sizeof( OpCodeType ) );

	accessResult = getOpCommand( fileAccessPtr, newNodePtr );

	startCount = updateStartCount( startCount, newNodePtr->opName );
	endCount = updateEndCount( endCount, newNodePtr->opName );

	if( accessResult != COMPLETE_OPCMD_FOUND_MSG )
		{
			fclose( fileAccessPtr );

			*opCodeDataHead = clearMetaDataList( localHeadPtr );

			free( newNodePtr );

			return accessResult;
		}

	while( accessResult == COMPLETE_OPCMD_FOUND_MSG )
		{
			localHeadPtr = addNode( localHeadPtr, newNodePtr );
			accessResult = getOpCommand( fileAccessPtr, newNodePtr );

			startCount = updateStartCount( startCount, newNodePtr->opName );
			endCount = updateEndCount( endCount, newNodePtr->opName );

		}

	if( accessResult == LAST_OPCMD_FOUND_MSG )
		{
			if( startCount == endCount )
				{
					localHeadPtr = addNode( localHeadPtr, newNodePtr );
					accessResult = NO_ERR;

					if( getLineTo( fileAccessPtr, MAX_STR_LEN, PERIOD,
										dataBuffer, IGNORE_LEADING_WS ) != NO_ERR
							|| compareString( dataBuffer, "End Program Meta-Data Code" )
																										!= STR_EQ )
						{
							accessResult = MD_CORRUPT_DESCRIPTOR_ERR;
						}
				}
			else
				{
					accessResult = UNBALANCED_START_END_ERR;
				}
		}

	if( accessResult != NO_ERR )
		{
			localHeadPtr = clearMetaDataList( localHeadPtr );
		}

	fclose( fileAccessPtr );
	free( newNodePtr );
	*opCodeDataHead = localHeadPtr;

	return accessResult;

      
   }

int updateStartCount( int count, char *opString )
	{
		if( compareString( opString, "start" ) == STR_EQ )
			{
				return count + 1;
			}
		return count;
	}

int updateEndCount( int count, char *opString )
	{
		if( compareString( opString, "end" ) == STR_EQ )
			{
				return count + 1;
			}
		return count;
	}

OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode )
	{
		if( localPtr == NULL )
			{
				localPtr = ( OpCodeType * ) malloc(sizeof( OpCodeType ) );
				localPtr->opLtr = newNode->opLtr;
				copyString( localPtr->opName, newNode->opName );
				localPtr->opValue = newNode ->opValue;
				localPtr->next = NULL;

				return localPtr;
			}
		
		localPtr->next = addNode( localPtr->next, newNode );

		return localPtr;
	}

Boolean checkOpString( char *testStr )
	{
		if( compareString( testStr, "access" )			== STR_EQ 
		 || compareString( testStr, "allocate" )		== STR_EQ 
		 || compareString( testStr, "end" )				== STR_EQ 
		 || compareString( testStr, "hard drive" )	== STR_EQ 
		 || compareString( testStr, "keyboard" )		== STR_EQ 
		 || compareString( testStr, "printer" )		== STR_EQ 
		 || compareString( testStr, "monitor" )		== STR_EQ 
		 || compareString( testStr, "run" )				== STR_EQ 
		 || compareString( testStr, "start" )			== STR_EQ )
			{
				return True;
			}

		return False;
	}

Boolean isDigit( char testChar )
	{
		if( testChar >= '0' && testChar <= '9' )
			{
				return True;
			}
		return False;
	}


void displayMetaDataError( int code )
   {
		char errList[10][35] =
									{ "No Error",
									  "Incomplete File Error",
									  "MD File Access Error",
									  "MD Corrupt Descriptor Error",
									  "Op Command Access Error",
									  "Corrupt Op Command Letter Error",
									  "Corrupt Op Command Name Error",
									  "Corrupt Op Command Value Error",
									  "Unbalanced Start-End Code Error" };
		printf( "\nFATAL ERROR: %s, Program aborted\n", errList[ code ] );
		
   }

void displayMetaData( OpCodeType *localPtr )
   {
		printf( "\nMeta-Data File Display\n" );
		printf( "======================" );

		while( localPtr != NULL )
			{
				printf( "Op code letter: %c\n", localPtr->opLtr );
				printf( "Op code name: %s\n", localPtr->opName );
				printf( "Op code value : %d\n\n", localPtr->opValue );

				localPtr = localPtr->next;
			}

   }

OpCodeType *clearMetaDataList( OpCodeType *localPtr )
   {
		if( localPtr != NULL )
			{
				if( localPtr->next != NULL )
					{
						clearMetaDataList( localPtr->next );
					}
				free( localPtr );
			}

      return NULL;
   }