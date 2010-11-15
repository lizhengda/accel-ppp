#ifndef __LOG_H
#define __LOG_H

#include <stdarg.h>
#include <sys/time.h>
#include "list.h"

#define LOG_MSG   0
#define LOG_ERROR 1
#define LOG_WARN  2
#define LOG_INFO  3
#define LOG_DEBUG 4

#define LOG_CHUNK_SIZE 128
#define LOG_MAX_SIZE 4096

struct ppp_t;
struct triton_context_t;

struct log_msg_t
{
	struct list_head entry;
	void *lpd;
	void *tpd;
	struct timeval timestamp;
	int level;
	struct log_chunk_t *hdr;
	struct list_head *chunks;		
};

struct log_chunk_t
{
	struct list_head entry;
	int len;
	char msg[0];
};

struct log_target_t
{
	struct list_head entry;

	void (*log)(struct log_target_t *, struct log_msg_t *, struct ppp_t *ppp);
	void (*reopen)(void);
};

void log_free_msg(struct log_msg_t *msg);

void log_emerg(const char *fmt, ...);

void log_error(const char *fmt,...);
void log_warn(const char *fmt,...);
void log_info(const char *fmt,...);
void log_debug(const char *fmt,...);
void log_msg(const char *fmt,...);

void log_ppp_error(const char *fmt,...);
void log_ppp_warn(const char *fmt,...);
void log_ppp_info(const char *fmt,...);
void log_ppp_debug(const char *fmt,...);
void log_ppp_msg(const char *fmt,...);

void log_switch(struct triton_context_t *ctx, void *arg);

void log_register_target(struct log_target_t *t);

#endif
