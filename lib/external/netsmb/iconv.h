/*	$NetBSD: iconv.h,v 1.10 2010/12/17 13:05:29 pooka Exp $	*/

/*
 * Copyright (c) 2000-2001, Boris Popov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Boris Popov.
 * 4. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/sys/iconv.h,v 1.5 2002/07/15 13:34:50 markm Exp $
 */
#ifndef _NETSMB_ICONV_H_
#define _NETSMB_ICONV_H_

#define	ICONV_CSNMAXLEN		31	/* maximum length of charset name */
#define	ICONV_CNVNMAXLEN	31	/* maximum length of converter name */
#define	ICONV_CSMAXDATALEN	1024	/* maximum size of data associated with cs pair */

/*
 * Entry for cslist sysctl
 */
#define	ICONV_CSPAIR_INFO_VER	1

struct iconv_cspair_info {
	int	cs_version;
	int	cs_id;
	int	cs_base;
	int	cs_refcount;
	char	cs_to[ICONV_CSNMAXLEN];
	char	cs_from[ICONV_CSNMAXLEN];
};

/*
 * Parameters for 'add' sysctl
 */
#define	ICONV_ADD_VER	1

struct iconv_add_in {
	int	ia_version;
	char	ia_converter[ICONV_CNVNMAXLEN];
	char	ia_to[ICONV_CSNMAXLEN];
	char	ia_from[ICONV_CSNMAXLEN];
	int	ia_datalen;
	const void *ia_data;
};

struct iconv_add_out {
	int	ia_csid;
};

#ifndef _KERNEL

__BEGIN_DECLS

int   kiconv_add_xlat_table(const char *, const char *, const u_char *);

__END_DECLS

#else /* !_KERNEL */


#ifdef MALLOC_DECLARE
MALLOC_DECLARE(M_ICONV);
#endif

/*
 * Basic conversion functions
 */
int rumpns_iconv_open(const char *, const char *, void **);
int rumpns_iconv_close(void *);
int rumpns_iconv_conv(void *, const char **, size_t *, char **, size_t *);
char *rumpns_iconv_convstr(void *, char *, const char *, size_t);
void *rumpns_iconv_convmem(void *, void *, const void *, int);

/*
 * Internal functions
 */
int rumpns_iconv_lookupcp(const char **, const char *);


#ifdef ICONV_DEBUG
#define ICDEBUG(x)	aprint_debug x
#else
#define ICDEBUG(x)	/* nothing */
#endif

#endif /* !_KERNEL */

#endif /* !_NETSMB_ICONV_H_ */
