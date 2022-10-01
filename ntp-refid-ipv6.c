***//**
 *  @file       ntp-refid-ipv6.c
 *
 *  @brief      Quick program to create an NTP refid from an IPv6 address 
 *
 *  @date       2022-09-30 20:12
 *  
 *  @author     eoinpk.ek@gmail.com
 *  
 *  RFC5905 describes NTPv4 and how to calculate the refid for an NTP server. 
 *  RFC5905 states the following: "If using the IPv4 address family, the
 *  identifier is the four-octet IPv4 address.
 *  If using the IPv6 address family, it is the first four octets of the MD5
 *  hash of the IPv6 address."
 *  This program, takes an IPv6 address from the command line, gets the md5 of
 *  the IPv6 address using the openssl library and returns the first 4 octets
 *  as the refid. 
 *
 *  compile with -lcrypto
 ***************************************************************************************/

#include <openssl/md5.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int
main (int argc, char *argv[])
{
  long filesize = 16;
  unsigned char *md5_result = NULL;
  unsigned char buf6[INET6_ADDRSTRLEN];
  unsigned char str[INET6_ADDRSTRLEN];
  int i, s;

  if (argc != 2)
    {
      fprintf (stderr, "Usage: %s ipv6 address\n", argv[0]);
      exit (EXIT_FAILURE);
    }
//Converts an IPv6 text address to an IPv6 numeric address. Allows format
//expansions of :: etc. 
  s = inet_pton (AF_INET6, argv[1], buf6);
  if (s <= 0)
    {
      if (s == 0)
	fprintf (stderr, "Not in presentation format");
      else
	perror ("inet_pton");
      exit (EXIT_FAILURE);
    }
//    if (inet_ntop(AF_INET6, buf6, str, INET6_ADDRSTRLEN) == NULL) {
//        perror("inet_ntop");
//        exit(EXIT_FAILURE);
//    }
//    printf("%s\n", str);
  md5_result = malloc (MD5_DIGEST_LENGTH);	//allocated 16 bytes for the results

//unsigned char *MD5(const unsigned char *d, unsigned long n, unsigned char *md);
//MD5() compute the MD5 message digest of the n bytes at d and place it in MD5
//_DIGEST_LENGTH (which must have space == MD5_DIGEST_LENGTH == 16 bytes of output)
//MD5() return pointers to the hash value.
//
  MD5 (buf6, filesize, md5_result);

  printf ("First 4 bytes of the MD5 of (%s) = ", argv[1]);
//  for (i=0; i < MD5_DIGEST_LENGTH; i++)
//  {
//    printf("md5_result %02x\n",  md5_result[i]);
//  }
  printf ("ntp refid = %02x", md5_result[0] << 24 |
	  md5_result[1] << 16 | md5_result[2] << 8 | md5_result[3]);

  printf ("\n");
  free (md5_result);
  return 0;
}
