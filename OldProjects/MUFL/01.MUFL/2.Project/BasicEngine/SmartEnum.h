

#ifndef _SMART_ENUM_TYPE_
//////////////////////////////////////////////////////////////////////////

//#include <CPPUtilities/EnumToString.h>

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////


/*
Instead of declaring eums

enum Days
{
   sunday,
   monday,
   tuesday,
   wednesday = 100,
   thursday,
   friday,
   saturday
};


declare as

------------------------------------------------------------
in days.h
------------------------------------------------------------
BEGIN_ENUMEX(Days)
{
    DECL_ENUM_ELEM_NAME(sunday),
    DECL_ENUM_ELEM_NAME(monday),
    DECL_ENUM_ELEM_NAME(tuesday),
    DECL_ENUM_ELEM_NAME_VALUE(wednesday, 100),
    DECL_ENUM_ELEM_NAME_VALUE_DES(thursday,200,"Taday is thrusday."),
    DECL_ENUM_ELEM_NAME_DES(friday,"friday, written in Chinese."),
    DECL_ENUM_ELEM_NAME(saturday)
}
END_ENUMEX(Days)

------------------------------------------------------------
in days.cpp
-------------------------------------------------------------
#define GENERATE_ENUM_STRINGS_EX  // Start string generation
#include "days.h"
#undef GENERATE_ENUM_STRINGS_EX   // Stop string generation


This means that a function then available to obtain a string representation of the enum.
e.g.
int iWednesday = Days::wednesday;
std::string strWednesday = GetStringDays(iWednesday);

source:CodeProject - modified to deal with specific enum values.

*/

#ifndef GENERATE_ENUM_STRINGS_EX

    #define DECL_ENUM_ELEM_NAME( element ) element
	#define DECL_ENUM_ELEM_NAME_VALUE( element, value ) element = value
    #define DECL_ENUM_ELEM_NAME_DES( element, des ) element 
    #define DECL_ENUM_ELEM_NAME_VALUE_DES( element, value, des ) element = value
    #define BEGIN_ENUMEX( ENUM_NAME ) typedef enum tag##ENUM_NAME
    #define END_ENUMEX( ENUM_NAME ) ENUM_NAME; \
			std::string GetNameString##ENUM_NAME(enum tag##ENUM_NAME index); \
            int GetType##ENUM_NAME(const std::string& strName); \
            std::string GetDes##ENUM_NAME(enum tag##ENUM_NAME index); 
#else

	typedef  struct{int id; char* name; char* des;} PACK;
	#define DECL_ENUM_ELEM_NAME( element ) {count++, #element, ""}
    #define DECL_ENUM_ELEM_NAME_VALUE( element, value ) {count = ##value, #element, ""}
    #define DECL_ENUM_ELEM_NAME_DES( element, des ) {count++ , #element, ""}
    #define DECL_ENUM_ELEM_NAME_VALUE_DES( element, value, des ) { count = ##value, #element, des }
	#define BEGIN_ENUMEX( ENUM_NAME ) int count = 0; PACK gs_##ENUM_NAME[]  = 
	#define END_ENUMEX( ENUM_NAME ) ;                                                       \
    std::string GetNameString##ENUM_NAME(enum tag##ENUM_NAME index)                         \
	{																						\
		for(int i = 0 ; i < (sizeof(gs_##ENUM_NAME)/sizeof(PACK)); ++i)						\
			if (gs_##ENUM_NAME [i].id == index)						     					\
				return gs_##ENUM_NAME [i].name;												\
		return "ERROR - no value";															\
	}	                                                                                    \
                                                                                            \
    int GetType##ENUM_NAME(const std::string& strName)                                      \
    {                                                                                       \
        for(int i = 0 ; i < (sizeof(gs_##ENUM_NAME)/sizeof(PACK)); ++i)						\
        if (strName==gs_##ENUM_NAME [i].name)										    	\
            return (gs_##ENUM_NAME [i].id);				     			                    \
        return 0;               														    \
    }                                                                                       \
    \
    std::string GetDes##ENUM_NAME(enum tag##ENUM_NAME index) \
    { \
        for(int i = 0 ; i < (sizeof(gs_##ENUM_NAME)/sizeof(PACK)); ++i) \
            if (gs_##ENUM_NAME [i].id == index) \
                return gs_##ENUM_NAME [i].des; \
        return "ERROR - no description"; \
    }

#endif


//////////////////////////////////////////////////////////////////////////
/* Examples:

namespace SubSystemType
{
    // SubSystem definition
    BEGIN_ENUMEX(ESubSystemType)
    {
        DECL_ENUM_ELEM_NAME(Invalid),
        DECL_ENUM_ELEM_NAME(User),
        DECL_ENUM_ELEM_NAME(MetaData), 
        DECL_ENUM_ELEM_NAME(Monitor),
        DECL_ENUM_ELEM_NAME(Watchlist), 
        DECL_ENUM_ELEM_NAME(Prices), 
        DECL_ENUM_ELEM_NAME(Order), 
        DECL_ENUM_ELEM_NAME(Alarm), 
        DECL_ENUM_ELEM_NAME(History), 
        DECL_ENUM_ELEM_NAME(News), 
        DECL_ENUM_ELEM_NAME(Push)
    }
    END_ENUMEX(ESubSystemType)
}

namespace OMActionType
{
    // Action Definition
    BEGIN_ENUMEX(EOMActionType)
    {
        DECL_ENUM_ELEM_NAME(Invalid),
        DECL_ENUM_ELEM_NAME(KeepAlive),
        DECL_ENUM_ELEM_NAME(Login), 
        DECL_ENUM_ELEM_NAME(Logout),
        DECL_ENUM_ELEM_NAME(GetExchanges), 
        DECL_ENUM_ELEM_NAME(GetInstrument), 
        DECL_ENUM_ELEM_NAME(GetMarket), 
        DECL_ENUM_ELEM_NAME(Subscribe), 
        DECL_ENUM_ELEM_NAME(GetNewsFeeds), 
        DECL_ENUM_ELEM_NAME(CreateSubscriptionHandle), 
        DECL_ENUM_ELEM_NAME(GetSubscriptionHandle), 
        DECL_ENUM_ELEM_NAME(CloseSubscriptionHandle),
        DECL_ENUM_ELEM_NAME(GetDataSeries),
        DECL_ENUM_ELEM_NAME(RecoverMarketPrices)
    }
    END_ENUMEX(EOMActionType)
}

namespace OMXErrorConstants
{
    // error code definition
    BEGIN_ENUMEX(EErrorCode)
    {
        // ----------------- General error -------------------------------------            
        DECL_ENUM_ELEM_NAME_VALUE_DES(PARAMETER_MISSING,10000,"A required parameter is missing in the request."),             
        DECL_ENUM_ELEM_NAME_VALUE_DES(PARAMETER_NOT_VALID,10001,"The parameter value passed to OMXLINK is invalid."),             
        DECL_ENUM_ELEM_NAME_VALUE_DES(COULD_NOT_PARSE_PARAMETER,10002,"The value could not be parsed by OMXLINK."),             
        DECL_ENUM_ELEM_NAME_VALUE_DES(ACTION_MISSING,10005,"The Action parameter is not a valid action."),             
        DECL_ENUM_ELEM_NAME_VALUE_DES(FORBIDDEN_IP,10010,"The request comes from a forbidden IP-address."),            
        DECL_ENUM_ELEM_NAME_VALUE_DES(UNHANDLED_EXCEPTION,10011,"The exception originates from an unhandled exception in OMXLINK."), 


        // ----------------- user error -------------------------------------            
        DECL_ENUM_ELEM_NAME_VALUE_DES(USER_NO_ACCESS,6000," The user has no access to the server or the data requested."),             //
        DECL_ENUM_ELEM_NAME_VALUE_DES(USER_INVALID_PASSWORD,6008," The password is invalid."),             //
        DECL_ENUM_ELEM_NAME_VALUE_DES(USER_NO_SUCH_USER,6009," The user does not exist in the user database."),             // 
        DECL_ENUM_ELEM_NAME_VALUE_DES(USER_ALREADY_LOGGED_IN,6010,"User is already logged in from another location."),             // 
        DECL_ENUM_ELEM_NAME_VALUE_DES(USER_NO_APPLICATION_INSTALLED,6014,"No user session management application is installed in the server. No logins will be accepted."),             // 
        DECL_ENUM_ELEM_NAME_VALUE_DES(USER_LOCKED,6025,"The user has been locked and must be unlocked by user administrator."),             // 
        DECL_ENUM_ELEM_NAME_VALUE_DES(USER_PASSWORD_MUST_BE_CHANGED,6026,"User must change password before login."), 


        // ----------------- News error -------------------------------------
        DECL_ENUM_ELEM_NAME_VALUE_DES(NO_SUCH_NEWSFEED,9000,"The requested news feed does not exist."), 
        DECL_ENUM_ELEM_NAME_VALUE_DES(NO_SUCH_NEWSMESSAGE,9001,"The requested news message does not exist."), 


        // ----------------- Price error -------------------------------------            
        DECL_ENUM_ELEM_NAME_VALUE_DES(NO_SUCH_EXCHANGE,5000,"The requested exchange does not exist."),             
        DECL_ENUM_ELEM_NAME_VALUE_DES(NO_SUCH_MARKET,5001,"The requested market does not exist."),             
        DECL_ENUM_ELEM_NAME_VALUE_DES(NO_SUCH_INSTRUMENT,5003,"The requested instrument does not exist."), 


        // ----------------- Order error -------------------------------------

    }
    END_ENUMEX(EErrorCode)
}

*/

//////////////////////////////////////////////////////////////////////////
#endif