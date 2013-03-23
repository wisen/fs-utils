/*	$NetBSD: fsu_fts.h,v 1.1 2009/03/23 20:54:14 stacktic Exp $	*/

/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)fsu_fts.h	8.3 (Berkeley) 8/14/94
 */

#ifndef	_FSU_FTS_H_
#define	_FSU_FTS_H_

#ifndef	__fsu_fts_stat_t
#define	__fsu_fts_stat_t	struct stat
#endif
#ifndef	__fsu_fts_nlink_t
#define	__fsu_fts_nlink_t	nlink_t
#endif
#ifndef	__fsu_fts_ino_t
#define	__fsu_fts_ino_t	ino_t
#endif
#ifndef	__fsu_fts_length_t
#define	__fsu_fts_length_t	unsigned int
#endif
#ifndef	__fsu_fts_number_t
#define	__fsu_fts_number_t	int64_t
#endif

#ifndef FTS_COMFOLLOW
/* fts_options */
#define	FTS_COMFOLLOW	0x001		/* follow command line symlinks */
#define	FTS_LOGICAL	0x002		/* logical walk */
#define	FTS_NOCHDIR	0x004		/* don't change directories */
#define	FTS_NOSTAT	0x008		/* don't get stat info */
#define	FTS_PHYSICAL	0x010		/* physical walk */
#define	FTS_SEEDOT	0x020		/* return dot and dot-dot */
#define	FTS_XDEV	0x040		/* don't cross devices */
#define	FTS_WHITEOUT	0x080		/* return whiteout information */
#define	FTS_OPTIONMASK	0x0ff		/* valid user option mask */

#define	FTS_NAMEONLY	0x100		/* (private) child names only */
#define	FTS_STOP	0x200		/* (private) unrecoverable error */

/* fts_level */
#define	FTS_ROOTPARENTLEVEL	-1
#define	FTS_ROOTLEVEL		 0

/* fts_info */
#define	FTS_D		 1		/* preorder directory */
#define	FTS_DC		 2		/* directory that causes cycles */
#define	FTS_DEFAULT	 3		/* none of the above */
#define	FTS_DNR		 4		/* unreadable directory */
#define	FTS_DOT		 5		/* dot or dot-dot */
#define	FTS_DP		 6		/* postorder directory */
#define	FTS_ERR		 7		/* error; errno is set */
#define	FTS_F		 8		/* regular file */
#define	FTS_INIT	 9		/* initialized only */
#define	FTS_NS		10		/* stat(2) failed */
#define	FTS_NSOK	11		/* no stat(2) requested */
#define	FTS_SL		12		/* symbolic link */
#define	FTS_SLNONE	13		/* symbolic link without target */
#define	FTS_W		14		/* whiteout object */

/* fts_flags */
#define	FTS_DONTCHDIR	 0x01		/* don't chdir .. to the parent */
#define	FTS_SYMFOLLOW	 0x02		/* followed a symlink to get here */
#define	FTS_ISW		 0x04		/* this is a whiteout object */

/* fts_instr */
#define	FTS_AGAIN	 1		/* read node again */
#define	FTS_FOLLOW	 2		/* follow symbolic link */
#define	FTS_NOINSTR	 3		/* no instructions */
#define	FTS_SKIP	 4		/* discard node */

#endif /* !FTS_COMFOLLOW */

typedef struct {
	struct _fsu_ftsent *fts_cur;	/* current node */
	struct _fsu_ftsent *fts_child;	/* linked list of children */
	struct _fsu_ftsent **fts_array;	/* sort array */
	dev_t fts_dev;			/* starting device # */
	char *fts_path;			/* path for this descent */
	char *fts_rpath;			/* fd for root */
	unsigned int fts_pathlen;	/* sizeof(path) */
	unsigned int fts_nitems;	/* elements in the sort array */
	int (*fts_compar)		/* compare function */
		(const struct _fsu_ftsent **, const struct _fsu_ftsent **);
	int fts_options;		/* fsu_fts_open options, global flags */

} FSU_FTS;

typedef struct _fsu_ftsent {
	struct _fsu_ftsent *fts_cycle;	/* cycle node */
	struct _fsu_ftsent *fts_parent;	/* parent directory */
	struct _fsu_ftsent *fts_link;	/* next file in directory */
	__fsu_fts_number_t fts_number;      /* local numeric value */
	void *fts_pointer;	        /* local address value */
	char *fts_accpath;		/* access path */
	char *fts_path;			/* root path */
	int fts_errno;			/* errno for this node */
	char *fts_sympath;			/* fd for symlink */
	__fsu_fts_length_t fts_pathlen;	/* strlen(fsu_fts_path) */
	__fsu_fts_length_t fts_namelen;	/* strlen(fsu_fts_name) */

	__fsu_fts_ino_t fts_ino;		/* inode */
	dev_t fts_dev;			/* device */
	__fsu_fts_nlink_t fts_nlink;	/* link count */

	short fts_level;		/* depth (-1 to N) */

	unsigned short fts_info;   /* user flags for FSU_FTSENT structure */

	unsigned short fts_flags;  /* private flags for FSU_FTSENT structure */

	unsigned short fts_instr;	/* fsu_fts_set() instructions */

	__fsu_fts_stat_t *fts_statp;	/* stat(2) information */
	char fts_name[1];		/* file name */
} FSU_FTSENT;

#include <sys/cdefs.h>


FSU_FTSENT	*fsu_fts_children(FSU_FTS *, int);
int		fsu_fts_close(FSU_FTS *);
FSU_FTS		*fsu_fts_open(char * const *, int,
			      int (*)(const FSU_FTSENT **,
				      const FSU_FTSENT **));
FSU_FTSENT	*fsu_fts_read(FSU_FTS *);
int		fsu_fts_set(FSU_FTS *, FSU_FTSENT *, int);


#endif /* !_FSU_FTS_H_ */