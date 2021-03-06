#ifndef _LIBGSMD_SMS_H
#define _LIBGSMD_SMS_H

#include <libgsmd/libgsmd.h>

/* Short Message Service */

/* Coding of Alpha fields in the SIM for UCS2, (3GPP TS 11.11 Annex B) */
//enum {

//};


/* SMS delflg from 3GPP TS 07.05, Clause 3.5.4 */
enum lgsm_msg_sms_delflg {
	LGSM_SMS_DELFLG_INDEX		= 0,
	LGSM_SMS_DELFLG_READ		= 1,
	LGSM_SMS_DELFLG_READ_SENT	= 2,
	LGSM_SMS_DELFLG_LEAVING_UNREAD	= 3,
	LGSM_SMS_DELFLG_ALL		= 4,
};

/* SMS stat from 3GPP TS 07.05, Clause 3.1 */
/* FIXME: only support PDU mode */
enum lgsm_msg_sms_stat {
	LGSM_SMS_REC_UNREAD		= 0,
	LGSM_SMS_REC_READ		= 1,
	LGSM_SMS_STO_UNSENT		= 2,
	LGSM_SMS_STO_SENT		= 3,
	LGSM_SMS_ALL			= 4,
};

/* Refer to GSM 07.05 subclause 3.5.4 */
struct lgsm_sms_delete {
	int index;
	enum lgsm_msg_sms_delflg delflg;
};

/* Refer to GSM 03.40 subclause 9.2.2.2 */
#define LGSM_SMS_DATA_MAXLEN	140
struct lgsm_sms {
	char addr[LGSM_ADDR_MAXLEN+1];
	/* FIXME: max length of data,
	 * 7 bit coding - 160(140*8/7); ucs2 coding - 70(140/2) */
	struct gsmd_sms_datacodingscheme dcs;
	u_int8_t data[LGSM_SMS_DATA_MAXLEN+1];
	u_int8_t physical_byte_length;
	u_int8_t size_encoded_userdata;
	int ask_ds;
};

/* GSM 03.40 subclause 9.2.2.2 and GSM 07.05 subclause 4.4 and subclause 3.1 */
struct lgsm_sms_write {
	enum lgsm_msg_sms_stat stat;
	struct lgsm_sms sms;
};

/* List Messages */
extern int lgsm_sms_list(struct lgsm_handle *lh, enum gsmd_msg_sms_type stat);

/* Read Message */
extern int lgsm_sms_read(struct lgsm_handle *lh, int index);

/* Delete Message */
extern int lgsm_sms_delete(struct lgsm_handle *lh,
		const struct lgsm_sms_delete *sms_del);

/* Send Message */
extern int lgsm_sms_send(
	struct lgsm_handle *lh, const struct lgsm_sms *sms, int pdu_user_header);

/* Write Message to Memory */
extern int lgsm_sms_write(struct lgsm_handle *lh,
		const struct lgsm_sms_write *sms_write, int pdu_user_header);

/* Send SMS Ack */
extern int lgsm_ack_sms(struct lgsm_handle *lh, int ack); // JIM

/* Retrieve SMS storage information */
extern int lgsm_sms_get_storage(struct lgsm_handle *lh);

/* Set preferred SMS storage */
extern int lgsm_sms_set_storage(struct lgsm_handle *lh,
		enum ts0705_mem_type mem1, enum ts0705_mem_type mem2,
		enum ts0705_mem_type mem3);

/* Retrieve current default service centre address */
extern int lgsm_sms_get_smsc(struct lgsm_handle *lh);

/* Set new default service centre address */
extern int lgsm_sms_set_smsc(struct lgsm_handle *lh, const char *number);

/* Cancel specified sms request */
extern int lgsm_sms_cancel(struct lgsm_handle *lh, int subtype);

extern int lgsm_convert_ucs2_to_utf8(
	const unsigned short* ucs2_src, const int len, unsigned char* dest);
extern int lgsm_convert_utf8_to_ucs2(
	const unsigned char* src, const int len, unsigned short* dest);

extern int lgsm_convert_gsm338_to_utf8(
	const unsigned char* src, const int len, unsigned char* dest);
extern int lgsm_convert_utf8_to_gsm338(
	const unsigned char* src, const int len, unsigned char* dest);

/* Packing of 7-bit characters, refer to GSM 03.38 subclause 6.1.2.1.1 */
extern int packing_7bit_character(
	const char *src, u_int8_t length, struct lgsm_sms *dest, u_int8_t header);

/* Packing of 7-bit characters, refer to GSM 03.38 subclause 6.1.2.1.1 */
extern int unpacking_7bit_character(const struct gsmd_sms *src, unsigned char *dest);
extern int cbm_unpacking_7bit_character(const char *src, unsigned char *dest);

/* Refer to 3GPP TS 11.11 Annex B */
extern int packing_UCS2_80(char *src, char *dest);

/* Refer to 3GPP TS 11.11 Annex B */
extern int unpacking_UCS2_80(char *src, char *dest);

/* Refer to 3GPP TS 11.11 Annex B */
extern int packing_UCS2_81(char *src, char *dest);

/* Refer to 3GPP TS 11.11 Annex B */
extern int unpacking_UCS2_81(char *src, char *dest);

/* Refer to 3GPP TS 11.11 Annex B */
extern int packing_UCS2_82(char *src, char *dest);

/* Refer to 3GPP TS 11.11 Annex B */
extern int unpacking_UCS2_82(char *src, char *dest);

/* This phone wants to receive Cell Broadcast Messages */
extern int lgsm_cb_subscribe(struct lgsm_handle *lh);

/* This phone wants no more Cell Broadcast Messages */
extern int lgsm_cb_unsubscribe(struct lgsm_handle *lh);

/* Cancel specified Cell Broadcast request */
extern int lgsm_cb_cancel(struct lgsm_handle *lh, int subtype);

#endif
