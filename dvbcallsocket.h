/*
 * Copyright (c) 2014 Amlogic, Inc. All rights reserved.
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Description:
 *     AMLOGIC
 */

#ifndef __CPP_H__
#define __CPP_H__

#ifndef _DVB_CALL_SOCKET_CPP_
#define _DVB_CALL_SOCKET_CPP_

#ifdef __cplusplus
extern "C" {
#endif

int am_audio_open(int dev_no);
int am_audio_close(int dev_no);
int am_audio_opendecoder(int dev_no);
int am_audio_closedecoder(int dev_no);

#ifdef __cplusplus
}
#endif

#endif
#endif
