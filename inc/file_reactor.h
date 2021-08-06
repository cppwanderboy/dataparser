#ifndef _FILEBASE_INCLUDE_H_
#define _FILEBASE_INCLUDE_H_

#include<unistd.h>
#include<string.h>

#include"data_format.h"
#include"encoder.h"

namespace parser{
    using namespace parser::szNET;

    class OrderFileReactor{
    public:
        inline void operator()(int fd, OrderByDeal<OrderGoodsConcentratedBiddingType>* value){
            char mem[100];
            OrderByDealEncoder encoder_{};
            int length = encoder_.encode(value, mem);
            write(fd, mem, length);
        }
    };

    class DealFileReactor{
    public:
        inline void operator()(int fd, DealByDeal<DealGoodsConcentratedBiddingType>* value){
            char mem[100];
            DealByDealEncoder encoder_{};
            int length = encoder_.encode(value, mem);
            write(fd, mem, length);
        }
    };
}

#endif /**_FILEBASE_INCLUDE_H_ */