/*
 * Copyright (c) 2014 Amlogic, Inc. All rights reserved.
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Description: c++ file
 */
#define TAG "dvbcallsocket"

#include "am_av.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <android/log.h>
#include <systemcontrol/SystemControlClient.h>
#include "dvbcallsocket.h"

using namespace android;

#define LOGD(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

static sp<SystemControlClient> mSystemControl = NULL;

static void av_audio_callback(int event_type, AudioParms* param, void *user_data) {
    LOGD("%s enter\n",__FUNCTION__);

    switch ( event_type ) {
        case AM_AV_EVT_AUDIO_CB:
        /*
            param->cmd;
            param->param1;
            param->param2;
        */
            LOGD("%s: cmd: %d, param1: %d, param2: %d\n",__FUNCTION__, param->cmd, param->param1, param->param2);
            if (mSystemControl != NULL) {
                mSystemControl->setAudioParam(param->cmd, param->param1, param->param2);
            } else {
                LOGD("%s: binder systemcontrol service failed!\n", __FUNCTION__);
            }
            break;
     }
}

#define  ADEC_OPEN_DECODER       12
#define  ADEC_CLOSE_DECODER      13
#define  ADEC_SET_AUDIO_PATCH_MANAGE_MODE 26

int am_audio_open(int dev_no) {
    LOGD("%s enter\n",__FUNCTION__);

    if (mSystemControl == NULL) {
        //mSystemControl = new SystemControlClient();
        mSystemControl = SystemControlClient::getInstance();
        AM_AV_SetAudioCallback(0,av_audio_callback,0);

        LOGD("%s register av_audio_callback success!\n",__FUNCTION__);
		AudioParms param;
		if (mSystemControl != NULL) {
			param.cmd = ADEC_SET_AUDIO_PATCH_MANAGE_MODE;
			param.param1 = 0;
			param.param2 = 1;
			av_audio_callback(AM_AV_EVT_AUDIO_CB, &param, NULL);

			LOGD("%s ADEC_SET_AUDIO_PATCH_MANAGE_MODE success!\n",__FUNCTION__);
		}
        return 0;
    }

    LOGD("%s SystemControlClient exsit!\n",__FUNCTION__);
    return 1;
}

int am_audio_opendecoder(int dev_no) {
    AudioParms param;

    LOGD("%s enter\n",__FUNCTION__);
    if (mSystemControl != NULL) {
        param.cmd = ADEC_OPEN_DECODER;
        param.param1 = 0;
        param.param2 = 0;
        av_audio_callback(AM_AV_EVT_AUDIO_CB, &param, NULL);

        LOGD("%s success!\n",__FUNCTION__);
        return 0;
    }

    LOGD("%s SystemControlClient is not exsit!\n",__FUNCTION__);
    return 1;
}

int am_audio_closedecoder(int dev_no) {
    AudioParms param;

    LOGD("%s enter\n",__FUNCTION__);
    if (mSystemControl != NULL) {
        param.cmd = ADEC_CLOSE_DECODER;
        param.param1 = 0;
        param.param2 = 0;
        av_audio_callback(AM_AV_EVT_AUDIO_CB, &param, NULL);

        LOGD("%s success!\n",__FUNCTION__);
        return 0;
    }

    LOGD("%s SystemControlClient is not exsit!\n",__FUNCTION__);
    return 1;
}

int am_audio_close(int dev_no) {
    LOGD("%s enter\n",__FUNCTION__);

    AM_AV_SetAudioCallback(0,NULL,NULL);

    return 0;
}
