#ifndef SOUP_H
#define SOUP_H

#include <stdio.h>
#include <stdbool.h>


bool getLink(const char* srcAddr, char* link, const int maxLinkLength);
/*
 * srcAddr should be a web address (e.g., http://www.yahoo.com).
 * link should point to an array of maxLinkLength characters.
 * getLink returns 1 if a link was found and 0 otherwise.
 * If a link was found, "link" will be filled in with the web address.
 */


int getText(const char* srcAddr, char* buffer, const int bufSize);
/*
*   unknown.
*/


#endif