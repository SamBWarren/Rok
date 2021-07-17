/*
 * basic.h
 * the lowest level header
 */

/*
########
Objects in C:
	thing = object_create();		/returns object structure
	object_do_something(thing);		/returns void
########
 */

#ifndef BASIC_H
#define BASIC_H

typedef unsigned int uint;
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;

/*C89 boolean*/
typedef enum
{
	false = (1==0),
	true = (!false)
} Bool;

typedef struct
{
	int32 x;
	int32 y;
} coord;

typedef struct
{
	coord a;
	coord b;
} vector;

#endif /* BASIC_H */
