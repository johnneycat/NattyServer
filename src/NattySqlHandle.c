/*
 *  Author : WangBoJing , email : 1989wangbojing@gmail.com
 * 
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of Author. (C) 2016
 * 
 *
 
****       *****
  ***        *
  ***        *                         *               *
  * **       *                         *               *
  * **       *                         *               *
  *  **      *                        **              **
  *  **      *                       ***             ***
  *   **     *       ******       ***********     ***********    *****    *****
  *   **     *     **     **          **              **           **      **
  *    **    *    **       **         **              **           **      *
  *    **    *    **       **         **              **            *      *
  *     **   *    **       **         **              **            **     *
  *     **   *            ***         **              **             *    *
  *      **  *       ***** **         **              **             **   *
  *      **  *     ***     **         **              **             **   *
  *       ** *    **       **         **              **              *  *
  *       ** *   **        **         **              **              ** *
  *        ***   **        **         **              **               * *
  *        ***   **        **         **     *        **     *         **
  *         **   **        **  *      **     *        **     *         **
  *         **    **     ****  *       **   *          **   *          *
*****        *     ******   ***         ****            ****           *
                                                                       *
                                                                      *
                                                                  *****
                                                                  ****


 *
 */

#include "NattyBPlusTree.h"

#include "NattySqlHandle.h" 
#include "NattyAbstractClass.h"
#include "NattyResult.h"
#include "NattyDaveMQ.h"
#include "NattyMessage.h"
#include "NattyServAction.h"
#include "NattyUdpServer.h"
#include "NattyProtocol.h"
#include "NattyPush.h"

int ntyReadOfflineVoiceHandle(void *arg);


int ntyVoiceAckHandle(void *arg) {
	if (arg == NULL) return NTY_RESULT_ERROR;
	VALUE_TYPE *tag = arg;

	ntylog(" ntyVoiceAckHandle \n");

	C_DEVID fromId = tag->fromId;
	int msgId = tag->arg;

	int ret = ntyExecuteVoiceOfflineMsgDeleteHandle(msgId, fromId);
	if (ret == NTY_RESULT_FAILED) {
		ntyJsonCommonResult(fromId, NATTY_RESULT_CODE_ERR_DB_NOEXIST);
	} 
#if 0
	//read offline voice msg
	ret = ntyReadOfflineVoiceMsgAction(fromId);
	if (ret == NTY_RESULT_NOEXIST) {
		//BindConfirmReq
		//
	}
	
	free(tag);
	return ret;
#else

	tag->Type = MSG_TYPE_VOICE_OFFLINE_READ_HANDLE;
	tag->cb = ntyReadOfflineVoiceHandle;
	return ntyDaveMqPushMessage(tag);
	
#endif

}

int ntyCommonAckHandle(void *arg) {
	if (arg == NULL) return NTY_RESULT_ERROR;
	VALUE_TYPE *tag = arg;

	ntylog(" ntyCommonAckHandle \n");

	C_DEVID fromId = tag->fromId;
	int msgId = tag->arg;

	int ret = ntyExecuteCommonOfflineMsgDeleteHandle(msgId, fromId);
	if (ret == NTY_RESULT_FAILED) {
		ntylog("ntyCommonAckHandle DB Error \n");
	}
	
	tag->fromId = fromId;
	tag->Type = MSG_TYPE_OFFLINE_MSG_REQ_HANDLE;

	if (tag->Type == MSG_TYPE_DEVICE_COMMON_ACK_HANDLE) { //watch
		tag->cb = ntyDeviceOfflineMsgReqHandle;
	} else {
		tag->cb = ntyOfflineMsgReqHandle;
	}

	ntyDaveMqPushMessage(tag);


	return ret;
}


int ntyVoiceDataReqHandle(void *arg) {
	if (arg == NULL) return NTY_RESULT_ERROR;
	VALUE_TYPE *tag = arg;


	C_DEVID senderId = tag->fromId;
	C_DEVID gId = tag->toId;
	U8 *filename = tag->Tag;
	
	ntylog(" ntyVoiceDataReqHandle \n");
	U32 msgId = 0;

	//insert voice msg to db
	int ret = ntyQueryVoiceMsgInsertHandle(senderId, gId, filename, &msgId);
	if (ret == NTY_RESULT_SUCCESS) {
		ntyJsonCommonResult(senderId, NATTY_RESULT_CODE_SUCCESS);
	} else { //
		ntyJsonCommonResult(senderId, NATTY_RESULT_CODE_ERR_DB_OPERATION);
		return ret;
	}
	//broadcast to all id
	//json is null, length is 0
	ntySendVoiceBroadCastResult(senderId, gId, NULL, 0, msgId);
}


int ntyVoiceReqHandle(void *arg) {
	if (arg == NULL) return NTY_RESULT_ERROR;
	VALUE_TYPE *tag = arg;

	C_DEVID fromId = tag->fromId;
	int msgId = tag->arg;

	int ret = ntyVoiceReqAction(fromId, msgId);
	if (NTY_RESULT_FAILED == ret) {
		//delete fromId And MsgId
		ret = ntyExecuteVoiceOfflineMsgDeleteHandle(msgId, fromId);
		if (ret == NTY_RESULT_FAILED) {
			ntylog("ntyVoiceReqHandle --> ntyExecuteVoiceOfflineMsgDeleteHandle failed\n");
		} 
		//send next voice msg
		ret = ntyReadOfflineVoiceMsgAction(fromId);
		if (ret == NTY_RESULT_NOEXIST) {
			//read
			ntylog("ntyVoiceReqHandle --> ntyReadOfflineVoiceMsgAction failed\n");
		}
	}

	return 0;
}

//添加联系人消息发送到管理员
void ntyBindAgreeWatch(C_DEVID adminId, C_DEVID DeviceId, char *phonenum, int contactsTempId, char *pname, char *pimage) {
	AddContactsAck *pAddContactsAck = malloc(sizeof(AddContactsAck));
	if (pAddContactsAck == NULL) {
		ntylog("ntyBindAgreeWatch --> malloc AddContactsAck failed\n");
		return;
	}
	memset(pAddContactsAck, 0, sizeof(AddContactsAck));

	char bufIMEI[64] = {0};
	sprintf(bufIMEI, "%llx", DeviceId);
	char contactsId[16] = {0};
	sprintf(contactsId, "%d", contactsTempId);
	char add[16] = {0};
	char category[16] = {0};
	strcat(add, "Add");
	strcat(category, "Contacts");
	pAddContactsAck->results.id = contactsId;
	pAddContactsAck->results.IMEI = bufIMEI;
	pAddContactsAck->results.category = category;
	pAddContactsAck->results.action = add;
	pAddContactsAck->results.contacts.id = NULL;
	pAddContactsAck->results.contacts.name = pname;
	pAddContactsAck->results.contacts.image = pimage;
	pAddContactsAck->results.contacts.telphone = phonenum;

	C_DEVID fromId = adminId;
	C_DEVID toId = DeviceId;
	char *jsonagree = ntyJsonWriteAddContacts(pAddContactsAck);
	ntylog(" ntyBindAgreeWatch jsonagree: %s\n", jsonagree);
	
	int ret = ntySendRecodeJsonPacket(fromId, toId, jsonagree, (int)strlen(jsonagree));
	if (ret < 0) {
		ntylog(" ntyBindAgreeWatch --> SendCommonReq Exception\n");
		//ntyJsonCommonResult(fromId, NATTY_RESULT_CODE_ERR_DEVICE_NOTONLINE);
	}
	ntyJsonFree(jsonagree);
	free(pAddContactsAck);
}

int ntyBindConfirm(C_DEVID adminId, C_DEVID *ProposerId, C_DEVID DeviceId, U32 msgId, U8 *phonenum) {
	C_DEVID AppId = 0x0;

	int result = 0;
	int contactsTempId = 0;
	char pname[128] = {0};
	char pimage[512] = {0};
	
#if 1
	int ret = ntyExecuteDevAppGroupBindAndAgreeInsertHandle(msgId, ProposerId, phonenum, &contactsTempId, pname, pimage);
#else
	int ret = ntyExecuteDevAppGroupBindInsertHandle(msgId, ProposerId, phonenum);
#endif

	memcpy(&AppId, ProposerId, sizeof(C_DEVID));
	if (ret == -1) {
		ntylog(" ntyBindConfirm --> DB Exception\n");
	} else if (ret == -2) {
		ntylog(" ntyBindConfirm Cann't find %d msgid.\n", msgId);
	} else if (ret == -3) {
		ntylog(" ntyBindConfirm --> DB ROLLBACK\n");
	} else if (ret == 0) { //Bind Success Update RBTree
		
		void *heap = ntyBHeapInstance();
		NRecord *record = ntyBHeapSelect(heap, AppId);
		if (record != NULL) {
			Client *aclient = record->value;
			ASSERT(aclient != NULL);
			ntyVectorInsert(aclient->friends, &DeviceId, sizeof(C_DEVID));
		}

		record = ntyBHeapSelect(heap, DeviceId);
		if (record != NULL) {
			Client *dclient = record->value;
			ASSERT(dclient != NULL);
			ntyVectorInsert(dclient->friends, &AppId, sizeof(C_DEVID));
		}
		
		ntyBindAgreeWatch(adminId, DeviceId, phonenum, contactsTempId, pname, pimage);
	}
	ntylog(" ntyBindConfirm --> ntyJsonCommonResult\n");
	
	return ret;
}


int ntyBindConfirmReqHandle(void *arg) {
	ntylog("------------------- ntyBindConfirmReqHandle  begin--------------------------\n");
	
	if (arg == NULL) return NTY_RESULT_ERROR;

	VALUE_TYPE *tag = arg;
	U8 json[PACKET_BUFFER_SIZE] = {0};

	C_DEVID adminId = tag->fromId;
	C_DEVID proposerId = tag->toId; //read from TB_BIND_CONFIRM proposerId by msgid
	C_DEVID gId = tag->gId;
	U32 msgId = tag->arg;

	char msgIds[64] = {0};
	char answer[64] = {0};
	char imei[64] = {0};
	char adminIds[64] = {0};
	char bindConfirmReq[64] = {0};
	memcpy(bindConfirmReq, NATTY_USER_PROTOCOL_BINDCONFIRMREQ, strlen(NATTY_USER_PROTOCOL_BINDCONFIRMREQ));
	sprintf(imei, "%llx", gId);
	sprintf(msgIds, "%d", msgId);
	sprintf(adminIds, "%lld", tag->fromId);
	
	U8 flag = tag->u8LocationType;
	ntylog(" ntyBindConfirmReqHandle flag:%d, proposerId:%lld\n", flag, proposerId);
	if (flag == 1) { // AGREE
		char phonenum[64] = {0};
		int ret = ntyBindConfirm(adminId, &proposerId, gId, msgId, phonenum); 
#if 0
		//select phone 
		ntyQueryPhoneBookSelectHandle(gId, proposerId, phonenum);
		ntydbg("ntyBindConfirmReqHandle->flag:%d, phnum:%s\n", flag, phonenum);
#endif
		BindBroadCast *pBindBroadCast = malloc(sizeof(BindBroadCast));
		memcpy(answer, NATTY_USER_PROTOCOL_AGREE, strlen(NATTY_USER_PROTOCOL_AGREE));
		
		pBindBroadCast->result.IMEI = imei;
		pBindBroadCast->result.category = bindConfirmReq;
		pBindBroadCast->result.proposer = phonenum;
		pBindBroadCast->result.answer = answer;
		
		char *jsonresult = ntyJsonWriteBindBroadCast(pBindBroadCast);
		ntydbg("ntyBindConfirmReqHandle agree json: ->%s\n",  jsonresult);

		//保存离线数据到数据库
		int tempMsgId = 0;
		ret = ntyExecuteCommonMsgInsertHandle(adminId, gId, jsonresult, &tempMsgId);
		
		ntyJsonBroadCastRecvResult(adminId, gId, (U8*)jsonresult, msgId);
		ntyJsonFree(jsonresult);
		free(pBindBroadCast);

#if 0
		//发送管理员同意消息到手表
		ntyBindAgreeAction(imei, adminId, proposerId, gId, phonenum, msgId);
#endif
	} else if (flag == 0) {  // REJECT

		char phonenum[64] = {0};
#if 0
		int ret = ntyBindConfirm(adminId, &proposerId, gId, msgId, phonenum); 
#else
		int ret = ntyExecuteBindConfirmDeleteHandle(msgId, phonenum, &proposerId);
		ntydbg("ntyJsonBroadCastRecvResult->%lld\n", proposerId);
#endif
		BindBroadCast *pBindBroadCast = malloc(sizeof(BindBroadCast));
		memcpy(answer, NATTY_USER_PROTOCOL_REJECT, strlen(NATTY_USER_PROTOCOL_REJECT));
		
		pBindBroadCast->result.IMEI = imei;
		pBindBroadCast->result.category = bindConfirmReq;
		pBindBroadCast->result.proposer = phonenum;
		pBindBroadCast->result.answer = answer;
		
		char *jsonresult = ntyJsonWriteBindBroadCast(pBindBroadCast);
		ntydbg("ntyJsonBroadCastRecvResult->%s\n",  jsonresult);

		//保存离线数据到数据库
		int tempMsgId = 0;
		ret = ntyExecuteCommonMsgToProposerInsertHandle(proposerId, gId, jsonresult, &tempMsgId);
		
		
		ntyProtoBindAck(proposerId, gId, 6); //reject

		ntyJsonFree(jsonresult);
		free(pBindBroadCast);
	}
	
	free(tag);
	
	ntylog("------------------- ntyBindConfirmReqHandle  end--------------------------\n");
	return 0;
}

int ntyReadOfflineBindMsgHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;
	if (tag == NULL) return NTY_RESULT_ERROR;
	
	C_DEVID fromId = tag->fromId;
	
	int ret = ntyReadOfflineBindMsgToAdminAction(fromId);
	if (ret == NTY_RESULT_NOEXIST) { 
		ntylog("ntyReadOfflineBindMsgHandle --> Client Id: %lld have no offline msg\n", fromId);
	}
	free(tag);

	return ret;
}

int ntyReadOfflineVoiceHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;
	if (tag == NULL) return NTY_RESULT_ERROR;
	
	C_DEVID fromId = tag->fromId;

	int ret = ntyReadOfflineVoiceMsgAction(fromId);
	if (ret == NTY_RESULT_NOEXIST) {

		void *heap = ntyBHeapInstance();
		NRecord *record = ntyBHeapSelect(heap, fromId);
		if (record == NULL) goto exit;
		
		Client *pClient = (Client *)record->value;
		if (pClient->deviceType != NTY_PROTO_CLIENT_WATCH) {

			tag->Type = MSG_TYPE_BIND_OFFLINE_PUSH_HANDLE;
			tag->cb = ntyReadOfflineBindMsgHandle;
			return ntyDaveMqPushMessage(tag);
		}
	}
	
exit:
	free(tag);

	return ret;
}

int ntyDeviceOfflineMsgReqHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;
	if (tag == NULL) return NTY_RESULT_ERROR;
	
	C_DEVID fromId = tag->fromId;

	int ret = ntyReadDeviceOfflineCommonMsgAction(fromId);
	if (ret == NTY_RESULT_NOEXIST) {
		ntylog("ntyDeviceOfflineMsgReqHandle --> no offline message\n");
		
		tag->Type = MSG_TYPE_VOICE_OFFLINE_READ_HANDLE;
		tag->cb = ntyReadOfflineVoiceHandle;
		return ntyDaveMqPushMessage(tag);
	}
	free(tag);

	return ret;
}

int ntyOfflineMsgReqHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;
	if (tag == NULL) return NTY_RESULT_ERROR;
	
	C_DEVID fromId = tag->fromId;

	int ret = ntyReadOfflineCommonMsgAction(fromId);
	if (ret == NTY_RESULT_NOEXIST) {
		
		tag->Type = MSG_TYPE_VOICE_OFFLINE_READ_HANDLE;
		tag->cb = ntyReadOfflineVoiceHandle;
		return ntyDaveMqPushMessage(tag);
	}
	free(tag);

	return ret;
}

int ntyBindPushAdministratorHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;
	
	if (tag == NULL) return NTY_RESULT_ERROR;

	C_DEVID devId = tag->gId;
	C_DEVID proposer = tag->fromId;
	C_DEVID admin = tag->toId;

	char phonenum[30] = {0};
	ntyQueryPhoneBookSelectHandle(devId, proposer, phonenum);
	ntylog(" ntyBindPushAdministratorHandle : %s\n", phonenum);

	if (tag->Tag == NULL) return NTY_RESULT_ERROR;
	
	BindReq *pBindReq = (BindReq*)tag->Tag;
	
	int msgId = tag->arg;

	BindConfirmPush *pBindConfirmPush = malloc(sizeof(BindConfirmPush));
	if (pBindConfirmPush == NULL) {
		goto exit;
	}
	pBindConfirmPush->result.IMEI = pBindReq->IMEI;
	pBindConfirmPush->result.proposer = phonenum;
	pBindConfirmPush->result.userName = pBindReq->bind.userName;
	
	char ids[30] = {0};
	sprintf(ids, "%d", msgId);
	pBindConfirmPush->result.msgId = ids;
	char *jsonstring = ntyJsonWriteBindConfirmPush(pBindConfirmPush);

	ntydbg("-----------------------send json to admin---------------------------------\n");
		//send json to admin
	ntySendBindConfirmPushResult(proposer, admin, (U8*)jsonstring, strlen(jsonstring));

	//release 
	free(pBindConfirmPush);
	
exit:
	free(pBindReq);
	free(tag);
}

int ntyBindParserJsonHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;

	if (tag == NULL) return NTY_RESULT_ERROR;
	
	JSON_Value *json = (JSON_Value*)tag->Tag;
	if (json == NULL) {
		ntylog( " ntyBindParserJsonHandle Json Error\n ");
		return NTY_RESULT_ERROR;
	}

	ntylog(" ntyBindParserJsonHandle \n");
	BindReq *pBindReq = malloc(sizeof(BindReq));
	if (pBindReq == NULL) return NTY_RESULT_ERROR;
	ntyJsonBind(json, pBindReq);


	C_DEVID proposer = tag->fromId;
	C_DEVID devId = tag->gId;
	C_DEVID admin = tag->toId;
	U8 *name = (U8*)pBindReq->bind.watchName;
	U8 *wimage = (U8*)pBindReq->bind.watchImage;
	U8 *call = (U8*)pBindReq->bind.userName;
	U8 *uimage = (U8*)pBindReq->bind.userImage;

	if (tag->arg == NTY_BIND_ACK_FIRST_BIND) {

		ntyFreeJsonValue(json);
		free(tag);
		
		return ntyQueryAdminGroupInsertHandle(devId, name, proposer, call, wimage, uimage);
		
	} else if (tag->arg == NTY_BIND_ACK_SUCCESS) {
		int msgId = 0;
		//绑定确认添加
		ntyQueryBindConfirmInsertHandle(admin, devId, name, wimage, proposer, call, uimage, &msgId);

		ntyFreeJsonValue(json);
		tag->Tag = (U8*)pBindReq;
	
		tag->arg = msgId;
		tag->Type = MSG_TYPE_BIND_PUSH_ADMINISTRATOR_HANDLE;
		tag->cb = ntyBindPushAdministratorHandle;
		ntyDaveMqPushMessage(tag);

		return NTY_RESULT_PROCESS;
		
	}

	ntyFreeJsonValue(json);
	free(tag);
}


int ntyAdministratorSelectHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;

	if (tag == NULL) return NTY_RESULT_ERROR;

	C_DEVID fromId = tag->fromId;
	C_DEVID devId = tag->gId;
	C_DEVID admin = 0x0;

	ntylog(" ntyAdministratorSelectHandle fromId:%lld, devId:%lld\n", fromId, devId);
	if(NTY_RESULT_FAILED == ntyQueryAdminSelectHandle(devId, &admin)) {
		ntylog(" ntyAdministratorSelectHandle Failed\n");
		if (tag->Tag != NULL) {
			JSON_Value *json = (JSON_Value*)tag->Tag;
			if (json != NULL) {
				ntyFreeJsonValue(json);
			}
			tag->Tag = NULL;
		}
		free(tag);

		return NTY_RESULT_ERROR;
	}

	tag->toId = admin;
	tag->Type = MSG_TYPE_BIND_JSON_PARSER_HANDLE;
	tag->cb = ntyBindParserJsonHandle;
	ntyDaveMqPushMessage(tag);

	return NTY_RESULT_SUCCESS;
}




int ntyBindDeviceCheckStatusReqHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;
	if (tag == NULL) return NTY_RESULT_ERROR;
	
	C_DEVID fromId = tag->fromId;
	C_DEVID devId = tag->gId;

	ntylog(" ntyBindDeviceCheckStatusReqHandle fromId:%lld, devId:%lld\n", fromId, devId);
	int ret = ntyQueryDevAppGroupCheckSelectHandle(fromId, devId);

	if (ret == NTY_RESULT_FAILED) {
		ret = NTY_BIND_ACK_ERROR;
	}
	ntyProtoBindAck(fromId, devId, ret); //return to fromId

	ntylog(" ntyBindDeviceCheckStatusReqHandle ret:%d\n", ret);
	if (ret == NTY_BIND_ACK_FIRST_BIND) { //SQL first band Watch
	
		tag->arg = NTY_BIND_ACK_FIRST_BIND;
		tag->toId = fromId;
		tag->Type = MSG_TYPE_BIND_JSON_PARSER_HANDLE;
		tag->cb = ntyBindParserJsonHandle;
		ntyDaveMqPushMessage(tag);
		
		return NTY_RESULT_SUCCESS;
	} else if (ret == NTY_BIND_ACK_SUCCESS){

		tag->arg = NTY_BIND_ACK_SUCCESS;
		tag->Type = MSG_TYPE_BIND_SELECT_ADMIN_HANDLE;
		tag->cb = ntyAdministratorSelectHandle;
		
		ntyDaveMqPushMessage(tag);

		return NTY_RESULT_SUCCESS;
	}

	JSON_Value *json = (JSON_Value*)tag->Tag;
	if (json != NULL) {
		ntyFreeJsonValue(json);
	}
	free(tag);

	return NTY_RESULT_FAILED;

	
}


int ntyLocationBroadCastHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;

	if (tag == NULL) return NTY_RESULT_ERROR;

	C_DEVID fromId = tag->fromId;
	C_DEVID gId = tag->gId;
	U8 *json = tag->Tag;
	int length = tag->length;


	ntySendLocationBroadCastResult(fromId, gId, json, length);

	if (tag->Tag == NULL) {
		free(tag->Tag);
	}
	free(tag);

	return NTY_RESULT_SUCCESS;
}


int ntyIOSPushHandle(void *arg) {
	VALUE_TYPE *tag = (VALUE_TYPE*)arg;

	if (tag == NULL) return NTY_RESULT_ERROR;

	C_DEVID toId = tag->toId;
	U8 *msg = tag->Tag;

	void *heap = ntyBHeapInstance();
	NRecord *record = ntyBHeapSelect(heap, toId);
	if (record == NULL) goto exit;
	Client *pClient = (Client *)record->value;

	if (pClient->deviceType == NTY_PROTO_CLIENT_IOS) {
		if (pClient->token != NULL) {
			ntylog("ntySendPushNotify --> selfId:%lld  token:%s\n", toId, pClient->token);
			void *pushHandle = ntyPushHandleInstance();
			ntyPushNotifyHandle(pushHandle, msg, pClient->token);
		}
		goto exit;
	}
exit:
	free(msg);
	free(tag);
	
	return NTY_RESULT_SUCCESS;
}


