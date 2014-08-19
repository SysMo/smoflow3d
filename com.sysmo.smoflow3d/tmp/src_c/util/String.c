/*
 * Arrays.c
 *
 *  Created on: Oct 22, 2013
 *      Author: Milen Borisov
 */
#include "String.h"
#include "Common.h"
#include <string.h>
#include <ctype.h>

/**
 * String - functions
 */
String* String_new(const char* content) {
	NEW_OBJECT(String, self);
	int stringLength = strlen(content);
	NEW_ARRAY(char, stringLength + 1, chars); //'+1' add the extra char for the '\0' termination
	strcpy(chars, content);
	self->chars = chars;
	self->length = stringLength;
	return self;
}

void String_free(String** pSelf) {
	if (*pSelf == NULL) return;

	String* self = *pSelf;
	free(self->chars);
	free(self);

	*pSelf = NULL;
}

void String_trim(String* self) {
	char* str = self->chars;
    char* start;
    char* end;

    /* Find first non-whitespace */
    for (start = str; *start; start++)
    {
        if (!isspace((unsigned char)start[0]))
            break;
    }

    /* Find start of last all-whitespace */
    for (end = start + strlen(start); end > start + 1; end--)
    {
        if (!isspace((unsigned char)end[-1]))
            break;
    }

    *end = 0; /* Truncate last whitespace */

    /* Shift from "start" to the beginning of the string */
    if (start > str)
        memmove(str, start, (end - start) + 1);

    self->length = (end - start);
}
