//
// Created by kylaro on 1/23/2021.
//
#include "e131_packet.h"

uint8_t seq_i = 0;
e131_packet_t packet;
e131_packet_t packets[97];//NUM UNIVERSES

uint16_t formatUniverse(uint16_t universe) {
    uint8_t high = universe >> 8;
    uint8_t low = universe;
    universe = (low << 8) | (high);

    return universe;
}

void initPackets() {
    for (uint16_t univ = 0; univ < 97; univ++) {
        uint8_t acn_pid[12] = "ASC-E1.17\0\0";
        uint8_t cid[16] = { 0x43,0x68,0x61,0x6d,0x53,0x79,0x40,0x00,0x80,0x00,0xac,0x11,0x1e,0x28,0x0,0x0 };
        uint8_t sourcename[64] = "PoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoo";

        
        //ROOOT
        packets[univ].root.preamble_size = 0x1000;
        packets[univ].root.postamble_size = 0x0000;
        for (int i = 0; i < 12; i++) {
            packets[univ].root.acn_pid[i] = acn_pid[i];
        }
        packets[univ].root.flength = 0x6e72;
        packets[univ].root.vector = 0x04000000;
        for (int i = 0; i < 16; i++) {
            packets[univ].root.cid[i] = cid[i];
        }

        //FRAMING
        packets[univ].frame.flength = 0x5872;
        packets[univ].frame.vector = 0x02;
        for (int i = 0; i < 64; i++) {
            packets[univ].frame.source_name[i] = sourcename[i];
        }
        packets[univ].frame.priority = 0x64;
        packets[univ].frame.reserved = 0;
        packets[univ].frame.seq_number = seq_i; // TODO +1 each packet sent
        packets[univ].frame.options = 0;
        packets[univ].frame.universe = formatUniverse(univ);

        //DMP
        packets[univ].dmp.flength = 0x0b72;
        packets[univ].dmp.vector = 0x02;
        packets[univ].dmp.type = 0xa1;
        packets[univ].dmp.first_addr = 0x00;
        packets[univ].dmp.addr_inc = 0x0100;
        packets[univ].dmp.prop_val_cnt = 0xFFFF;

        //these are all the channels
        for (int i = 0; i < 512; i++) {
            packets[univ].dmp.prop_val[i] = 0x00;
        }
        packets[univ].dmp.prop_val[0] = 0; // THIS ONE SHOULD ALWAYS BE 0 OR ELSE IT DONT WORK
    }
}

//Initializes the packet to the right numbers
// nobody knows what it means, but it's provocative
void initPacket() {
    uint8_t acn_pid[12] = "ASC-E1.17\0\0";
    uint8_t cid[16] = { 0x43,0x68,0x61,0x6d,0x53,0x79,0x40,0x00,0x80,0x00,0xac,0x11,0x1e,0x28,0x0,0x0 };
    uint8_t sourcename[64] = "PoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoopPoo";

    //ROOOT
    packet.root.preamble_size = 0x1000;
    packet.root.postamble_size = 0x0000;
    for (int i = 0; i < 12; i++) {
        packet.root.acn_pid[i] = acn_pid[i];
    }
    packet.root.flength = 0x6e72;
    packet.root.vector = 0x04000000;
    for (int i = 0; i < 16; i++) {
        packet.root.cid[i] = cid[i];
    }

    //FRAMING
    packet.frame.flength = 0x5872;
    packet.frame.vector = 0x02;
    for (int i = 0; i < 64; i++) {
        packet.frame.source_name[i] = sourcename[i];
    }
    packet.frame.priority = 0x64;
    packet.frame.reserved = 0;
    packet.frame.seq_number = seq_i; // TODO +1 each packet sent
    packet.frame.options = 0;
    packet.frame.universe = 0x0100;

    //DMP
    packet.dmp.flength = 0x0b72;
    packet.dmp.vector = 0x02;
    packet.dmp.type = 0xa1;
    packet.dmp.first_addr = 0x00;
    packet.dmp.addr_inc = 0x0100;
    packet.dmp.prop_val_cnt = 0xFFFF;

    //these are all the channels
    for (int i = 0; i < 512; i++) {
        packet.dmp.prop_val[i] = 0x00;
    }
    packet.dmp.prop_val[0] = 0; // THIS ONE SHOULD ALWAYS BE 0 OR ELSE IT DONT WORK

}



void setUniverse(uint16_t universe) {
    //Lol need to flip the high and low byte tho
    uint8_t high = universe >> 8;
    uint8_t low = universe;
    universe = (low << 8) | (high);

    packet.frame.universe = universe;
}

void setSeq(uint16_t universe, uint8_t seq) {
    packets[universe].frame.seq_number = seq;
}

void incSeq() {
    packet.frame.seq_number++;
}