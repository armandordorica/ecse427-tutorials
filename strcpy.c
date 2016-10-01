/* The C library function char *strcpy(char *dest, const char *src) copies the string pointed to, by src to dest. */

#include <stdio.h>
#include <string.h>

int main()
{
   char src[40];
   char dest[100];
  
   memset(dest, '\0', sizeof(dest));
   strcpy(src, "This is tutorialspoint.com");
   strcpy(dest, src);

   printf("Final copied string : %s\n", dest);
   
   return(0);
}




/*dest -- This is the pointer to the destination array where the content is to be copied.

src -- This is the string to be copied.

*/