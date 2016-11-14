#pragma once
#ifndef __CKDEF_H__
#define __CKDEF_H__

#if (defined WIN32 || defined _WIN32 || defined WINCE || defined __CYGWIN__)
#  define CK_EXPORTS __declspec(dllexport)
#elif defined __GNUC__ && __GNUC__ >= 4
#  define CK_EXPORTS __attribute__ ((visibility ("default")))
#else
#  define CK_EXPORTS
#endif

#define CK_ERROR -1
#define CK_TRUE 0

#endif