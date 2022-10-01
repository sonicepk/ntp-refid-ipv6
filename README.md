# ntp-refid-ipv6
Example code to create an NTP refid from an IPv6 address
RFC5905 describes NTPv4 and how to calculate the refid for an NTP server.
As there are only 32 bits available for the NTP refid, the IPv6 address will
not fit. Hence the workaround of getting the md5 of the IPv6 address and using the first 4 bytes of the md5 for the refid. 

### host ntp1-pw.heanet.ie
ntp1-pw.heanet.ie has address 193.1.8.106
ntp1-pw.heanet.ie has IPv6 address **2001:770:101:2::2**

### chronyc tracking
```
Reference ID    : **E8B9A649** (ntp1-pw.heanet.ie)
Stratum         : 2
Ref time (UTC)  : Sat Oct 01 17:11:42 2022
System time     : 0.000000724 seconds fast of NTP time
Last offset     : -0.000001201 seconds
RMS offset      : 0.000017060 seconds
Frequency       : 27.721 ppm slow
Residual freq   : +0.000 ppm
Skew            : 0.006 ppm
Root delay      : 0.000622455 seconds
Root dispersion : 0.000645751 seconds
Update interval : 1040.8 seconds
Leap status     : Normal
```
###example output
```
$ gcc ntp-refid-ipv6.c -l crypto -o ntp-refid-ipv6
$ ./ntp-refid-ipv6 **2001:770:101:2::2**
First 4 bytes of the MD5 of (2001:770:101:2::2) = ntp refid = **e8b9a649**
```
