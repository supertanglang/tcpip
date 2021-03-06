/******************************************************
 * IMIGE/TCP, Copyright (C) 1995, IMIGE Systems Inc.
 *
 *  All rights reserved.
 *  This software is under BSD license. see LICENSE.txt
 *
 *  Author : Minsuk Lee (ykhl1itj@gmail.com)
 ******************************************************/

#include "imigelib.h"

int
shutdown(int sd, int how)
{
	struct _IMIGE_SOCKET *sp = _imige_sock + sd;
	union  REGS _imige_reg;

	if (!_imige_vec)
		if (_find_kernel() == 0)
			exit(1);

	if ((sd < 0) || (sd >= _num_sock)) {
		errno = ENOTSOCK;
		return(-1);
	}
	if (sp->so_type == 0) {
		errno = EBADF;
		return(-1);
	}
	_imige_reg.h.ah = IMG_SHUTDOWN;
	_imige_reg.h.al = sd;
	_imige_reg.x.bx = how;
	int86(_imige_vec, &_imige_reg, &_imige_reg);
	if (!(how & 1)) {
		sp->so_state |= SS_CANTRCVMORE;
	}
	if (how > 0) {
		sp->so_state |= SS_CANTSENDMORE;
	}
	return(0);
}
