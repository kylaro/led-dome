//
// Created by kylaro on 1/23/2021.
//

#ifndef LEDCONTROL_E131_PACKET_H
#define LEDCONTROL_E131_PACKET_H

#include <cstdint>

#define LEDS_PER_UNIVERSE 170

typedef union {
    struct {
        struct { /* ACN Root Layer: 38 bytes */
            uint16_t preamble_size;    /* Preamble Size */
            uint16_t postamble_size;   /* Post-amble Size */
            uint8_t  acn_pid[12];      /* ACN Packet Identifier */
            uint16_t flength;          /* Flags (high 4 bits) & Length (low 12 bits) */
            uint32_t vector;           /* Layer Vector */
            uint8_t  cid[16];          /* Component Identifier (UUID) */
        } __attribute__((packed)) root;

        struct { /* Framing Layer: 77 bytes */
            uint16_t flength;          /* Flags (high 4 bits) & Length (low 12 bits) */
            uint32_t vector;           /* Layer Vector */
            uint8_t  source_name[64];  /* User Assigned Name of Source (UTF-8) */
            uint8_t  priority;         /* Packet Priority (0-200, default 100) */
            uint16_t reserved;         /* Reserved (should be always 0) */
            uint8_t  seq_number;       /* Sequence Number (detect duplicates or out of order packets) */
            uint8_t  options;          /* Options Flags (bit 7: preview data, bit 6: stream terminated) */
            uint16_t universe;         /* DMX Universe Number */
        } __attribute__((packed)) frame;

        struct { /* Device Management Protocol (DMP) Layer: 523 bytes */
            uint16_t flength;          /* Flags (high 4 bits) / Length (low 12 bits) */
            uint8_t  vector;           /* Layer Vector */
            uint8_t  type;             /* Address Type & Data Type */
            uint16_t first_addr;       /* First Property Address */
            uint16_t addr_inc;         /* Address Increment */
            uint16_t prop_val_cnt;     /* Property Value Count (1 + number of slots) */
            uint8_t  prop_val[513];    /* Property Values (DMX start code + slots data) */
            //NOTES ABOUT PROP_VAL
            //PROP_VAL[0] MUST BE 0
            //PROP_VAL[1] IS FIRST RED, PROP_VAL[2] IS FIRST GREEN, PROP_VAL[3] IS FIRST BLUE
            //PROP_VAL[508] IS LAST RED, PROP_VAL[509] IS LAST GREEN, PROP_VAL[510] IS LAST BLUE
            //this means there should be 170 leds per universe
        } __attribute__((packed)) dmp;
    } __attribute__((packed));

    char raw[638]; /* raw buffer view: 638 bytes */
} e131_packet_t;

extern e131_packet_t packet;

void incSeq();
void initPacket();
void setUniverse(uint16_t universe);

#endif //LEDCONTROL_E131_PACKET_H

