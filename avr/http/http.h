//Copyright 2012 Charles Lohr under the MIT/x11, newBSD, LGPL or GPL licenses.  You choose.

#ifndef _HTTP_H
#define _HTTP_H

#include <stdint.h>
#include "eth_config.h"

#ifdef INCLUDE_HTTP_SERVER

#ifndef INCLUDE_TCP
#error INCLUDE_HTTP_SERVER set without TCP support.
#endif

/*
#if (HTTP_CONNECTIONS) < (TCP_SOCKETS-1)
#error Not enough TCP connections for requested HTTP connections.
#endif
*/
#define MAX_PATHLEN 38

//You must call:
void HTTPInit( uint8_t id );
void HTTPGotData( uint8_t id, uint16_t len );
void HTTPClose( uint8_t id );
void HTTPTick();


//You must provide:
void HTTPCustomStart( uint8_t id );
void HTTPCustomCallback( uint8_t id );  //called when we can send more data

#define TCP_STATE_NONE        0
#define TCP_STATE_WAIT_METHOD 1
#define TCP_STATE_WAIT_PATH   2
#define TCP_STATE_WAIT_PROTO  3

#define TCP_STATE_WAIT_FLAG   4
#define TCP_STATE_WAIT_INFLAG 5
#define TCP_STATE_DATA_XFER 7

#define TCP_WAIT_CLOSE        15

struct HTTPConnection
{
	uint8_t  state:4;
	uint8_t  state_deets;
	uint8_t  pathbuffer[MAX_PATHLEN];
	uint8_t  is_dynamic:1;
	uint16_t timeout;

	int32_t clusterno;
	uint32_t bytesleft;
	uint32_t bytessofar;

	uint8_t  is404:1;
	uint8_t  isdone:1;
	uint8_t  isfirst:1;
} HTTPConnections[HTTP_CONNECTIONS];

#endif

#endif

