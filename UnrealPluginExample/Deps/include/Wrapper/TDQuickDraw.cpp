#include "Prefix/StdAfx.h"

#include "TDQuickDraw.h"

Sint32 GetTimeStamp()
/*
	Returns the number of seconds since midnight Jan 1, 1970
*/
{
    std::tm *tptr;
    std::time_t secs, local_secs, gmt_secs;
    std::time(&secs);  // Current time in GMT
    
    // Remember that localtime/gmtime overwrite same location
    tptr = std::localtime( &secs );
    
    local_secs = std::mktime( tptr );
    tptr = std::gmtime(&secs);
    gmt_secs = std::mktime( tptr );
    Sint32 diff_secs = (Sint32) difftime(local_secs, gmt_secs);
    
    return (Sint32) (std::time(0) + diff_secs); 
}