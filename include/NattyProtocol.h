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





#ifndef __NATTY_PROTOCOL_H__
#define __NATTY_PROTOCOL_H__

#define NTY_PROTO_VERSION				'A'

#define NTY_PROTO_CLIENT_WATCH			'D'
#define NTY_PROTO_CLIENT_ANDROID		'A'
#define NTY_PROTO_CLIENT_IOS			'I'
#define NTY_PROTO_CLIENT_IOS_PUBLISH	'P'		
#define NTY_PROTO_CLIENT_WEB			'W'
#define NTY_PROTO_CLIENT_PC				'C'
#define NTY_PROTO_SERVER				'S'
#define NTY_PROTO_CLIENT_DEFAULT		0x0 //server

#define NTY_PROTO_SELFTYPE				NTY_PROTO_CLIENT_WATCH

#define NTY_PROTO_MULTICAST_DEVID		0x0

/* ** **** ********  ****************  Length  ****************  ******** **** ** */
#define NTY_DEVID_LENGTH				8
#define NTY_ACKNUM_LENGTH				4
#define NTY_IPADDR_LENGTH				4
#define NTY_IPPORT_LENGTH				2
#define NTY_CRCNUM_LENGTH				4

#define NTY_JSON_COUNT_LENGTH			2
#define NTY_STATUS_LENGTH				2
#define NTY_RESULT_LENGTH				4
#define NTY_PROTO_MIN_LENGTH			16

#define NTY_PKTIDX_LENGTH				2
#define NTY_VOICEREQ_COUNT_LENGTH		30
#define NTY_VOICEREQ_HEADER_LENGTH		32
#define NTY_VOICEREQ_PACKET_LENGTH		1024
#define NTY_VOICEREQ_DATA_LENGTH		988
#define NTY_VOICEREQ_EXTEND_LENGTH		(NTY_VOICEREQ_HEADER_LENGTH+NTY_CRCNUM_LENGTH)


#define NTY_HEARTBEAT_ACK_LENGTH		32
#define NTY_LOGOUT_ACK_LENGTH			5
#define NTY_LOGIN_ACK_LENGTH			512
#define NTY_P2PADDR_ACK_LENGTH			512
#define NTY_P2P_NOTIFY_ACK_LENGTH		128
#define NTY_PROXYDATA_PACKET_LENGTH		1024
#define NTY_DATA_PACKET_LENGTH			1024
//#define NTY_PROTO_DATAPACKET_ACK_LENGTH	32

/* ** **** ********  ****************  Index  ****************  ******** **** ** */
#define NTY_PROTO_VERSION_IDX					0  //'A' is device and 'B' is app
#define NTY_PROTO_DEVTYPE_IDX					(NTY_PROTO_VERSION_IDX+1)
#define NTY_PROTO_PROTOTYPE_IDX					(NTY_PROTO_DEVTYPE_IDX+1)
#define NTY_PROTO_MSGTYPE_IDX					(NTY_PROTO_PROTOTYPE_IDX+1)

#define NTY_PROTO_DEVID_IDX						(NTY_PROTO_MSGTYPE_IDX+1)
#define NTY_PROTO_ACKNUM_IDX					(NTY_PROTO_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_DEST_DEVID_IDX				(NTY_PROTO_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_CRC_IDX						(NTY_PROTO_DEST_DEVID_IDX+NTY_DEVID_LENGTH)

#define NTY_PROTO_LOGIN_REQ_DEVID_IDX			NTY_PROTO_DEVID_IDX	
#define NTY_PROTO_LOGIN_REQ_JSON_LENGTH_IDX		(NTY_PROTO_LOGIN_REQ_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_LOGIN_REQ_JSON_CONTENT_IDX	(NTY_PROTO_LOGIN_REQ_JSON_LENGTH_IDX+2)
//have no json data
#define NTY_PROTO_LOGIN_REQ_CRC_IDX				(NTY_PROTO_LOGIN_REQ_DEVID_IDX+NTY_DEVID_LENGTH)

#define NTY_PROTO_LOGIN_ACK_STATUS_IDX				(NTY_PROTO_MSGTYPE_IDX+1)
#define NTY_PROTO_LOGIN_ACK_JSON_LENGTH_IDX			(NTY_PROTO_LOGIN_ACK_STATUS_IDX+NTY_STATUS_LENGTH)
#define NTY_PROTO_LOGIN_ACK_JSON_CONTENT_IDX		(NTY_PROTO_LOGIN_ACK_JSON_LENGTH_IDX+2)
//have no json data
#define NTY_PROTO_LOGIN_ACK_CRC_IDX					(NTY_PROTO_LOGIN_ACK_STATUS_IDX+NTY_STATUS_LENGTH)

#define NTY_PROTO_HEARTBEAT_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_HEARTBEAT_CRC_IDX					(NTY_PROTO_HEARTBEAT_DEVID_IDX+NTY_DEVID_LENGTH)

#define NTY_PROTO_HEARTBEAT_REQ_DEVID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_HEARTBEAT_REQ_CRC_IDX					(NTY_PROTO_HEARTBEAT_DEVID_IDX+NTY_DEVID_LENGTH)

#define NTY_PROTO_HEARTBEAT_ACK_STATUS_IDX			(NTY_PROTO_MSGTYPE_IDX+1)		
#define NTY_PROTO_HEARTBEAT_ACK_CRC_IDX				(NTY_PROTO_HEARTBEAT_ACK_STATUS_IDX+NTY_STATUS_LENGTH)

#define NTY_PROTO_LOGOUT_REQ_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_LOGOUT_REQ_CRC_IDX				(NTY_PROTO_LOGOUT_REQ_DEVID_IDX+NTY_DEVID_LENGTH)

#define NTY_PROTO_LOGOUT_ACK_STATUS_IDX				(NTY_PROTO_MSGTYPE_IDX+1)
#define NTY_PROTO_LOGOUT_ACK_CRC_IDX				(NTY_PROTO_LOGOUT_ACK_STATUS_IDX+NTY_STATUS_LENGTH)

#define NTY_PROTO_TIME_REQ_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_TIME_REQ_CRC_IDX					(NTY_PROTO_TIME_REQ_DEVID_IDX+NTY_DEVID_LENGTH)

#define NTY_PROTO_TIME_ACK_YEAR_IDX					(NTY_PROTO_MSGTYPE_IDX+1)
#define NTY_PROTO_TIME_ACK_MONTH_IDX				(NTY_PROTO_TIME_ACK_YEAR_IDX+1)
#define NTY_PROTO_TIME_ACK_DAY_IDX					(NTY_PROTO_TIME_ACK_MONTH_IDX+1)
#define NTY_PROTO_TIME_ACK_WDAY_IDX					(NTY_PROTO_TIME_ACK_DAY_IDX+1)
#define NTY_PROTO_TIME_ACK_HOUR_IDX					(NTY_PROTO_TIME_ACK_WDAY_IDX+1)
#define NTY_PROTO_TIME_ACK_MINUTE_IDX				(NTY_PROTO_TIME_ACK_HOUR_IDX+1)
#define NTY_PROTO_TIME_ACK_SECOND_IDX				(NTY_PROTO_TIME_ACK_MINUTE_IDX+1)
#define NTY_PROTO_TIME_ACK_CRC_IDX					(NTY_PROTO_TIME_ACK_SECOND_IDX+1)

#define NTY_PROTO_ICCID_REQ_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_ICCID_REQ_JSON_LENGTH_IDX			(NTY_PROTO_ICCID_REQ_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_ICCID_REQ_JSON_CONTENT_IDX		(NTY_PROTO_ICCID_REQ_JSON_LENGTH_IDX+2)

#define NTY_PROTO_ICCID_ACK_STATUS_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_ICCID_ACK_JSON_LENGTH_IDX			(NTY_PROTO_ICCID_ACK_STATUS_IDX+2)			
#define NTY_PROTO_ICCID_ACK_JSON_CONTENT_IDX		(NTY_PROTO_ICCID_ACK_JSON_LENGTH_IDX+NTY_DEVID_LENGTH)


#define NTY_PROTO_VOICE_REQ_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_VOICE_REQ_MSGID_IDX				(NTY_PROTO_VOICE_REQ_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_VOICE_REQ_JSON_LENGTH_IDX			(NTY_PROTO_VOICE_REQ_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_VOICE_REQ_JSON_CONTENT_IDX		(NTY_PROTO_VOICE_REQ_JSON_LENGTH_IDX+2)


#define NTY_PROTO_VOICE_ACK_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_VOICE_ACK_MSGID_IDX				(NTY_PROTO_VOICE_ACK_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_VOICE_ACK_JSON_LENGTH_IDX			(NTY_PROTO_VOICE_ACK_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_VOICE_ACK_JSON_CONTENT_IDX		(NTY_PROTO_VOICE_ACK_JSON_LENGTH_IDX+2)


#define NTY_PROTO_COMMON_REQ_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_COMMON_REQ_RSVD_IDX				(NTY_PROTO_COMMON_REQ_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_COMMON_REQ_RECVID_IDX				(NTY_PROTO_COMMON_REQ_RSVD_IDX+4)
#define NTY_PROTO_COMMON_REQ_JSON_LENGTH_IDX		(NTY_PROTO_COMMON_REQ_RECVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_COMMON_REQ_JSON_CONTENT_IDX		(NTY_PROTO_COMMON_REQ_JSON_LENGTH_IDX+2)

#define NTY_PROTO_COMMON_ACK_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_COMMON_ACK_MSGID_IDX				(NTY_PROTO_COMMON_ACK_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_COMMON_ACK_JSON_LENGTH_IDX		(NTY_PROTO_COMMON_ACK_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_COMMON_ACK_JSON_CONTENT_IDX		(NTY_PROTO_COMMON_ACK_JSON_LENGTH_IDX+2)


#define NTY_PROTO_VOICE_DATA_REQ_DEVID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_VOICE_DATA_REQ_GROUP_IDX			(NTY_PROTO_VOICE_DATA_REQ_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_VOICE_DATA_REQ_PKTINDEX_IDX		(NTY_PROTO_VOICE_DATA_REQ_GROUP_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_VOICE_DATA_REQ_PKTTOTLE_IDX		(NTY_PROTO_VOICE_DATA_REQ_PKTINDEX_IDX+2)
#define NTY_PROTO_VOICE_DATA_REQ_PKTLENGTH_IDX		(NTY_PROTO_VOICE_DATA_REQ_PKTTOTLE_IDX+2)
#define NTY_PROTO_VOICE_DATA_REQ_OFFLINEMSGID_IDX	(NTY_PROTO_VOICE_DATA_REQ_PKTLENGTH_IDX+4)
#define NTY_PROTO_VOICE_DATA_REQ_PKTDATA_START_IDX	32


#define NTY_PROTO_VOICE_DATA_ACK_STATUS_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_VOICE_DATA_ACK_CRC_IDX				(NTY_PROTO_VOICE_DATA_ACK_STATUS_IDX+2)

#define NTY_PROTO_LOCATION_ASYNC_REQ_DEVID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_LOCATION_ASYNC_REQ_JSON_LENGTH_IDX	(NTY_PROTO_LOCATION_ASYNC_REQ_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_LOCATION_ASYNC_REQ_JSON_CONTENT_IDX	(NTY_PROTO_LOCATION_ASYNC_REQ_JSON_LENGTH_IDX+2)

#define NTY_PROTO_LOCATION_PUSH_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_LOCATION_PUSH_JSON_LENGTH_IDX			(NTY_PROTO_LOCATION_PUSH_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_LOCATION_PUSH_JSON_CONTENT_IDX		(NTY_PROTO_LOCATION_PUSH_JSON_LENGTH_IDX+2)


#define NTY_PROTO_WEATHER_ASYNC_REQ_DEVID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_WEATHER_ASYNC_REQ_JSON_LENGTH_IDX		(NTY_PROTO_WEATHER_ASYNC_REQ_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_WEATHER_ASYNC_REQ_JSON_CONTENT_IDX	(NTY_PROTO_WEATHER_ASYNC_REQ_JSON_LENGTH_IDX+2)


#define NTY_PROTO_WEATHER_PUSH_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_WEATHER_PUSH_JSON_LENGTH_IDX			(NTY_PROTO_WEATHER_PUSH_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_WEATHER_PUSH_JSON_CONTENT_IDX			(NTY_PROTO_WEATHER_PUSH_JSON_LENGTH_IDX+2)



#define NTY_PROTO_DATA_ROUTE_DEVID_IDX					NTY_PROTO_DEVID_IDX
#define NTY_PROTO_DATA_ROUTE_RSVD_IDX					(NTY_PROTO_DATA_ROUTE_DEVID_IDX+NTY_DEVID_LENGTH)
//SYN Data
#define NTY_PROTO_DATA_ROUTE_RECVID_IDX					(NTY_PROTO_DATA_ROUTE_RSVD_IDX+4)
#define NTY_PROTO_DATA_ROUTE_JSON_LENGTH_IDX			(NTY_PROTO_DATA_ROUTE_RECVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_DATA_ROUTE_JSON_CONTENT_IDX			(NTY_PROTO_DATA_ROUTE_JSON_LENGTH_IDX+2)

#define NTY_PROTO_DATA_RESULT_STATUS_IDX				NTY_PROTO_DEVID_IDX
//Ack Data
#define NTY_PROTO_DATA_RESULT_ACKNUM_IDX				(NTY_PROTO_DATA_RESULT_STATUS_IDX+2)
#define NTY_PROTO_DATA_RESULT_JSON_LENGTH_IDX			(NTY_PROTO_DATA_RESULT_ACKNUM_IDX+4)
#define NTY_PROTO_DATA_RESULT_JSON_CONTENT_IDX			(NTY_PROTO_DATA_RESULT_JSON_LENGTH_IDX+2)
#define NTY_PROTO_DATA_RESULT_CRC_IDX					(NTY_PROTO_DATA_RESULT_ACKNUM_IDX+4)


#define NTY_PROTO_VOICE_BROADCAST_DEVID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_VOICE_BROADCAST_MSGID_IDX				(NTY_PROTO_VOICE_BROADCAST_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_VOICE_BROADCAST_RSVD_IDX				(NTY_PROTO_VOICE_BROADCAST_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_VOICE_BROADCAST_JSON_LENGTH_IDX		(NTY_PROTO_VOICE_BROADCAST_RSVD_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_VOICE_BROADCAST_JSON_CONTENT_IDX		(NTY_PROTO_VOICE_BROADCAST_JSON_LENGTH_IDX+2)

#define NTY_PROTO_LOCATION_BROADCAST_DEVID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_LOCATION_BROADCAST_RSVD_IDX			(NTY_PROTO_LOCATION_BROADCAST_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_LOCATION_BROADCAST_JSON_LENGTH_IDX	(NTY_PROTO_LOCATION_BROADCAST_RSVD_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_LOCATION_BROADCAST_JSON_CONTENT_IDX	(NTY_PROTO_LOCATION_BROADCAST_JSON_LENGTH_IDX+2)

#define NTY_PROTO_COMMON_BROADCAST_DEVID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_COMMON_BROADCAST_MSGID_IDX			(NTY_PROTO_COMMON_BROADCAST_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_COMMON_BROADCAST_RSVD_IDX				(NTY_PROTO_COMMON_BROADCAST_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_COMMON_BROADCAST_JSON_LENGTH_IDX		(NTY_PROTO_COMMON_BROADCAST_RSVD_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_COMMON_BROADCAST_JSON_CONTENT_IDX		(NTY_PROTO_COMMON_BROADCAST_JSON_LENGTH_IDX+2)


#define NTY_PROTO_UNBIND_APPID_IDX						NTY_PROTO_DEVID_IDX
#define NTY_PROTO_UNBIND_ACKNUM_IDX						NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_UNBIND_DEVICEID_IDX					NTY_PROTO_DEST_DEVID_IDX
#define NTY_PROTO_UNBIND_CRC_IDX						NTY_PROTO_CRC_IDX

#define NTY_PROTO_UNBIND_ACK_DEVICEID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_UNBIND_ACK_RESULT_IDX					(NTY_PROTO_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_UNBIND_ACK_CRC_IDX					(NTY_PROTO_UNBIND_ACK_RESULT_IDX+NTY_RESULT_LENGTH)

#define NTY_PROTO_BIND_APPID_IDX						NTY_PROTO_DEVID_IDX
#define NTY_PROTO_BIND_ACKNUM_IDX						(NTY_PROTO_BIND_APPID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_DEVICEID_IDX						(NTY_PROTO_BIND_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_BIND_JSON_LENGTH_IDX					(NTY_PROTO_BIND_DEVICEID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_JSON_CONTENT_IDX					(NTY_PROTO_BIND_JSON_LENGTH_IDX+2)
#define NTY_PROTO_BIND_CRC_IDX							NTY_PROTO_CRC_IDX

#define NTY_PROTO_BIND_ACK_DEVICEID_IDX					NTY_PROTO_DEVID_IDX
#define NTY_PROTO_BIND_ACK_RESULT_IDX					(NTY_PROTO_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_ACK_JSON_LENGTH_IDX				(NTY_PROTO_BIND_ACK_RESULT_IDX+NTY_RESULT_LENGTH)
#define NTY_PROTO_BIND_ACK_JSON_CONTENT_IDX				(NTY_PROTO_BIND_ACK_JSON_LENGTH_IDX+NTY_RESULT_LENGTH)
#define NTY_PROTO_BIND_ACK_CRC_IDX						(NTY_PROTO_BIND_ACK_RESULT_IDX+NTY_RESULT_LENGTH)

#define NTY_PROTO_BIND_CONFIRM_REQ_ADMIN_SELFID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_BIND_CONFIRM_REQ_DEVICEID_IDX				(NTY_PROTO_BIND_CONFIRM_REQ_ADMIN_SELFID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_REQ_PROPOSER_IDX				(NTY_PROTO_BIND_CONFIRM_REQ_DEVICEID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_REQ_MSGID_IDX				(NTY_PROTO_BIND_CONFIRM_REQ_PROPOSER_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_REQ_JSON_LENGTH_IDX			(NTY_PROTO_BIND_CONFIRM_REQ_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_REQ_JSON_CONTENT_IDX			(NTY_PROTO_BIND_CONFIRM_REQ_JSON_LENGTH_IDX+2)


#define NTY_PROTO_BIND_CONFIRM_PUSH_PROPOSER_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_BIND_CONFIRM_PUSH_DEVICE_IDX					(NTY_PROTO_BIND_CONFIRM_PUSH_PROPOSER_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_PUSH_MSGID_IDX					(NTY_PROTO_BIND_CONFIRM_PUSH_DEVICE_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_PUSH_JSON_LENGTH_IDX				(NTY_PROTO_BIND_CONFIRM_PUSH_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_PUSH_JSON_CONTENT_IDX			(NTY_PROTO_BIND_CONFIRM_PUSH_JSON_LENGTH_IDX+2)



#define NTY_PROTO_OFFLINE_MSG_REQ_DEVICEID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_OFFLINE_MSG_REQ_CRC_IDX					(NTY_PROTO_OFFLINE_MSG_REQ_DEVICEID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_OFFLINE_MSG_REQ_JSON_LENGTH_IDX			(NTY_PROTO_OFFLINE_MSG_ACK_STATUS_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_OFFLINE_MSG_REQ_JSON_CONTENT_IDX			(NTY_PROTO_OFFLINE_MSG_ACK_JSON_LENGTH_IDX+2)


#define NTY_PROTO_OFFLINE_MSG_ACK_STATUS_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_OFFLINE_MSG_ACK_MSGID_IDX					(NTY_PROTO_OFFLINE_MSG_ACK_STATUS_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_OFFLINE_MSG_ACK_JSON_LENGTH_IDX			(NTY_PROTO_OFFLINE_MSG_ACK_STATUS_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_OFFLINE_MSG_ACK_JSON_CONTENT_IDX			(NTY_PROTO_OFFLINE_MSG_ACK_JSON_LENGTH_IDX+2)

#define NTY_PROTO_USERDATA_PACKET_REQ_DEVICEID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_USERDATA_PACKET_REQ_JSON_LENGTH_IDX		(NTY_PROTO_USERDATA_PACKET_REQ_DEVICEID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_USERDATA_PACKET_REQ_JSON_CONTENT_IDX		(NTY_PROTO_USERDATA_PACKET_REQ_JSON_LENGTH_IDX+2)

#define NTY_PROTO_USERDATA_PACKET_ACK_DEVICEID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_USERDATA_PACKET_ACK_JSON_LENGTH_IDX		(NTY_PROTO_USERDATA_PACKET_ACK_DEVICEID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_USERDATA_PACKET_ACK_JSON_CONTENT_IDX		(NTY_PROTO_USERDATA_PACKET_ACK_JSON_LENGTH_IDX+2)


#if 0
#define NTY_PROTO_BIND_CONFIRM_REQ_DEVICEID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_BIND_CONFIRM_REQ_RSVD_IDX				(NTY_PROTO_BIND_CONFIRM_REQ_DEVICEID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_REQ_JSON_LENGTH_IDX		(NTY_PROTO_BIND_CONFIRM_REQ_RSVD_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_REQ_JSON_CONTENT_IDX		(NTY_PROTO_BIND_CONFIRM_REQ_JSON_LENGTH_IDX+2)

#define NTY_PROTO_BIND_CONFIRM_PUSH_DEVICEID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_BIND_CONFIRM_PUSH_MSGID_IDX				(NTY_PROTO_BIND_CONFIRM_PUSH_DEVICEID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_PUSH_JSON_LENGTH_IDX			(NTY_PROTO_BIND_CONFIRM_PUSH_MSGID_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_BIND_CONFIRM_PUSH_JSON_CONTENT_IDX		(NTY_PROTO_BIND_CONFIRM_PUSH_JSON_LENGTH_IDX+2)
#endif

/** ** **** ******** **************** rsvd **************** ******** **** ** **/


#define NTY_PROTO_LOGIN_ACK_ACKNUM_IDX					NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_LOGIN_ACK_FRIENDS_COUNT_IDX			(NTY_PROTO_LOGIN_ACK_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_LOGIN_ACK_FRIENDSLIST_START_IDX		(NTY_PROTO_LOGIN_ACK_FRIENDS_COUNT_IDX+2)

#define NTY_PROTO_LOGIN_ACK_FRIENDSLIST_DEVID_IDX(x)								\
					(NTY_PROTO_LOGIN_ACK_FRIENDSLIST_START_IDX + 					\
					(NTY_DEVID_LENGTH+NTY_IPADDR_LENGTH+NTY_IPPORT_LENGTH)*(x))
					
#define NTY_PROTO_LOGIN_ACK_FRIENDSLIST_ADDR_IDX(x)								\
					(NTY_PROTO_LOGIN_ACK_FRIENDSLIST_START_IDX + NTY_DEVID_LENGTH +	\
					(NTY_DEVID_LENGTH+NTY_IPADDR_LENGTH+NTY_IPPORT_LENGTH)*(x))

#define NTY_PROTO_LOGIN_ACK_FRIENDSLIST_PORT_IDX(x)								\
					(NTY_PROTO_LOGIN_ACK_FRIENDSLIST_START_IDX + NTY_DEVID_LENGTH + NTY_IPADDR_LENGTH +	\
					(NTY_DEVID_LENGTH+NTY_IPADDR_LENGTH+NTY_IPPORT_LENGTH)*(x))

//#define NTY_PROTO_LOGIN_ACK_CRC_IDX(x)		NTY_PROTO_LOGIN_ACK_FRIENDSLIST_DEVID_IDX(x)



#define NTY_PROTO_DATAPACKET_DEVID_IDX				NTY_PROTO_HEARTBEAT_DEVID_IDX
#define NTY_PROTO_DATAPACKET_ACKNUM_IDX				(NTY_PROTO_HEARTBEAT_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_DATAPACKET_DEST_DEVID_IDX			(NTY_PROTO_DATAPACKET_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_DATAPACKET_CONTENT_COUNT_IDX		(NTY_PROTO_DATAPACKET_DEST_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_DATAPACKET_CONTENT_IDX			(NTY_PROTO_DATAPACKET_CONTENT_COUNT_IDX+2)

#define NTY_PROTO_DATAPACKET_NOTIFY_DEVID_IDX		NTY_PROTO_HEARTBEAT_DEVID_IDX
#define NTY_PROTO_DATAPACKET_NOTIFY_ACKNUM_IDX		(NTY_PROTO_HEARTBEAT_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_DATAPACKET_NOTIFY_DEST_DEVID_IDX	(NTY_PROTO_DATAPACKET_NOTIFY_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_DATAPACKET_NOTIFY_CONTENT_COUNT_IDX		(NTY_PROTO_DATAPACKET_NOTIFY_DEST_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_DATAPACKET_NOTIFY_CONTENT_IDX		(NTY_PROTO_DATAPACKET_NOTIFY_CONTENT_COUNT_IDX+4)


#define NTY_PROTO_DATAPACKET_ACK_DEVID_IDX		NTY_PROTO_HEARTBEAT_DEVID_IDX
#define NTY_PROTO_DATAPACKET_ACK_ACKNUM_IDX		(NTY_PROTO_HEARTBEAT_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_DATAPACKET_ACK_SRC_DEVID_IDX	(NTY_PROTO_DATAPACKET_ACK_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_DATAPACKET_ACK_CRC_IDX		(NTY_PROTO_DATAPACKET_ACK_SRC_DEVID_IDX+NTY_DEVID_LENGTH)

#define NTY_PROTO_TIMECHECK_ACKNUM_IDX			NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_TIMECHECK_YEAR_IDX			(NTY_PROTO_ACKNUM_IDX+1)
#define NTY_PROTO_TIMECHECK_MONTH_IDX			(NTY_PROTO_TIMECHECK_YEAR_IDX+1)
#define NTY_PROTO_TIMECHECK_DAY_IDX				(NTY_PROTO_TIMECHECK_MONTH_IDX+1)
#define NTY_PROTO_TIMECHECK_WDAY_IDX			(NTY_PROTO_TIMECHECK_DAY_IDX+1)
#define NTY_PROTO_TIMECHECK_HOUR_IDX			(NTY_PROTO_TIMECHECK_WDAY_IDX+1)
#define NTY_PROTO_TIMECHECK_MINUTE_IDX			(NTY_PROTO_TIMECHECK_HOUR_IDX+1)
#define NTY_PROTO_TIMECHECK_SECOND_IDX			(NTY_PROTO_TIMECHECK_MINUTE_IDX+1)
#define NTY_PROTO_TIMECHECK_CRC_IDX				(NTY_PROTO_TIMECHECK_SECOND_IDX+1)


#define NTY_PROTO_MULTICAST_TYPE_IDX			NTY_PROTO_MSGTYPE_IDX
#define NTY_PROTO_MULTICAST_SELFID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_MULTICAST_ACKNUM_IDX			NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_MULTICAST_DEVICEID_IDX		NTY_PROTO_DEST_DEVID_IDX
#define NTY_PROTO_MULTICAST_CONTENT_COUNT_IDX	(NTY_PROTO_DEST_DEVID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_MULTICAST_CONTENT_IDX			(NTY_PROTO_MULTICAST_CONTENT_COUNT_IDX+2)

#define NTY_PROTO_ICCIDREQ_TYPE_IDX				NTY_PROTO_MSGTYPE_IDX
#define NTY_PROTO_ICCIDREQ_SLFID_IDX 			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_ICCIDREQ_ACKNUM_IDX			NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_ICCIDREQ_CONTENT_COUNT_IDX	(NTY_PROTO_ICCIDREQ_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_ICCIDREQ_CONTENT_IDX			(NTY_PROTO_ICCIDREQ_CONTENT_COUNT_IDX+2)

#define NTY_PROTO_ICCIDACK_TYPE_IDX				NTY_PROTO_MSGTYPE_IDX
#define NTY_PROTO_ICCIDACK_SLFID_IDX 			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_ICCIDACK_CONTENT_COUNT_IDX	(NTY_PROTO_ICCIDACK_SLFID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_ICCIDACK_CONTENT_IDX			(NTY_PROTO_ICCIDREQ_CONTENT_COUNT_IDX+2)


#define NTY_PROTO_VOICEREQ_TYPE_IDX				NTY_PROTO_MSGTYPE_IDX
#define NTY_PROTO_VOICEREQ_SELFID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_VOICEREQ_DESTID_IDX			(NTY_PROTO_VOICEREQ_SELFID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_VOICEREQ_PKTINDEX_IDX			(NTY_PROTO_VOICEREQ_DESTID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_VOICEREQ_PKTTOTLE_IDX			(NTY_PROTO_VOICEREQ_PKTINDEX_IDX+NTY_PKTIDX_LENGTH)
#define NTY_PROTO_VOICEREQ_PKTLENGTH_IDX		(NTY_PROTO_VOICEREQ_PKTTOTLE_IDX+NTY_PKTIDX_LENGTH)

#define NTY_PROTO_VOICEACK_TYPE_IDX				NTY_PROTO_MSGTYPE_IDX
#define NTY_PROTO_VOICEACK_SELFID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_VOICEACK_ACKNUM_IDX			NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_VOICEACK_DESTID_IDX			NTY_PROTO_DEST_DEVID_IDX
#define NTY_PROTO_VOICEACK_CRC_IDX				NTY_PROTO_CRC_IDX

#define NTY_PROTO_EFENCE_TYPE_IDX				NTY_PROTO_MSGTYPE_IDX
#define NTY_PROTO_EFENCE_SLEFID_IDX				NTY_PROTO_DEVID_IDX
#define NTY_PROTO_EFENCE_ACKNUM_IDX				NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_EFENCE_DESTID_IDX				NTY_PROTO_DEST_DEVID_IDX
#define NTY_PROTO_EFENCE_CONTENT_COUNT_IDX		(NTY_PROTO_EFENCE_DESTID_IDX+NTY_DEVID_LENGTH)
#define NTY_PROTO_EFENCE_CONTENT_IDX			(NTY_PROTO_EFENCE_CONTENT_COUNT_IDX+2)

#define NTY_PROTO_EFENCE_ACK_DEVID_IDX			NTY_PROTO_DEVID_IDX
#define NTY_PROTO_EFENCE_ACK_ACKNUM_IDX			NTY_PROTO_ACKNUM_IDX
#define NTY_PROTO_EFENCE_ACK_SRC_DEVID_IDX		(NTY_PROTO_EFENCE_ACK_ACKNUM_IDX+NTY_ACKNUM_LENGTH)
#define NTY_PROTO_EFENCE_ACK_CRC_IDX			(NTY_PROTO_EFENCE_ACK_SRC_DEVID_IDX+NTY_DEVID_LENGTH)


//#define NTY_PROTO_P2P_HEARTBEAT_DEST_DEVID_IDX					

/* ** **** ********  ****************  Header  ****************  ******** **** ** */
#define NTY_PROTO_LOGIN_REQ					0x01
#define NTY_PROTO_LOGIN_ACK					0x81

#define NTY_PROTO_HEARTBEAT_REQ				0x02 //'H'
#define NTY_PROTO_HEARTBEAT_ACK				0x82

#define NTY_PROTO_LOGOUT_REQ				0x03
#define NTY_PROTO_LOGOUT_ACK				0x83

#define NTY_PROTO_TIME_CHECK_REQ			0x04
#define NTY_PROTO_TIME_CHECK_ACK			0x84

#define NTY_PROTO_ICCID_REQ					0x05
#define NTY_PROTO_ICCID_ACK					0x85

#define NTY_PROTO_VOICE_REQ					0x06
#define NTY_PROTO_VOICE_ACK					0x86

#define NTY_PROTO_COMMON_REQ				0x07
#define NTY_PROTO_COMMON_ACK				0x87

#define NTY_PROTO_VOICE_DATA_REQ			0x08
#define NTY_PROTO_VOICE_DATA_ACK			0x88

#define NTY_PROTO_OFFLINE_MSG_REQ			0x09
#define NTY_PROTO_OFFLINE_MSG_ACK			0x89

#define NTY_PROTO_UNBIND_REQ				0x0A
#define NTY_PROTO_UNBIND_ACK				0x8A

#define NTY_PROTO_BIND_REQ					0x0B
#define NTY_PROTO_BIND_ACK					0x8B


#define NTY_PROTO_MULTICAST_REQ				0x0C
#define NTY_PROTO_MULTICAST_ACK				0x8C


#define NTY_PROTO_LOCATION_ASYNCREQ			0x11
#define NTY_PROTO_LOCATION_PUSH				0x91

#define NTY_PROTO_WEATHER_ASYNCREQ			0x12
#define NTY_PROTO_WEATHER_PUSH				0x92


#define NTY_PROTO_DATA_ROUTE				0x21
#define NTY_PROTO_DATA_RESULT				0xA1

#define NTY_PROTO_DATAPACKET_REQ			0x22 
#define NTY_PROTO_DATAPACKET_ACK			0xA2 

#define NTY_PROTO_VOICE_BROADCAST			0x31
#define NTY_PROTO_LOCATION_BROADCAST		0x33
#define NTY_PROTO_COMMON_BROADCAST			0x34

#define NTY_PROTO_BIND_CONFIRM_REQ			0x35
#define NTY_PROTO_BIND_CONFIRM_PUSH			0xB5

#define NTY_PROTO_VOICE_UPLOAD				0x41 //rsvd
#define NTY_PROTO_VOICE_DOWNLOAD			0x42 //rsvd

/* ** rsvd start ** */

#define NTY_PROTO_DATAPACKET_NOTIFY_REQ		0x22 //use for client ,
#define NTY_PROTO_DATAPACKET_NOTIFY_ACK		0xA2 //use for client ,

#define NTY_PROTO_P2PDATAPACKET_REQ			0x23 //use for client ,
#define NTY_PROTO_P2PDATAPACKET_ACK			0xA3 //use for client ,

#define NTY_PROTO_P2P_HEARTBEAT_REQ			0x24
#define NTY_PROTO_P2P_HEARTBEAT_ACK			0xA4

#define NTY_PROTO_ROUTERDATA_REQ			0x25


#define NTY_PROTO_EFENCE_DATA_REQ			0x27
#define NTY_PROTO_EFENCE_DATA_ACK			0x28

#define NTY_PROTO_EFENCE_REQ				0x51
#define NTY_PROTO_EFENCE_ACK				0xD1

/* ** rsvd end ** */


//#define NTY_PROTO_P2P_DATAPACKET_REQ		0x24
//#define NTY_PROTO_P2P_DATAPACKET_ACK		0xA4

//#define NTY_PROTO_FRIENDSLIST_ADDR_INFO				0x24
//#define NTY_PROTO_FRIENDSLIST_ADDR_ACK				0xA4


/* ** **** ********  ****************  Timer  ****************  ******** **** ** */

#define NTY_TIMER_LOGIN_CLIENT 				0x01
#define NTY_TIMER_HEARTBEAT_CLIENT			0x02
#define NTY_TIMER_HEARTBEAT_SERVER			0x03
#define NTY_TIMER_LOGOUT_CLIENT				0x04
#define NTY_TIMER_PROXY_USERDATA_CLIENT		0x05
#define NTY_TIMER_P2P_USERDATA_CLIENT		0x06


enum {
	PROTO_ROUTE = 0x01,
	PROTO_BROADCAST = 0x02,
	PROTO_REQ = 0x03,
	PROTO_ACK = 0x04,
	PROTO_UPLOAD = 0x05,
	PROTO_DOWNLOAD = 0x06,
	PROTO_MULTICAST = 0x07,
	PROTO_ASYNCREQ = 0x08,
	PROTO_PUSH = 0x09,
	
	MSG_REQ = 0x01,
	MSG_ACK = 0x02,
	MSG_RET	= 0x03, //proxy server to return
	MSG_UPDATE = 0x04, //Update Message
};

#endif





