#ifndef _MVD_EXPORT_H__
#define _MVD_EXPORT_H__

/* note: Interface export definition of the namespace VisionDesigner */

namespace VisionDesigner
{
    #ifndef MVD_CPP_API
        #ifdef _WIN32
            #if defined(MVD_CPP_EXPORTS)
                #define MVD_CPP_API __declspec(dllexport)
            #else
                #define MVD_CPP_API __declspec(dllimport)
            #endif
        #else
            #ifndef __stdcall
                #define __stdcall
            #endif
            #ifndef MVD_CPP_API
                #define  MVD_CPP_API
            #endif
        #endif
    #endif


    #ifndef IN
        #define IN
    #endif

    #ifndef OUT
        #define OUT
    #endif

    #ifndef INOUT
        #define INOUT
    #endif
}


#endif    ///< _MVD_EXPORT_H__
