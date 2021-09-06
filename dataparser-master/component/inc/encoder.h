#ifndef _ENCODER_INCLUDE_H_
#define _ENCODER_INCLUDE_H_

#include<stdint.h>
#include<string.h>
#include <arpa/inet.h>

#include<utility>

#include"data_format.h"

namespace parser{
    using namespace parser::szNET;

    class EncoderBase{
    public:
        EncoderBase()=default;
        ~EncoderBase(){}

        // encode operation =========================================================================
        // Encode int variables into ASCNII characters
        inline char* int2Code(char* mem, int integer);
        // Encode int64 variables into ASCNII characters
        inline char* int64_2_Code(char* mem, uint64_t integer);

        inline int getBitCount()const;
    protected:
        char nums[20];
        int bitCount;
        const char comma = ',';
        const char CLRF = '\n';
    };

    class OrderByDealEncoder:public EncoderBase{
    public:
        OrderByDealEncoder()=default;
        ~OrderByDealEncoder(){}

        // encode OrderBydeal data into ASCNII charactor code
        inline int encode(OrderByDeal<OrderGoodsConcentratedBiddingType>* value, char* mem);
    private:
        // '1'->'0' '2'->'1' 'U'->'2'
        const char type_lookup_table[38] = {
            ' ', '0', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '2'
        };
    };

    class DealByDealEncoder:public EncoderBase{
    public:
        DealByDealEncoder()=default;
        ~DealByDealEncoder(){}

        // encode OrderBydeal data into ASCNII charactor code
        inline int encode(DealByDeal<DealGoodsConcentratedBiddingType>* value, char* mem);
    private:
        const char type_lookup_table[24] = {
            ' ', ' ', ' ', ' ', '0', ' ', 
            ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', 'C', ' '
        };
    };

/* ---------------------------------------------------------------------------------------------------------------
   -------------------------------------------  code -------------------------------------------------------------
   ---------------------------------------------------------------------------------------------------------------
*/
    typedef struct {
	    uint32_t u32_h;
	    uint32_t u32_l;
    }Int64_t;
 
    typedef union {
	    uint64_t u64;
	    Int64_t st64;
    }Convert64_t;

    inline uint64_t ntohLL(uint64_t numn){
        Convert64_t numh_;
        Convert64_t numn_;
        numn_.u64 = numn;
        numh_.st64.u32_h = ntohl(numn_.st64.u32_l);
        numh_.st64.u32_l = ntohl(numn_.st64.u32_h);
        return static_cast<uint64_t>(numh_.u64);
    }
    
    inline char* EncoderBase::int2Code(char* mem, int integer){
        this->bitCount = 0;
        if(integer == 0){
            *mem = '0';
            this->bitCount = 1;
            mem++;
            return mem;
        }
        while(integer){
            this->nums[bitCount++] = (integer % 10) + '0';
            integer /= 10;
        }
        for(int i = bitCount - 1; i >= 0; i--){
            *mem = this->nums[i];
            mem++;
        }
        return mem;
    }

    inline char* EncoderBase::int64_2_Code(char* mem, uint64_t integer){
        this->bitCount = 0;
        if(integer == 0){
            *mem = '0';
            mem++;
            this->bitCount = 1;
            return mem;
        }
        while(integer){
            this->nums[bitCount++] = (integer % 10) + '0';
            integer /= 10;
        }
        for(int i = bitCount - 1; i >= 0; i--){
            *mem = this->nums[i];
            mem++;
        }
        return mem;
    }

    inline int EncoderBase::getBitCount()const {
        return this->bitCount;
    }

    int OrderByDealEncoder::encode(OrderByDeal<OrderGoodsConcentratedBiddingType>* value, char* mem_){
        char* mem = mem_;
        int length = 0;
        uint64_t trdtime = ntohLL(value->head.transTime);
        //date
        uint64_t date = trdtime / 1000000000;
        mem = int64_2_Code(mem, date);
        *mem++ = '\t';
        length = length + this->getBitCount() + 1;

        //code
        mem[0] = value->head.securityID[0];
        mem[1] = value->head.securityID[1];
        mem[2] = value->head.securityID[2];
        mem[3] = value->head.securityID[3];
        mem[4] = value->head.securityID[4];
        mem[5] = value->head.securityID[5];
        mem = mem + 6;
        *mem++ = '\t';
        length = length + 6 + 1;

        //trdTime
        trdtime = trdtime % 1000000000;
        trdtime = trdtime * 1000000;
        mem = int64_2_Code(mem, trdtime);
        *mem++ = '\t';
        length = length + this->getBitCount() + 1;

        //recvTime
        mem = int64_2_Code(mem, 0);
        *mem++ = '\t';
        length = length + this->getBitCount() + 1;
        
        //ordPrc
        uint64_t ordprc = ntohLL(value->head.price);
        mem = int64_2_Code(mem, ordprc);
        *mem++ = '\t';
        length = length + this->getBitCount() + 1; 

        //ordQty
        uint64_t ordqty = ntohLL(value->head.orderQty) / 100;
        mem = int64_2_Code(mem, ordqty);
        *mem++ = '\t';
        length = length + this->getBitCount() + 1;

        //bsflag
        int side = value->head.side - '0';
        switch(side){
        case 1:{
            *mem++ = '1';
            *mem++ = '\t';
            length = length + 2;
            break;
        }
        case 2:{
            *mem++ = '-';
            *mem++ = '1';
            *mem++ = '\t';
            length = length + 3;
            break;
        }
        default:{
            *mem++ = '0';
            *mem++ = '\t';
            length = length + 2;
            break;
        }
        }

        //type
        *mem++ = this->type_lookup_table[value->extendFiels.orderType - '0'];
        *mem++ = '\t';
        length = length + 2;

        //idOrd
        uint64_t idord = ntohLL(value->head.applSeqNum);
        mem = int64_2_Code(mem, idord);
        *mem++ = '\n';
        length = length + this->getBitCount() + 1;

        return length;
    }


    int DealByDealEncoder::encode(DealByDeal<DealGoodsConcentratedBiddingType>* data, char* mem_){
        char* mem = mem_;
        int length = this->bitCount;
        // code
        mem[0] = data->head.securityID[0];
        mem[1] = data->head.securityID[1];
        mem[2] = data->head.securityID[2];
        mem[3] = data->head.securityID[3];
        mem[4] = data->head.securityID[4];
        mem[5] = data->head.securityID[5];
        mem[6] = '\t';
        mem = mem + 7;
        length = length + 7;
        
        // date
        uint64_t totaltime = ntohLL(data->head.transactime);
        uint64_t datetime = totaltime / 1000000000;
        mem = int64_2_Code(mem, datetime);
        *mem++ = '\t';
        length = length + 1 + this->bitCount;

        // time
        uint64_t trdtime = totaltime % 1000000000;
        trdtime = trdtime * 1000000;
        mem = int64_2_Code(mem, trdtime);
        *mem++ = '\t';
        length = length + this->bitCount + 1;

        // localtime
        mem = int64_2_Code(mem, 0);
        *mem++ = '\t';
        length = length + this->bitCount + 1;

        // transid
        uint64_t transid = ntohLL(data->head.applSeqNum);
        mem = int64_2_Code(mem, transid);
        *mem++ = '\t';
        length = length + this->bitCount + 1;

        //type
        *mem++ = this->type_lookup_table[data->head.execType - '0'];
        *mem++ = '\t';
        length = length + 2;

        //direction
        uint64_t askid = ntohLL(data->head.offerApplSeqNum);
        uint64_t bidid = ntohLL(data->head.bidApplSeqNum);
        if(data->head.execType == 'F'){
            if(askid > bidid){
                *mem++ = 'S';
            }
            else {
                *mem++ = 'B';
            }
            length = length + 1;
        }
        *mem++ = '\t';
        length = length + 1;

        //price
        uint64_t trdprc = ntohLL(data->head.lastPX);
        mem = int64_2_Code(mem, trdprc);
        *mem++ = '\t';
        length = length + this->bitCount + 1;

        //vol
        uint64_t trdqty = ntohLL(data->head.lastQty);
        mem = int64_2_Code(mem, trdqty);
        *mem++  = '\t';
        length = length + this->bitCount + 1;

        //askid
        mem = int64_2_Code(mem, askid);
        *mem++ = '\t';
        length = length + this->bitCount + 1;

        //bidid
        mem = int64_2_Code(mem, bidid);
        *mem = '\n';
        length = length + this->bitCount + 1;
        return length;
    }

}

#endif /**_ENCODER_INCLUDE_H_*/